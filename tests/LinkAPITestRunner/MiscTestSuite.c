#include "CuTest.h"
#include "CustomCuTest.h"
#include "CustomHelperFunctions.h"

#include "LinkAPI.h"

/*
 * ---------------------------- TEST CASES -------------------------------
 */


#define INITIAL_UI_VERSION 2

void TestMiscSuite_frameworkSetupLM(CuTest* tc) {
	CuAssertPtrNotNull(tc, lm);
}

void TestMiscSuite_doUnlink(CuTest* tc) {
	LINKAPI_NATIVE_UINT32 startVersion = getVersion();
	CuAssertIntEquals(tc, startVersion, lm->version);

	unlinkMumble();
	LINKAPI_NATIVE_UINT32 actual = getVersion();
	CuAssertIntEquals(tc, actual, lm->version);
	CuAssertIntEquals(tc, LINKAPI_UI_VERSION_UNLINK, actual);
}

void TestMiscSuite_commit(CuTest* tc) {
	LINKAPI_ERROR_CODE err = setVersion(7);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	LINKAPI_NATIVE_UINT32 startVersion = getVersion();
	CuAssertIntEquals(tc, startVersion, lm->version);
	LINKAPI_NATIVE_DWORD startTick = getTick();
	CuAssertIntEquals(tc, startTick, lm->tick);

	err = commit();
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	LINKAPI_NATIVE_UINT32 actualVersion = getVersion();
	CuAssertIntEquals(tc, actualVersion, lm->version);
	CuAssertIntEquals(tc, startVersion, actualVersion);
	LINKAPI_NATIVE_UINT32 actualTick = getTick();
	CuAssertIntEquals(tc, actualTick, lm->tick);
	CuAssertIntEquals(tc, startTick + 1, actualTick);


	unlinkMumble();
	actualVersion = getVersion();
	CuAssertIntEquals(tc, actualVersion, lm->version);
	CuAssertIntEquals(tc, LINKAPI_UI_VERSION_UNLINK, actualVersion);


	err = commit();
	actualVersion = getVersion();
	CuAssertIntEquals(tc, actualVersion, lm->version);
	actualTick = getTick();
	CuAssertIntEquals(tc, actualTick, lm->tick);
	CuAssertIntEquals(tc, startTick + 2, actualTick);
	CuAssertIntEquals(tc, startVersion, actualVersion);
}

void TestMiscSuite_initializeMultipleTimes(CuTest* tc) {
	wchar_t name[LINKAPI_MAX_NAME_LENGTH] = L"Name After Reinit\0";
	wchar_t description[LINKAPI_MAX_DESCRIPTION_LENGTH] = L"Description After Reinit\0";
	LINKAPI_NATIVE_UINT32 version = 6;

	LINKAPI_ERROR_CODE err = initialize(name, description, version);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	wchar_t* actualName = getName();
	CuAssertWCharTArrayEquals(tc, lm->name, actualName, LINKAPI_MAX_NAME_LENGTH);
	CuAssertWCharTArrayEquals(tc, name, actualName, LINKAPI_MAX_NAME_LENGTH);
	CuAssertPtrNotEquals(tc, name, actualName);
	wchar_t* actualDescription = getDescription();
	CuAssertWCharTArrayEquals(tc, actualDescription, lm->description, LINKAPI_MAX_DESCRIPTION_LENGTH);
	CuAssertWCharTArrayEquals(tc, description, actualDescription, LINKAPI_MAX_DESCRIPTION_LENGTH);
	CuAssertPtrNotEquals(tc, description, actualDescription);
	LINKAPI_NATIVE_UINT32 actualVersion = getVersion();
	CuAssertIntEquals(tc, actualVersion, lm->version);
	CuAssertIntEquals(tc, version, actualVersion);


	unlinkMumble();
	actualVersion = getVersion();
	CuAssertIntEquals(tc, actualVersion, lm->version);
	CuAssertIntEquals(tc, LINKAPI_UI_VERSION_UNLINK, actualVersion);


	wchar_t name2[LINKAPI_MAX_NAME_LENGTH] = L"Completely new Name\0";
	wchar_t description2[LINKAPI_MAX_DESCRIPTION_LENGTH] = L"Completely new Description\0";
	version = 10;

	err = initialize(name2, description2, version);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	actualName = getName();
	CuAssertWCharTArrayEquals(tc, lm->name, actualName, LINKAPI_MAX_NAME_LENGTH);
	CuAssertWCharTArrayEquals(tc, name2, actualName, LINKAPI_MAX_NAME_LENGTH);
	CuAssertPtrNotEquals(tc, name2, actualName);
	actualDescription = getDescription();
	CuAssertWCharTArrayEquals(tc, lm->description, actualDescription, LINKAPI_MAX_DESCRIPTION_LENGTH);
	CuAssertWCharTArrayEquals(tc, description2, actualDescription, LINKAPI_MAX_DESCRIPTION_LENGTH);
	CuAssertPtrNotEquals(tc, description2, actualDescription);
	actualVersion = getVersion();
	CuAssertIntEquals(tc, actualVersion, lm->version);
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

	LINKAPI_ERROR_CODE initError = initialize((wchar_t*) "TestName\0", (wchar_t*) "TestDescription\0", INITIAL_UI_VERSION);
	if (initError == LINKAPI_ERROR_CODE_NO_ERROR) {

		SUITE_ADD_TEST(suite, TestMiscSuite_frameworkSetupLM);

		SUITE_ADD_TEST(suite, TestMiscSuite_doUnlink);
		SUITE_ADD_TEST(suite, TestMiscSuite_commit);
		SUITE_ADD_TEST(suite, TestMiscSuite_initializeMultipleTimes);


	} else {
		SUITE_ADD_TEST(suite, initializationFailed);
	}

	return suite;
}