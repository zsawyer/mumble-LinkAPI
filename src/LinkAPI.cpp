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

#define VERIFY_LM if (!lm) { return false; }

int initialize() {

#ifdef WIN32
	HANDLE hMapObject = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, L"MumbleLink");
	if (hMapObject == NULL)
		return 1;

	lm = (LinkedMem *) MapViewOfFile(hMapObject, FILE_MAP_ALL_ACCESS, 0, 0, sizeof (LinkedMem));
	if (lm == NULL) {
		CloseHandle(hMapObject);
		hMapObject = NULL;
		return 2;
	}
#else
	char memname[256];
	snprintf(memname, 256, "/MumbleLink.%d", getuid());

	int shmfd = shm_open(memname, O_RDWR, S_IRUSR | S_IWUSR);

	if (shmfd < 0) {
		return 3;
	}

	lm = (LinkedMem *) (mmap(NULL, sizeof (struct LinkedMem), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0));

	if (lm == (void *) (-1)) {
		lm = NULL;
		return 4;
	}
#endif

	return 0;
}

static wchar_t backupName[MAX_NAME_LENGTH];
static wchar_t backupDescription[MAX_DESCRIPTION_LENGTH];
static NATIVE_UNIT32 backupUiVersion;

int initialize(wchar_t name[], wchar_t description[], NATIVE_UNIT32 uiVersion) {
	wcsncpy(backupName, name, MAX_NAME_LENGTH);
	wcsncpy(backupDescription, description, MAX_DESCRIPTION_LENGTH);
	backupUiVersion = uiVersion;

	int err = initialize();

	if (err != 0) {
		return err;
	}

	if (!lm) {
		return 5;
	}

	if (lm->uiVersion != uiVersion) {
		wcsncpy(lm->name, name, MAX_NAME_LENGTH);
		wcsncpy(lm->description, description, MAX_DESCRIPTION_LENGTH);

		lm->uiVersion = uiVersion;
	}
	lm->uiTick = 0;

	return 0;
}

/**
 * identifies that the link plugin was unlocked and tells it lock again
 *   this can happen when updates were too infrequent - then the plugin unlinks
 *
 * this will effectively relink the plugin
 *
 * @return always true as there is no error handling yet
 */
bool relock() {
	if (lm->uiVersion != backupUiVersion) {
		wcsncpy(lm->name, backupName, MAX_NAME_LENGTH);
		wcsncpy(lm->description, backupDescription, MAX_DESCRIPTION_LENGTH);

		lm->uiVersion = backupUiVersion;
	}

	return true;
}

/**
 * notifies the plugin that the data was updated
 * all update* functions call this method at the end
 *
 * @return always true because right now no feedback is given by the plugin
 */
bool update() {
	lm->uiTick++;

	return relock();
}

bool updateName(wchar_t name[MAX_NAME_LENGTH]) {
	wcsncpy(backupName, name, MAX_NAME_LENGTH);

	VERIFY_LM;

	wcsncpy(lm->name, name, MAX_NAME_LENGTH);

	return update();
}

bool updateDescription(wchar_t description[MAX_DESCRIPTION_LENGTH]) {
	wcsncpy(backupDescription, description, MAX_DESCRIPTION_LENGTH);

	VERIFY_LM;

	wcsncpy(lm->description, description, MAX_DESCRIPTION_LENGTH);

	return update();
}

bool updateIdentity(wchar_t identity[MAX_IDENTITY_LENGTH]) {
	VERIFY_LM;

	wcsncpy(lm->identity, identity, MAX_IDENTITY_LENGTH);

	return update();
}

bool updateContext(unsigned char context[], NATIVE_UNIT32 context_len) {
	VERIFY_LM;

	memcpy(lm->context, context, context_len);
	lm->context_len = context_len;

	return update();
}

bool updateIdentityAndContext(wchar_t identity[], unsigned char context[], NATIVE_UNIT32 context_len) {
	VERIFY_LM;

	wcsncpy(lm->identity, identity, MAX_IDENTITY_LENGTH);
	memcpy(lm->context, context, context_len);
	lm->context_len = context_len;

	return update();
}

void setVector(float target[VECTOR_LENGTH], float source[VECTOR_LENGTH]) {
	for (int i = 0; i < VECTOR_LENGTH; i++) {
		target[i] = source[i];
	}
}

bool updateVectors(
		float fAvatarPosition[VECTOR_LENGTH],
		float fAvatarFront[VECTOR_LENGTH],
		float fAvatarTop[VECTOR_LENGTH],
		float fCameraPosition[VECTOR_LENGTH],
		float fCameraFront[VECTOR_LENGTH],
		float fCameraTop[VECTOR_LENGTH]) {
	VERIFY_LM;

	setVector(lm->fAvatarPosition, fAvatarPosition);
	setVector(lm->fAvatarFront, fAvatarFront);
	setVector(lm->fAvatarTop, fAvatarTop);

	setVector(lm->fCameraPosition, fCameraPosition);
	setVector(lm->fCameraFront, fCameraFront);
	setVector(lm->fCameraTop, fCameraTop);

	return update();
}

bool updateVectorsByAvatar(
		float fAvatarPosition[VECTOR_LENGTH],
		float fAvatarFront[VECTOR_LENGTH],
		float fAvatarTop[VECTOR_LENGTH]) {
	return updateVectors(fAvatarPosition, fAvatarFront, fAvatarTop,
			fAvatarPosition, fAvatarFront, fAvatarTop);
}

bool updateData(LinkedMem* source) {
	memcpy(lm, source, sizeof (LinkedMem));
	return true;
}




