#include "CuTest.h"
#include "CustomCuTest.h"
#include "CustomHelperFunctions.h"

#include "linkAPI.h"

#include <string.h>

/*
 * ---------------- TEST CASES -------------------------------
 */

void TestUpdaterSuite_commitUiTick(CuTest* tc) {
	LINKAPI_NATIVE_DWORD tick = 123;
	LINKAPI_NATIVE_DWORD tick2 = 125;

	LINKAPI_ERROR_CODE err = commitTick(tick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	LINKAPI_NATIVE_DWORD actual;
	err = getTick(&actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, tick, actual);
	CuAssertPtrNotEquals(tc, &tick, &actual);

	err = commitTick(tick2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	err = getTick(&actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, tick2, actual);
	CuAssertPtrNotEquals(tc, &tick2, &actual);
}

void TestUpdaterSuite_commitUiVersion(CuTest* tc) {
	LINKAPI_NATIVE_DWORD startTick;
	LINKAPI_ERROR_CODE err = getTick(&startTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);

	LINKAPI_NATIVE_UINT32 version = 321;
	LINKAPI_NATIVE_UINT32 version2 = 2;

	err = commitVersion(version);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	LINKAPI_NATIVE_UINT32 actual;
	err = getVersion(&actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, version, actual);
	CuAssertPtrNotEquals(tc, &version, &actual);
	LINKAPI_NATIVE_DWORD actualTick;
	err = getTick(&actualTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	err = commitVersion(version2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	err = getVersion(&actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, version2, actual);
	CuAssertPtrNotEquals(tc, &version2, &actual);
	err = getTick(&actualTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, startTick + 2, actualTick);
}

void TestUpdaterSuite_commitIdentity(CuTest* tc) {
	LINKAPI_NATIVE_DWORD startTick;
	LINKAPI_ERROR_CODE err = getTick(&startTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);

	wchar_t text[LINKAPI_MAX_IDENTITY_LENGTH] = L"TestIdentity\0";
	wchar_t text2[LINKAPI_MAX_IDENTITY_LENGTH] = L"SomeTotallyDifferentID\0";

	err = commitIdentity(text);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	wchar_t actual[LINKAPI_MAX_IDENTITY_LENGTH];
	memset(&actual, 0, sizeof actual);
	err = getIdentity(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, text, actual, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, text, actual);
	LINKAPI_NATIVE_DWORD actualTick;
	err = getTick(&actualTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	err = commitIdentity(text2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	memset(&actual, 0, sizeof actual);
	err = getIdentity(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, text2, actual, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, text2, actual);
	err = getTick(&actualTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, startTick + 2, actualTick);
}

void TestUpdaterSuite_commitName(CuTest* tc) {
	LINKAPI_NATIVE_DWORD startTick;
	LINKAPI_ERROR_CODE err = getTick(&startTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);

	wchar_t text[LINKAPI_MAX_NAME_LENGTH] = L"TestName\0";
	wchar_t text2[LINKAPI_MAX_NAME_LENGTH] = L"SomeTotallyDifferentNm\0";

	err = commitName(text);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	wchar_t actual[LINKAPI_MAX_NAME_LENGTH];
	memset(&actual, 0, sizeof actual);
	err = getName(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, text, actual, LINKAPI_MAX_NAME_LENGTH);
	CuAssertPtrNotEquals(tc, text, actual);
	LINKAPI_NATIVE_DWORD actualTick;
	err = getTick(&actualTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	err = commitName(text2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	memset(&actual, 0, sizeof actual);
	err = getName(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, text2, actual, LINKAPI_MAX_NAME_LENGTH);
	CuAssertPtrNotEquals(tc, text2, actual);
	err = getTick(&actualTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, startTick + 2, actualTick);
}

void TestUpdaterSuite_commitDescription(CuTest* tc) {
	LINKAPI_NATIVE_DWORD startTick;
	LINKAPI_ERROR_CODE err = getTick(&startTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);

	wchar_t text[LINKAPI_MAX_DESCRIPTION_LENGTH] = L"TestDescription\0";
	wchar_t text2[LINKAPI_MAX_DESCRIPTION_LENGTH] = L"SomeTotallyDifferentDSCRPTN\0";

	err = commitDescription(text);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	wchar_t actual[LINKAPI_MAX_DESCRIPTION_LENGTH];
	memset(&actual, 0, sizeof actual);
	err = getDescription(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, text, actual, LINKAPI_MAX_DESCRIPTION_LENGTH);
	CuAssertPtrNotEquals(tc, text, actual);
	LINKAPI_NATIVE_DWORD actualTick;
	err = getTick(&actualTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	err = commitDescription(text2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	memset(&actual, 0, sizeof actual);
	err = getDescription(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, text2, actual, LINKAPI_MAX_DESCRIPTION_LENGTH);
	CuAssertPtrNotEquals(tc, text2, actual);
	err = getTick(&actualTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, startTick + 2, actualTick);
}

void TestUpdaterSuite_commitContext(CuTest* tc) {
	LINKAPI_NATIVE_DWORD startTick;
	LINKAPI_ERROR_CODE err = getTick(&startTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);

	unsigned char text[LINKAPI_MAX_CONTEXT_LENGTH] = "TestContext\0";
	unsigned char text2[LINKAPI_MAX_CONTEXT_LENGTH] = "SomeTotallyDifferentCNTX\0";
	unsigned char text3[LINKAPI_MAX_CONTEXT_LENGTH] = "This context string is ridiculously long.\0";
	unsigned char text3Excerpt[256] = "This context\0";

	size_t len = strlen((char*) text);
	size_t len2 = strlen((char*) text2);
	size_t len3Excerpt = strlen((char*) text3Excerpt);

	err = commitContext(text, len);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	LINKAPI_NATIVE_UINT32 actualLen, actualLen2;
	err = getContextLen(&actualLen);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, len, actualLen);
	unsigned char actual[LINKAPI_MAX_CONTEXT_LENGTH];
	memset(&actual, 0, sizeof actual);
	err = getContext(actual, &actualLen2, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, actualLen, actualLen2);
	CuAssertCharArrayEquals(tc, text, actual, len);
	CuAssertPtrNotEquals(tc, text, actual);
	LINKAPI_NATIVE_DWORD actualTick;
	err = getTick(&actualTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	err = commitContext(text2, len2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	err = getContextLen(&actualLen);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, len2, actualLen);
	memset(&actual, 0, sizeof actual);
	err = getContext(actual, &actualLen2, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, actualLen, actualLen2);
	CuAssertCharArrayEquals(tc, text2, actual, len2);
	CuAssertPtrNotEquals(tc, text2, actual);
	err = getTick(&actualTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, startTick + 2, actualTick);

	err = commitContext(text3, len3Excerpt);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	err = getContextLen(&actualLen);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, len3Excerpt, actualLen);
	memset(&actual, 0, sizeof actual);
	err = getContext(actual, &actualLen2, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, actualLen, actualLen2);
	CuAssertCharArrayEquals(tc, text3Excerpt, actual, len3Excerpt);
	CuAssertPtrNotEquals(tc, text3, actual);
	err = getTick(&actualTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, startTick + 3, actualTick);

	err = commitContext(text, LINKAPI_MAX_CONTEXT_LENGTH + 10);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_CONTEXT_LENGTH_EXCEEDED, err);
	err = getContextLen(&actualLen);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, len3Excerpt, actualLen);
	memset(&actual, 0, sizeof actual);
	err = getContext(actual, &actualLen2, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, actualLen, actualLen2);
	CuAssertCharArrayEquals(tc, text3Excerpt, actual, len3Excerpt);
	CuAssertPtrNotEquals(tc, text3, actual);
	err = getTick(&actualTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, startTick + 3, actualTick);
}

void TestUpdaterSuite_commitIdentityAndContext(CuTest* tc) {
	LINKAPI_NATIVE_DWORD startTick;
	LINKAPI_ERROR_CODE err = getTick(&startTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);

	wchar_t identity[LINKAPI_MAX_IDENTITY_LENGTH] = L"TestIdentity\0";
	wchar_t identity2[LINKAPI_MAX_IDENTITY_LENGTH] = L"SomeTotallyDifferentID\0";

	unsigned char text[LINKAPI_MAX_CONTEXT_LENGTH] = "TestContext\0";
	unsigned char text2[LINKAPI_MAX_CONTEXT_LENGTH] = "SomeTotallyDifferentCNTX\0";
	unsigned char text3[LINKAPI_MAX_CONTEXT_LENGTH] = "This context string is ridiculously long.\0";
	unsigned char text3Excerpt[256] = "This context\0";

	size_t actualLen = strlen((char*) text);
	size_t actualLen2 = strlen((char*) text2);
	size_t actualLen3Excerpt = strlen((char*) text3Excerpt);

	err = commitIdentityAndContext(identity, text, actualLen);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	unsigned char actual[LINKAPI_MAX_CONTEXT_LENGTH];
	LINKAPI_NATIVE_UINT32 lengthActual;
	memset(&actual, 0, sizeof actual);
	err = getContext(actual, &lengthActual, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, actualLen, lengthActual);
	CuAssertCharArrayEquals(tc, text, actual, actualLen);
	CuAssertPtrNotEquals(tc, text, actual);
	wchar_t actualId[LINKAPI_MAX_IDENTITY_LENGTH];
	memset(&actualId, 0, sizeof actualId);
	err = getIdentity(actualId);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, identity, actualId, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, identity, actualId);
	LINKAPI_NATIVE_DWORD actualTick;
	err = getTick(&actualTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	err = commitIdentityAndContext(identity2, text2, actualLen2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	memset(&actual, 0, sizeof actual);
	err = getContext(actual, &lengthActual, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, actualLen2, lengthActual);
	CuAssertCharArrayEquals(tc, text2, actual, actualLen2);
	CuAssertPtrNotEquals(tc, text2, actual);
	memset(&actualId, 0, sizeof actualId);
	err = getIdentity(actualId);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, identity2, actualId, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, identity2, actualId);
	err = getTick(&actualTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, startTick + 2, actualTick);

	err = commitIdentityAndContext(identity, text3, actualLen3Excerpt);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	memset(&actual, 0, sizeof actual);
	err = getContext(actual, &lengthActual, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, actualLen3Excerpt, lengthActual);
	CuAssertCharArrayEquals(tc, text3Excerpt, actual, actualLen3Excerpt);
	CuAssertPtrNotEquals(tc, text3, actual);
	memset(&actualId, 0, sizeof actualId);
	err = getIdentity(actualId);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, identity, actualId, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, identity, actualId);
	err = getTick(&actualTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, startTick + 3, actualTick);
}

void TestUpdaterSuite_commitVectors(CuTest* tc) {
	LINKAPI_NATIVE_DWORD startTick;
	LINKAPI_ERROR_CODE err = getTick(&startTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);

	float avatarFront[3] = {1.1, 2.1, 3.1};
	float avatarPosition[3] = {4.1, 5.1, 6.1};
	float avatarTop [3] = {7.1, 8.1, 9.1};
	float fCameraFront [3] = {10.1, 11.1, 12.1};
	float fCameraPosition [3] = {13.1, 14.1, 15.1};
	float fCameraTop [3] = {16.1, 17.1, 18.1};


	err = commitVectors(avatarPosition, avatarFront, avatarTop, fCameraPosition, fCameraFront, fCameraTop);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	LINKAPI_NATIVE_DWORD actualTick;
	err = getTick(&actualTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	float actual[3];
	memset(&actual, 0, sizeof actual);
	err = getAvatarFront(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertFloatArrayEquals(tc, avatarFront, actual, 3);
	CuAssertPtrNotEquals(tc, avatarFront, actual);

	memset(&actual, 0, sizeof actual);
	err = getAvatarPosition(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertFloatArrayEquals(tc, avatarPosition, actual, 3);
	CuAssertPtrNotEquals(tc, avatarPosition, actual);

	memset(&actual, 0, sizeof actual);
	err = getAvatarTop(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertFloatArrayEquals(tc, avatarTop, actual, 3);
	CuAssertPtrNotEquals(tc, avatarTop, actual);


	memset(&actual, 0, sizeof actual);
	err = getCameraFront(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertFloatArrayEquals(tc, fCameraFront, actual, 3);
	CuAssertPtrNotEquals(tc, fCameraFront, actual);

	memset(&actual, 0, sizeof actual);
	err = getCameraPosition(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertFloatArrayEquals(tc, fCameraPosition, actual, 3);
	CuAssertPtrNotEquals(tc, fCameraPosition, actual);

	memset(&actual, 0, sizeof actual);
	err = getCameraTop(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertFloatArrayEquals(tc, fCameraTop, actual, 3);
	CuAssertPtrNotEquals(tc, fCameraTop, actual);
}

void TestUpdaterSuite_commitVectorsByAvatar(CuTest* tc) {
	LINKAPI_NATIVE_DWORD startTick;
	LINKAPI_ERROR_CODE err = getTick(&startTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);

	float avatarFront[3] = {1.1, 2.1, 3.1};
	float avatarPosition[3] = {4.1, 5.1, 6.1};
	float avatarTop [3] = {7.1, 8.1, 9.1};


	err = commitVectorsAvatarAsCamera(avatarPosition, avatarFront, avatarTop);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	LINKAPI_NATIVE_DWORD actualTick;
	err = getTick(&actualTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	float actual[3];
	memset(&actual, 0, sizeof actual);
	err = getAvatarFront(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertFloatArrayEquals(tc, avatarFront, actual, 3);
	CuAssertPtrNotEquals(tc, avatarFront, actual);

	memset(&actual, 0, sizeof actual);
	err = getAvatarPosition(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertFloatArrayEquals(tc, avatarPosition, actual, 3);
	CuAssertPtrNotEquals(tc, avatarPosition, actual);

	memset(&actual, 0, sizeof actual);
	err = getAvatarTop(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertFloatArrayEquals(tc, avatarTop, actual, 3);
	CuAssertPtrNotEquals(tc, avatarTop, actual);


	memset(&actual, 0, sizeof actual);
	err = getCameraFront(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertFloatArrayEquals(tc, avatarFront, actual, 3);
	CuAssertPtrNotEquals(tc, avatarFront, actual);

	memset(&actual, 0, sizeof actual);
	err = getCameraPosition(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertFloatArrayEquals(tc, avatarPosition, actual, 3);
	CuAssertPtrNotEquals(tc, avatarPosition, actual);

	memset(&actual, 0, sizeof actual);
	err = getCameraTop(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertFloatArrayEquals(tc, avatarTop, actual, 3);
	CuAssertPtrNotEquals(tc, avatarTop, actual);
}

/*
 * ---------------------------- SUITE SETUP -------------------------------
 */

/**
 * main suite assembly function
 */
CuSuite* UpdatersSuite(void) {
	CuSuite* suite = CuSuiteNew();

	LINKAPI_ERROR_CODE initError = initialize((wchar_t*) "TestName\0", (wchar_t*) "TestDescription\0", 2);
	if (initError == LINKAPI_ERROR_CODE_NO_ERROR) {


		SUITE_ADD_TEST(suite, TestUpdaterSuite_commitUiTick);
		SUITE_ADD_TEST(suite, TestUpdaterSuite_commitUiVersion);
		SUITE_ADD_TEST(suite, TestUpdaterSuite_commitIdentity);
		SUITE_ADD_TEST(suite, TestUpdaterSuite_commitName);
		SUITE_ADD_TEST(suite, TestUpdaterSuite_commitDescription);
		SUITE_ADD_TEST(suite, TestUpdaterSuite_commitContext);
		SUITE_ADD_TEST(suite, TestUpdaterSuite_commitIdentityAndContext);
		SUITE_ADD_TEST(suite, TestUpdaterSuite_commitVectors);
		SUITE_ADD_TEST(suite, TestUpdaterSuite_commitVectorsByAvatar);


	} else {
		SUITE_ADD_TEST(suite, initializationFailed);
	}


	return suite;
}