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

#    include <sys/mman.h> /* shm_open, PROT_READ, PROT_WRITE, MAP_SHARED mmap */
#endif

static LINKAPI_LINKED_MEMORY *lm = NULL;

#define LINKAPI_VERIFY_LM			if (!lm) { return LINKAPI_ERROR_CODE_NO_MEMORY_WAS_INITIALIZED; }
#define LINKAPI_VERIFY_NO_ERROR 	if (err != LINKAPI_ERROR_CODE_NO_ERROR) { return err; }

LINKAPI_ERROR_CODE nativeInitialize() {
#ifdef WIN32
	HANDLE hMapObject = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, L"MumbleLink");
	if (hMapObject == NULL) {
		return LINKAPI_ERROR_CODE_WIN32_NO_HANDLE;
	}

	lm = (LINKAPI_LINKED_MEMORY *) MapViewOfFile(hMapObject, FILE_MAP_ALL_ACCESS, 0, 0, sizeof (LINKAPI_LINKED_MEMORY));
	if (lm == NULL) {
		CloseHandle(hMapObject);
		hMapObject = NULL;
		return LINKAPI_ERROR_CODE_WIN32_NO_STRUCTURE;
	}
#else
	char memname[256];
	snprintf(memname, 256, "/MumbleLink.%d", getuid());

	int shmfd = shm_open(memname, O_RDWR, S_IRUSR | S_IWUSR);

	if (shmfd < 0) {
		return LINKAPI_ERROR_CODE_UNIX_NO_HANDLE;
	}

	lm = (LinkedMem *) (mmap(NULL, sizeof (struct LinkedMem), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0));

	if (lm == (void *) (-1)) {
		lm = NULL;
		return LINKAPI_ERROR_CODE_UNIX_NO_STRUCTURE;
	}
#endif

	return LINKAPI_ERROR_CODE_NO_ERROR;
}

static wchar_t backupName[LINKAPI_MAX_NAME_LENGTH];
static wchar_t backupDescription[LINKAPI_MAX_DESCRIPTION_LENGTH];
static LINKAPI_NATIVE_UINT32 backupUiVersion;

LINKAPI_ERROR_CODE initialize(wchar_t name[LINKAPI_MAX_NAME_LENGTH], wchar_t description[LINKAPI_MAX_DESCRIPTION_LENGTH], LINKAPI_NATIVE_UINT32 uiVersion) {
	LINKAPI_ERROR_CODE err;

	err = nativeInitialize();
	LINKAPI_VERIFY_NO_ERROR;

	LINKAPI_VERIFY_LM;
	if (lm->uiVersion != uiVersion) {
		err = setName(name);
		LINKAPI_VERIFY_NO_ERROR;
		err = setDescription(description);
		LINKAPI_VERIFY_NO_ERROR;
		err = setUiVersion(uiVersion);
		LINKAPI_VERIFY_NO_ERROR;
	}
	err = setUiTick(0);

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
	if (lm->uiVersion != backupUiVersion) {
		wcsncpy(lm->name, backupName, LINKAPI_MAX_NAME_LENGTH);
		wcsncpy(lm->description, backupDescription, LINKAPI_MAX_DESCRIPTION_LENGTH);

		lm->uiVersion = backupUiVersion;
	}

	return LINKAPI_ERROR_CODE_NO_ERROR;
}

void unlinkMumble() {
	lm->uiVersion = LINKAPI_UI_VERSION_UNLINK;
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
	lm->uiTick++;
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

LINKAPI_ERROR_CODE updateName(wchar_t name[LINKAPI_MAX_NAME_LENGTH]) {
	return commitOnNoError(setName(name));
}

wchar_t* getDescription() {
	return lm->description;
}

LINKAPI_ERROR_CODE setDescription(wchar_t description[LINKAPI_MAX_DESCRIPTION_LENGTH]) {
	return setAndBackupWCharTArray(lm->description, description, backupDescription, LINKAPI_MAX_DESCRIPTION_LENGTH);
}

LINKAPI_ERROR_CODE updateDescription(wchar_t description[LINKAPI_MAX_DESCRIPTION_LENGTH]) {
	return commitOnNoError(setDescription(description));
}

wchar_t* getIdentity() {
	return lm->identity;
}

LINKAPI_ERROR_CODE setIdentity(wchar_t identity[LINKAPI_MAX_IDENTITY_LENGTH]) {
	return setWCharTArray(lm->identity, identity, LINKAPI_MAX_IDENTITY_LENGTH);
}

LINKAPI_ERROR_CODE updateIdentity(wchar_t identity[LINKAPI_MAX_IDENTITY_LENGTH]) {
	return commitOnNoError(setIdentity(identity));
}

unsigned char * getContext(LINKAPI_NATIVE_UINT32* context_len) {
	if(context_len != NULL) {
		*context_len = lm->context_len;
	}
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

LINKAPI_ERROR_CODE updateContext(unsigned char context[], LINKAPI_NATIVE_UINT32 context_len) {
	return commitOnNoError(setContext(context, context_len));
}

LINKAPI_ERROR_CODE setIdentityAndContext(wchar_t identity[], unsigned char context[], LINKAPI_NATIVE_UINT32 context_len) {
	LINKAPI_ERROR_CODE err = setIdentity(identity);
	LINKAPI_VERIFY_NO_ERROR;
	return setContext(context, context_len);
}

LINKAPI_ERROR_CODE updateIdentityAndContext(wchar_t identity[], unsigned char context[], LINKAPI_NATIVE_UINT32 context_len) {
	return commitOnNoError(setIdentityAndContext(identity, context, context_len));
}

void setVector(float target[LINKAPI_VECTOR_LENGTH], float x, float y, float z) {
	target[0] = x;
	target[1] = y;
	target[2] = z;
}

float* getAvatarPosition() {
	return lm->fAvatarPosition;
}

LINKAPI_ERROR_CODE setAvatarPosition(float x, float y, float z) {
	LINKAPI_VERIFY_LM;
	setVector(lm->fAvatarPosition, x, y, z);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

float* getAvatarFront() {
	return lm->fAvatarFront;
}

LINKAPI_ERROR_CODE setAvatarFront(float x, float y, float z) {
	LINKAPI_VERIFY_LM;
	setVector(lm->fAvatarFront, x, y, z);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

float* getAvatarTop() {
	return lm->fAvatarTop;
}

LINKAPI_ERROR_CODE setAvatarTop(float x, float y, float z) {
	LINKAPI_VERIFY_LM;
	setVector(lm->fAvatarTop, x, y, z);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

float* getCameraPosition() {
	return lm->fCameraPosition;
}

LINKAPI_ERROR_CODE setCameraPosition(float x, float y, float z) {
	LINKAPI_VERIFY_LM;
	setVector(lm->fCameraPosition, x, y, z);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

float* getCameraFront() {
	return lm->fCameraFront;
}

LINKAPI_ERROR_CODE setCameraFront(float x, float y, float z) {
	LINKAPI_VERIFY_LM;
	setVector(lm->fCameraFront, x, y, z);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

float* getCameraTop() {
	return lm->fCameraTop;
}

LINKAPI_ERROR_CODE setCameraTop(float x, float y, float z) {
	LINKAPI_VERIFY_LM;
	setVector(lm->fCameraTop, x, y, z);
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

void copyVector(float target[LINKAPI_VECTOR_LENGTH], float source[LINKAPI_VECTOR_LENGTH]) {
	int i;
	for (i = 0; i < LINKAPI_VECTOR_LENGTH; i++) {
		target[i] = source[i];
	}
}

LINKAPI_ERROR_CODE setVectors(
		float fAvatarPosition[LINKAPI_VECTOR_LENGTH],
		float fAvatarFront[LINKAPI_VECTOR_LENGTH],
		float fAvatarTop[LINKAPI_VECTOR_LENGTH],
		float fCameraPosition[LINKAPI_VECTOR_LENGTH],
		float fCameraFront[LINKAPI_VECTOR_LENGTH],
		float fCameraTop[LINKAPI_VECTOR_LENGTH]) {
	LINKAPI_VERIFY_LM;

	copyVector(lm->fAvatarPosition, fAvatarPosition);
	copyVector(lm->fAvatarFront, fAvatarFront);
	copyVector(lm->fAvatarTop, fAvatarTop);

	copyVector(lm->fCameraPosition, fCameraPosition);
	copyVector(lm->fCameraFront, fCameraFront);
	copyVector(lm->fCameraTop, fCameraTop);

	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE updateVectors(
		float fAvatarPosition[LINKAPI_VECTOR_LENGTH],
		float fAvatarFront[LINKAPI_VECTOR_LENGTH],
		float fAvatarTop[LINKAPI_VECTOR_LENGTH],
		float fCameraPosition[LINKAPI_VECTOR_LENGTH],
		float fCameraFront[LINKAPI_VECTOR_LENGTH],
		float fCameraTop[LINKAPI_VECTOR_LENGTH]) {

	return commitOnNoError(setVectors(fAvatarPosition, fAvatarFront, fAvatarTop,
			fCameraPosition, fCameraFront, fCameraTop));
}

LINKAPI_ERROR_CODE setVectorsAvatarAsCamera(
		float fAvatarPosition[LINKAPI_VECTOR_LENGTH],
		float fAvatarFront[LINKAPI_VECTOR_LENGTH],
		float fAvatarTop[LINKAPI_VECTOR_LENGTH]) {
	return setVectors(fAvatarPosition, fAvatarFront, fAvatarTop,
			fAvatarPosition, fAvatarFront, fAvatarTop);
}

LINKAPI_ERROR_CODE updateVectorsAvatarAsCamera(
		float fAvatarPosition[LINKAPI_VECTOR_LENGTH],
		float fAvatarFront[LINKAPI_VECTOR_LENGTH],
		float fAvatarTop[LINKAPI_VECTOR_LENGTH]) {
	return updateVectors(fAvatarPosition, fAvatarFront, fAvatarTop,
			fAvatarPosition, fAvatarFront, fAvatarTop);
}

LINKAPI_NATIVE_DWORD getUiTick() {
	return lm->uiTick;
}

LINKAPI_ERROR_CODE setUiTick(LINKAPI_NATIVE_DWORD tick) {
	LINKAPI_VERIFY_LM;
	lm->uiTick = tick;
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE updateUiTick(LINKAPI_NATIVE_DWORD tick) {
	LINKAPI_ERROR_CODE err = setUiTick(tick);
	LINKAPI_VERIFY_NO_ERROR;
	/* cannot commit() as it would change the uiTick too! */
	return relock();
}

LINKAPI_NATIVE_UINT32 getUiVersion() {
	return lm->uiVersion;
}

LINKAPI_ERROR_CODE setUiVersion(LINKAPI_NATIVE_UINT32 version) {
	LINKAPI_VERIFY_LM;
	backupUiVersion = version;
	lm->uiVersion = version;
	return LINKAPI_ERROR_CODE_NO_ERROR;
}

LINKAPI_ERROR_CODE updateUiVersion(LINKAPI_NATIVE_UINT32 version) {
	return commitOnNoError(setUiVersion(version));
}

LINKAPI_LINKED_MEMORY* getData() {
	return lm;
}

LINKAPI_ERROR_CODE setData(LINKAPI_LINKED_MEMORY* source) {
	LINKAPI_VERIFY_LM;
	memcpy(lm, source, sizeof (LINKAPI_LINKED_MEMORY));
	return LINKAPI_ERROR_CODE_NO_ERROR;
}
