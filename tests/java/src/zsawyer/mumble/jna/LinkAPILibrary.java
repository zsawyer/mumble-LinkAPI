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
package zsawyer.mumble.jna;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.NativeLibrary;
import com.sun.jna.Structure;
import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.FloatBuffer;
import java.util.Arrays;
import java.util.List;

/**
 * JNA Wrapper for library <b>LinkAPI</b><br>
 * This file was autogenerated by <a
 * href="http://jnaerator.googlecode.com/">JNAerator</a>, a tool written by <a
 * href="http://ochafik.com/">Olivier Chafik</a> that <a
 * href="http://code.google.com/p/jnaerator/wiki/CreditsAndLicense">uses a few
 * opensource projects.</a> For help, please visit <a
 * href="http://nativelibs4java.googlecode.com/">NativeLibs4Java</a> , <a
 * href="http://rococoa.dev.java.net/">Rococoa</a>, or <a
 * href="http://jna.dev.java.net/">JNA</a>.
 *
 * @author cleaned up by zsawyer, 2013
 */
public interface LinkAPILibrary extends Library {

	public static final String JNA_LIBRARY_NAME = "LinkAPI";
	public static final NativeLibrary JNA_NATIVE_LIB = NativeLibrary
			.getInstance(LinkAPILibrary.JNA_LIBRARY_NAME);
	public static final LinkAPILibrary INSTANCE = (LinkAPILibrary) Native
			.loadLibrary(LinkAPILibrary.JNA_LIBRARY_NAME, LinkAPILibrary.class);
	//
	public static final int VECTOR_LENGTH = 3;
	public static final int MAX_IDENTITY_LENGTH = 256;
	public static final int MAX_NAME_LENGTH = 256;
	public static final int MAX_CONTEXT_LENGTH = 256;
	public static final int MAX_DESCRIPTION_LENGTH = 2048;

	/**
	 * initialize the linked memory
	 * and set the name and description
	 *
	 * it corresponds to initMumble() defined here:
	 * http://mumble.sourceforge.net/Link
	 * but also sets the name and description as this should only needed to be
	 * set once
	 *
	 * @param name	       the display name of the application which links with
	 *                       mumble (i.e. L"TestLink")
	 * @param description	a text stating the purpose of this link
	 * @param uiVersion	  no description available (this should usually be set
	 *                       to 2)
	 *
	 * @return	an error code <br>
	 * 0: no error<br>
	 * 1: win32 specific: OpenFileMappingW failed to return a handle<br>
	 * 2: win32 specific: MapViewOfFile failed to return a structure<br>
	 * 3: unix specific: shm_open returned a negative integer<br>
	 * 4: unix specific: mmap failed to return a structure<br>
	 * 5: shared memory was not initialized<br>
	 *
	 * <br>
	 * Original signature :
	 * <code>int initialize(wchar_t[256], wchar_t[2048], UINT32)</code>
	 */
	int initialize(CharBuffer name, CharBuffer description, int uiVersion);

	/**
	 * update the identity only
	 *
	 * Notice: The identity does not need to be updated every single frame. It
	 * shouldn't change more than a few times per second if at all during a
	 * game.
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
	 *            memory structure was not initialized properly)
	 *
	 * <br>
	 * Original signature : <code>bool updateIdentity(wchar_t[256])</code>
	 */
	byte updateIdentity(CharBuffer identity);

	/**
	 * update the context only
	 *
	 * Notice: The context does not need to be updated every single frame. It
	 * shouldn't change more than a few times per second if at all during a
	 * game.
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
	 * @param context	    a generic context
	 * @param context_len	the length of the context (number of array elements)
	 *
	 * @return true if success else false (this would usually mean that the
	 *            memory structure was not initialized properly)
	 *
	 * <br>
	 * Original signature :
	 * <code>bool updateContext(unsigned char[256], UINT32)</code>
	 */
	byte updateContext(ByteBuffer context, int context_len);

	/**
	 * update the identity and context
	 *
	 * Notice: The identity and/or context does not need to be updated every
	 * single frame. It shouldn't change more than a few times per second if at
	 * all during a game.
	 *
	 * see updateIdentity(..) and updateContext(..) for detailed information
	 *
	 * @param identity	   unique id of the user
	 * @param context	    a generic context
	 * @param context_len	the length of the context (number of active array
	 *                       elements)
	 *
	 * @return true if success else false (this would usually mean that the
	 *            memory structure was not initialized properly)
	 *
	 * <br>
	 * Original signature :
	 * <code>bool updateIdentityAndContext(wchar_t[256], unsigned char[256], UINT32)</code>
	 */
	byte updateIdentityAndContext(CharBuffer identity, ByteBuffer context, int context_len);

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
	 * @param name	the display name of the application which links with mumble
	 *                (i.e. L"TestLink")
	 *
	 * @return true if success else false (this would usually mean that the
	 *            memory structure was not initialized properly)
	 *
	 * <br>
	 * Original signature : <code>bool updateName(wchar_t[256])</code>
	 */
	byte updateName(CharBuffer name);

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
	 *            memory structure was not initialized properly)
	 *
	 * <br>
	 * Original signature :
	 * <code>bool updateDescription(wchar_t[2048])</code>
	 */
	byte updateDescription(CharBuffer description);

	/**
	 * updates avatar and camera vectors
	 *
	 * Notice: Mumble fetches these values 50 times a second, so please update
	 * them every frame.
	 *
	 * @param fAvatarPosition	Position of the avatar.
	 * @param fAvatarFront	   Unit vector pointing out of the avatar's eyes.
	 * @param fAvatarTop	     Unit vector pointing out of the top of the
	 *                           avatar's head.
	 * @param fCameraPosition	Position of the camera.
	 * @param fCameraFront	   Unit vector pointing out of the camera's lense.
	 * @param fCameraTop	     Unit vector pointing out of the camera's top.
	 *
	 * @return true if success else false (this would usually mean that the
	 *            memory structure was not initialized properly)
	 *
	 * <br>
	 * Original signature :
	 * <code>bool updateVectors(float[3], float[3], float[3], float[3], float[3], float[3])</code>
	 */
	byte updateVectors(FloatBuffer fAvatarPosition, FloatBuffer fAvatarFront,
			FloatBuffer fAvatarTop, FloatBuffer fCameraPosition,
			FloatBuffer fCameraFront, FloatBuffer fCameraTop);

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
	 * @param fAvatarFront	   Unit vector pointing out of the camera/avatar's
	 *                           eyes.
	 * @param fAvatarTop	     Unit vector pointing out of the top of the
	 *                           avatar's head/camera's top.
	 *
	 * @return true if success else false (this would usually mean that the
	 *            memory structure was not initialized properly)
	 *
	 * <br>
	 * Original signature :
	 * <code>bool updateVectorsByAvatar(float[3], float[3], float[3])</code>
	 */
	byte updateVectorsByAvatar(FloatBuffer fAvatarPosition,
			FloatBuffer fAvatarFront, FloatBuffer fAvatarTop);

	/**
	 * a convenience function to directly manipulate the entire linked memory at
	 * once
	 *
	 * Notice: Parts of this does not need to be updated every single frame.
	 * Please use the more directly appropriate update functions instead.
	 *
	 * @param source data structure which is to be copied
	 *
	 * @return true if success else false (this would usually mean that the
	 *            memory structure was not initialized properly)
	 *
	 * <br>
	 * Original signature : <code>bool updateData(LinkedMem*)</code>
	 */
	byte updateData(LinkAPILibrary.LinkedMem source);

	/** <i>native declaration : line 89</i> */
	public static class LinkedMem extends Structure {

		/** C type : UINT32 */
		public int uiVersion;
		public int uiTick;
		/** C type : float[3] */
		public float[] fAvatarPosition = new float[VECTOR_LENGTH];
		/** C type : float[3] */
		public float[] fAvatarFront = new float[VECTOR_LENGTH];
		/** C type : float[3] */
		public float[] fAvatarTop = new float[VECTOR_LENGTH];
		/** C type : wchar_t[256] */
		public char[] name = new char[MAX_NAME_LENGTH];
		/** C type : float[3] */
		public float[] fCameraPosition = new float[VECTOR_LENGTH];
		/** C type : float[3] */
		public float[] fCameraFront = new float[VECTOR_LENGTH];
		/** C type : float[3] */
		public float[] fCameraTop = new float[VECTOR_LENGTH];
		/** C type : wchar_t[256] */
		public char[] identity = new char[MAX_IDENTITY_LENGTH];
		/** C type : UINT32 */
		public int context_len;
		/** C type : unsigned char[256] */
		public byte[] context = new byte[MAX_CONTEXT_LENGTH];
		/** C type : wchar_t[2048] */
		public char[] description = new char[MAX_DESCRIPTION_LENGTH];

		public LinkedMem() {
			super();
		}

		protected List getFieldOrder() {
			return Arrays.asList("uiVersion", "uiTick", "fAvatarPosition",
					"fAvatarFront", "fAvatarTop", "name", "fCameraPosition",
					"fCameraFront", "fCameraTop", "identity", "context_len",
					"context", "description");
		}

		public static class ByReference extends LinkedMem implements
				Structure.ByReference {
		};

		public static class ByValue extends LinkedMem implements
				Structure.ByValue {
		};
	};
}
