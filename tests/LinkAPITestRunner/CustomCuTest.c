#include "CustomCuTest.h"
#include "CustomHelperFunctions.h"
#include <stdio.h>
#include <string.h>

void CuAssertPtrNotEquals_LineMsg(CuTest* tc, const char* file, int line, const char* message,
		void* expected, void* actual) {
	char buf[STRING_MAX];
	if (expected != actual) return;
	sprintf(buf, "expected pointer to not be equal but <0x%p> but was <0x%p>", expected, actual);
	CuFail_Line(tc, file, line, message, buf);
}

void CuAssertFloatArrayEquals_LineMsg(CuTest* tc, const char* file, int line, const char* message,
		float* expected, float* actual, int size) {
	char buf[STRING_MAX];

	int i;
	for (i = 0; i < size; i++) {
		if (expected[i] - actual[i] != 0.0) {
			sprintf(buf, "expected vector component [%d] <%f> but was <%f>", i, expected[i], actual[i]);
			CuFail_Line(tc, file, line, message, buf);
		}
	}
}

void CuAssertVecEquals_LineMsg(CuTest* tc, const char* file, int line, const char* message,
		LINKAPI_VECTOR_3D* expected, LINKAPI_VECTOR_3D * actual) {

	CuAssertDblEquals_LineMsg(tc, file, line, "expected vector x mismatch", expected->x, actual->x, 0);
	CuAssertDblEquals_LineMsg(tc, file, line, "expected vector y mismatch", expected->y, actual->y, 0);
	CuAssertDblEquals_LineMsg(tc, file, line, "expected vector z mismatch", expected->z, actual->z, 0);
}

void CuAssertArrayEqualsVec_LineMsg(CuTest* tc, const char* file, int line, const char* message,
		float* array, LINKAPI_VECTOR_3D * vector) {
	CuAssertDblEquals_LineMsg(tc, file, line, "array entry [0] mismatch", array[0], vector->x, 0);
	CuAssertDblEquals_LineMsg(tc, file, line, "array entry [1] mismatch", array[1], vector->y, 0);
	CuAssertDblEquals_LineMsg(tc, file, line, "array entry [2] mismatch", array[2], vector->z, 0);
}

void CuAssertByteArrayEquals_LineMsg(CuTest* tc, const char* file, int line, const char* message,
		const void* expected, const void* actual, size_t size, int asChars, int asWCharT) {
	CuString string;

	char* type;
	char* format;
	int bytes;
	if (asChars) {
		format = "%c";
		bytes = (size * (sizeof (char)));
		type = "char";
	} else if (asWCharT) {
		format = "%lc";
		bytes = (size * (sizeof (wchar_t)));
		type = "wchar_t";
	} else {
		format = "%x";
		bytes = size;
		type = "byte";
	}

	int result;
	if (expected == NULL && actual == NULL)
		return;
	if (expected != NULL && actual != NULL) {
		if (asWCharT) {
			result = wmemcmp(expected, actual, size);
		} else {
			result = memcmp(expected, actual, bytes);
		}
		if (result == 0) {
			return;
		}
	}

	CuStringInit(&string);
	CuStringAppendFormat(&string, "(memcmp: %d) ", result);
	if (message != NULL) {
		CuStringAppend(&string, message);
		CuStringAppend(&string, ": ");
	}

	CuStringAppendFormat(&string, "%d %ss (%d bytes)", size, type, bytes);
	CuStringAppend(&string, ": ");

	CuStringAppend(&string, "expected \n\n<");
	CuStringAppendByteArray(&string, format, expected, size, asChars, asWCharT);
	CuStringAppend(&string, ">\n\n but was \n\n<");
	CuStringAppendByteArray(&string, format, actual, size, asChars, asWCharT);
	CuStringAppend(&string, ">\n");

	CuFail_Line(tc, file, line, "array comparison failed", string.buffer);
}
