/* Copyright (C) 2013, Niall Douglas
   modified by zsawyer <zsawyer@users.sourceforge.net>

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

#ifndef APIEXPORTHELPER_H
#    define	APIEXPORTHELPER_H


/* Generic helper definitions for shared library support */
#    if defined _WIN32 || defined __CYGWIN__
#        define LINKAPI_HELPER_DLL_IMPORT __declspec(dllimport)
#        define LINKAPI_HELPER_DLL_EXPORT __declspec(dllexport)
#        define LINKAPI_HELPER_DLL_LOCAL
#    else
#        if __GNUC__ >= 4
#            define LINKAPI_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
#            define LINKAPI_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
#            define LINKAPI_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#        else
#            define LINKAPI_HELPER_DLL_IMPORT
#            define LINKAPI_HELPER_DLL_EXPORT
#            define LINKAPI_HELPER_DLL_LOCAL
#        endif
#    endif

/*
 * Now we use the generic helper definitions above to define LINKAPI_API and LINKAPI_LOCAL.
 * LINKAPI_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
 * LINKAPI_LOCAL is used for non-api symbols.
 */
#    ifndef LINKAPI_NO_DLL /* defined if LINKAPI is compiled as a DLL */
#        ifndef LINKAPI_DLL_IMPORTS /* defined if we are building the LINKAPI DLL (instead of using it) */
#            define LINKAPI_API LINKAPI_HELPER_DLL_EXPORT
#        else
#            define LINKAPI_API LINKAPI_HELPER_DLL_IMPORT
#        endif /* LINKAPI_DLL_EXPORTS */
#        define LINKAPI_LOCAL LINKAPI_HELPER_DLL_LOCAL
#    else /* LINKAPI_DLL is not defined: this means LINKAPI is a static lib. */
#        define LINKAPI_API
#        define LINKAPI_LOCAL
#    endif /* LINKAPI_DLL */



#endif	/* APIEXPORTHELPER_H */

