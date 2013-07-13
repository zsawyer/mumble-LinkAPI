#include "CustomCuTest.h"
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
		const void* expected, const void* actual, size_t size) {
	CuString string;
	if ((expected == NULL && actual == NULL) ||
			(expected != NULL && actual != NULL &&
			memcmp(expected, actual, size) == 0)) {
		return;
	}

	CuStringInit(&string);
	if (message != NULL) {
		CuStringAppend(&string, message);
		CuStringAppend(&string, ": ");
	}
	CuStringAppendFormat(&string, "%d bytes", size);
	CuStringAppendFormat(&string, " (%d chars)", (size / (sizeof (char))));
	CuStringAppend(&string, ": ");

	int i;
	CuStringAppend(&string, "expected \n\n<");
	for (i = 0; i < (size / (sizeof (char))); i++) {
		CuStringAppendChar(&string, ((char*) expected)[i]);
	}
	CuStringAppend(&string, ">\n\n but was \n\n<");
	for (i = 0; i < (size / (sizeof (char))); i++) {
		CuStringAppendChar(&string, ((char*) actual)[i]);
	}
	CuStringAppend(&string, ">");
	CuFail_Line(tc, file, line, "byte comparison failed", string.buffer);
}
