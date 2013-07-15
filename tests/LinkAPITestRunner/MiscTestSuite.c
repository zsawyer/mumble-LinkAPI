#include "CuTest.h"
#include "CustomCuTest.h"
#include "CustomHelperFunctions.h"

#include "linkAPI.h"

/*
 * ---------------------------- TEST CASES -------------------------------
 */


#define INITIAL_UI_VERSION 2

void TestMiscSuite_frameworkSetupLM(CuTest* tc) {
	CuAssertPtrNotNull(tc, lm);
}

void TestMiscSuite_doUnlink(CuTest* tc) {
	NATIVE_UINT32 startVersion = getUiVersion();
	CuAssertIntEquals(tc, startVersion, lm->uiVersion);

	doUnlink();
	NATIVE_UINT32 actual = getUiVersion();
	CuAssertIntEquals(tc, actual, lm->uiVersion);
	CuAssertIntEquals(tc, UI_VERSION_UNLINK, actual);
}

void TestMiscSuite_commit(CuTest* tc) {
	ErrorCode err = setUiVersion(7);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	NATIVE_UINT32 startVersion = getUiVersion();
	CuAssertIntEquals(tc, startVersion, lm->uiVersion);
	NATIVE_DWORD startTick = getUiTick();
	CuAssertIntEquals(tc, startTick, lm->uiTick);

	err = commit();
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	NATIVE_UINT32 actualVersion = getUiVersion();
	CuAssertIntEquals(tc, actualVersion, lm->uiVersion);
	CuAssertIntEquals(tc, startVersion, actualVersion);
	NATIVE_UINT32 actualTick = getUiTick();
	CuAssertIntEquals(tc, actualTick, lm->uiTick);
	CuAssertIntEquals(tc, startTick + 1, actualTick);


	doUnlink();
	actualVersion = getUiVersion();
	CuAssertIntEquals(tc, actualVersion, lm->uiVersion);
	CuAssertIntEquals(tc, UI_VERSION_UNLINK, actualVersion);


	err = commit();
	actualVersion = getUiVersion();
	CuAssertIntEquals(tc, actualVersion, lm->uiVersion);
	actualTick = getUiTick();
	CuAssertIntEquals(tc, actualTick, lm->uiTick);
	CuAssertIntEquals(tc, startTick + 2, actualTick);
	CuAssertIntEquals(tc, startVersion, actualVersion);
}

void TestMiscSuite_initializeMultipleTimes(CuTest* tc) {
	wchar_t name[MAX_NAME_LENGTH] = L"Name After Reinit\0";
	wchar_t description[MAX_DESCRIPTION_LENGTH] = L"Description After Reinit\0";
	NATIVE_UINT32 version = 6;

	ErrorCode err = initialize(name, description, version);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	wchar_t* actualName = getName();
	CuAssertWCharTArrayEquals(tc, lm->name, actualName, MAX_NAME_LENGTH);
	CuAssertWCharTArrayEquals(tc, name, actualName, MAX_NAME_LENGTH);
	CuAssertPtrNotEquals(tc, name, actualName);
	wchar_t* actualDescription = getDescription();
	CuAssertWCharTArrayEquals(tc, actualDescription, lm->description, MAX_DESCRIPTION_LENGTH);
	CuAssertWCharTArrayEquals(tc, description, actualDescription, MAX_DESCRIPTION_LENGTH);
	CuAssertPtrNotEquals(tc, description, actualDescription);
	NATIVE_UINT32 actualVersion = getUiVersion();
	CuAssertIntEquals(tc, actualVersion, lm->uiVersion);
	CuAssertIntEquals(tc, version, actualVersion);


	doUnlink();
	actualVersion = getUiVersion();
	CuAssertIntEquals(tc, actualVersion, lm->uiVersion);
	CuAssertIntEquals(tc, UI_VERSION_UNLINK, actualVersion);


	wchar_t name2[MAX_NAME_LENGTH] = L"Completely new Name\0";
	wchar_t description2[MAX_DESCRIPTION_LENGTH] = L"Completely new Description\0";
	version = 10;

	err = initialize(name2, description2, version);
	CuAssertIntEquals(tc, ERROR_CODE_NO_ERROR, err);
	actualName = getName();
	CuAssertWCharTArrayEquals(tc, lm->name, actualName, MAX_NAME_LENGTH);
	CuAssertWCharTArrayEquals(tc, name2, actualName, MAX_NAME_LENGTH);
	CuAssertPtrNotEquals(tc, name2, actualName);
	actualDescription = getDescription();
	CuAssertWCharTArrayEquals(tc, lm->description, actualDescription, MAX_DESCRIPTION_LENGTH);
	CuAssertWCharTArrayEquals(tc, description2, actualDescription, MAX_DESCRIPTION_LENGTH);
	CuAssertPtrNotEquals(tc, description2, actualDescription);
	actualVersion = getUiVersion();
	CuAssertIntEquals(tc, actualVersion, lm->uiVersion);
	CuAssertIntEquals(tc, version, actualVersion);
}


/*
 * ---------------------------- SUITE SETUP -------------------------------
 */

/**
 * main suite assembly function
 */
CuSuite* MiscSuite(void) {
	CuSuite* suite = CuSuiteNew();

	ErrorCode initError = initialize((wchar_t*) "TestName\0", (wchar_t*) "TestDescription\0", INITIAL_UI_VERSION);
	if (initError == ERROR_CODE_NO_ERROR) {

		SUITE_ADD_TEST(suite, TestMiscSuite_frameworkSetupLM);

		SUITE_ADD_TEST(suite, TestMiscSuite_doUnlink);
		SUITE_ADD_TEST(suite, TestMiscSuite_commit);
		SUITE_ADD_TEST(suite, TestMiscSuite_initializeMultipleTimes);


	} else {
		SUITE_ADD_TEST(suite, initializationFailed);
	}

	return suite;
}