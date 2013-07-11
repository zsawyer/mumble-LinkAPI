/* 
 * File:   apiHelper.h
 * Author: zsawyer
 *
 * Created on April 6, 2013, 10:31 PM
 */

#ifndef APIEXPORTHELPER_H
#define	APIEXPORTHELPER_H


// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
  #define LINKAPI_HELPER_DLL_IMPORT __declspec(dllimport)
  #define LINKAPI_HELPER_DLL_EXPORT __declspec(dllexport)
  #define LINKAPI_HELPER_DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define LINKAPI_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define LINKAPI_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define LINKAPI_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define LINKAPI_HELPER_DLL_IMPORT
    #define LINKAPI_HELPER_DLL_EXPORT
    #define LINKAPI_HELPER_DLL_LOCAL
  #endif
#endif

// Now we use the generic helper definitions above to define LINKAPI_API and LINKAPI_LOCAL.
// LINKAPI_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// LINKAPI_LOCAL is used for non-api symbols.

#ifndef LINKAPI_NO_DLL // defined if LINKAPI is compiled as a DLL
  #ifndef LINKAPI_DLL_IMPORTS // defined if we are building the LINKAPI DLL (instead of using it)
    #define LINKAPI_API LINKAPI_HELPER_DLL_EXPORT
  #else
    #define LINKAPI_API LINKAPI_HELPER_DLL_IMPORT
  #endif // LINKAPI_DLL_EXPORTS
  #define LINKAPI_LOCAL LINKAPI_HELPER_DLL_LOCAL
#else // LINKAPI_DLL is not defined: this means LINKAPI is a static lib.
  #define LINKAPI_API
  #define LINKAPI_LOCAL
#endif // LINKAPI_DLL



#endif	/* APIEXPORTHELPER_H */

