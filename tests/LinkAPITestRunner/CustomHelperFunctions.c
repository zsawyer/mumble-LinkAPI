
#include "CustomHelperFunctions.h"
#include "LinkAPI.h"
#include <stdio.h>


ErrorCode initError;

void initializationFailed(CuTest* tc) {
	char msg[1024];
	sprintf(msg, "initialization failed! code: %d", initError);
	if (initError == ERROR_CODE_WIN32_NO_HANDLE ||
			initError == ERROR_CODE_UNIX_NO_HANDLE) {

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
				CuStringAppendFormat(tmpString, format, (unsigned char) ((byte*) src)[i]);
			}
		}
	}
	CuStringAppend(string, tmpString->buffer);
}