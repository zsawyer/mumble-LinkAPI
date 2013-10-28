#include "CuTest.h"
#include "CustomCuTest.h"
#include "CustomHelperFunctions.h"

#include "linkAPI.h"

/*
 * ---------------- TEST CASES -------------------------------
 */

void TestUpdaterSuite_commitUiTick(CuTest* tc) {
	LINKAPI_NATIVE_DWORD tick = 123;
	LINKAPI_NATIVE_DWORD tick2 = 125;

	LINKAPI_ERROR_CODE err = commitUiTick(tick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	LINKAPI_NATIVE_DWORD actual = getUiTick();
	CuAssertIntEquals(tc, tick, actual);
	CuAssertPtrNotEquals(tc, &tick, &actual);

	err = commitUiTick(tick2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	actual = getUiTick();
	CuAssertIntEquals(tc, tick2, actual);
	CuAssertPtrNotEquals(tc, &tick2, &actual);
}

void TestUpdaterSuite_commitUiVersion(CuTest* tc) {
	LINKAPI_NATIVE_DWORD startTick = getUiTick();

	LINKAPI_NATIVE_UINT32 version = 321;
	LINKAPI_NATIVE_UINT32 version2 = 2;

	LINKAPI_ERROR_CODE err = commitUiVersion(version);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	LINKAPI_NATIVE_UINT32 actual = getUiVersion();
	CuAssertIntEquals(tc, version, actual);
	CuAssertPtrNotEquals(tc, &version, &actual);
	LINKAPI_NATIVE_DWORD actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	err = commitUiVersion(version2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	actual = getUiVersion();
	CuAssertIntEquals(tc, version2, actual);
	CuAssertPtrNotEquals(tc, &version2, &actual);
	actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 2, actualTick);
}

void TestUpdaterSuite_commitIdentity(CuTest* tc) {
	LINKAPI_NATIVE_DWORD startTick = getUiTick();

	wchar_t text[LINKAPI_MAX_IDENTITY_LENGTH] = L"TestIdentity\0";
	wchar_t text2[LINKAPI_MAX_IDENTITY_LENGTH] = L"SomeTotallyDifferentID\0";

	LINKAPI_ERROR_CODE err = commitIdentity(text);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	wchar_t* actual = getIdentity();
	CuAssertWCharTArrayEquals(tc, text, actual, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, text, actual);
	LINKAPI_NATIVE_DWORD actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	err = commitIdentity(text2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	actual = getIdentity();
	CuAssertWCharTArrayEquals(tc, text2, actual, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, text2, actual);
	actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 2, actualTick);
}

void TestUpdaterSuite_commitName(CuTest* tc) {
	LINKAPI_NATIVE_DWORD startTick = getUiTick();

	wchar_t text[LINKAPI_MAX_NAME_LENGTH] = L"TestName\0";
	wchar_t text2[LINKAPI_MAX_NAME_LENGTH] = L"SomeTotallyDifferentNm\0";

	LINKAPI_ERROR_CODE err = commitName(text);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	wchar_t* actual = getName();
	CuAssertWCharTArrayEquals(tc, text, actual, LINKAPI_MAX_NAME_LENGTH);
	CuAssertPtrNotEquals(tc, text, actual);
	LINKAPI_NATIVE_DWORD actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	err = commitName(text2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	actual = getName();
	CuAssertWCharTArrayEquals(tc, text2, actual, LINKAPI_MAX_NAME_LENGTH);
	CuAssertPtrNotEquals(tc, text2, actual);
	actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 2, actualTick);
}

void TestUpdaterSuite_commitDescription(CuTest* tc) {
	LINKAPI_NATIVE_DWORD startTick = getUiTick();

	wchar_t text[LINKAPI_MAX_DESCRIPTION_LENGTH] = L"TestDescription\0";
	wchar_t text2[LINKAPI_MAX_DESCRIPTION_LENGTH] = L"SomeTotallyDifferentDSCRPTN\0";

	LINKAPI_ERROR_CODE err = commitDescription(text);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	wchar_t* actual = getDescription();
	CuAssertWCharTArrayEquals(tc, text, actual, LINKAPI_MAX_DESCRIPTION_LENGTH);
	CuAssertPtrNotEquals(tc, text, actual);
	LINKAPI_NATIVE_DWORD actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	err = commitDescription(text2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	actual = getDescription();
	CuAssertWCharTArrayEquals(tc, text2, actual, LINKAPI_MAX_DESCRIPTION_LENGTH);
	CuAssertPtrNotEquals(tc, text2, actual);
	actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 2, actualTick);
}

void TestUpdaterSuite_commitContext(CuTest* tc) {
	LINKAPI_NATIVE_DWORD startTick = getUiTick();

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
	LINKAPI_NATIVE_DWORD actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	err = commitContext(text2, len2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	actualLen = getContextLen();
	CuAssertIntEquals(tc, len2, actualLen);
	actual = getContext();
	CuAssertCharArrayEquals(tc, text2, actual, len2);
	CuAssertPtrNotEquals(tc, text2, actual);
	actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 2, actualTick);

	err = commitContext(text3, len3Excerpt);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	actualLen = getContextLen();
	CuAssertIntEquals(tc, len3Excerpt, actualLen);
	actual = getContext();
	CuAssertCharArrayEquals(tc, text3Excerpt, actual, len3Excerpt);
	CuAssertPtrNotEquals(tc, text3, actual);
	actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 3, actualTick);

	err = commitContext(text, LINKAPI_MAX_CONTEXT_LENGTH + 10);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_CONTEXT_LENGTH_EXCEEDED, err);	
	actualLen = getContextLen();
	CuAssertIntEquals(tc, len3Excerpt, actualLen);
	actual = getContext();
	CuAssertCharArrayEquals(tc, text3Excerpt, actual, len3Excerpt);
	CuAssertPtrNotEquals(tc, text3, actual);
	actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 3, actualTick);
}

void TestUpdaterSuite_commitIdentityAndContext(CuTest* tc) {
	LINKAPI_NATIVE_DWORD startTick = getUiTick();

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
	LINKAPI_NATIVE_DWORD actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	err = commitIdentityAndContext(identity2, text2, actualLen2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	actual = getContext();
	CuAssertCharArrayEquals(tc, text2, actual, actualLen2);
	CuAssertPtrNotEquals(tc, text2, actual);
	actualId = getIdentity();
	CuAssertWCharTArrayEquals(tc, identity2, actualId, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, identity2, actualId);
	actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 2, actualTick);

	err = commitIdentityAndContext(identity, text3, actualLen3Excerpt);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	actual = getContext();
	CuAssertCharArrayEquals(tc, text3Excerpt, actual, actualLen3Excerpt);
	CuAssertPtrNotEquals(tc, text3, actual);
	actualId = getIdentity();
	CuAssertWCharTArrayEquals(tc, identity, actualId, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, identity, actualId);
	actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 3, actualTick);
}

void TestUpdaterSuite_commitVectors(CuTest* tc) {
	LINKAPI_NATIVE_DWORD startTick = getUiTick();

	float fAvatarFront[LINKAPI_VECTOR_LENGTH] = {1.1, 2.1, 3.1};
	float fAvatarPosition[LINKAPI_VECTOR_LENGTH] = {4.1, 5.1, 6.1};
	float fAvatarTop [LINKAPI_VECTOR_LENGTH] = {7.1, 8.1, 9.1};
	float fCameraFront [LINKAPI_VECTOR_LENGTH] = {10.1, 11.1, 12.1};
	float fCameraPosition [LINKAPI_VECTOR_LENGTH] = {13.1, 14.1, 15.1};
	float fCameraTop [LINKAPI_VECTOR_LENGTH] = {16.1, 17.1, 18.1};


	LINKAPI_ERROR_CODE err = commitVectors(fAvatarPosition, fAvatarFront, fAvatarTop, fCameraPosition, fCameraFront, fCameraTop);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	LINKAPI_NATIVE_DWORD actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	float* actual = getAvatarFront();
	CuAssertVecEquals(tc, fAvatarFront, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarFront, actual);

	actual = getAvatarPosition();
	CuAssertVecEquals(tc, fAvatarPosition, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarPosition, actual);

	actual = getAvatarTop();
	CuAssertVecEquals(tc, fAvatarTop, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarTop, actual);


	actual = getCameraFront();
	CuAssertVecEquals(tc, fCameraFront, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fCameraFront, actual);

	actual = getCameraPosition();
	CuAssertVecEquals(tc, fCameraPosition, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fCameraPosition, actual);

	actual = getCameraTop();
	CuAssertVecEquals(tc, fCameraTop, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fCameraTop, actual);
}

void TestUpdaterSuite_commitVectorsByAvatar(CuTest* tc) {
	LINKAPI_NATIVE_DWORD startTick = getUiTick();

	float fAvatarFront[LINKAPI_VECTOR_LENGTH] = {1.1, 2.1, 3.1};
	float fAvatarPosition[LINKAPI_VECTOR_LENGTH] = {4.1, 5.1, 6.1};
	float fAvatarTop [LINKAPI_VECTOR_LENGTH] = {7.1, 8.1, 9.1};


	LINKAPI_ERROR_CODE err = commitVectorsAvatarAsCamera(fAvatarPosition, fAvatarFront, fAvatarTop);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	LINKAPI_NATIVE_DWORD actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	float* actual = getAvatarFront();
	CuAssertVecEquals(tc, fAvatarFront, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarFront, actual);

	actual = getAvatarPosition();
	CuAssertVecEquals(tc, fAvatarPosition, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarPosition, actual);

	actual = getAvatarTop();
	CuAssertVecEquals(tc, fAvatarTop, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarTop, actual);


	actual = getCameraFront();
	CuAssertVecEquals(tc, fAvatarFront, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarFront, actual);

	actual = getCameraPosition();
	CuAssertVecEquals(tc, fAvatarPosition, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarPosition, actual);

	actual = getCameraTop();
	CuAssertVecEquals(tc, fAvatarTop, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarTop, actual);
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