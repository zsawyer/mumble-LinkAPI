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
 * Note that all commit...(...) methods will increment tick and reinitialize
 * the memory structure if the lock was lost (unlinked).
 *
 * CONCURRENCY WARNING:
 * All methods are non-synchronized! Race conditions are likely to happen.
 * Especially when calling getters in sequence, data writes to the shared memory
 * can happen in between the read sequence.
 * DO NOT rely upon a sequence of functions to work on the same "tick".
 * Currently the memory does not provide the means to synchronize and ensure
 * that all data are coherently relating to the same tick/each other.
 * The contextLength is not guaranteed to belong to the context retrieved
 * immediately before or after thereof.
 *
 *
 * The difference to a regular plugin is that instead of developing a native
 * plugin and submitting it to mumble, one can use the provided library and
 * call upon the native methods directly.
 *
 * This is initially intended to work mainly for JNA (https://github.com/twall/jna)
 * but is not limited to it.
 * It should work with anything that is able to call native methods directly
 * (i.e. Scripts, AutoIt etc.), simply provide this library. 
 *
 * For more information about the different data that can be committed see
 * http://mumble.sourceforge.net/Link
 *
 *
 * To compile this as a static library define LINKAPI_NO_DLL
 * If you are using this header file to define your imports define LINKAPI_DLL_IMPORTS
 *
 * @author zsawyer, 2013-03-20
 */

#ifndef LINKAPI_H
#    define	LINKAPI_H

#    ifdef	__cplusplus
extern "C" {
#    endif

#    include "apiExportHelper.h"

#    if defined (_WIN32) && ! defined (WIN32)
#        define WIN32
#    endif

#    include <wchar.h> /* wchar_t */

#    ifndef WIN32
#        include <stdint.h> /* uint32_t */
#        define LINKAPI_NATIVE_UINT32 uint32_t
#        define LINKAPI_NATIVE_DWORD uint32_t
#    else
#        include <windows.h>
#        define LINKAPI_NATIVE_UINT32 UINT32
#        define LINKAPI_NATIVE_DWORD DWORD
#    endif


#    define LINKAPI_MAX_IDENTITY_LENGTH 256
#    define LINKAPI_MAX_CONTEXT_LENGTH 256
#    define LINKAPI_MAX_NAME_LENGTH 256
#    define LINKAPI_MAX_DESCRIPTION_LENGTH 2048

#    define LINKAPI_VERSION_UNLINK 0

	/**
	 * the structure of the shared memory as defined by mumble Link plugin v1.2.0
	 */
	typedef struct LINKAPI_LINKED_MEMORY {
		LINKAPI_NATIVE_UINT32 version;
		LINKAPI_NATIVE_DWORD tick;
		float avatarPosition[3];
		float avatarFront[3];
		float avatarTop[3];
		wchar_t name[LINKAPI_MAX_NAME_LENGTH];
		float cameraPosition[3];
		float cameraFront[3];
		float cameraTop[3];
		wchar_t identity[LINKAPI_MAX_IDENTITY_LENGTH];
		LINKAPI_NATIVE_UINT32 contextLength;
		unsigned char context[LINKAPI_MAX_CONTEXT_LENGTH];
		wchar_t description[LINKAPI_MAX_DESCRIPTION_LENGTH];
	} LINKAPI_LINKED_MEMORY;

	/**
	 * error codes hinting at the root cause of a failure
	 */
	typedef enum LINKAPI_ERROR_CODE {
		/** no error */
		LINKAPI_ERROR_CODE_NO_ERROR = 0,
		/** no handle to the shared memory structure was received */
		LINKAPI_ERROR_CODE_NO_HANDLE = 1,
		/** no structure could be initialized */
		LINKAPI_ERROR_CODE_NO_STRUCTURE = 2,
		/** the shared memory was not initialized */
		LINKAPI_ERROR_CODE_NO_MEMORY_WAS_INITIALIZED = 3,
		/** the provided context length was out of bounds */
		LINKAPI_ERROR_CODE_CONTEXT_LENGTH_EXCEEDED = 4
	} LINKAPI_ERROR_CODE;

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
	 * @param version	no description available (this should usually be set to 2)
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE initialize(
			const wchar_t name[LINKAPI_MAX_NAME_LENGTH],
			const wchar_t description[LINKAPI_MAX_DESCRIPTION_LENGTH],
			LINKAPI_NATIVE_UINT32 version);

	/**
	 * forcefully unlinks the plugin instantly
	 *
	 * this function directly circumvents the timeout wait of the link plugin
	 *
	 * this effect is undone when calling a commit...(...)-function or
	 * <code>initialize(...)</code>
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE unlinkMumble();

	/**
	 * Notifies the plugin that the data is up-to-date. commit...(...)-functions
	 * call this method at the end.
	 *
	 * This is to prevent a timeout which causes the plugin to automatically unlink.
	 * It will also re-link if the link has previously been lost ("relock").
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE commit();

	/**
	 * sets and commits the identity
	 *
	 * Notice: The identity does not need to be updated every single frame. It
	 * shouldn't change more than a few times per second if at all during a game.
	 *
	 *      see <code>setIdentity(...)</code> for details
	 *
	 * @param identity	unique id of the user in a given context
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE commitIdentity(const wchar_t identity[LINKAPI_MAX_IDENTITY_LENGTH]);

	/**
	 * get the client's identity
	 *      see <code>setIdentity(...)</code> for details
	 *
	 * @param destination the client's identity
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE getIdentity(wchar_t destination[LINKAPI_MAX_IDENTITY_LENGTH]);

	/**
	 * set the identity only
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
	 * @param identity	unique id of the user in a given context
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE setIdentity(const wchar_t identity[LINKAPI_MAX_IDENTITY_LENGTH]);

	/**
	 * sets and commits the context
	 *
	 * Notice: The context does not need to be updated every single frame. It
	 * shouldn't change more than a few times per second if at all during a game.
	 *
	 *      see <code>setContext(...)</code> for details
	 *
	 * @param context	a generic context
	 * @param contextLength	the length of the context (number of array elements)
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE commitContext(
			const unsigned char * context,
			LINKAPI_NATIVE_UINT32 contextLength);

	/**
	 * the length of the context (number of valid array elements retrieved).
	 *
	 * This cannot exceed <code>LINKAPI_MAX_CONTEXT_LENGTH</code>.
	 *
	 * @param destination the length of the current context
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE getContextLen(LINKAPI_NATIVE_UINT32* destination);

	/**
	 * getter for the client's context
	 *      see <code>setContext(...)</code> for details
	 *
	 * @param destinationForContext the client's context
	 * @param destinationForActualLength the length of the usable context
	 * @param maxContextLength the maximum length to write to at the destination
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE getContext(
			unsigned char * destinationForContext,
			LINKAPI_NATIVE_UINT32* destinationForActualLength,
			LINKAPI_NATIVE_UINT32 maxContextLength);

	/**
	 * sets the context
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
	 * @param contextLength	the length of the context (number of active array elements)
	 *                          LINKAPI_MAX_CONTEXT_LENGTH limits this number
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE setContext(
			const unsigned char * context,
			LINKAPI_NATIVE_UINT32 contextLength);

	/**
	 * sets and commits the identity AND context
	 *
	 * Notice: The identity and/or context does not need to be updated every
	 * single frame. It shouldn't change more than a few times per second if at
	 * all during a game.
	 *
	 * see <code>setIdentity(...)</code> and <code>setContext(...)</code> for detailed information
	 *
	 * @param identity	unique id of the user
	 * @param context	a generic context
	 * @param contextLength	the length of the context (number of active array elements)
	 *                          LINKAPI_MAX_CONTEXT_LENGTH limits this number
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE commitIdentityAndContext(
			const wchar_t identity[LINKAPI_MAX_IDENTITY_LENGTH],
			const unsigned char * context,
			LINKAPI_NATIVE_UINT32 contextLength);

	/**
	 * sets the identity AND context
	 *
	 * Notice: The identity and/or context does not need to be updated every
	 * single frame. It shouldn't change more than a few times per second if at
	 * all during a game.
	 *
	 * see <code>setIdentity(..)</code> and <code>setContext(..)</code> for detailed informations
	 *
	 * @param identity	unique id of the user
	 * @param context	a generic context
	 * @param contextLength	the length of the context (number of active array elements)
	 *                          LINKAPI_MAX_CONTEXT_LENGTH limits this number
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE setIdentityAndContext(
			const wchar_t identity[LINKAPI_MAX_IDENTITY_LENGTH],
			const unsigned char * context,
			LINKAPI_NATIVE_UINT32 contextLength);

	/**
	 * sets and commits the display name of the application currently linked
	 * with mumble
	 *
	 * Notice: This does not need to be updated every single frame. It shouldn't
	 * change at all during a game.
	 *
	 *      see <code>setName(...)</code> for details
	 *
	 * @param name	the display name of the application which links with mumble (i.e. L"TestLink")
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE commitName(const wchar_t name[LINKAPI_MAX_NAME_LENGTH]);

	/**
	 * the display name of the application currently linked with mumble
	 *      see <code>setName(...)</code> for details
	 * 
	 * @param destination for the application name
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE getName(wchar_t destination[LINKAPI_MAX_NAME_LENGTH]);

	/**
	 * sets only the display name of the application currently linked with mumble
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
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE setName(const wchar_t name[LINKAPI_MAX_NAME_LENGTH]);

	/**
	 * sets and commits the application's description
	 *
	 * Notice: This does not need to be updated every single frame. It shouldn't
	 * change at all during a game.
	 *
	 *      see <code>setDescription(...)</code> for details
	 *
	 * @param description	a text stating the purpose of this link
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE commitDescription(
			const wchar_t description[LINKAPI_MAX_DESCRIPTION_LENGTH]);

	/**
	 * the linked application's description
	 *      see <code>setDescription(...)</code> for details
	 * @param destination a text stating the purpose of this link
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE getDescription(wchar_t destination[LINKAPI_MAX_DESCRIPTION_LENGTH]);

	/**
	 * sets only the application's description
	 *
	 * Notice: This does not need to be updated every single frame. It shouldn't
	 * change at all during a game.
	 *
	 * this is the text to explain the plugin and its purpose
	 *
	 * @param description	a text stating the purpose of this link
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE setDescription(
			const wchar_t description[LINKAPI_MAX_DESCRIPTION_LENGTH]);

	/**
	 * updates and commits the avatar and camera vectors
	 *
	 * Notice: Mumble fetches these values 50 times a second, so please update
	 * them every frame.
	 *
	 * @param avatarPosition	Position of the avatar.
	 * @param avatarFront	Unit vector pointing out of the avatar's eyes.
	 * @param avatarTop	Unit vector pointing out of the top of the avatar's head.
	 * @param cameraPosition	Position of the camera.
	 * @param cameraFront	Unit vector pointing out of the camera's lense.
	 * @param cameraTop	Unit vector pointing out of the camera's top.
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE commitVectors(
			const float avatarPosition[3],
			const float avatarFront[3],
			const float avatarTop[3],
			const float cameraPosition[3],
			const float cameraFront[3],
			const float cameraTop[3]);

	/**
	 * sets avatar and camera vectors
	 *
	 * Notice: Mumble fetches these values 50 times a second, so please update
	 * them every frame.
	 *
	 * @param avatarPosition	Position of the avatar.
	 * @param avatarFront	Unit vector pointing out of the avatar's eyes.
	 * @param avatarTop	Unit vector pointing out of the top of the avatar's head.
	 * @param cameraPosition	Position of the camera.
	 * @param cameraFront	Unit vector pointing out of the camera's lense.
	 * @param cameraTop	Unit vector pointing out of the camera's top.
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE setVectors(
			const float avatarPosition[3],
			const float avatarFront[3],
			const float avatarTop[3],
			const float cameraPosition[3],
			const float cameraFront[3],
			const float cameraTop[3]);

	/**
	 * updates and commits avatar AND camera vectors with the same values
	 *
	 * Notice: Mumble fetches these values 50 times a second, so please update
	 * them every frame.
	 *
	 *      see <code>setVectorsAvatarAsCamera(...)</code> for details
	 *
	 * @param avatarPosition	Position of the avatar and camera.
	 * @param avatarFront	Unit vector pointing out of the camera/avatar's eyes.
	 * @param avatarTop	Unit vector pointing out of the top of the avatar's head/camera's top.
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE commitVectorsAvatarAsCamera(
			const float avatarPosition[3],
			const float avatarFront[3],
			const float avatarTop[3]);

	/**
	 * sets avatar AND camera vectors with the same values
	 *
	 * this simply reuses the given vectors for the camera
	 *
	 * short cut function to use when the camera of the game/program is not
	 * independent of the avatar
	 *
	 * Notice: Mumble fetches these values 50 times a second, so please update
	 * them every frame.
	 *
	 *      see the respective single vector setters for details
	 *
	 * @param avatarPosition	Position of the avatar and camera.
	 * @param avatarFront	Unit vector pointing out of the camera/avatar's eyes.
	 * @param avatarTop	Unit vector pointing out of the top of the avatar's head/camera's top.
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE setVectorsAvatarAsCamera(
			const float avatarPosition[3],
			const float avatarFront[3],
			const float avatarTop[3]);

	/**
	 * The position of the avatar
	 *
	 * location of the avatar or avatar's head where it is located in the 3D game world
	 *
	 * @param destination the 3D vector represented by a float array
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE getAvatarPosition(float destination[3]);

	/**
	 * sets the position of the avatar
	 *
	 * location of the avatar or avatar's head where it is located in the 3D game world
	 *
	 * Using the head's position is preferred. This in particular applies when
	 * the head is not at the origin of the avatar model coordinate space. E.g. if
	 * the origin is at the feet of the model the sound will be perceived as
	 * coming from the feet instead of the head.
	 *
	 * @param x the magnitude of the x basis vector
	 * @param y the magnitude of the y basis vector
	 * @param z the magnitude of the z basis vector
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE setAvatarPosition(float x, float y, float z);

	/**
	 * Unit vector pointing out of the avatar's eyes
	 *
	 * indicates the direction the avatar or avatar's head is pointing at
	 *
	 * @param destination the 3D vector (look vector) represented by a float array
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE getAvatarFront(float destination[3]);

	/**
	 * sets unit vector pointing out of the avatar's eyes
	 *
	 * indicates the direction the avatar or avatar's head is pointing at
	 *
	 * Note: this vector should be perpendicular to the top vector
	 *
	 * @param x the magnitude of the x basis vector
	 * @param y the magnitude of the y basis vector
	 * @param z the magnitude of the z basis vector
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE setAvatarFront(float x, float y, float z);

	/**
	 * Unit vector pointing out of the top of the avatar's head
	 *
	 * indicates the direction that the top of the avatar or
	 * avatar's head is pointing at
	 *
	 * @param destination the 3D vector (the avatar's up vector) represented by a float array
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE getAvatarTop(float destination[3]);

	/**
	 * sets unit vector pointing out of the top of the avatar's head
	 *
	 * indicates the direction that the top of the avatar or
	 * avatar's head is pointing at
	 *
	 * Note: this vector should be perpendicular to the front vector
	 *
	 * @param x the magnitude of the x basis vector
	 * @param y the magnitude of the y basis vector
	 * @param z the magnitude of the z basis vector
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE setAvatarTop(float x, float y, float z);

	/**
	 * The position of the camera
	 *
	 * location of the camera where it is located in the 3D game world
	 *
	 * @param destination the 3D vector represented by a float array
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE getCameraPosition(float destination[3]);

	/**
	 * sets the position of the camera
	 *
	 * location of the camera where it is located in the 3D game world
	 *
	 * @param x the magnitude of the x basis vector
	 * @param y the magnitude of the y basis vector
	 * @param z the magnitude of the z basis vector
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE setCameraPosition(float x, float y, float z);

	/**
	 * Unit vector pointing out of the front/lens of the camera
	 *
	 * indicates the direction the camera is pointing at
	 *
	 * @param destination the 3D vector (look vector) represented by a float array
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE getCameraFront(float destination[3]);

	/**
	 * sets unit vector pointing out of the front/lens of the camera
	 *
	 * indicates the direction the camera is pointing at
	 *
	 * Note: this vector should be perpendicular to the top vector
	 *
	 * @param x the magnitude of the x basis vector
	 * @param y the magnitude of the y basis vector
	 * @param z the magnitude of the z basis vector
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE setCameraFront(float x, float y, float z);

	/**
	 * Unit vector pointing out of the top of the camera
	 *
	 * indicates the direction that the top of the camera is pointing at
	 *
	 * @param destination the 3D vector (the camera's up vector) represented by a float array
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE getCameraTop(float destination[3]);

	/**
	 * sets unit vector pointing out of the top of the camera
	 *
	 * indicates the direction that the top of the camera is pointing at
	 *
	 * Note: this vector should be perpendicular to the front vector
	 *
	 * @param x the magnitude of the x basis vector
	 * @param y the magnitude of the y basis vector
	 * @param z the magnitude of the z basis vector
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE setCameraTop(float x, float y, float z);

	LINKAPI_API
	LINKAPI_ERROR_CODE getVersion(LINKAPI_NATIVE_UINT32* destination);

	LINKAPI_API
	LINKAPI_ERROR_CODE setVersion(LINKAPI_NATIVE_UINT32 version);

	LINKAPI_API
	LINKAPI_ERROR_CODE commitVersion(LINKAPI_NATIVE_UINT32 version);

	/**
	 * tick counter which is used to tell if updates to the shared memory occurred
	 *
	 * If this number stays the same the rest of the shared memory is not read
	 * by the link plugin and it will unlink after a certain timeout.
	 *
	 * @param destination the current tick number
	 * 
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE getTick(LINKAPI_NATIVE_DWORD* destination);

	/**
	 * sets the tick counter which is used to tell if updates to the shared memory occurred
	 *
	 * If this number stays the same the rest of the shared memory is not read
	 * by the link plugin and it will unlink after a certain timeout.
	 *
	 * If the plugin is already unlinked updating this value does not re-link,
	 * for this to happen version needs to be updated too.
	 * Use <code>commitTick(...)</code> to clean-up the linked memory and
	 * enforce a re-link.
	 *
	 * @param tick the tick number to set
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE setTick(LINKAPI_NATIVE_DWORD tick);

	/**
	 * set and commit the tick counter which is used to tell if updates to the
	 * shared memory occurred
	 *
	 * If this number stays the same the rest of the shared memory is not read
	 * by the link plugin and it will unlink after a certain timeout.
	 *
	 * @param tick the tick number to set
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE commitTick(LINKAPI_NATIVE_DWORD tick);

	/**
	 * directly manipulate the entire linked memory at once
	 *
	 * IMPORTANT: Note that you should also update tick yourself, else a timeout
	 * will occur and your data will not be read. Subsequently calling the
	 * commit()-function once will not help when tick is always set to the same
	 * value.
	 *
	 * Notice: Parts of this does not need to be updated every single frame.
	 * Please use the more directly appropriate commit...(...) functions instead.
	 *
	 * @param source data structure which is to be copied
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE setData(const LINKAPI_LINKED_MEMORY *source);

	/**
	 * the entire shared memory for direct access
	 *
	 * @param destination a pointer to a copy target of the shared memory structure
	 *
	 * @return	an error code, see <code>enum LINKAPI_ERROR_CODE</code>
	 */
	LINKAPI_API
	LINKAPI_ERROR_CODE getData(LINKAPI_LINKED_MEMORY* destination);

#    ifdef	__cplusplus
}
#    endif

#endif	/* LINKAPI_H */

