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
 * @author zsawyer, 2010-03-20
 */

#include "LinkAPI.h"

#include <stdio.h> // snprintf
#include <string.h> // memcpy

#ifndef WIN32
#    include <unistd.h> // getuid
#    include <sys/stat.h> // S_IRUSR, S_IWUSR
#    include <fcntl.h> // O_RDWR

#    include <sys/mman.h> // shm_open, PROT_READ, PROT_WRITE, MAP_SHARED mmap
#endif

static LinkedMem *lm = NULL;

#define VERIFY_LM			if (!lm) { return ERROR_CODE_NO_MEMORY_WAS_INITIALIZED; }
#define VERIFY_NO_ERROR 	if (err != ERROR_CODE_NO_ERROR) { return err; }

ErrorCode nativeInitialize() {
#ifdef WIN32
	HANDLE hMapObject = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, L"MumbleLink");
	if (hMapObject == NULL)
		return ERROR_CODE_WIN32_NO_HANDLE;

	lm = (LinkedMem *) MapViewOfFile(hMapObject, FILE_MAP_ALL_ACCESS, 0, 0, sizeof (LinkedMem));
	if (lm == NULL) {
		CloseHandle(hMapObject);
		hMapObject = NULL;
		return ERROR_CODE_WIN32_NO_STRUCTURE;
	}
#else
	char memname[256];
	snprintf(memname, 256, "/MumbleLink.%d", getuid());

	int shmfd = shm_open(memname, O_RDWR, S_IRUSR | S_IWUSR);

	if (shmfd < 0) {
		return ERROR_CODE_UNIX_NO_HANDLE;
	}

	lm = (LinkedMem *) (mmap(NULL, sizeof (struct LinkedMem), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0));

	if (lm == (void *) (-1)) {
		lm = NULL;
		return ERROR_CODE_UNIX_NO_STRUCTURE;
	}
#endif

	return ERROR_CODE_NO_ERROR;
}

static wchar_t backupName[MAX_NAME_LENGTH];
static wchar_t backupDescription[MAX_DESCRIPTION_LENGTH];
static NATIVE_UINT32 backupUiVersion;

ErrorCode initialize(wchar_t name[MAX_NAME_LENGTH], wchar_t description[MAX_DESCRIPTION_LENGTH], NATIVE_UINT32 uiVersion) {
	ErrorCode err;

	err = nativeInitialize();
	VERIFY_NO_ERROR;

	VERIFY_LM;
	if (lm->uiVersion != uiVersion) {
		err = setName(name);
		VERIFY_NO_ERROR;
		err = setDescription(description);
		VERIFY_NO_ERROR;
		err = setUiVersion(uiVersion);
		VERIFY_NO_ERROR;
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
 * @return	an error code, see <code>enum ErrorCode</code>, ERROR_CODE_NO_ERROR
 *			on success
 */
ErrorCode relock() {
	VERIFY_LM;
	if (lm->uiVersion != backupUiVersion) {
		wcsncpy(lm->name, backupName, MAX_NAME_LENGTH);
		wcsncpy(lm->description, backupDescription, MAX_DESCRIPTION_LENGTH);

		lm->uiVersion = backupUiVersion;
	}

	return ERROR_CODE_NO_ERROR;
}

void doUnlink() {
	lm->uiVersion = UI_VERSION_UNLINK;
}

/**
 * commits if the passed error code indicates no severity
 *
 * @param previousCode	a code which a previous function might have returned
 *				that was not yet evaluated
 * @return	the error code of the commit result or the previous error code if 
 *			it was considered severe
 */
ErrorCode commitOnNoError(ErrorCode previousCode) {
	if (previousCode != ERROR_CODE_NO_ERROR) {
		return previousCode;
	}
	return commit();
}

ErrorCode commit() {
	lm->uiTick++;
	return relock();
}

ErrorCode setWCharTArray(wchar_t* destination, wchar_t* source, int count) {
	VERIFY_LM;
	wcsncpy(destination, source, count);
	return ERROR_CODE_NO_ERROR;
}

ErrorCode setAndBackupWCharTArray(wchar_t* destination, wchar_t* source, wchar_t* backupDestination, int count) {
	ErrorCode err = setWCharTArray(destination, source, count);
	VERIFY_NO_ERROR;
	wcsncpy(backupDestination, source, count);
	return err;
}

wchar_t* getName() {
	return lm->name;
}

ErrorCode setName(wchar_t name[MAX_NAME_LENGTH]) {
	return setAndBackupWCharTArray(lm->name, name, backupName, MAX_NAME_LENGTH);
}

ErrorCode updateName(wchar_t name[MAX_NAME_LENGTH]) {
	return commitOnNoError(setName(name));
}

wchar_t* getDescription() {
	return lm->description;
}

ErrorCode setDescription(wchar_t description[MAX_DESCRIPTION_LENGTH]) {
	return setAndBackupWCharTArray(lm->description, description, backupDescription, MAX_DESCRIPTION_LENGTH);
}

ErrorCode updateDescription(wchar_t description[MAX_DESCRIPTION_LENGTH]) {
	return commitOnNoError(setDescription(description));
}

wchar_t* getIdentity() {
	return lm->identity;
}

ErrorCode setIdentity(wchar_t identity[MAX_IDENTITY_LENGTH]) {
	return setWCharTArray(lm->identity, identity, MAX_IDENTITY_LENGTH);
}

ErrorCode updateIdentity(wchar_t identity[MAX_IDENTITY_LENGTH]) {
	return commitOnNoError(setIdentity(identity));
}

NATIVE_UINT32 getContextLen() {
	return lm->context_len;
}

unsigned char * getContext() {
	return lm->context;
}

ErrorCode setContext(unsigned char context[], NATIVE_UINT32 context_len) {
	VERIFY_LM;
	if (context_len > MAX_CONTEXT_LENGTH) {
		return ERROR_CODE_CONTEXT_LENGTH_EXCEEDED;
	}
	memcpy(lm->context, context, context_len);
	lm->context_len = context_len;
	return ERROR_CODE_NO_ERROR;
}

ErrorCode updateContext(unsigned char context[], NATIVE_UINT32 context_len) {
	return commitOnNoError(setContext(context, context_len));
}

ErrorCode setIdentityAndContext(wchar_t identity[], unsigned char context[], NATIVE_UINT32 context_len) {
	ErrorCode err = setIdentity(identity);
	VERIFY_NO_ERROR;
	return setContext(context, context_len);
}

ErrorCode updateIdentityAndContext(wchar_t identity[], unsigned char context[], NATIVE_UINT32 context_len) {
	return commitOnNoError(setIdentityAndContext(identity, context, context_len));
}

void setVector(float target[VECTOR_LENGTH], float x, float y, float z) {
	target[0] = x;
	target[1] = y;
	target[2] = z;
}

float* getAvatarPosition() {
	return lm->fAvatarPosition;
}

ErrorCode setAvatarPosition(float x, float y, float z) {
	VERIFY_LM;
	setVector(lm->fAvatarPosition, x, y, z);
	return ERROR_CODE_NO_ERROR;
}

float* getAvatarFront() {
	return lm->fAvatarFront;
}

ErrorCode setAvatarFront(float x, float y, float z) {
	VERIFY_LM;
	setVector(lm->fAvatarFront, x, y, z);
	return ERROR_CODE_NO_ERROR;
}

float* getAvatarTop() {
	return lm->fAvatarTop;
}

ErrorCode setAvatarTop(float x, float y, float z) {
	VERIFY_LM;
	setVector(lm->fAvatarTop, x, y, z);
	return ERROR_CODE_NO_ERROR;
}

float* getCameraPosition() {
	return lm->fCameraPosition;
}

ErrorCode setCameraPosition(float x, float y, float z) {
	VERIFY_LM;
	setVector(lm->fCameraPosition, x, y, z);
	return ERROR_CODE_NO_ERROR;
}

float* getCameraFront() {
	return lm->fCameraFront;
}

ErrorCode setCameraFront(float x, float y, float z) {
	VERIFY_LM;
	setVector(lm->fCameraFront, x, y, z);
	return ERROR_CODE_NO_ERROR;
}

float* getCameraTop() {
	return lm->fCameraTop;
}

ErrorCode setCameraTop(float x, float y, float z) {
	VERIFY_LM;
	setVector(lm->fCameraTop, x, y, z);
	return ERROR_CODE_NO_ERROR;
}

void copyVector(float target[VECTOR_LENGTH], float source[VECTOR_LENGTH]) {
	int i;
	for (i = 0; i < VECTOR_LENGTH; i++) {
		target[i] = source[i];
	}
}

ErrorCode setVectors(
		float fAvatarPosition[VECTOR_LENGTH],
		float fAvatarFront[VECTOR_LENGTH],
		float fAvatarTop[VECTOR_LENGTH],
		float fCameraPosition[VECTOR_LENGTH],
		float fCameraFront[VECTOR_LENGTH],
		float fCameraTop[VECTOR_LENGTH]) {
	VERIFY_LM;

	copyVector(lm->fAvatarPosition, fAvatarPosition);
	copyVector(lm->fAvatarFront, fAvatarFront);
	copyVector(lm->fAvatarTop, fAvatarTop);

	copyVector(lm->fCameraPosition, fCameraPosition);
	copyVector(lm->fCameraFront, fCameraFront);
	copyVector(lm->fCameraTop, fCameraTop);

	return ERROR_CODE_NO_ERROR;
}

ErrorCode updateVectors(
		float fAvatarPosition[VECTOR_LENGTH],
		float fAvatarFront[VECTOR_LENGTH],
		float fAvatarTop[VECTOR_LENGTH],
		float fCameraPosition[VECTOR_LENGTH],
		float fCameraFront[VECTOR_LENGTH],
		float fCameraTop[VECTOR_LENGTH]) {

	return commitOnNoError(setVectors(fAvatarPosition, fAvatarFront, fAvatarTop,
			fCameraPosition, fCameraFront, fCameraTop));
}

ErrorCode setVectorsByAvatar(
		float fAvatarPosition[VECTOR_LENGTH],
		float fAvatarFront[VECTOR_LENGTH],
		float fAvatarTop[VECTOR_LENGTH]) {
	return setVectors(fAvatarPosition, fAvatarFront, fAvatarTop,
			fAvatarPosition, fAvatarFront, fAvatarTop);
}

ErrorCode updateVectorsByAvatar(
		float fAvatarPosition[VECTOR_LENGTH],
		float fAvatarFront[VECTOR_LENGTH],
		float fAvatarTop[VECTOR_LENGTH]) {
	return updateVectors(fAvatarPosition, fAvatarFront, fAvatarTop,
			fAvatarPosition, fAvatarFront, fAvatarTop);
}

NATIVE_DWORD getUiTick() {
	return lm->uiTick;
}

ErrorCode setUiTick(NATIVE_DWORD tick) {
	VERIFY_LM;
	lm->uiTick = tick;
	return ERROR_CODE_NO_ERROR;
}

ErrorCode updateUiTick(NATIVE_DWORD tick) {
	ErrorCode err = setUiTick(tick);
	VERIFY_NO_ERROR;
	// cannot commit() as it would change the uiTick too
	return relock();
}

NATIVE_UINT32 getUiVersion() {
	return lm->uiVersion;
}

ErrorCode setUiVersion(NATIVE_UINT32 version) {
	VERIFY_LM;
	backupUiVersion = version;
	lm->uiVersion = version;
	return ERROR_CODE_NO_ERROR;
}

ErrorCode updateUiVersion(NATIVE_UINT32 version) {
	return commitOnNoError(setUiVersion(version));
}

LinkedMem* getData() {
	return lm;
}

ErrorCode setData(LinkedMem* source) {
	VERIFY_LM;
	memcpy(lm, source, sizeof (LinkedMem));
	return ERROR_CODE_NO_ERROR;
}
