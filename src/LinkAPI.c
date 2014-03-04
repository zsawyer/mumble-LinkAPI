/* Copyright (C) 2013, zsawyer <zsawyer@users.sourceforge.net>

   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

   - Redistributions of source code must retain the above copyright notice,
	 this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright notice,
	 this list of conditions and the following disclaimer in the documentation
	 and/or other materials provided with the distribution.
   - Neither the name of the Mumble Developers nor the names of its
	 contributors may be used to endorse or promote products derived from this
	 software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *
 * @author zsawyer, 2013-03-20
 */

#include "LinkAPI.h"

#include <stdio.h> /* snprintf */
#include <string.h> /* memcpy */

#ifndef WIN32
#    include <unistd.h> /* getuid */
#    include <sys/stat.h> /* S_IRUSR, S_IWUSR */
#    include <fcntl.h> /* O_RDWR */

#    include <sys/mman.h>
#    include <stdlib.h> /* shm_open, PROT_READ, PROT_WRITE, MAP_SHARED mmap */
#endif

static LINKAPI_LINKED_MEMORY *lm = NULL;

#define LINKAPI_VERIFY_LM			if (!lm) { return LINKAPI_ERROR_CODE_NO_MEMORY_WAS_INITIALIZED; }
#define LINKAPI_VERIFY_NO_ERROR 	if (err != LINKAPI_ERROR_CODE_NO_ERROR) { return err; }

LINKAPI_ERROR_CODE nativeInitialize() {
#ifdef WIN32
	HANDLE hMapObject = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, L"MumbleLink");
	if (hMapObject == NULL) {
		return LINKAPI_ERROR_CODE_NO_HANDLE;
	}

	lm = (LINKAPI_LINKED_MEMORY *) MapViewOfFile(hMapObject, FILE_MAP_ALL_ACCESS, 0, 0, sizeof (LINKAPI_LINKED_MEMORY));
	if (lm == NULL) {
		CloseHandle(hMapObject);
		hMapObject = NULL;
		return LINKAPI_ERROR_CODE_NO_STRUCTURE;
	}
#else
	int shmfd;
	char memname[256];
	snprintf(memname, 256, "/MumbleLink.%d", getuid());

	shmfd = shm_open(memname, O_RDWR, S_IRUSR | S_IWUSR);

	if (shmfd < 0) {
		return LINKAPI_ERROR_CODE_NO_HANDLE;
	}

	lm = (LINKAPI_LINKED_MEMORY *) (mmap(NULL, sizeof (struct LINKAPI_LINKED_MEMORY), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0));

	if (lm == (void *) (-1)) {
		lm = NULL;
		return LINKAPI_ERROR_CODE_NO_STRUCTURE;
	}
#endif

	return LINKAPI_ERROR_CODE_NO_ERROR;
}

static wchar_t backupName[LINKAPI_MAX_NAME_LENGTH];
static wchar_t backupDescription[LINKAPI_MAX_DESCRIPTION_LENGTH];
static LINKAPI_NATIVE_UINT32 backupUiVersion;

LINKAPI_ERROR_CODE initialize(
		const wchar_t name[LINKAPI_MAX_NAME_LENGTH],
		const wchar_t description[LINKAPI_MAX_DESCRIPTION_LENGTH],
		LINKAPI_NATIVE_UINT32 version) {
	LINKAPI_ERROR_CODE err;

	err = nativeInitialize();
	LINKAPI_VERIFY_NO_ERROR;

	LINKAPI_VERIFY_LM;
	if (lm->version != version) {
		err = setName(name);
		LINKAPI_VERIFY_NO_ERROR;
		err = setDescription(description);
		LINKAPI_VERIFY_NO_ERROR;
		err = setVersion(version);
		LINKAPI_VERIFY_NO_ERROR;
	}
	err = setTick(0);

	return err;
}

/**
 * identifies that the link plugin was unlocked and tells it to lock again
 *   this can happen when updates were too infrequent - then the plugin unlinks
 *
 * this will effectively relink the plugin
 *
 * @return	an error code, see <code>enum ErrorCode</code>, LINKAPI_ERROR_CODE_NO_ERROR
 *			on success
 */
LINKAPI_ERROR_CODE relock() {
	LINKAPI_VERIFY_LM;
	if (lm->version != backupUiVersion) {
		wcsncpy(lm->name, backupName, LINKAPI_MAX_NAME_LENGTH);
		wcsncpy(lm->description, backupDescription, LINKAPI_MAX_DESCRIPTION_LENGTH);

		lm->version = backupUiVersion;
	}

	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE unlinkMumble() {
	LINKAPI_VERIFY_LM;
	lm->version = LINKAPI_VERSION_UNLINK;
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

/**
 * commits if the passed error code indicates no severity
 *
 * @param previousCode	a code which a previous function might have returned
 *				that was not yet evaluated
 * @return	the error code of the commit result or the previous error code if 
 *			it was considered severe
 */
LINKAPI_ERROR_CODE commitOnNoError(LINKAPI_ERROR_CODE previousCode) {
	if (previousCode != LINKAPI_ERROR_CODE_NO_ERROR) {
		return previousCode;
	}
	return commit();
}

LINKAPI_ERROR_CODE commit() {
	lm->tick++;
	return relock();
}

LINKAPI_ERROR_CODE setWCharTArray(
		wchar_t* destination,
		const wchar_t* source,
		int count) {
	LINKAPI_VERIFY_LM;
	wcsncpy(destination, source, count);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE setAndBackupWCharTArray(
		wchar_t* destination,
		const wchar_t* source,
		wchar_t* backupDestination,
		int count) {
	LINKAPI_ERROR_CODE err = setWCharTArray(destination, source, count);
	LINKAPI_VERIFY_NO_ERROR;
	wcsncpy(backupDestination, source, count);
	return err;
}

LINKAPI_ERROR_CODE getName(wchar_t destination[LINKAPI_MAX_NAME_LENGTH]) {
	return setWCharTArray(destination, lm->name, LINKAPI_MAX_NAME_LENGTH);
}

LINKAPI_ERROR_CODE setName(const wchar_t name[LINKAPI_MAX_NAME_LENGTH]) {
	return setAndBackupWCharTArray(lm->name, name, backupName, LINKAPI_MAX_NAME_LENGTH);
}

LINKAPI_ERROR_CODE commitName(const wchar_t name[LINKAPI_MAX_NAME_LENGTH]) {
	return commitOnNoError(setName(name));
}

LINKAPI_ERROR_CODE getDescription(wchar_t destination[LINKAPI_MAX_DESCRIPTION_LENGTH]) {
	return setWCharTArray(destination, lm->description, LINKAPI_MAX_DESCRIPTION_LENGTH);
}

LINKAPI_ERROR_CODE setDescription(
		const wchar_t description[LINKAPI_MAX_DESCRIPTION_LENGTH]) {
	return setAndBackupWCharTArray(lm->description,
			description,
			backupDescription,
			LINKAPI_MAX_DESCRIPTION_LENGTH);
}

LINKAPI_ERROR_CODE commitDescription(
		const wchar_t description[LINKAPI_MAX_DESCRIPTION_LENGTH]) {
	return commitOnNoError(setDescription(description));
}

LINKAPI_ERROR_CODE getIdentity(wchar_t destination[LINKAPI_MAX_IDENTITY_LENGTH]) {
	return setWCharTArray(destination, lm->identity, LINKAPI_MAX_IDENTITY_LENGTH);
}

LINKAPI_ERROR_CODE setIdentity(const wchar_t identity[LINKAPI_MAX_IDENTITY_LENGTH]) {
	return setWCharTArray(lm->identity, identity, LINKAPI_MAX_IDENTITY_LENGTH);
}

LINKAPI_ERROR_CODE commitIdentity(const wchar_t identity[LINKAPI_MAX_IDENTITY_LENGTH]) {
	return commitOnNoError(setIdentity(identity));
}

LINKAPI_ERROR_CODE getContextLen(LINKAPI_NATIVE_UINT32* destination) {
	LINKAPI_VERIFY_LM;
	*destination = lm->contextLength;
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE getContext(
		unsigned char * destinationForContext,
		LINKAPI_NATIVE_UINT32* destinationForActualLength,
		LINKAPI_NATIVE_UINT32 maxContextLength) {
	LINKAPI_VERIFY_LM;
	if (destinationForActualLength != NULL) {
		*destinationForActualLength = lm->contextLength;
	}
	if (maxContextLength > LINKAPI_MAX_CONTEXT_LENGTH) {
		maxContextLength = LINKAPI_MAX_CONTEXT_LENGTH;
	}
	memcpy(destinationForContext, lm->context, (maxContextLength) * sizeof (unsigned char));

	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE setContext(
		const unsigned char * context,
		LINKAPI_NATIVE_UINT32 contextLength) {
	LINKAPI_VERIFY_LM;
	if (contextLength > LINKAPI_MAX_CONTEXT_LENGTH) {
		return LINKAPI_ERROR_CODE_CONTEXT_LENGTH_EXCEEDED;
	}
	lm->contextLength = contextLength;
	memcpy(lm->context, context, contextLength * sizeof (unsigned char));

	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE commitContext(
		const unsigned char * context,
		LINKAPI_NATIVE_UINT32 contextLength) {
	return commitOnNoError(setContext(context, contextLength));
}

LINKAPI_ERROR_CODE setIdentityAndContext(
		const wchar_t identity[LINKAPI_MAX_IDENTITY_LENGTH],
		const unsigned char * context,
		LINKAPI_NATIVE_UINT32 contextLength) {
	LINKAPI_ERROR_CODE err = setIdentity(identity);
	LINKAPI_VERIFY_NO_ERROR;
	return setContext(context, contextLength);
}

LINKAPI_ERROR_CODE commitIdentityAndContext(
		const wchar_t identity[LINKAPI_MAX_IDENTITY_LENGTH],
		const unsigned char * context,
		LINKAPI_NATIVE_UINT32 contextLength) {
	return commitOnNoError(setIdentityAndContext(identity, context, contextLength));
}

/**
 * overrides the coordinates of a given vector
 * 
 * @param destination the vector to write to
 * @param x the magnitude of the x basis vector
 * @param y the magnitude of the y basis vector
 * @param z the magnitude of the z basis vector
 *
 * @return destination
 */
float* setVector(float destination[3], float x, float y, float z) {
	destination[0] = x;
	destination[1] = y;
	destination[2] = z;

	return destination;
}

/**
 * copies the values of the source vector into the destination vector
 *
 * @param destination vector to be written to
 * @param source vector to be read from
 * @return destination
 */
float* copyVector(float destination[3], const float source[3]) {
	setVector(destination,
			source[0],
			source[1],
			source[2]);

	return destination;
}

LINKAPI_ERROR_CODE getAvatarPosition(float destination[3]) {
	LINKAPI_VERIFY_LM;
	copyVector(destination, lm->avatarPosition);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE setAvatarPosition(float x, float y, float z) {
	LINKAPI_VERIFY_LM;
	setVector(lm->avatarPosition, x, y, z);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE getAvatarFront(float destination[3]) {
	LINKAPI_VERIFY_LM;
	copyVector(destination, lm->avatarFront);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE setAvatarFront(float x, float y, float z) {
	LINKAPI_VERIFY_LM;
	setVector(lm->avatarFront, x, y, z);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE getAvatarTop(float destination[3]) {
	LINKAPI_VERIFY_LM;
	copyVector(destination, lm->avatarTop);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE setAvatarTop(float x, float y, float z) {
	LINKAPI_VERIFY_LM;
	setVector(lm->avatarTop, x, y, z);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE getCameraPosition(float destination[3]) {
	LINKAPI_VERIFY_LM;
	copyVector(destination, lm->cameraPosition);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE setCameraPosition(float x, float y, float z) {
	LINKAPI_VERIFY_LM;
	setVector(lm->cameraPosition, x, y, z);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE getCameraFront(float destination[3]) {
	LINKAPI_VERIFY_LM;
	copyVector(destination, lm->cameraFront);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE setCameraFront(float x, float y, float z) {
	LINKAPI_VERIFY_LM;
	setVector(lm->cameraFront, x, y, z);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE getCameraTop(float destination[3]) {
	LINKAPI_VERIFY_LM;
	copyVector(destination, lm->cameraTop);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE setCameraTop(float x, float y, float z) {
	LINKAPI_VERIFY_LM;
	setVector(lm->cameraTop, x, y, z);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE setVectors(
		const float avatarPosition[3],
		const float avatarFront[3],
		const float avatarTop[3],
		const float cameraPosition[3],
		const float cameraFront[3],
		const float cameraTop[3]) {
	LINKAPI_VERIFY_LM;

	copyVector(lm->avatarPosition, avatarPosition);
	copyVector(lm->avatarFront, avatarFront);
	copyVector(lm->avatarTop, avatarTop);

	copyVector(lm->cameraPosition, cameraPosition);
	copyVector(lm->cameraFront, cameraFront);
	copyVector(lm->cameraTop, cameraTop);

	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE commitVectors(
		const float avatarPosition[3],
		const float avatarFront[3],
		const float avatarTop[3],
		const float cameraPosition[3],
		const float cameraFront[3],
		const float cameraTop[3]) {

	return commitOnNoError(setVectors(avatarPosition, avatarFront, avatarTop,
			cameraPosition, cameraFront, cameraTop));
}

LINKAPI_ERROR_CODE setVectorsAvatarAsCamera(
		const float avatarPosition[3],
		const float avatarFront[3],
		const float avatarTop[3]) {
	return setVectors(avatarPosition, avatarFront, avatarTop,
			avatarPosition, avatarFront, avatarTop);
}

LINKAPI_ERROR_CODE commitVectorsAvatarAsCamera(
		const float avatarPosition[3],
		const float avatarFront[3],
		const float avatarTop[3]) {
	return commitVectors(avatarPosition, avatarFront, avatarTop,
			avatarPosition, avatarFront, avatarTop);
}

LINKAPI_ERROR_CODE getTick(LINKAPI_NATIVE_DWORD* destination) {
	LINKAPI_VERIFY_LM;
	*destination = lm->tick;
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE setTick(LINKAPI_NATIVE_DWORD tick) {
	LINKAPI_VERIFY_LM;
	lm->tick = tick;
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE commitTick(LINKAPI_NATIVE_DWORD tick) {
	LINKAPI_ERROR_CODE err = setTick(tick);
	LINKAPI_VERIFY_NO_ERROR;
	/* cannot commit() as it would change the tick too! */
	return relock();
}

LINKAPI_ERROR_CODE getVersion(LINKAPI_NATIVE_UINT32* destination) {
	LINKAPI_VERIFY_LM;
	*destination = lm->version;
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE setVersion(LINKAPI_NATIVE_UINT32 version) {
	LINKAPI_VERIFY_LM;
	backupUiVersion = version;
	lm->version = version;
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE commitVersion(LINKAPI_NATIVE_UINT32 version) {
	return commitOnNoError(setVersion(version));
}

LINKAPI_ERROR_CODE getData(LINKAPI_LINKED_MEMORY* destination) {
	LINKAPI_VERIFY_LM;
	memcpy(destination, lm, sizeof (LINKAPI_LINKED_MEMORY));
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE setData(const LINKAPI_LINKED_MEMORY* source) {
	LINKAPI_VERIFY_LM;

	wcsncpy(backupName, source->name, LINKAPI_MAX_NAME_LENGTH);
	wcsncpy(backupDescription, source->description, LINKAPI_MAX_DESCRIPTION_LENGTH);
	backupUiVersion = source->version;

	memcpy(lm, source, sizeof (LINKAPI_LINKED_MEMORY));
	return LINKAPI_ERROR_CODE_NO_ERROR;
}
