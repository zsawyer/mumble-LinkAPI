#include "CuTest.h"
#include "CustomCuTest.h"
#include "CustomHelperFunctions.h"

#include "linkAPI.h"

/*
 * ---------------- TEST CASES -------------------------------
 */

void TestSettersSuite_setUiTick(CuTest* tc) {

	NATIVE_DWORD tick = 123;
	NATIVE_DWORD tick2 = 125;

	ErrorCode err = setUiTick(tick);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	NATIVE_DWORD actual = getUiTick();
	CuAssertIntEquals(tc, tick, actual);
	CuAssertPtrNotEquals(tc, &tick, &actual);

	err = setUiTick(tick2);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	actual = getUiTick();
	CuAssertIntEquals(tc, tick2, actual);
	CuAssertPtrNotEquals(tc, &tick2, &actual);
}

void TestSettersSuite_setUiVersion(CuTest* tc) {

	NATIVE_UINT32 version = 321;
	NATIVE_UINT32 version2 = 2;

	ErrorCode err = setUiVersion(version);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	NATIVE_UINT32 actual = getUiVersion();
	CuAssertIntEquals(tc, version, actual);
	CuAssertPtrNotEquals(tc, &version, &actual);

	err = setUiVersion(version2);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	actual = getUiVersion();
	CuAssertIntEquals(tc, version2, actual);
	CuAssertPtrNotEquals(tc, &version2, &actual);
}

void TestSettersSuite_setIdentity(CuTest* tc) {

	wchar_t text[MAX_IDENTITY_LENGTH] = L"TestIdentity\0";
	wchar_t text2[MAX_IDENTITY_LENGTH] = L"SomeTotallyDifferentID\0";

	ErrorCode err = setIdentity(text);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	wchar_t* actual = getIdentity();
	CuAssertByteArrayEquals(tc, text, actual, MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, text, actual);

	err = setIdentity(text2);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	actual = getIdentity();
	CuAssertByteArrayEquals(tc, text2, actual, MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, text2, actual);
}

void TestSettersSuite_setName(CuTest* tc) {

	wchar_t text[MAX_NAME_LENGTH] = L"TestName\0";
	wchar_t text2[MAX_NAME_LENGTH] = L"SomeTotallyDifferentNm\0";

	ErrorCode err = setName(text);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	wchar_t* actual = getName();
	CuAssertByteArrayEquals(tc, text, actual, MAX_NAME_LENGTH);
	CuAssertPtrNotEquals(tc, text, actual);

	err = setName(text2);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	actual = getName();
	CuAssertByteArrayEquals(tc, text2, actual, MAX_NAME_LENGTH);
	CuAssertPtrNotEquals(tc, text2, actual);
}

void TestSettersSuite_setDescription(CuTest* tc) {

	wchar_t text[MAX_DESCRIPTION_LENGTH] = L"TestDescription\0";
	wchar_t text2[MAX_DESCRIPTION_LENGTH] = L"SomeTotallyDifferentDSCRPTN\0";

	ErrorCode err = setDescription(text);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	wchar_t* actual = getDescription();
	CuAssertByteArrayEquals(tc, text, actual, MAX_DESCRIPTION_LENGTH);
	CuAssertPtrNotEquals(tc, text, actual);

	err = setDescription(text2);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	actual = getDescription();
	CuAssertByteArrayEquals(tc, text2, actual, MAX_DESCRIPTION_LENGTH);
	CuAssertPtrNotEquals(tc, text2, actual);
}

void TestSettersSuite_setContext(CuTest* tc) {

	unsigned char text[MAX_CONTEXT_LENGTH] = "TestContext\0";
	unsigned char text2[MAX_CONTEXT_LENGTH] = "SomeTotallyDifferentCNTX\0";
	unsigned char text3[MAX_CONTEXT_LENGTH] = "This context string is ridiculously long.\0";
	unsigned char text3Excerpt[256] = "This context\0";

	size_t len = strlen(text);
	size_t len2 = strlen(text2);
	size_t len3Excerpt = strlen(text3Excerpt);

	ErrorCode err = setContext(text, len);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	NATIVE_UINT32 actualLen = getContextLen();
	CuAssertIntEquals(tc, len, actualLen);
	unsigned char* actual = getContext();
	CuAssertByteArrayEquals(tc, text, actual, len);
	CuAssertPtrNotEquals(tc, text, actual);

	err = setContext(text2, len2);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	actualLen = getContextLen();
	CuAssertIntEquals(tc, len2, actualLen);
	actual = getContext();
	CuAssertByteArrayEquals(tc, text2, actual, len2);
	CuAssertPtrNotEquals(tc, text2, actual);

	err = setContext(text3, len3Excerpt);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	actualLen = getContextLen();
	CuAssertIntEquals(tc, len3Excerpt, actualLen);
	actual = getContext();
	CuAssertByteArrayEquals(tc, text3Excerpt, actual, len3Excerpt);
	CuAssertPtrNotEquals(tc, text3, actual);

	err = setContext(text, MAX_CONTEXT_LENGTH + 10);
	CuAssertIntEquals(tc, ERROR_CODE_CONTEXT_LENGTH_EXCEEDED, err);
	actualLen = getContextLen();
	CuAssertIntEquals(tc, len3Excerpt, actualLen);
	actual = getContext();
	CuAssertByteArrayEquals(tc, text3Excerpt, actual, len3Excerpt);
	CuAssertPtrNotEquals(tc, text3, actual);
}

void TestSettersSuite_setIdentityAndContext(CuTest* tc) {

	wchar_t identity[MAX_IDENTITY_LENGTH] = L"TestIdentity\0";
	wchar_t identity2[MAX_IDENTITY_LENGTH] = L"SomeTotallyDifferentID\0";

	unsigned char text[MAX_CONTEXT_LENGTH] = "TestContext\0";
	unsigned char text2[MAX_CONTEXT_LENGTH] = "SomeTotallyDifferentCNTX\0";
	unsigned char text3[MAX_CONTEXT_LENGTH] = "This context string is ridiculously long.\0";
	unsigned char text3Excerpt[256] = "This context\0";

	size_t actualLen = strlen(text);
	size_t actualLen2 = strlen(text2);
	size_t actualLen3Excerpt = strlen(text3Excerpt);

	ErrorCode err = setIdentityAndContext(identity, text, actualLen);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	unsigned char* actual = getContext();
	CuAssertByteArrayEquals(tc, text, actual, actualLen);
	CuAssertPtrNotEquals(tc, text, actual);
	wchar_t* actualId = getIdentity();
	CuAssertByteArrayEquals(tc, identity, actualId, MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, identity, actualId);

	err = setIdentityAndContext(identity2, text2, actualLen2);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	actual = getContext();
	CuAssertByteArrayEquals(tc, text2, actual, actualLen2);
	CuAssertPtrNotEquals(tc, text2, actual);
	actualId = getIdentity();
	CuAssertByteArrayEquals(tc, identity2, actualId, MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, identity2, actualId);

	err = setIdentityAndContext(identity, text3, actualLen3Excerpt);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	actual = getContext();
	CuAssertByteArrayEquals(tc, text3Excerpt, actual, actualLen3Excerpt);
	CuAssertPtrNotEquals(tc, text3, actual);
	actualId = getIdentity();
	CuAssertByteArrayEquals(tc, identity, actualId, MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, identity, actualId);
}

void TestSettersSuite_setData(CuTest* tc) {
	LinkedMem data;
	data.context_len = MAX_CONTEXT_LENGTH;

	LinkedMem data2 = {
		.context = "Context From setData\0",
		.context_len = MAX_CONTEXT_LENGTH,
		.description = L"Description From setData\0",
		.fAvatarFront =
		{1.1, 2.1, 3.1},
		.fAvatarPosition =
		{4.1, 5.1, 6.1},
		.fAvatarTop =
		{7.1, 8.1, 9.1},
		.fCameraFront =
		{10.1, 11.1, 12.1},
		.fCameraPosition =
		{13.1, 14.1, 15.1},
		.fCameraTop =
		{16.1, 17.1, 18.1},
		.identity = L"Identity From setData\0",
		.name = L"Name From setData\0",
		.uiTick = 5000,
		.uiVersion = 2
	};

	size_t lmSize = sizeof (LinkedMem);

	ErrorCode err = setData(&data);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	LinkedMem* actual = getData();
	CuAssertByteArrayEquals(tc, &data, actual, lmSize);
	CuAssertPtrNotEquals(tc, &data, actual);

	err = setData(&data2);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	actual = getData();
	CuAssertByteArrayEquals(tc, &data2, actual, (sizeof (LinkedMem)));
	CuAssertPtrNotEquals(tc, &data2, actual);

	float expAF[VECTOR_LENGTH] = {1.1, 2.1, 3.1};
	CuAssertVecEquals(tc, expAF, getAvatarFront(), VECTOR_LENGTH);
	float expAP[VECTOR_LENGTH] = {4.1, 5.1, 6.1};
	CuAssertVecEquals(tc, expAP, getAvatarPosition(), VECTOR_LENGTH);
	float expAT[VECTOR_LENGTH] = {7.1, 8.1, 9.1};
	CuAssertVecEquals(tc, expAT, getAvatarTop(), VECTOR_LENGTH);


}

void TestSettersSuite_setVectors(CuTest* tc) {
	float fAvatarFront[VECTOR_LENGTH] = {1.1, 2.1, 3.1};
	float fAvatarPosition[VECTOR_LENGTH] = {4.1, 5.1, 6.1};
	float fAvatarTop [VECTOR_LENGTH] = {7.1, 8.1, 9.1};
	float fCameraFront [VECTOR_LENGTH] = {10.1, 11.1, 12.1};
	float fCameraPosition [VECTOR_LENGTH] = {13.1, 14.1, 15.1};
	float fCameraTop [VECTOR_LENGTH] = {16.1, 17.1, 18.1};


	ErrorCode err = setVectors(fAvatarPosition, fAvatarFront, fAvatarTop, fCameraPosition, fCameraFront, fCameraTop);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);

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

void TestSettersSuite_setVectorsByAvatar(CuTest* tc) {
	float fAvatarFront[VECTOR_LENGTH] = {1.1, 2.1, 3.1};
	float fAvatarPosition[VECTOR_LENGTH] = {4.1, 5.1, 6.1};
	float fAvatarTop [VECTOR_LENGTH] = {7.1, 8.1, 9.1};


	ErrorCode err = setVectorsByAvatar(fAvatarPosition, fAvatarFront, fAvatarTop);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);

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
 * --------------------------- HELPER FUNCTIONS --------------------------------
 */
typedef ErrorCode(*SetterFunction)(float x, float y, float z);
typedef float* (*GetterFunction)();

void TestSettersSuite_Helper_set(CuTest* tc, const char* name, SetterFunction setter, GetterFunction getter) {

	float x = 1.0;
	float y = 1.0 / 5.0;
	float z = 1.0 / 3.0;

	float x2 = 4.0;
	float y2 = 4.0 / 5.0;
	float z2 = 4.0 / 3.0;

	float delta = 0.0;

	ErrorCode err = (setter) (x, y, z);
	CuAssertIntEquals_Msg(tc, name, err, ERROR_CODE_NO_ERROR);
	float* actual = getter();
	CuAssertDblEquals_Msg(tc, name, x, actual[0], delta);
	CuAssertDblEquals_Msg(tc, name, y, actual[1], delta);
	CuAssertDblEquals_Msg(tc, name, z, actual[2], delta);

	err = setter(x2, y2, z2);
	CuAssertIntEquals_Msg(tc, name, err, ERROR_CODE_NO_ERROR);
	actual = getter();
	CuAssertDblEquals_Msg(tc, name, x2, actual[0], delta);
	CuAssertDblEquals_Msg(tc, name, y2, actual[1], delta);
	CuAssertDblEquals_Msg(tc, name, z2, actual[2], delta);
}


#define MAKE_TEST_CASE_FOR_XYZ_SETTER(NAME)	\
void TestSettersSuite_set ## NAME (CuTest* tc) {	\
	TestSettersSuite_Helper_set(tc, #NAME, set ## NAME , get ## NAME ); \
}

MAKE_TEST_CASE_FOR_XYZ_SETTER(AvatarFront);
MAKE_TEST_CASE_FOR_XYZ_SETTER(AvatarTop);
MAKE_TEST_CASE_FOR_XYZ_SETTER(AvatarPosition);
MAKE_TEST_CASE_FOR_XYZ_SETTER(CameraFront);
MAKE_TEST_CASE_FOR_XYZ_SETTER(CameraTop);
MAKE_TEST_CASE_FOR_XYZ_SETTER(CameraPosition);

void addVectorTests(CuSuite* suite) {

	SUITE_ADD_TEST(suite, TestSettersSuite_setAvatarFront);
	SUITE_ADD_TEST(suite, TestSettersSuite_setAvatarTop);
	SUITE_ADD_TEST(suite, TestSettersSuite_setAvatarPosition);
	SUITE_ADD_TEST(suite, TestSettersSuite_setCameraFront);
	SUITE_ADD_TEST(suite, TestSettersSuite_setCameraTop);
	SUITE_ADD_TEST(suite, TestSettersSuite_setCameraPosition);
}

/*
 * ---------------------------- SUITE SETUP -------------------------------
 */

ErrorCode initError;

/**
 * main suite assembly function
 */
CuSuite* SettersSuite(void) {
	CuSuite* suite = CuSuiteNew();

	initError = initialize((wchar_t*) "TestName\0", (wchar_t*) "TestDescription\0", 2);
	if (initError == ERROR_CODE_NO_ERROR) {

		SUITE_ADD_TEST(suite, TestSettersSuite_setUiTick);
		SUITE_ADD_TEST(suite, TestSettersSuite_setUiVersion);
		SUITE_ADD_TEST(suite, TestSettersSuite_setIdentity);
		SUITE_ADD_TEST(suite, TestSettersSuite_setName);
		SUITE_ADD_TEST(suite, TestSettersSuite_setDescription);
		SUITE_ADD_TEST(suite, TestSettersSuite_setContext);
		SUITE_ADD_TEST(suite, TestSettersSuite_setIdentityAndContext);
		SUITE_ADD_TEST(suite, TestSettersSuite_setVectors);
		SUITE_ADD_TEST(suite, TestSettersSuite_setData);
		SUITE_ADD_TEST(suite, TestSettersSuite_setVectorsByAvatar);


		addVectorTests(suite);
	} else {
		SUITE_ADD_TEST(suite, initializationFailed);
	}


	return suite;
}