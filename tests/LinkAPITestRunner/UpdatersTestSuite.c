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
	LINKAPI_NATIVE_DWORD actual = getTick();
	CuAssertIntEquals(tc, tick, actual);
	CuAssertPtrNotEquals(tc, &tick, &actual);

	err = commitTick(tick2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	actual = getTick();
	CuAssertIntEquals(tc, tick2, actual);
	CuAssertPtrNotEquals(tc, &tick2, &actual);
}

void TestUpdaterSuite_commitUiVersion(CuTest* tc) {
	LINKAPI_NATIVE_DWORD startTick = getTick();

	LINKAPI_NATIVE_UINT32 version = 321;
	LINKAPI_NATIVE_UINT32 version2 = 2;

	LINKAPI_ERROR_CODE err = commitVersion(version);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	LINKAPI_NATIVE_UINT32 actual = getVersion();
	CuAssertIntEquals(tc, version, actual);
	CuAssertPtrNotEquals(tc, &version, &actual);
	LINKAPI_NATIVE_DWORD actualTick = getTick();
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	err = commitVersion(version2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	actual = getVersion();
	CuAssertIntEquals(tc, version2, actual);
	CuAssertPtrNotEquals(tc, &version2, &actual);
	actualTick = getTick();
	CuAssertIntEquals(tc, startTick + 2, actualTick);
}

void TestUpdaterSuite_commitIdentity(CuTest* tc) {
	LINKAPI_NATIVE_DWORD startTick = getTick();

	wchar_t text[LINKAPI_MAX_IDENTITY_LENGTH] = L"TestIdentity\0";
	wchar_t text2[LINKAPI_MAX_IDENTITY_LENGTH] = L"SomeTotallyDifferentID\0";

	LINKAPI_ERROR_CODE err = commitIdentity(text);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	wchar_t* actual = getIdentity();
	CuAssertWCharTArrayEquals(tc, text, actual, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, text, actual);
	LINKAPI_NATIVE_DWORD actualTick = getTick();
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	err = commitIdentity(text2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	actual = getIdentity();
	CuAssertWCharTArrayEquals(tc, text2, actual, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, text2, actual);
	actualTick = getTick();
	CuAssertIntEquals(tc, startTick + 2, actualTick);
}

void TestUpdaterSuite_commitName(CuTest* tc) {
	LINKAPI_NATIVE_DWORD startTick = getTick();

	wchar_t text[LINKAPI_MAX_NAME_LENGTH] = L"TestName\0";
	wchar_t text2[LINKAPI_MAX_NAME_LENGTH] = L"SomeTotallyDifferentNm\0";

	LINKAPI_ERROR_CODE err = commitName(text);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	wchar_t* actual = getName();
	CuAssertWCharTArrayEquals(tc, text, actual, LINKAPI_MAX_NAME_LENGTH);
	CuAssertPtrNotEquals(tc, text, actual);
	LINKAPI_NATIVE_DWORD actualTick = getTick();
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	err = commitName(text2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	actual = getName();
	CuAssertWCharTArrayEquals(tc, text2, actual, LINKAPI_MAX_NAME_LENGTH);
	CuAssertPtrNotEquals(tc, text2, actual);
	actualTick = getTick();
	CuAssertIntEquals(tc, startTick + 2, actualTick);
}

void TestUpdaterSuite_commitDescription(CuTest* tc) {
	LINKAPI_NATIVE_DWORD startTick = getTick();

	wchar_t text[LINKAPI_MAX_DESCRIPTION_LENGTH] = L"TestDescription\0";
	wchar_t text2[LINKAPI_MAX_DESCRIPTION_LENGTH] = L"SomeTotallyDifferentDSCRPTN\0";

	LINKAPI_ERROR_CODE err = commitDescription(text);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	wchar_t* actual = getDescription();
	CuAssertWCharTArrayEquals(tc, text, actual, LINKAPI_MAX_DESCRIPTION_LENGTH);
	CuAssertPtrNotEquals(tc, text, actual);
	LINKAPI_NATIVE_DWORD actualTick = getTick();
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	err = commitDescription(text2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	actual = getDescription();
	CuAssertWCharTArrayEquals(tc, text2, actual, LINKAPI_MAX_DESCRIPTION_LENGTH);
	CuAssertPtrNotEquals(tc, text2, actual);
	actualTick = getTick();
	CuAssertIntEquals(tc, startTick + 2, actualTick);
}

void TestUpdaterSuite_commitContext(CuTest* tc) {
	LINKAPI_NATIVE_DWORD startTick = getTick();

	unsigned char text[LINKAPI_MAX_CONTEXT_LENGTH] = "TestContext\0";
	unsigned char text2[LINKAPI_MAX_CONTEXT_LENGTH] = "SomeTotallyDifferentCNTX\0";
	unsigned char text3[LINKAPI_MAX_CONTEXT_LENGTH] = "This context string is ridiculously long.\0";
	unsigned char text3Excerpt[256] = "This context\0";

	size_t len = strlen((char*) text);
	size_t len2 = strlen((char*) text2);
	size_t len3Excerpt = strlen((char*) text3Excerpt);

	LINKAPI_ERROR_CODE err = commitContext(text, len);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	LINKAPI_NATIVE_UINT32 actualLen = getContextLen();
	CuAssertIntEquals(tc, len, actualLen);
	unsigned char* actual = getContext();
	CuAssertCharArrayEquals(tc, text, actual, len);
	CuAssertPtrNotEquals(tc, text, actual);
	LINKAPI_NATIVE_DWORD actualTick = getTick();
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	err = commitContext(text2, len2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	actualLen = getContextLen();
	CuAssertIntEquals(tc, len2, actualLen);
	actual = getContext();
	CuAssertCharArrayEquals(tc, text2, actual, len2);
	CuAssertPtrNotEquals(tc, text2, actual);
	actualTick = getTick();
	CuAssertIntEquals(tc, startTick + 2, actualTick);

	err = commitContext(text3, len3Excerpt);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	actualLen = getContextLen();
	CuAssertIntEquals(tc, len3Excerpt, actualLen);
	actual = getContext();
	CuAssertCharArrayEquals(tc, text3Excerpt, actual, len3Excerpt);
	CuAssertPtrNotEquals(tc, text3, actual);
	actualTick = getTick();
	CuAssertIntEquals(tc, startTick + 3, actualTick);

	err = commitContext(text, LINKAPI_MAX_CONTEXT_LENGTH + 10);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_CONTEXT_LENGTH_EXCEEDED, err);
	actualLen = getContextLen();
	CuAssertIntEquals(tc, len3Excerpt, actualLen);
	actual = getContext();
	CuAssertCharArrayEquals(tc, text3Excerpt, actual, len3Excerpt);
	CuAssertPtrNotEquals(tc, text3, actual);
	actualTick = getTick();
	CuAssertIntEquals(tc, startTick + 3, actualTick);
}

void TestUpdaterSuite_commitIdentityAndContext(CuTest* tc) {
	LINKAPI_NATIVE_DWORD startTick = getTick();

	wchar_t identity[LINKAPI_MAX_IDENTITY_LENGTH] = L"TestIdentity\0";
	wchar_t identity2[LINKAPI_MAX_IDENTITY_LENGTH] = L"SomeTotallyDifferentID\0";

	unsigned char text[LINKAPI_MAX_CONTEXT_LENGTH] = "TestContext\0";
	unsigned char text2[LINKAPI_MAX_CONTEXT_LENGTH] = "SomeTotallyDifferentCNTX\0";
	unsigned char text3[LINKAPI_MAX_CONTEXT_LENGTH] = "This context string is ridiculously long.\0";
	unsigned char text3Excerpt[256] = "This context\0";

	size_t actualLen = strlen((char*) text);
	size_t actualLen2 = strlen((char*) text2);
	size_t actualLen3Excerpt = strlen((char*) text3Excerpt);

	LINKAPI_ERROR_CODE err = commitIdentityAndContext(identity, text, actualLen);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	unsigned char* actual = getContext();
	CuAssertCharArrayEquals(tc, text, actual, actualLen);
	CuAssertPtrNotEquals(tc, text, actual);
	wchar_t* actualId = getIdentity();
	CuAssertWCharTArrayEquals(tc, identity, actualId, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, identity, actualId);
	LINKAPI_NATIVE_DWORD actualTick = getTick();
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	err = commitIdentityAndContext(identity2, text2, actualLen2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	actual = getContext();
	CuAssertCharArrayEquals(tc, text2, actual, actualLen2);
	CuAssertPtrNotEquals(tc, text2, actual);
	actualId = getIdentity();
	CuAssertWCharTArrayEquals(tc, identity2, actualId, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, identity2, actualId);
	actualTick = getTick();
	CuAssertIntEquals(tc, startTick + 2, actualTick);

	err = commitIdentityAndContext(identity, text3, actualLen3Excerpt);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	actual = getContext();
	CuAssertCharArrayEquals(tc, text3Excerpt, actual, actualLen3Excerpt);
	CuAssertPtrNotEquals(tc, text3, actual);
	actualId = getIdentity();
	CuAssertWCharTArrayEquals(tc, identity, actualId, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, identity, actualId);
	actualTick = getTick();
	CuAssertIntEquals(tc, startTick + 3, actualTick);
}

void TestUpdaterSuite_commitVectors(CuTest* tc) {
	LINKAPI_NATIVE_DWORD startTick = getTick();

	float avatarFront[3] = {1.1, 2.1, 3.1};
	float avatarPosition[3] = {4.1, 5.1, 6.1};
	float avatarTop [3] = {7.1, 8.1, 9.1};
	float fCameraFront [3] = {10.1, 11.1, 12.1};
	float fCameraPosition [3] = {13.1, 14.1, 15.1};
	float fCameraTop [3] = {16.1, 17.1, 18.1};


	LINKAPI_ERROR_CODE err = commitVectors(avatarPosition, avatarFront, avatarTop, fCameraPosition, fCameraFront, fCameraTop);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	LINKAPI_NATIVE_DWORD actualTick = getTick();
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	LINKAPI_VECTOR_3D* actual = getAvatarFront();
	CuAssertArrayEqualsVec(tc, avatarFront, actual);
	CuAssertPtrNotEquals(tc, avatarFront, actual);

	actual = getAvatarPosition();
	CuAssertArrayEqualsVec(tc, avatarPosition, actual);
	CuAssertPtrNotEquals(tc, avatarPosition, actual);

	actual = getAvatarTop();
	CuAssertArrayEqualsVec(tc, avatarTop, actual);
	CuAssertPtrNotEquals(tc, avatarTop, actual);


	actual = getCameraFront();
	CuAssertArrayEqualsVec(tc, fCameraFront, actual);
	CuAssertPtrNotEquals(tc, fCameraFront, actual);

	actual = getCameraPosition();
	CuAssertArrayEqualsVec(tc, fCameraPosition, actual);
	CuAssertPtrNotEquals(tc, fCameraPosition, actual);

	actual = getCameraTop();
	CuAssertArrayEqualsVec(tc, fCameraTop, actual);
	CuAssertPtrNotEquals(tc, fCameraTop, actual);
}

void TestUpdaterSuite_commitVectorsByAvatar(CuTest* tc) {
	LINKAPI_NATIVE_DWORD startTick = getTick();

	float avatarFront[3] = {1.1, 2.1, 3.1};
	float avatarPosition[3] = {4.1, 5.1, 6.1};
	float avatarTop [3] = {7.1, 8.1, 9.1};


	LINKAPI_ERROR_CODE err = commitVectorsAvatarAsCamera(avatarPosition, avatarFront, avatarTop);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	LINKAPI_NATIVE_DWORD actualTick = getTick();
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	LINKAPI_VECTOR_3D* actual = getAvatarFront();
	CuAssertArrayEqualsVec(tc, avatarFront, actual);
	CuAssertPtrNotEquals(tc, avatarFront, actual);

	actual = getAvatarPosition();
	CuAssertArrayEqualsVec(tc, avatarPosition, actual);
	CuAssertPtrNotEquals(tc, avatarPosition, actual);

	actual = getAvatarTop();
	CuAssertArrayEqualsVec(tc, avatarTop, actual);
	CuAssertPtrNotEquals(tc, avatarTop, actual);


	actual = getCameraFront();
	CuAssertArrayEqualsVec(tc, avatarFront, actual);
	CuAssertPtrNotEquals(tc, avatarFront, actual);

	actual = getCameraPosition();
	CuAssertArrayEqualsVec(tc, avatarPosition, actual);
	CuAssertPtrNotEquals(tc, avatarPosition, actual);

	actual = getCameraTop();
	CuAssertArrayEqualsVec(tc, avatarTop, actual);
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