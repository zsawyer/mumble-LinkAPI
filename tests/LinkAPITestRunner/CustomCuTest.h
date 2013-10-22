/* 
 * File:   CustomCuTest.h
 * Author: zsawyer
 *
 * Created on July 13, 2013, 5:23 AM
 */

#ifndef CUSTOMCUTEST_H
#    define	CUSTOMCUTEST_H

#    include "CuTest.h"
#    include "LinkAPI.h"

#    ifdef	__cplusplus
extern "C" {
#    endif

    extern LINKAPI_LINKED_MEMORY* lm;

#    define CuAssertPtrNotEquals(tc,ex,ac)           CuAssertPtrNotEquals_LineMsg((tc),__FILE__,__LINE__,NULL,(ex),(ac))
#    define CuAssertVecEqualsDefault(tc,ex,ac)           CuAssertVecEquals_LineMsg((tc),__FILE__,__LINE__,NULL,(ex),(ac),LINKAPI_VECTOR_LENGTH)
#    define CuAssertVecEquals(tc,ex,ac,sz)           CuAssertVecEquals_LineMsg((tc),__FILE__,__LINE__,NULL,(ex),(ac),(sz))
#    define CuAssertByteArrayEquals(tc,ex,ac,sz)           CuAssertByteArrayEquals_LineMsg((tc),__FILE__,__LINE__,NULL,(ex),(ac),(sz),0,0)
#    define CuAssertCharArrayEquals(tc,ex,ac,sz)           CuAssertByteArrayEquals_LineMsg((tc),__FILE__,__LINE__,NULL,(ex),(ac),(sz),1,0)
#    define CuAssertWCharTArrayEquals(tc,ex,ac,sz)           CuAssertByteArrayEquals_LineMsg((tc),__FILE__,__LINE__,NULL,(ex),(ac),(sz),0,1)


    void CuAssertPtrNotEquals_LineMsg(CuTest* tc, const char* file, int line, const char* message,
            void* expected, void* actual);

    void CuAssertVecEquals_LineMsg(CuTest* tc, const char* file, int line, const char* message,
            float expected[LINKAPI_VECTOR_LENGTH], float actual[LINKAPI_VECTOR_LENGTH], int size);

    void CuAssertByteArrayEquals_LineMsg(CuTest* tc, const char* file, int line, const char* message,
            const void* expected, const void* actual, size_t size, int asChar, int asWCharT);

#    ifdef	__cplusplus
}
#    endif

#endif	/* CUSTOMCUTEST_H */

