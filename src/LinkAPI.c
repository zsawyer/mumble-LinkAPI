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

LINKAPI_ERROR_CODE initialize(wchar_t name[LINKAPI_MAX_NAME_LENGTH], wchar_t description[LINKAPI_MAX_DESCRIPTION_LENGTH], LINKAPI_NATIVE_UINT32 version) {
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

void unlinkMumble() {
	lm->version = LINKAPI_UI_VERSION_UNLINK;
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

LINKAPI_ERROR_CODE setWCharTArray(wchar_t* destination, wchar_t* source, int count) {
	LINKAPI_VERIFY_LM;
	wcsncpy(destination, source, count);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE setAndBackupWCharTArray(wchar_t* destination, wchar_t* source, wchar_t* backupDestination, int count) {
	LINKAPI_ERROR_CODE err = setWCharTArray(destination, source, count);
	LINKAPI_VERIFY_NO_ERROR;
	wcsncpy(backupDestination, source, count);
	return err;
}

wchar_t* getName() {
	return lm->name;
}

LINKAPI_ERROR_CODE setName(wchar_t name[LINKAPI_MAX_NAME_LENGTH]) {
	return setAndBackupWCharTArray(lm->name, name, backupName, LINKAPI_MAX_NAME_LENGTH);
}

LINKAPI_ERROR_CODE commitName(wchar_t name[LINKAPI_MAX_NAME_LENGTH]) {
	return commitOnNoError(setName(name));
}

wchar_t* getDescription() {
	return lm->description;
}

LINKAPI_ERROR_CODE setDescription(wchar_t description[LINKAPI_MAX_DESCRIPTION_LENGTH]) {
	return setAndBackupWCharTArray(lm->description, description, backupDescription, LINKAPI_MAX_DESCRIPTION_LENGTH);
}

LINKAPI_ERROR_CODE commitDescription(wchar_t description[LINKAPI_MAX_DESCRIPTION_LENGTH]) {
	return commitOnNoError(setDescription(description));
}

wchar_t* getIdentity() {
	return lm->identity;
}

LINKAPI_ERROR_CODE setIdentity(wchar_t identity[LINKAPI_MAX_IDENTITY_LENGTH]) {
	return setWCharTArray(lm->identity, identity, LINKAPI_MAX_IDENTITY_LENGTH);
}

LINKAPI_ERROR_CODE commitIdentity(wchar_t identity[LINKAPI_MAX_IDENTITY_LENGTH]) {
	return commitOnNoError(setIdentity(identity));
}

LINKAPI_NATIVE_UINT32 getContextLen() {
	return lm->context_len;
}

unsigned char * getContext() {
	return lm->context;
}

LINKAPI_ERROR_CODE setContext(unsigned char context[], LINKAPI_NATIVE_UINT32 context_len) {
	LINKAPI_VERIFY_LM;
	if (context_len > LINKAPI_MAX_CONTEXT_LENGTH) {
		return LINKAPI_ERROR_CODE_CONTEXT_LENGTH_EXCEEDED;
	}
	memcpy(lm->context, context, context_len);
	lm->context_len = context_len;
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE commitContext(unsigned char context[], LINKAPI_NATIVE_UINT32 context_len) {
	return commitOnNoError(setContext(context, context_len));
}

LINKAPI_ERROR_CODE setIdentityAndContext(wchar_t identity[], unsigned char context[], LINKAPI_NATIVE_UINT32 context_len) {
	LINKAPI_ERROR_CODE err = setIdentity(identity);
	LINKAPI_VERIFY_NO_ERROR;
	return setContext(context, context_len);
}

LINKAPI_ERROR_CODE commitIdentityAndContext(wchar_t identity[], unsigned char context[], LINKAPI_NATIVE_UINT32 context_len) {
	return commitOnNoError(setIdentityAndContext(identity, context, context_len));
}

void setVector(float target[3], float x, float y, float z) {
	target[0] = x;
	target[1] = y;
	target[2] = z;
}

LINKAPI_VECTOR_3D* getVector(float source[3]) {
	LINKAPI_VECTOR_3D* vector = malloc(sizeof (LINKAPI_VECTOR_3D));

	vector->x = source[0];
	vector->y = source[1];
	vector->z = source[2];

	return vector;
}

LINKAPI_VECTOR_3D* getAvatarPosition() {
	return getVector(lm->avatarPosition);
}

LINKAPI_ERROR_CODE setAvatarPosition(float x, float y, float z) {
	LINKAPI_VERIFY_LM;
	setVector(lm->avatarPosition, x, y, z);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_VECTOR_3D* getAvatarFront() {
	return getVector(lm->avatarFront);
}

LINKAPI_ERROR_CODE setAvatarFront(float x, float y, float z) {
	LINKAPI_VERIFY_LM;
	setVector(lm->avatarFront, x, y, z);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_VECTOR_3D* getAvatarTop() {
	return getVector(lm->avatarTop);
}

LINKAPI_ERROR_CODE setAvatarTop(float x, float y, float z) {
	LINKAPI_VERIFY_LM;
	setVector(lm->avatarTop, x, y, z);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_VECTOR_3D* getCameraPosition() {
	return getVector(lm->cameraPosition);
}

LINKAPI_ERROR_CODE setCameraPosition(float x, float y, float z) {
	LINKAPI_VERIFY_LM;
	setVector(lm->cameraPosition, x, y, z);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_VECTOR_3D* getCameraFront() {
	return getVector(lm->cameraFront);
}

LINKAPI_ERROR_CODE setCameraFront(float x, float y, float z) {
	LINKAPI_VERIFY_LM;
	setVector(lm->cameraFront, x, y, z);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_VECTOR_3D* getCameraTop() {
	return getVector(lm->cameraTop);
}

LINKAPI_ERROR_CODE setCameraTop(float x, float y, float z) {
	LINKAPI_VERIFY_LM;
	setVector(lm->cameraTop, x, y, z);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

void copyVector(float target[3], float source[3]) {
	int i;
	for (i = 0; i < 3; i++) {
		target[i] = source[i];
	}
}

LINKAPI_ERROR_CODE setVectors(
		float avatarPosition[3],
		float avatarFront[3],
		float avatarTop[3],
		float cameraPosition[3],
		float cameraFront[3],
		float cameraTop[3]) {
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
		float avatarPosition[3],
		float avatarFront[3],
		float avatarTop[3],
		float cameraPosition[3],
		float cameraFront[3],
		float cameraTop[3]) {

	return commitOnNoError(setVectors(avatarPosition, avatarFront, avatarTop,
			cameraPosition, cameraFront, cameraTop));
}

LINKAPI_ERROR_CODE setVectorsAvatarAsCamera(
		float avatarPosition[3],
		float avatarFront[3],
		float avatarTop[3]) {
	return setVectors(avatarPosition, avatarFront, avatarTop,
			avatarPosition, avatarFront, avatarTop);
}

LINKAPI_ERROR_CODE commitVectorsAvatarAsCamera(
		float avatarPosition[3],
		float avatarFront[3],
		float avatarTop[3]) {
	return commitVectors(avatarPosition, avatarFront, avatarTop,
			avatarPosition, avatarFront, avatarTop);
}

LINKAPI_NATIVE_DWORD getTick() {
	return lm->tick;
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

LINKAPI_NATIVE_UINT32 getVersion() {
	return lm->version;
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

LINKAPI_LINKED_MEMORY* getData() {
	return lm;
}

LINKAPI_ERROR_CODE setData(LINKAPI_LINKED_MEMORY* source) {
	LINKAPI_VERIFY_LM;
	memcpy(lm, source, sizeof (LINKAPI_LINKED_MEMORY));
	return LINKAPI_ERROR_CODE_NO_ERROR;
}
