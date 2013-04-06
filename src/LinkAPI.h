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
 * This header file specifies a generic interface to provide positional audio
 * information to mumble it depends on the "Mumble Link Plugin" ("Link") v1.2.0
 *
 * note that all update* methods will increment uiTick
 *
 * The difference to a regular plugin is that instead of developing a native
 * plugin and submitting it to mumble,
 * one can use the provided library and call upon the native methods directly.
 *
 * This is initially intended to work mainly for JNA (https://github.com/twall/jna)
 * but is not limited to it.
 * It should work with anything that is able to call native methods directly
 * (i.e. Scripts, AutoIt etc.), simply provide this library. 
 *
 * For more information about the different data that can be updated see
 * http://mumble.sourceforge.net/Link
 *
 *
 * To compile this as a static library define LINKAPI_NO_DLL
 * If you are using this header file to define your imports define LINKAPI_DLL_IMPORTS
 *
 * @author zsawyer, 2010-03-20
 */

#ifndef LINKAPI_H
#define	LINKAPI_H

#include "apiHelper.h"

#ifdef _WIN32
#define WIN32
#endif

#include <stdio.h>
#include <string.h>
#include <wchar.h>

#include <locale> // std::use_facet, std::ctype

#ifndef WIN32

#include <stdint.h> // uint32_t
#include <sys/mman.h> // shm_open, PROT_READ, PROT_WRITE, MAP_SHARED mmap
#include <unistd.h> // getuid
#include <sys/stat.h> // S_IRUSR, S_IWUSR
#include <fcntl.h> // O_RDWR

#define NATIVE_UNIT32 uint32_t

#else
#include <windows.h>
#define NATIVE_UNIT32 UINT32
#endif


#ifdef	__cplusplus
extern "C" {
#endif

#define VECTOR_LENGTH 3

#define MAX_IDENTITY_LENGTH 256
#define MAX_CONTEXT_LENGTH 256
#define MAX_NAME_LENGTH 256
#define MAX_DESCRIPTION_LENGTH 2048

	struct LinkedMem {
		NATIVE_UNIT32 uiVersion;
#ifdef WIN32		
		DWORD uiTick;
#else
		uint32_t uiTick;
#endif
		float fAvatarPosition[VECTOR_LENGTH];
		float fAvatarFront[VECTOR_LENGTH];
		float fAvatarTop[VECTOR_LENGTH];
		wchar_t name[MAX_NAME_LENGTH];
		float fCameraPosition[VECTOR_LENGTH];
		float fCameraFront[VECTOR_LENGTH];
		float fCameraTop[VECTOR_LENGTH];
		wchar_t identity[MAX_IDENTITY_LENGTH];
		NATIVE_UNIT32 context_len;
		unsigned char context[MAX_CONTEXT_LENGTH];
		wchar_t description[MAX_DESCRIPTION_LENGTH];
	};

	LinkedMem *lm = NULL;

	/**
	 * initialize the linked memory
	 * and set the name and description
	 *
	 * it corresponds to initMumble() defined here: http://mumble.sourceforge.net/Link
	 * but also sets the name and description as this should only needed to be
	 * set once
	 *
	 * @param name	the display name of the application which links with mumble (i.e. L"TestLink")
	 * @param description	a text stating the purpose of this link
	 * @param uiVersion	no description available (this should usually be set to 2)
	 *
	 * @return	an error code <br>
	 *		0: no error<br>
	 *		1: win32 specific: OpenFileMappingW failed to return a handle<br>
	 *		2: win32 specific: MapViewOfFile failed to return a structure<br>
	 *		3: unix specific: shm_open returned a negative integer<br>
	 *		4: unix specific: mmap failed to return a structure<br>
	 *		5: shared memory was not initialized<br>
	 */
	LINKAPI_API
	int initialize(wchar_t name[MAX_NAME_LENGTH],
			wchar_t description[MAX_DESCRIPTION_LENGTH],
			NATIVE_UNIT32 uiVersion);


	/**
	 * update the identity only
	 *
	 * Notice: The identity does not need to be updated every single frame. It
	 * shouldn't change more than a few times per second if at all during a game.
	 *
	 * Identity should contain a string which uniquely identifies the player in
	 * the given context. This is usually satisfied by the in-game player name
	 * or the players ID (player-/connection-ID on the server or a global ID).
	 *
	 * Additionally the identity can contain any additional information about
	 * the player that might be interesting for the mumble server.
	 *
	 * We recommend using an easily parseable format like JSON or CSV for
	 * encoding the information but this is up to the game. Remember that the
	 * link structures only allow for limited characters of identity data.
	 *
	 * @param identity	unique id of the user
	 *
	 * @return true if success else false (this would usually mean that the
	 * memory structure was not initialized properly)
	 */
	LINKAPI_API
	bool updateIdentity(wchar_t identity[MAX_IDENTITY_LENGTH]);

	/**
	 * update the context only
	 *
	 * Notice: The context does not need to be updated every single frame. It
	 * shouldn't change more than a few times per second if at all during a game.
	 *
	 * The context string is used to determine which users on a Mumble server
	 * should hear each other positionally. If context between two mumble user
	 * does not match the positional audio data is stripped server-side and
	 * voice will be received as non-positional.
	 *
	 * Accordingly the context should only match for players on the same server
	 * in the same game on the same map. Whether to include things like team in
	 * this string depends on the game itself. When in doubt err on the side of
	 * including less. This gives more flexibility later on.
	 *
	 * @param context	a generic context
	 * @param context_len	the length of the context (number of array elements)
	 *
	 * @return true if success else false (this would usually mean that the
	 * memory structure was not initialized properly)
	 */
	LINKAPI_API
	bool updateContext(unsigned char context[MAX_CONTEXT_LENGTH],
			NATIVE_UNIT32 context_len);

	/**
	 * update the identity and context
	 *
	 * Notice: The identity and/or context does not need to be updated every
	 * single frame. It shouldn't change more than a few times per second if at
	 * all during a game.
	 *
	 * see updateIdentity(..) and updateContext(..) for detailed information
	 *
	 * @param identity	unique id of the user
	 * @param context	a generic context
	 * @param context_len	the length of the context (number of active array
	 *		elements)
	 * 
	 * @return true if success else false (this would usually mean that the
	 * memory structure was not initialized properly)
	 */
	LINKAPI_API
	bool updateIdentityAndContext(
			wchar_t identity[MAX_IDENTITY_LENGTH],
			unsigned char context[MAX_CONTEXT_LENGTH],
			NATIVE_UNIT32 context_len);


	/**
	 * update the name only
	 *
	 * Notice: This does not need to be updated every single frame. It shouldn't
	 * change at all during a game.
	 *
	 * this name is shown in the mumble interface to indicate which plugin's 
	 * positional audio is being used (i.e. used for the "XXX linked." message
	 * in the mumble log)
	 *
	 * @param name	the display name of the application which links with mumble (i.e. L"TestLink")
	 *
	 * @return true if success else false (this would usually mean that the
	 * memory structure was not initialized properly)
	 */
	LINKAPI_API
	bool updateName(wchar_t name[MAX_NAME_LENGTH]);

	/**
	 * update the description only
	 *
	 * Notice: This does not need to be updated every single frame. It shouldn't
	 * change at all during a game.
	 *
	 * this is the text to explain the plugin and its purpose
	 * 
	 * @param description	a text stating the purpose of this link
	 *
	 * @return true if success else false (this would usually mean that the
	 * memory structure was not initialized properly)
	 */
	LINKAPI_API
	bool updateDescription(wchar_t description[MAX_DESCRIPTION_LENGTH]);


	/**
	 * updates avatar and camera vectors
	 *
	 * Notice: Mumble fetches these values 50 times a second, so please update
	 * them every frame.
	 *
	 * @param fAvatarPosition	Position of the avatar.
	 * @param fAvatarFront	Unit vector pointing out of the avatar's eyes.
	 * @param fAvatarTop	Unit vector pointing out of the top of the avatar's head.
	 * @param fCameraPosition	Position of the camera.
	 * @param fCameraFront	Unit vector pointing out of the camera's lense.
	 * @param fCameraTop	Unit vector pointing out of the camera's top.
	 *
	 * @return true if success else false (this would usually mean that the
	 * memory structure was not initialized properly)
	 */
	LINKAPI_API
	bool updateVectors(
			float fAvatarPosition[VECTOR_LENGTH],
			float fAvatarFront[VECTOR_LENGTH],
			float fAvatarTop[VECTOR_LENGTH],
			float fCameraPosition[VECTOR_LENGTH],
			float fCameraFront[VECTOR_LENGTH],
			float fCameraTop[VECTOR_LENGTH]);

	/**
	 * updates avatar AND camera vectors
	 *
	 * this simply reuses the given vectors for the camera	 
	 *
	 * short cut function to use when the camera of the game/program is not
	 * independent of the avatar
	 *
	 * Notice: Mumble fetches these values 50 times a second, so please update
	 * them every frame.
	 *
	 * @param fAvatarPosition	Position of the avatar and camera.
	 * @param fAvatarFront	Unit vector pointing out of the camera/avatar's eyes.
	 * @param fAvatarTop	Unit vector pointing out of the top of the avatar's head/camera's top.
	 *
	 * @return true if success else false (this would usually mean that the
	 * memory structure was not initialized properly)
	 */
	LINKAPI_API
	bool updateVectorsByAvatar(
			float fAvatarPosition[VECTOR_LENGTH],
			float fAvatarFront[VECTOR_LENGTH],
			float fAvatarTop[VECTOR_LENGTH]);


	/**
	 * a convenience function to directly manipulate the entire linked memory at once
	 *
	 * Notice: Parts of this does not need to be updated every single frame.
	 * Please use the more directly appropriate update functions instead.
	 *
	 * @param source data structure which is to be copied
	 *
	 * @return true if success else false (this would usually mean that the
	 * memory structure was not initialized properly)
	 */
	LINKAPI_API
	bool updateData(LinkedMem *source);


#ifdef	__cplusplus
}
#endif

#endif	/* LINKAPI_H */
