
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
