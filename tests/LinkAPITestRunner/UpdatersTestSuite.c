#include "CuTest.h"
#include "CustomCuTest.h"
#include "CustomHelperFunctions.h"

#include "linkAPI.h"

/*
 * ---------------- TEST CASES -------------------------------
 */

void TestUpdaterSuite_updateUiTick(CuTest* tc) {

	NATIVE_DWORD tick = 123;
	NATIVE_DWORD tick2 = 125;

	ErrorCode err = updateUiTick(tick);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	NATIVE_DWORD actual = getUiTick();
	CuAssertIntEquals(tc, tick, actual);
	CuAssertPtrNotEquals(tc, &tick, &actual);

	err = updateUiTick(tick2);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	actual = getUiTick();
	CuAssertIntEquals(tc, tick2, actual);
	CuAssertPtrNotEquals(tc, &tick2, &actual);
}

void TestUpdaterSuite_updateUiVersion(CuTest* tc) {
	NATIVE_DWORD startTick = getUiTick();

	NATIVE_UINT32 version = 321;
	NATIVE_UINT32 version2 = 2;

	ErrorCode err = updateUiVersion(version);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	NATIVE_UINT32 actual = getUiVersion();
	CuAssertIntEquals(tc, version, actual);
	CuAssertPtrNotEquals(tc, &version, &actual);
	NATIVE_DWORD actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	err = updateUiVersion(version2);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	actual = getUiVersion();
	CuAssertIntEquals(tc, version2, actual);
	CuAssertPtrNotEquals(tc, &version2, &actual);
	actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 2, actualTick);
}

void TestUpdaterSuite_updateIdentity(CuTest* tc) {
	NATIVE_DWORD startTick = getUiTick();

	wchar_t text[MAX_IDENTITY_LENGTH] = L"TestIdentity\0";
	wchar_t text2[MAX_IDENTITY_LENGTH] = L"SomeTotallyDifferentID\0";

	ErrorCode err = updateIdentity(text);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	wchar_t* actual = getIdentity();
	CuAssertByteArrayEquals(tc, text, actual, MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, text, actual);
	NATIVE_DWORD actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	err = updateIdentity(text2);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	actual = getIdentity();
	CuAssertByteArrayEquals(tc, text2, actual, MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, text2, actual);
	actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 2, actualTick);
}

void TestUpdaterSuite_updateName(CuTest* tc) {
	NATIVE_DWORD startTick = getUiTick();

	wchar_t text[MAX_NAME_LENGTH] = L"TestName\0";
	wchar_t text2[MAX_NAME_LENGTH] = L"SomeTotallyDifferentNm\0";

	ErrorCode err = updateName(text);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	wchar_t* actual = getName();
	CuAssertByteArrayEquals(tc, text, actual, MAX_NAME_LENGTH);
	CuAssertPtrNotEquals(tc, text, actual);
	NATIVE_DWORD actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	err = updateName(text2);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	actual = getName();
	CuAssertByteArrayEquals(tc, text2, actual, MAX_NAME_LENGTH);
	CuAssertPtrNotEquals(tc, text2, actual);
	actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 2, actualTick);
}

void TestUpdaterSuite_updateDescription(CuTest* tc) {
	NATIVE_DWORD startTick = getUiTick();

	wchar_t text[MAX_DESCRIPTION_LENGTH] = L"TestDescription\0";
	wchar_t text2[MAX_DESCRIPTION_LENGTH] = L"SomeTotallyDifferentDSCRPTN\0";

	ErrorCode err = updateDescription(text);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	wchar_t* actual = getDescription();
	CuAssertByteArrayEquals(tc, text, actual, MAX_DESCRIPTION_LENGTH);
	CuAssertPtrNotEquals(tc, text, actual);
	NATIVE_DWORD actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	err = updateDescription(text2);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	actual = getDescription();
	CuAssertByteArrayEquals(tc, text2, actual, MAX_DESCRIPTION_LENGTH);
	CuAssertPtrNotEquals(tc, text2, actual);
	actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 2, actualTick);
}

void TestUpdaterSuite_updateContext(CuTest* tc) {
	NATIVE_DWORD startTick = getUiTick();

	unsigned char text[MAX_CONTEXT_LENGTH] = "TestContext\0";
	unsigned char text2[MAX_CONTEXT_LENGTH] = "SomeTotallyDifferentCNTX\0";
	unsigned char text3[MAX_CONTEXT_LENGTH] = "This context string is ridiculously long.\0";
	unsigned char text3Excerpt[256] = "This context\0";

	size_t len = strlen(text);
	size_t len2 = strlen(text2);
	size_t len3Excerpt = strlen(text3Excerpt);

	ErrorCode err = updateContext(text, len);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	NATIVE_UINT32 actualLen = getContextLen();
	CuAssertIntEquals(tc, len, actualLen);
	unsigned char* actual = getContext();
	CuAssertByteArrayEquals(tc, text, actual, len);
	CuAssertPtrNotEquals(tc, text, actual);
	NATIVE_DWORD actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	err = updateContext(text2, len2);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	actualLen = getContextLen();
	CuAssertIntEquals(tc, len2, actualLen);
	actual = getContext();
	CuAssertByteArrayEquals(tc, text2, actual, len2);
	CuAssertPtrNotEquals(tc, text2, actual);
	actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 2, actualTick);

	err = updateContext(text3, len3Excerpt);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	actualLen = getContextLen();
	CuAssertIntEquals(tc, len3Excerpt, actualLen);
	actual = getContext();
	CuAssertByteArrayEquals(tc, text3Excerpt, actual, len3Excerpt);
	CuAssertPtrNotEquals(tc, text3, actual);
	actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 3, actualTick);

	err = updateContext(text, MAX_CONTEXT_LENGTH + 10);
	CuAssertIntEquals(tc, ERROR_CODE_CONTEXT_LENGTH_EXCEEDED, err);
	actualLen = getContextLen();
	CuAssertIntEquals(tc, len3Excerpt, actualLen);
	actual = getContext();
	CuAssertByteArrayEquals(tc, text3Excerpt, actual, len3Excerpt);
	CuAssertPtrNotEquals(tc, text3, actual);
	actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 3, actualTick);
}

void TestUpdaterSuite_updateIdentityAndContext(CuTest* tc) {
	NATIVE_DWORD startTick = getUiTick();

	wchar_t identity[MAX_IDENTITY_LENGTH] = L"TestIdentity\0";
	wchar_t identity2[MAX_IDENTITY_LENGTH] = L"SomeTotallyDifferentID\0";

	unsigned char text[MAX_CONTEXT_LENGTH] = "TestContext\0";
	unsigned char text2[MAX_CONTEXT_LENGTH] = "SomeTotallyDifferentCNTX\0";
	unsigned char text3[MAX_CONTEXT_LENGTH] = "This context string is ridiculously long.\0";
	unsigned char text3Excerpt[256] = "This context\0";

	size_t actualLen = strlen(text);
	size_t actualLen2 = strlen(text2);
	size_t actualLen3Excerpt = strlen(text3Excerpt);

	ErrorCode err = updateIdentityAndContext(identity, text, actualLen);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	unsigned char* actual = getContext();
	CuAssertByteArrayEquals(tc, text, actual, actualLen);
	CuAssertPtrNotEquals(tc, text, actual);
	wchar_t* actualId = getIdentity();
	CuAssertByteArrayEquals(tc, identity, actualId, MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, identity, actualId);
	NATIVE_DWORD actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	err = updateIdentityAndContext(identity2, text2, actualLen2);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	actual = getContext();
	CuAssertByteArrayEquals(tc, text2, actual, actualLen2);
	CuAssertPtrNotEquals(tc, text2, actual);
	actualId = getIdentity();
	CuAssertByteArrayEquals(tc, identity2, actualId, MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, identity2, actualId);
	actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 2, actualTick);

	err = updateIdentityAndContext(identity, text3, actualLen3Excerpt);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	actual = getContext();
	CuAssertByteArrayEquals(tc, text3Excerpt, actual, actualLen3Excerpt);
	CuAssertPtrNotEquals(tc, text3, actual);
	actualId = getIdentity();
	CuAssertByteArrayEquals(tc, identity, actualId, MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, identity, actualId);
	actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 3, actualTick);
}

void TestUpdaterSuite_updateVectors(CuTest* tc) {
	NATIVE_DWORD startTick = getUiTick();

	float fAvatarFront[VECTOR_LENGTH] = {1.1, 2.1, 3.1};
	float fAvatarPosition[VECTOR_LENGTH] = {4.1, 5.1, 6.1};
	float fAvatarTop [VECTOR_LENGTH] = {7.1, 8.1, 9.1};
	float fCameraFront [VECTOR_LENGTH] = {10.1, 11.1, 12.1};
	float fCameraPosition [VECTOR_LENGTH] = {13.1, 14.1, 15.1};
	float fCameraTop [VECTOR_LENGTH] = {16.1, 17.1, 18.1};


	ErrorCode err = updateVectors(fAvatarPosition, fAvatarFront, fAvatarTop, fCameraPosition, fCameraFront, fCameraTop);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	NATIVE_DWORD actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	float* actual = getAvatarFront();
	CuAssertVecEquals(tc, fAvatarFront, actual, VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarFront, actual);

	actual = getAvatarPosition();
	CuAssertVecEquals(tc, fAvatarPosition, actual, VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarPosition, actual);

	actual = getAvatarTop();
	CuAssertVecEquals(tc, fAvatarTop, actual, VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarTop, actual);


	actual = getCameraFront();
	CuAssertVecEquals(tc, fCameraFront, actual, VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fCameraFront, actual);

	actual = getCameraPosition();
	CuAssertVecEquals(tc, fCameraPosition, actual, VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fCameraPosition, actual);

	actual = getCameraTop();
	CuAssertVecEquals(tc, fCameraTop, actual, VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fCameraTop, actual);
}

void TestUpdaterSuite_updateVectorsByAvatar(CuTest* tc) {
	NATIVE_DWORD startTick = getUiTick();

	float fAvatarFront[VECTOR_LENGTH] = {1.1, 2.1, 3.1};
	float fAvatarPosition[VECTOR_LENGTH] = {4.1, 5.1, 6.1};
	float fAvatarTop [VECTOR_LENGTH] = {7.1, 8.1, 9.1};


	ErrorCode err = updateVectorsByAvatar(fAvatarPosition, fAvatarFront, fAvatarTop);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	NATIVE_DWORD actualTick = getUiTick();
	CuAssertIntEquals(tc, startTick + 1, actualTick);

	float* actual = getAvatarFront();
	CuAssertVecEquals(tc, fAvatarFront, actual, VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarFront, actual);

	actual = getAvatarPosition();
	CuAssertVecEquals(tc, fAvatarPosition, actual, VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarPosition, actual);

	actual = getAvatarTop();
	CuAssertVecEquals(tc, fAvatarTop, actual, VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarTop, actual);


	actual = getCameraFront();
	CuAssertVecEquals(tc, fAvatarFront, actual, VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarFront, actual);

	actual = getCameraPosition();
	CuAssertVecEquals(tc, fAvatarPosition, actual, VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarPosition, actual);

	actual = getCameraTop();
	CuAssertVecEquals(tc, fAvatarTop, actual, VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarTop, actual);
}

/*
 * ---------------------------- SUITE SETUP -------------------------------
 */

ErrorCode initError;

/**
 * main suite assembly function
 */
CuSuite* UpdatersSuite(void) {
	CuSuite* suite = CuSuiteNew();

	initError = initialize((wchar_t*) "TestName\0", (wchar_t*) "TestDescription\0", 2);
	if (initError == ERROR_CODE_NO_ERROR) {


		SUITE_ADD_TEST(suite, TestUpdaterSuite_updateUiTick);
		SUITE_ADD_TEST(suite, TestUpdaterSuite_updateUiVersion);
		SUITE_ADD_TEST(suite, TestUpdaterSuite_updateIdentity);
		SUITE_ADD_TEST(suite, TestUpdaterSuite_updateName);
		SUITE_ADD_TEST(suite, TestUpdaterSuite_updateDescription);
		SUITE_ADD_TEST(suite, TestUpdaterSuite_updateContext);
		SUITE_ADD_TEST(suite, TestUpdaterSuite_updateIdentityAndContext);
		SUITE_ADD_TEST(suite, TestUpdaterSuite_updateVectors);
		SUITE_ADD_TEST(suite, TestUpdaterSuite_updateVectorsByAvatar);


	} else {
		SUITE_ADD_TEST(suite, initializationFailed);
	}


	return suite;
}