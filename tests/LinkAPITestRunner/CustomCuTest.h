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

#    define CuAssertPtrNotEquals(tc,ex,ac)          CuAssertPtrNotEquals_LineMsg((tc),__FILE__,__LINE__,NULL,(ex),(ac))
#    define CuAssertArrayEqualsVec(tc,ar,vec)       CuAssertArrayEqualsVec_LineMsg((tc),__FILE__,__LINE__,NULL,(ar),(vec))
#    define CuAssertArrayEqualsVec_Msg(tc,ms,ar,vec)       CuAssertArrayEqualsVec_LineMsg((tc),__FILE__,__LINE__,(ms),(ar),(vec))
#    define CuAssertFloatArrayEquals(tc,ex,ac,sz)   CuAssertFloatArrayEquals_LineMsg((tc),__FILE__,__LINE__,NULL,(ex),(ac),(sz))
#    define CuAssertVecEquals(tc,ex,ac)				CuAssertVecEquals_LineMsg((tc),__FILE__,__LINE__,NULL,(ex),(ac))
#    define CuAssertByteArrayEquals(tc,ex,ac,sz)	CuAssertByteArrayEquals_LineMsg((tc),__FILE__,__LINE__,NULL,(ex),(ac),(sz),0,0)
#    define CuAssertCharArrayEquals(tc,ex,ac,sz)    CuAssertByteArrayEquals_LineMsg((tc),__FILE__,__LINE__,NULL,(ex),(ac),(sz),1,0)
#    define CuAssertWCharTArrayEquals(tc,ex,ac,sz)  CuAssertByteArrayEquals_LineMsg((tc),__FILE__,__LINE__,NULL,(ex),(ac),(sz),0,1)


	void CuAssertPtrNotEquals_LineMsg(CuTest* tc, const char* file, int line, const char* message,
			void* expected, void* actual);

	void CuAssertFloatArrayEquals_LineMsg(CuTest* tc, const char* file, int line, const char* message,
			float* expected, float* actual, int size);

	void CuAssertArrayEqualsVec_LineMsg(CuTest* tc, const char* file, int line, const char* message,
			float* array, LINKAPI_VECTOR_3D* vector);

	void CuAssertVecEquals_LineMsg(CuTest* tc, const char* file, int line, const char* message,
			LINKAPI_VECTOR_3D* expected, LINKAPI_VECTOR_3D* actual);

	void CuAssertByteArrayEquals_LineMsg(CuTest* tc, const char* file, int line, const char* message,
			const void* expected, const void* actual, size_t size, int asChar, int asWCharT);

#    ifdef	__cplusplus
}
#    endif

#endif	/* CUSTOMCUTEST_H */

