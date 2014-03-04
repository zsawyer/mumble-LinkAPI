#include "CuTest.h"
#include "CustomCuTest.h"
#include "CustomHelperFunctions.h"

#include "LinkAPI.h"

#include <string.h>
#include <wchar.h>

/*
 * ---------------------------- TEST CASES -------------------------------
 */


#define INITIAL_UI_VERSION 2

void TestMiscSuite_frameworkSetupLM(CuTest* tc) {
	CuAssertPtrNotNull(tc, lm);
}

void TestMiscSuite_doUnlink(CuTest* tc) {
	LINKAPI_NATIVE_UINT32 startVersion;
	LINKAPI_ERROR_CODE err = getVersion(&startVersion);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, startVersion, lm->version);

	err = unlinkMumble();
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);

	LINKAPI_NATIVE_UINT32 actual;
	err = getVersion(&actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, actual, lm->version);
	CuAssertIntEquals(tc, LINKAPI_VERSION_UNLINK, actual);
}

void TestMiscSuite_commit(CuTest* tc) {
	LINKAPI_ERROR_CODE err = setVersion(7);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	LINKAPI_NATIVE_UINT32 startVersion;
	err = getVersion(&startVersion);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, startVersion, lm->version);
	LINKAPI_NATIVE_DWORD startTick;
	err = getTick(&startTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, startTick, lm->tick);

	err = commit();
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	LINKAPI_NATIVE_UINT32 actualVersion;
	err = getVersion(&actualVersion);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, actualVersion, lm->version);
	CuAssertIntEquals(tc, startVersion, actualVersion);
	LINKAPI_NATIVE_UINT32 actualTick;
	err = getTick(&actualTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, actualTick, lm->tick);
	CuAssertIntEquals(tc, startTick + 1, actualTick);


	err = unlinkMumble();
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	err = getVersion(&actualVersion);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, actualVersion, lm->version);
	CuAssertIntEquals(tc, LINKAPI_VERSION_UNLINK, actualVersion);


	err = commit();
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	err = getVersion(&actualVersion);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, actualVersion, lm->version);
	err = getTick(&actualTick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, actualTick, lm->tick);
	CuAssertIntEquals(tc, startTick + 2, actualTick);
	CuAssertIntEquals(tc, startVersion, actualVersion);
}

void TestMiscSuite_initializeMultipleTimes(CuTest* tc) {
	wchar_t name[LINKAPI_MAX_NAME_LENGTH] = L"Name After Reinit\0";
	wchar_t description[LINKAPI_MAX_DESCRIPTION_LENGTH] = L"Description After Reinit\0";
	LINKAPI_NATIVE_UINT32 version = 6;

	wchar_t actualName[LINKAPI_MAX_NAME_LENGTH];
	wchar_t actualDescription[LINKAPI_MAX_DESCRIPTION_LENGTH];

	LINKAPI_ERROR_CODE err = initialize(name, description, version);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	memset(&actualName, 0, sizeof actualName);
	err = getName(actualName);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, lm->name, actualName, LINKAPI_MAX_NAME_LENGTH);
	CuAssertWCharTArrayEquals(tc, name, actualName, LINKAPI_MAX_NAME_LENGTH);
	CuAssertPtrNotEquals(tc, name, actualName);
	memset(&actualDescription, 0, sizeof actualDescription);
	err = getDescription(actualDescription);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, actualDescription, lm->description, LINKAPI_MAX_DESCRIPTION_LENGTH);
	CuAssertWCharTArrayEquals(tc, description, actualDescription, LINKAPI_MAX_DESCRIPTION_LENGTH);
	CuAssertPtrNotEquals(tc, description, actualDescription);
	LINKAPI_NATIVE_UINT32 actualVersion;
	err = getVersion(&actualVersion);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, actualVersion, lm->version);
	CuAssertIntEquals(tc, version, actualVersion);


	err = unlinkMumble();
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	err = getVersion(&actualVersion);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, actualVersion, lm->version);
	CuAssertIntEquals(tc, LINKAPI_VERSION_UNLINK, actualVersion);


	wchar_t name2[LINKAPI_MAX_NAME_LENGTH] = L"Completely new Name\0";
	wchar_t description2[LINKAPI_MAX_DESCRIPTION_LENGTH] = L"Completely new Description\0";
	version = 10;

	err = initialize(name2, description2, version);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	memset(&actualName, 0, sizeof actualName);
	err = getName(actualName);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, lm->name, actualName, LINKAPI_MAX_NAME_LENGTH);
	CuAssertWCharTArrayEquals(tc, name2, actualName, LINKAPI_MAX_NAME_LENGTH);
	CuAssertPtrNotEquals(tc, name2, actualName);
	memset(&actualDescription, 0, sizeof actualDescription);
	err = getDescription(actualDescription);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, lm->description, actualDescription, LINKAPI_MAX_DESCRIPTION_LENGTH);
	CuAssertWCharTArrayEquals(tc, description2, actualDescription, LINKAPI_MAX_DESCRIPTION_LENGTH);
	CuAssertPtrNotEquals(tc, description2, actualDescription);
	err = getVersion(&actualVersion);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, actualVersion, lm->version);
	CuAssertIntEquals(tc, version, actualVersion);
}

void TestMiscSuite_getContextNullAndExtendedMaxLengthTolerance(CuTest* tc) {
	unsigned char text[LINKAPI_MAX_CONTEXT_LENGTH] = "TestContext\0";
	wchar_t text2[LINKAPI_MAX_DESCRIPTION_LENGTH] = L"THIS SHOULD NOT BE HERE!\0";

	size_t len = strlen((char*) text);
	size_t len2 = wcslen(text2);

	LINKAPI_ERROR_CODE err = setDescription(text2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);

	err = setContext(text, len);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertCharArrayEquals(tc, text, lm->context, len);

	unsigned char actual[LINKAPI_MAX_CONTEXT_LENGTH * 2];

	memset(&actual, 0, sizeof actual);
	err = getContext(actual, NULL, LINKAPI_MAX_CONTEXT_LENGTH * 2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayNotEquals(tc, text2, &actual[LINKAPI_MAX_CONTEXT_LENGTH], len2);
	CuAssertCharArrayEquals(tc, text, actual, len);

	size_t cutLength = 4;
	memset(&actual, 0, sizeof actual);
	err = getContext(actual, NULL, cutLength);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertCharArrayNotEquals(tc, text, actual, len);
	CuAssertCharArrayNotEquals(tc, text, actual, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertCharArrayEquals(tc, text, actual, cutLength);
}

// TODO: test function that verifies that name, description and version are restored to the last values set before a relock (especially with setData)

/*
 * ---------------------------- SUITE SETUP -------------------------------
 */

/**
 * main suite assembly function
 */
CuSuite* MiscSuite(void) {
	CuSuite* suite = CuSuiteNew();

	LINKAPI_ERROR_CODE initError = initialize((wchar_t*) "TestName\0", (wchar_t*) "TestDescription\0", INITIAL_UI_VERSION);
	if (initError == LINKAPI_ERROR_CODE_NO_ERROR) {

		SUITE_ADD_TEST(suite, TestMiscSuite_frameworkSetupLM);

		SUITE_ADD_TEST(suite, TestMiscSuite_doUnlink);
		SUITE_ADD_TEST(suite, TestMiscSuite_commit);
		SUITE_ADD_TEST(suite, TestMiscSuite_initializeMultipleTimes);
		SUITE_ADD_TEST(suite, TestMiscSuite_getContextNullAndExtendedMaxLengthTolerance);


	} else {
		SUITE_ADD_TEST(suite, initializationFailed);
	}

	return suite;
}