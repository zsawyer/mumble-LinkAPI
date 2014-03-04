#include "CuTest.h"
#include "CustomCuTest.h"
#include "CustomHelperFunctions.h"

#include "linkAPI.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * ---------------- TEST CASES -------------------------------
 */

void TestSettersSuite_setUiTick(CuTest* tc) {
	lm->tick = 0;
	LINKAPI_NATIVE_DWORD tick = 123;
	LINKAPI_NATIVE_DWORD tickb = 123;
	LINKAPI_NATIVE_DWORD tick2 = 125;
	LINKAPI_NATIVE_DWORD tick2b = 125;

	LINKAPI_ERROR_CODE err = setTick(tick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, tick, lm->tick);
	LINKAPI_NATIVE_DWORD actual;
	err = getTick(&actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, lm->tick, actual);
	CuAssertIntEquals(tc, tick, actual);

	err = setTick(tick2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, tick2, lm->tick);
	err = getTick(&actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, lm->tick, actual);
	CuAssertIntEquals(tc, tick2, actual);

	// verify that it is unmodified
	CuAssertIntEquals(tc, tickb, tick);
	CuAssertIntEquals(tc, tick2b, tick2);
}

void TestSettersSuite_setUiVersion(CuTest* tc) {
	lm->version = 0;
	LINKAPI_NATIVE_UINT32 version = 321;
	LINKAPI_NATIVE_UINT32 versionB = 321;
	LINKAPI_NATIVE_UINT32 version2 = 2;
	LINKAPI_NATIVE_UINT32 version2B = 2;

	LINKAPI_ERROR_CODE err = setVersion(version);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, version, lm->version);
	LINKAPI_NATIVE_UINT32 actual;
	err = getVersion(&actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, lm->version, actual);
	CuAssertIntEquals(tc, version, actual);

	err = setVersion(version2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, version2, lm->version);
	err = getVersion(&actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, version2, actual);
	CuAssertIntEquals(tc, lm->version, actual);

	// verify that it is unmodified
	CuAssertIntEquals(tc, versionB, version);
	CuAssertIntEquals(tc, version2B, version2);
}

void TestSettersSuite_setIdentity(CuTest* tc) {
	wchar_t text[LINKAPI_MAX_IDENTITY_LENGTH] = L"TestIdentity\0";
	wchar_t textB[LINKAPI_MAX_IDENTITY_LENGTH] = L"TestIdentity\0";
	wchar_t text2[LINKAPI_MAX_IDENTITY_LENGTH] = L"SomeTotallyDifferentID\0";
	wchar_t text2B[LINKAPI_MAX_IDENTITY_LENGTH] = L"SomeTotallyDifferentID\0";

	wchar_t actual[LINKAPI_MAX_IDENTITY_LENGTH];

	LINKAPI_ERROR_CODE err = setIdentity(text);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, text, lm->identity, LINKAPI_MAX_IDENTITY_LENGTH);
	memset(&actual, 0, sizeof actual);
	err = getIdentity(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, lm->identity, actual, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertWCharTArrayEquals(tc, text, actual, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, text, actual);

	err = setIdentity(text2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, text2, lm->identity, LINKAPI_MAX_IDENTITY_LENGTH);
	memset(&actual, 0, sizeof actual);
	err = getIdentity(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, lm->identity, actual, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertWCharTArrayEquals(tc, text2, actual, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, text2, actual);

	// verify that it is unmodified
	CuAssertWCharTArrayEquals(tc, textB, text, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertWCharTArrayEquals(tc, text2B, text2, LINKAPI_MAX_IDENTITY_LENGTH);
}

void TestSettersSuite_setName(CuTest* tc) {
	wchar_t text[LINKAPI_MAX_NAME_LENGTH] = L"TestName\0";
	wchar_t textB[LINKAPI_MAX_NAME_LENGTH] = L"TestName\0";
	wchar_t text2[LINKAPI_MAX_NAME_LENGTH] = L"SomeTotallyDifferentNm\0";
	wchar_t text2B[LINKAPI_MAX_NAME_LENGTH] = L"SomeTotallyDifferentNm\0";

	LINKAPI_ERROR_CODE err = setName(text);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, text, lm->name, LINKAPI_MAX_NAME_LENGTH);
	wchar_t actual[LINKAPI_MAX_NAME_LENGTH];
	memset(&actual, 0, sizeof actual);
	err = getName(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, lm->name, actual, LINKAPI_MAX_NAME_LENGTH);
	CuAssertWCharTArrayEquals(tc, text, actual, LINKAPI_MAX_NAME_LENGTH);
	CuAssertPtrNotEquals(tc, text, actual);

	err = setName(text2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, text2, lm->name, LINKAPI_MAX_NAME_LENGTH);
	CuAssertByteArrayEquals(tc, text2, lm->name, LINKAPI_MAX_NAME_LENGTH * sizeof (wchar_t));
	memset(&actual, 0, sizeof actual);
	err = getName(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, lm->name, actual, LINKAPI_MAX_NAME_LENGTH);
	CuAssertWCharTArrayEquals(tc, text2, actual, LINKAPI_MAX_NAME_LENGTH);
	CuAssertPtrNotEquals(tc, text2, actual);

	// verify that it is unmodified
	CuAssertWCharTArrayEquals(tc, textB, text, LINKAPI_MAX_NAME_LENGTH);
	CuAssertWCharTArrayEquals(tc, text2B, text2, LINKAPI_MAX_NAME_LENGTH);
}

void TestSettersSuite_setDescription(CuTest* tc) {
	wchar_t text[LINKAPI_MAX_DESCRIPTION_LENGTH] = L"TestDescription\0";
	wchar_t textB[LINKAPI_MAX_DESCRIPTION_LENGTH] = L"TestDescription\0";
	wchar_t text2[LINKAPI_MAX_DESCRIPTION_LENGTH] = L"SomeTotallyDifferentDSCRPTN\0";
	wchar_t text2B[LINKAPI_MAX_DESCRIPTION_LENGTH] = L"SomeTotallyDifferentDSCRPTN\0";

	LINKAPI_ERROR_CODE err = setDescription(text);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, lm->description, text, LINKAPI_MAX_DESCRIPTION_LENGTH);
	wchar_t actual[LINKAPI_MAX_DESCRIPTION_LENGTH];
	memset(&actual, 0, sizeof actual);
	err = getDescription(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, lm->description, actual, LINKAPI_MAX_DESCRIPTION_LENGTH);
	CuAssertWCharTArrayEquals(tc, text, actual, LINKAPI_MAX_DESCRIPTION_LENGTH);
	CuAssertPtrNotEquals(tc, text, actual);

	err = setDescription(text2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, lm->description, text2, LINKAPI_MAX_DESCRIPTION_LENGTH);
	memset(&actual, 0, sizeof actual);
	err = getDescription(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, lm->description, actual, LINKAPI_MAX_DESCRIPTION_LENGTH);
	CuAssertWCharTArrayEquals(tc, text2, actual, LINKAPI_MAX_DESCRIPTION_LENGTH);
	CuAssertPtrNotEquals(tc, text2, actual);

	// verify that it is unmodified
	CuAssertWCharTArrayEquals(tc, textB, text, LINKAPI_MAX_DESCRIPTION_LENGTH);
	CuAssertWCharTArrayEquals(tc, text2B, text2, LINKAPI_MAX_DESCRIPTION_LENGTH);
}

void TestSettersSuite_setContext(CuTest* tc) {
	unsigned char text[LINKAPI_MAX_CONTEXT_LENGTH] = "TestContext\0";
	unsigned char textB[LINKAPI_MAX_CONTEXT_LENGTH] = "TestContext\0";
	unsigned char text2[LINKAPI_MAX_CONTEXT_LENGTH] = "SomeTotallyDifferentCNTX\0";
	unsigned char text2B[LINKAPI_MAX_CONTEXT_LENGTH] = "SomeTotallyDifferentCNTX\0";
	unsigned char text3[LINKAPI_MAX_CONTEXT_LENGTH] = "This context string is ridiculously long.\0";
	unsigned char text3B[LINKAPI_MAX_CONTEXT_LENGTH] = "This context string is ridiculously long.\0";
	unsigned char text3Excerpt[256] = "This context\0";
	unsigned char text3ExcerptB[256] = "This context\0";

	size_t len = strlen((char*) text);
	size_t len2 = strlen((char*) text2);
	size_t len3Excerpt = strlen((char*) text3Excerpt);

	LINKAPI_ERROR_CODE err = setContext(text, len);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertCharArrayEquals(tc, text, lm->context, len);
	LINKAPI_NATIVE_UINT32 actualLen, actualLen2;
	err = getContextLen(&actualLen);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, lm->contextLength, actualLen);
	CuAssertIntEquals(tc, len, actualLen);
	unsigned char actual[LINKAPI_MAX_CONTEXT_LENGTH];
	memset(&actual, 0, sizeof actual);
	err = getContext(actual, &actualLen2, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, actualLen, actualLen2);
	CuAssertCharArrayEquals(tc, lm->context, actual, len);
	CuAssertCharArrayEquals(tc, text, actual, len);
	CuAssertPtrNotEquals(tc, text, actual);

	err = setContext(text2, len2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertCharArrayEquals(tc, text2, lm->context, len2);
	err = getContextLen(&actualLen);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, lm->contextLength, actualLen);
	CuAssertIntEquals(tc, len2, actualLen);
	memset(&actual, 0, sizeof actual);
	err = getContext(actual, &actualLen2, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, actualLen, actualLen2);
	CuAssertCharArrayEquals(tc, lm->context, actual, len2);
	CuAssertCharArrayEquals(tc, text2, actual, len2);
	CuAssertPtrNotEquals(tc, text2, actual);

	err = setContext(text3, len3Excerpt);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertCharArrayEquals(tc, text3, lm->context, len3Excerpt);
	err = getContextLen(&actualLen);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, lm->contextLength, actualLen);
	CuAssertIntEquals(tc, len3Excerpt, actualLen);
	memset(&actual, 0, sizeof actual);
	err = getContext(actual, &actualLen2, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, actualLen, actualLen2);
	CuAssertCharArrayEquals(tc, lm->context, actual, len3Excerpt);
	CuAssertCharArrayEquals(tc, text3Excerpt, actual, len3Excerpt);
	CuAssertPtrNotEquals(tc, text3, actual);

	err = setContext(text, LINKAPI_MAX_CONTEXT_LENGTH + 10);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_CONTEXT_LENGTH_EXCEEDED, err);
	CuAssertCharArrayEquals(tc, text3Excerpt, lm->context, len3Excerpt);
	err = getContextLen(&actualLen);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, lm->contextLength, actualLen);
	CuAssertIntEquals(tc, len3Excerpt, actualLen);
	memset(&actual, 0, sizeof actual);
	err = getContext(actual, &actualLen2, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, actualLen, actualLen2);
	CuAssertCharArrayEquals(tc, lm->context, actual, len3Excerpt);
	CuAssertCharArrayEquals(tc, text3Excerpt, actual, len3Excerpt);
	CuAssertPtrNotEquals(tc, text3, actual);

	unsigned char contextOnlyActual[LINKAPI_MAX_CONTEXT_LENGTH];
	memset(&contextOnlyActual, 0, sizeof contextOnlyActual);
	err = getContext(contextOnlyActual, NULL, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertCharArrayEquals(tc, lm->context, contextOnlyActual, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertCharArrayEquals(tc, actual, contextOnlyActual, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertPtrNotEquals(tc, actual, contextOnlyActual);

	// verify that it is unmodified
	CuAssertCharArrayEquals(tc, textB, text, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertCharArrayEquals(tc, text2B, text2, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertCharArrayEquals(tc, text3B, text3, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertCharArrayEquals(tc, text3ExcerptB, text3Excerpt, 256);
}

void TestSettersSuite_setIdentityAndContext(CuTest* tc) {
	wchar_t identity[LINKAPI_MAX_IDENTITY_LENGTH] = L"TestIdentity\0";
	wchar_t identityB[LINKAPI_MAX_IDENTITY_LENGTH] = L"TestIdentity\0";
	wchar_t identity2[LINKAPI_MAX_IDENTITY_LENGTH] = L"SomeTotallyDifferentID\0";
	wchar_t identity2B[LINKAPI_MAX_IDENTITY_LENGTH] = L"SomeTotallyDifferentID\0";

	unsigned char text[LINKAPI_MAX_CONTEXT_LENGTH] = "TestContext\0";
	unsigned char textB[LINKAPI_MAX_CONTEXT_LENGTH] = "TestContext\0";
	unsigned char text2[LINKAPI_MAX_CONTEXT_LENGTH] = "SomeTotallyDifferentCNTX\0";
	unsigned char text2B[LINKAPI_MAX_CONTEXT_LENGTH] = "SomeTotallyDifferentCNTX\0";
	unsigned char text3[LINKAPI_MAX_CONTEXT_LENGTH] = "This context string is ridiculously long.\0";
	unsigned char text3B[LINKAPI_MAX_CONTEXT_LENGTH] = "This context string is ridiculously long.\0";
	unsigned char text3Excerpt[256] = "This context\0";
	unsigned char text3ExcerptB[256] = "This context\0";

	size_t actualLen = strlen((char*) text);
	size_t actualLen2 = strlen((char*) text2);
	size_t actualLen3Excerpt = strlen((char*) text3Excerpt);

	unsigned char actual[LINKAPI_MAX_CONTEXT_LENGTH];
	LINKAPI_NATIVE_UINT32 lengthActual;
	wchar_t actualId[LINKAPI_MAX_IDENTITY_LENGTH];

	LINKAPI_ERROR_CODE err = setIdentityAndContext(identity, text, actualLen);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, identity, lm->identity, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertCharArrayEquals(tc, text, lm->context, actualLen);
	memset(&actual, 0, sizeof actual);
	err = getContext(actual, &lengthActual, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, actualLen, lengthActual);
	CuAssertCharArrayEquals(tc, lm->context, actual, actualLen);
	CuAssertCharArrayEquals(tc, text, actual, actualLen);
	CuAssertPtrNotEquals(tc, text, actual);
	memset(&actualId, 0, sizeof actualId);
	err = getIdentity(actualId);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, lm->identity, actualId, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertWCharTArrayEquals(tc, identity, actualId, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, identity, actualId);

	err = setIdentityAndContext(identity2, text2, actualLen2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, identity2, lm->identity, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertCharArrayEquals(tc, text2, lm->context, actualLen2);
	memset(&actual, 0, sizeof actual);
	err = getContext(actual, &lengthActual, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, actualLen2, lengthActual);
	CuAssertCharArrayEquals(tc, lm->context, actual, actualLen2);
	CuAssertCharArrayEquals(tc, text2, actual, actualLen2);
	CuAssertPtrNotEquals(tc, text2, actual);
	memset(&actualId, 0, sizeof actualId);
	err = getIdentity(actualId);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, lm->identity, actualId, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertWCharTArrayEquals(tc, identity2, actualId, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, identity2, actualId);

	err = setIdentityAndContext(identity, text3, actualLen3Excerpt);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, identity, lm->identity, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertCharArrayEquals(tc, text3, lm->context, actualLen3Excerpt);
	memset(&actual, 0, sizeof actual);
	err = getContext(actual, &lengthActual, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, actualLen3Excerpt, lengthActual);
	CuAssertCharArrayEquals(tc, lm->context, actual, actualLen3Excerpt);
	CuAssertCharArrayEquals(tc, text3Excerpt, actual, actualLen3Excerpt);
	CuAssertPtrNotEquals(tc, text3, actual);
	memset(&actualId, 0, sizeof actualId);
	err = getIdentity(actualId);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, lm->identity, actualId, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertWCharTArrayEquals(tc, identity, actualId, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, identity, actualId);


	// verify that it is unmodified
	CuAssertWCharTArrayEquals(tc, identityB, identity, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertWCharTArrayEquals(tc, identity2B, identity2, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertCharArrayEquals(tc, textB, text, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertCharArrayEquals(tc, text2B, text2, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertCharArrayEquals(tc, text3B, text3, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertCharArrayEquals(tc, text3ExcerptB, text3Excerpt, 256);
}

void TestSettersSuite_setData(CuTest* tc) {
	size_t lmSize = sizeof (LINKAPI_LINKED_MEMORY);
	LINKAPI_LINKED_MEMORY data;
	data.contextLength = LINKAPI_MAX_CONTEXT_LENGTH;
	LINKAPI_LINKED_MEMORY dataB;
	memcpy(&dataB, &data, lmSize);


	LINKAPI_LINKED_MEMORY data2 = {
		.context = "Context From setData\0",
		.contextLength = LINKAPI_MAX_CONTEXT_LENGTH,
		.description = L"Description From setData\0",
		.avatarFront =
		{1.1, 2.1, 3.1},
		.avatarPosition =
		{4.1, 5.1, 6.1},
		.avatarTop =
		{7.1, 8.1, 9.1},
		.cameraFront =
		{10.1, 11.1, 12.1},
		.cameraPosition =
		{13.1, 14.1, 15.1},
		.cameraTop =
		{16.1, 17.1, 18.1},
		.identity = L"Identity From setData\0",
		.name = L"Name From setData\0",
		.tick = 5000,
		.version = 2
	};

	LINKAPI_LINKED_MEMORY data2b = {
		.context = "Context From setData\0",
		.contextLength = LINKAPI_MAX_CONTEXT_LENGTH,
		.description = L"Description From setData\0",
		.avatarFront =
		{1.1, 2.1, 3.1},
		.avatarPosition =
		{4.1, 5.1, 6.1},
		.avatarTop =
		{7.1, 8.1, 9.1},
		.cameraFront =
		{10.1, 11.1, 12.1},
		.cameraPosition =
		{13.1, 14.1, 15.1},
		.cameraTop =
		{16.1, 17.1, 18.1},
		.identity = L"Identity From setData\0",
		.name = L"Name From setData\0",
		.tick = 5000,
		.version = 2
	};

	LINKAPI_ERROR_CODE err = setData(&data);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertByteArrayEquals(tc, &data, lm, lmSize);
	LINKAPI_LINKED_MEMORY* actual = malloc(sizeof (LINKAPI_LINKED_MEMORY));
	memset(actual, 0, sizeof (LINKAPI_LINKED_MEMORY));
	err = getData(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertByteArrayEquals(tc, lm, actual, lmSize);
	CuAssertByteArrayEquals(tc, &data, actual, lmSize);
	CuAssertPtrNotEquals(tc, &data, actual);

	err = setData(&data2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertByteArrayEquals(tc, &data2, lm, lmSize);
	memset(actual, 0, sizeof (LINKAPI_LINKED_MEMORY));
	err = getData(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertByteArrayEquals(tc, lm, actual, lmSize);
	CuAssertByteArrayEquals(tc, &data2, actual, lmSize);
	CuAssertPtrNotEquals(tc, &data2, actual);

	float actualVector[3];
	float expAF[3] = {1.1, 2.1, 3.1};
	memset(&actualVector, 0, sizeof actualVector);
	err = getAvatarFront(actualVector);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertFloatArrayEquals(tc, expAF, actualVector, 3);
	float expAP[3] = {4.1, 5.1, 6.1};
	memset(&actualVector, 0, sizeof actualVector);
	err = getAvatarPosition(actualVector);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertFloatArrayEquals(tc, expAP, actualVector, 3);
	float expAT[3] = {7.1, 8.1, 9.1};
	memset(&actualVector, 0, sizeof actualVector);
	err = getAvatarTop(actualVector);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertFloatArrayEquals(tc, expAT, actualVector, 3);

	// verify that it is unmodified
	CuAssertByteArrayEquals(tc, &dataB, &data, lmSize);
	CuAssertByteArrayEquals(tc, &data2b, &data2, lmSize);
}

void TestSettersSuite_setVectors(CuTest* tc) {
	float avatarFront [3] = {1.1, 2.1, 3.1};
	float avatarFrontB[3] = {1.1, 2.1, 3.1};
	float avatarPosition [3] = {4.1, 5.1, 6.1};
	float avatarPositionB[3] = {4.1, 5.1, 6.1};
	float avatarTop [3] = {7.1, 8.1, 9.1};
	float avatarTopB[3] = {7.1, 8.1, 9.1};
	float cameraFront [3] = {10.1, 11.1, 12.1};
	float cameraFrontB[3] = {10.1, 11.1, 12.1};
	float cameraPosition [3] = {13.1, 14.1, 15.1};
	float cameraPositionB[3] = {13.1, 14.1, 15.1};
	float cameraTop [3] = {16.1, 17.1, 18.1};
	float cameraTopB[3] = {16.1, 17.1, 18.1};


	LINKAPI_ERROR_CODE err = setVectors(avatarPosition, avatarFront, avatarTop, cameraPosition, cameraFront, cameraTop);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertFloatArrayEquals(tc, avatarPosition, lm->avatarPosition, 3);
	CuAssertFloatArrayEquals(tc, avatarFront, lm->avatarFront, 3);
	CuAssertFloatArrayEquals(tc, avatarTop, lm->avatarTop, 3);

	CuAssertFloatArrayEquals(tc, cameraPosition, lm->cameraPosition, 3);
	CuAssertFloatArrayEquals(tc, cameraFront, lm->cameraFront, 3);
	CuAssertFloatArrayEquals(tc, cameraTop, lm->cameraTop, 3);

	float actual[3];
	memset(&actual, 0, sizeof actual);
	err = getAvatarFront(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertFloatArrayEquals(tc, lm->avatarFront, actual, 3);
	CuAssertFloatArrayEquals(tc, avatarFront, actual, 3);
	CuAssertPtrNotEquals(tc, avatarFront, actual);

	memset(&actual, 0, sizeof actual);
	err = getAvatarPosition(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertFloatArrayEquals(tc, lm->avatarPosition, actual, 3);
	CuAssertFloatArrayEquals(tc, avatarPosition, actual, 3);
	CuAssertPtrNotEquals(tc, avatarPosition, actual);

	memset(&actual, 0, sizeof actual);
	err = getAvatarTop(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertFloatArrayEquals(tc, lm->avatarTop, actual, 3);
	CuAssertFloatArrayEquals(tc, avatarTop, actual, 3);
	CuAssertPtrNotEquals(tc, avatarTop, actual);


	memset(&actual, 0, sizeof actual);
	err = getCameraFront(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertFloatArrayEquals(tc, lm->cameraFront, actual, 3);
	CuAssertFloatArrayEquals(tc, cameraFront, actual, 3);
	CuAssertPtrNotEquals(tc, cameraFront, actual);

	memset(&actual, 0, sizeof actual);
	err = getCameraPosition(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertFloatArrayEquals(tc, lm->cameraPosition, actual, 3);
	CuAssertFloatArrayEquals(tc, cameraPosition, actual, 3);
	CuAssertPtrNotEquals(tc, cameraPosition, actual);

	memset(&actual, 0, sizeof actual);
	err = getCameraTop(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertFloatArrayEquals(tc, lm->cameraTop, actual, 3);
	CuAssertFloatArrayEquals(tc, cameraTop, actual, 3);
	CuAssertPtrNotEquals(tc, cameraTop, actual);


	// verify that it is unmodified
	CuAssertFloatArrayEquals(tc, avatarFrontB, avatarFront, 3);
	CuAssertFloatArrayEquals(tc, avatarPositionB, avatarPosition, 3);
	CuAssertFloatArrayEquals(tc, avatarTopB, avatarTop, 3);
	CuAssertFloatArrayEquals(tc, cameraFrontB, cameraFront, 3);
	CuAssertFloatArrayEquals(tc, cameraPositionB, cameraPosition, 3);
	CuAssertFloatArrayEquals(tc, cameraTopB, cameraTop, 3);
}

void TestSettersSuite_setVectorsByAvatar(CuTest* tc) {
	float avatarFront [3] = {1.1, 2.1, 3.1};
	float avatarFrontB[3] = {1.1, 2.1, 3.1};
	float avatarPosition [3] = {4.1, 5.1, 6.1};
	float avatarPositionB[3] = {4.1, 5.1, 6.1};
	float avatarTop [3] = {7.1, 8.1, 9.1};
	float avatarTopB[3] = {7.1, 8.1, 9.1};


	LINKAPI_ERROR_CODE err = setVectorsAvatarAsCamera(avatarPosition, avatarFront, avatarTop);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);

	float actual[3];
	memset(&actual, 0, sizeof actual);
	err = getAvatarFront(actual);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertFloatArrayEquals(tc, lm->avatarFront, actual, 3);
	CuAssertFloatArrayEquals(tc, avatarFront, actual, 3);
	CuAssertPtrNotEquals(tc, avatarFront, actual);

	memset(&actual, 0, sizeof actual);
	err = getAvatarPosition(actual);
	CuAssertFloatArrayEquals(tc, lm->avatarPosition, actual, 3);
	CuAssertFloatArrayEquals(tc, avatarPosition, actual, 3);
	CuAssertPtrNotEquals(tc, avatarPosition, actual);

	memset(&actual, 0, sizeof actual);
	err = getAvatarTop(actual);
	CuAssertFloatArrayEquals(tc, lm->avatarTop, actual, 3);
	CuAssertFloatArrayEquals(tc, avatarTop, actual, 3);
	CuAssertPtrNotEquals(tc, avatarTop, actual);


	memset(&actual, 0, sizeof actual);
	err = getCameraFront(actual);
	CuAssertFloatArrayEquals(tc, lm->avatarFront, actual, 3);
	CuAssertFloatArrayEquals(tc, avatarFront, actual, 3);
	CuAssertPtrNotEquals(tc, avatarFront, actual);

	memset(&actual, 0, sizeof actual);
	err = getCameraPosition(actual);
	CuAssertFloatArrayEquals(tc, lm->avatarPosition, actual, 3);
	CuAssertFloatArrayEquals(tc, avatarPosition, actual, 3);
	CuAssertPtrNotEquals(tc, avatarPosition, actual);

	memset(&actual, 0, sizeof actual);
	err = getCameraTop(actual);
	CuAssertFloatArrayEquals(tc, lm->avatarTop, actual, 3);
	CuAssertFloatArrayEquals(tc, avatarTop, actual, 3);
	CuAssertPtrNotEquals(tc, avatarTop, actual);


	// verify that it is unmodified
	CuAssertFloatArrayEquals(tc, avatarFrontB, avatarFront, 3);
	CuAssertFloatArrayEquals(tc, avatarPositionB, avatarPosition, 3);
	CuAssertFloatArrayEquals(tc, avatarTopB, avatarTop, 3);
}

/*
 * --------------------------- HELPER FUNCTIONS --------------------------------
 */
typedef LINKAPI_ERROR_CODE(*SetterFunction)(float x, float y, float z);
typedef LINKAPI_ERROR_CODE(*GetterFunction)(float destination[3]);

void TestSettersSuite_Helper_set(CuTest* tc, const char* name, SetterFunction setter, GetterFunction getter) {
	float x = 1.0;
	float xB = 1.0;
	float y = 1.0 / 5.0;
	float yB = 1.0 / 5.0;
	float z = 1.0 / 3.0;
	float zB = 1.0 / 3.0;

	float x2 = 4.0;
	float x2B = 4.0;
	float y2 = 4.0 / 5.0;
	float y2B = 4.0 / 5.0;
	float z2 = 4.0 / 3.0;
	float z2B = 4.0 / 3.0;

	float delta = 0.0;

	LINKAPI_ERROR_CODE err = (setter) (x, y, z);
	CuAssertIntEquals_Msg(tc, name, err, LINKAPI_ERROR_CODE_NO_ERROR);
	float actual[3];
	memset(&actual, 0, sizeof actual);
	err = getter(actual);
	CuAssertIntEquals_Msg(tc, name, err, LINKAPI_ERROR_CODE_NO_ERROR);
	CuAssertDblEquals_Msg(tc, name, x, actual[0], delta);
	CuAssertDblEquals_Msg(tc, name, y, actual[1], delta);
	CuAssertDblEquals_Msg(tc, name, z, actual[2], delta);

	err = setter(x2, y2, z2);
	CuAssertIntEquals_Msg(tc, name, err, LINKAPI_ERROR_CODE_NO_ERROR);
	memset(&actual, 0, sizeof actual);
	err = getter(actual);
	CuAssertIntEquals_Msg(tc, name, err, LINKAPI_ERROR_CODE_NO_ERROR);
	CuAssertDblEquals_Msg(tc, name, x2, actual[0], delta);
	CuAssertDblEquals_Msg(tc, name, y2, actual[1], delta);
	CuAssertDblEquals_Msg(tc, name, z2, actual[2], delta);

	// verify that it is unmodified
	CuAssertDblEquals_Msg(tc, name, xB, x, delta);
	CuAssertDblEquals_Msg(tc, name, yB, y, delta);
	CuAssertDblEquals_Msg(tc, name, zB, z, delta);
	CuAssertDblEquals_Msg(tc, name, x2B, x2, delta);
	CuAssertDblEquals_Msg(tc, name, y2B, y2, delta);
	CuAssertDblEquals_Msg(tc, name, z2B, z2, delta);
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

/**
 * main suite assembly function
 */
CuSuite* SettersSuite(void) {
	CuSuite* suite = CuSuiteNew();

	LINKAPI_ERROR_CODE initError = initialize((wchar_t*) "TestName\0", (wchar_t*) "TestDescription\0", 2);
	if (initError == LINKAPI_ERROR_CODE_NO_ERROR) {

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