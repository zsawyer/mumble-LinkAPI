/* 
 * File:   CustomHelperFunctions.h
 * Author: zsawyer
 *
 * Created on July 13, 2013, 5:39 AM
 */

#ifndef CUSTOMHELPERFUNCTIONS_H
#    define	CUSTOMHELPERFUNCTIONS_H

#    include "CuTest.h"

#    ifdef	__cplusplus
extern "C" {
#    endif


	void initializationFailed(CuTest* tc);

	void CuStringAppendByteArray(CuString* string, char* format, const void* src, size_t size, int asChars, int asWCharT);

#    ifdef	__cplusplus
}
#    endif

#endif	/* CUSTOMHELPERFUNCTIONS_H */

