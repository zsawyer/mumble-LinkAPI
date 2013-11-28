
#include "CustomHelperFunctions.h"
#include "LinkAPI.h"
#include <stdio.h>


LINKAPI_ERROR_CODE initError;

void initializationFailed(CuTest* tc) {
	char msg[1024];
	sprintf(msg, "initialization failed! code: %d", initError);
	if (initError == LINKAPI_ERROR_CODE_NO_HANDLE) {

		sprintf(msg, "initialization failed! code: %d - START MUMBLE (or MumblePAHelper)!", initError);
	}

	CuFail(tc, msg);
}

void CuStringAppendByteArray(CuString* string, char* format, const void* src, size_t size, int asChars, int asWCharT) {
	CuString* tmpString = CuStringNew();

	if (src == NULL) {
		CuStringAppend(tmpString, "NULL");
	} else {
		int i;
		for (i = 0; i < size; i++) {
			if (asChars) {
				CuStringAppendFormat(tmpString, format, ((char*) src)[i]);
			} else if (asWCharT) {
				CuStringAppendFormat(tmpString, format, ((wchar_t*) src)[i]);
			} else {
				CuStringAppendFormat(tmpString, format, (unsigned char) ((unsigned char*) src)[i]);
			}
		}
	}
	CuStringAppend(string, tmpString->buffer);
}