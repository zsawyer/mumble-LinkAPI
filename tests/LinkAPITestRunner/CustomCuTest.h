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


#    define CuAssertPtrNotEquals(tc,ex,ac)           CuAssertPtrNotEquals_LineMsg((tc),__FILE__,__LINE__,NULL,(ex),(ac))
#    define CuAssertVecEquals(tc,ex,ac,sz)           CuAssertVecEquals_LineMsg((tc),__FILE__,__LINE__,NULL,(ex),(ac),(sz))
#    define CuAssertByteArrayEquals(tc,ex,ac,sz)           CuAssertByteArrayEquals_LineMsg((tc),__FILE__,__LINE__,NULL,(ex),(ac),(sz))


    void CuAssertPtrNotEquals_LineMsg(CuTest* tc, const char* file, int line, const char* message,
            void* expected, void* actual);

    void CuAssertVecEquals_LineMsg(CuTest* tc, const char* file, int line, const char* message,
            float expected[VECTOR_LENGTH], float actual[VECTOR_LENGTH], int size);

    void CuAssertByteArrayEquals_LineMsg(CuTest* tc, const char* file, int line, const char* message,
            const void* expected, const void* actual, size_t size);

#    ifdef	__cplusplus
}
#    endif

#endif	/* CUSTOMCUTEST_H */

