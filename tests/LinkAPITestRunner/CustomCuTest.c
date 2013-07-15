#include "CustomCuTest.h"
#include "CustomHelperFunctions.h"
#include <stdio.h>

void CuAssertPtrNotEquals_LineMsg(CuTest* tc, const char* file, int line, const char* message,
		void* expected, void* actual) {
	char buf[STRING_MAX];
	if (expected != actual) return;
	sprintf(buf, "expected pointer to not be equal but <0x%p> but was <0x%p>", expected, actual);
	CuFail_Line(tc, file, line, message, buf);
}

void CuAssertVecEquals_LineMsg(CuTest* tc, const char* file, int line, const char* message,
		float expected[VECTOR_LENGTH], float actual[VECTOR_LENGTH], int size) {
	char buf[STRING_MAX];

	int i;
	for (i = 0; i < size; i++) {
		if (expected[i] - actual[i] != 0.0) {
			sprintf(buf, "expected vector component [%d] <%f> but was <%f>", i, expected[i], actual[i]);
			CuFail_Line(tc, file, line, message, buf);
		}
	}
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
