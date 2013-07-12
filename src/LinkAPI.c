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

#define TRUE	1
#define FALSE	0

#define UI_VERSION_UNLINK 0

#define VERIFY_LM if (!lm) { return FALSE; }

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

ErrorCode initialize(wchar_t name[], wchar_t description[], NATIVE_UINT32 uiVersion) {
	ErrorCode err;
	wcsncpy(backupName, name, MAX_NAME_LENGTH);
	wcsncpy(backupDescription, description, MAX_DESCRIPTION_LENGTH);
	backupUiVersion = uiVersion;

	err = nativeInitialize();

	if (err != ERROR_CODE_NO_ERROR) {
		return err;
	}

	if (!lm) {
		return ERROR_CODE_NO_MEMORY_WAS_INITIALIZED;
	}

	if (lm->uiVersion != uiVersion) {
		wcsncpy(lm->name, name, MAX_NAME_LENGTH);
		wcsncpy(lm->description, description, MAX_DESCRIPTION_LENGTH);

		lm->uiVersion = uiVersion;
	}
	lm->uiTick = 0;

	return err;
}

/**
 * identifies that the link plugin was unlocked and tells it to lock again
 *   this can happen when updates were too infrequent - then the plugin unlinks
 *
 * this will effectively relink the plugin
 *
 * @return always TRUE as there is no error handling yet
 */
int relock() {
	if (lm->uiVersion != backupUiVersion) {
		wcsncpy(lm->name, backupName, MAX_NAME_LENGTH);
		wcsncpy(lm->description, backupDescription, MAX_DESCRIPTION_LENGTH);

		lm->uiVersion = backupUiVersion;
	}

	return TRUE;
}

void doUnlink() {
	lm->uiVersion = UI_VERSION_UNLINK;
}

int commit() {
	lm->uiTick++;
	return relock();
}

int setWCharTArray(wchar_t* destination, wchar_t* source, int count) {
	VERIFY_LM;
	wcsncpy(destination, source, count);
	return TRUE;
}

int setAndBackupWCharTArray(wchar_t* destination, wchar_t* source, wchar_t* backupDestination, int count) {
	wcsncpy(backupDestination, source, count);
	return setWCharTArray(source, destination, count);
}

wchar_t* getName() {
	return lm->name;
}

int setName(wchar_t name[MAX_NAME_LENGTH]) {
	return setAndBackupWCharTArray(lm->name, name, backupName, MAX_NAME_LENGTH);
}

int updateName(wchar_t name[MAX_NAME_LENGTH]) {
	if (!setName(name)) {
		return FALSE;
	}
	return commit();
}

wchar_t* getDescription() {
	return lm->description;
}

int setDescription(wchar_t description[MAX_DESCRIPTION_LENGTH]) {
	return setAndBackupWCharTArray(lm->description, description, backupDescription, MAX_DESCRIPTION_LENGTH);
}

int updateDescription(wchar_t description[MAX_DESCRIPTION_LENGTH]) {
	if (!setDescription(description)) {
		return FALSE;
	}
	return commit();
}

wchar_t* getIdentity() {
	return lm->identity;
}

int setIdentity(wchar_t identity[MAX_IDENTITY_LENGTH]) {
	return setWCharTArray(lm->identity, identity, MAX_IDENTITY_LENGTH);
}

int updateIdentity(wchar_t identity[MAX_IDENTITY_LENGTH]) {
	if (!setIdentity(identity)) {
		return FALSE;
	}
	return commit();
}

unsigned char * getContext() {
	return lm->context;
}

int setContext(unsigned char context[], NATIVE_UINT32 context_len) {
	VERIFY_LM;
	memcpy(lm->context, context, context_len);
	lm->context_len = context_len;
}

int updateContext(unsigned char context[], NATIVE_UINT32 context_len) {
	if (!setContext(context, context_len)) {
		return FALSE;
	}
	return commit();
}

int setIdentityAndContext(wchar_t identity[], unsigned char context[], NATIVE_UINT32 context_len) {
	return setIdentity(identity) &&
			setContext(context, context_len);
}

int updateIdentityAndContext(wchar_t identity[], unsigned char context[], NATIVE_UINT32 context_len) {
	if (!setIdentityAndContext(identity, context, context_len)) {
		return FALSE;
	}
	return commit();
}

void setVector(float target[VECTOR_LENGTH], float x, float y, float z) {
	target[0] = x;
	target[1] = x;
	target[2] = x;
}

float* getAvatarPosition() {
	return lm->fAvatarPosition;
}

int setAvatarPosition(float x, float y, float z) {
	VERIFY_LM
	setVector(lm->fAvatarPosition, x, y, z);
	return TRUE;
}

float* getAvatarFront() {
	return lm->fAvatarFront;
}

int setAvatarFront(float x, float y, float z) {
	VERIFY_LM
	setVector(lm->fAvatarFront, x, y, z);
	return TRUE;
}

float* getAvatarTop() {
	return lm->fAvatarTop;
}

int setAvatarTop(float x, float y, float z) {
	VERIFY_LM
	setVector(lm->fAvatarTop, x, y, z);
	return TRUE;
}

float* getCameraPosition() {
	return lm->fCameraPosition;
}

int setCameraPosition(float x, float y, float z) {
	VERIFY_LM
	setVector(lm->fCameraPosition, x, y, z);
	return TRUE;
}

float* getCameraFront() {
	return lm->fCameraFront;
}

int setCameraFront(float x, float y, float z) {
	VERIFY_LM
	setVector(lm->fCameraFront, x, y, z);
	return TRUE;
}

float* getCameraTop() {
	return lm->fCameraTop;
}

int setCameraTop(float x, float y, float z) {
	VERIFY_LM
	setVector(lm->fCameraTop, x, y, z);
	return TRUE;
}

void copyVector(float target[VECTOR_LENGTH], float source[VECTOR_LENGTH]) {
	int i;
	for (i = 0; i < VECTOR_LENGTH; i++) {
		target[i] = source[i];
	}
}

int setVectors(
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

	return TRUE;
}

int updateVectors(
		float fAvatarPosition[VECTOR_LENGTH],
		float fAvatarFront[VECTOR_LENGTH],
		float fAvatarTop[VECTOR_LENGTH],
		float fCameraPosition[VECTOR_LENGTH],
		float fCameraFront[VECTOR_LENGTH],
		float fCameraTop[VECTOR_LENGTH]) {

	if (!setVectors(fAvatarPosition, fAvatarFront, fAvatarTop,
			fCameraPosition, fCameraFront, fCameraTop)) {
		return FALSE;
	}

	return commit();
}

int setVectorsByAvatar(
		float fAvatarPosition[VECTOR_LENGTH],
		float fAvatarFront[VECTOR_LENGTH],
		float fAvatarTop[VECTOR_LENGTH]) {
	return setVectors(fAvatarPosition, fAvatarFront, fAvatarTop,
			fAvatarPosition, fAvatarFront, fAvatarTop);
}

int updateVectorsByAvatar(
		float fAvatarPosition[VECTOR_LENGTH],
		float fAvatarFront[VECTOR_LENGTH],
		float fAvatarTop[VECTOR_LENGTH]) {
	return updateVectors(fAvatarPosition, fAvatarFront, fAvatarTop,
			fAvatarPosition, fAvatarFront, fAvatarTop);
}

NATIVE_DWORD getUiTick() {
	return lm->uiTick;
}

int setUiTick(NATIVE_DWORD tick) {
	VERIFY_LM
	lm->uiTick = tick;
	return TRUE;
}

int updateUiTick(NATIVE_DWORD tick) {
	if (!setUiTick(tick)) {
		return FALSE;
	}
	return relock();
}

NATIVE_UINT32 getUiVersion() {
	return lm->uiVersion;
}

int setUiVersion(NATIVE_UINT32 version) {
	VERIFY_LM
	lm->uiVersion = version;
	return TRUE;
}

int updateUiVersion(NATIVE_UINT32 version) {
	if (!setUiVersion(version)) {
		return FALSE;
	}
	return commit();
}

LinkedMem* getData() {
	return lm;
}

int setData(LinkedMem* source) {
	VERIFY_LM
	memcpy(lm, source, sizeof (LinkedMem));
	return TRUE;
}
