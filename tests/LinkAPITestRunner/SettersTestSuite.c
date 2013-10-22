#include "CuTest.h"
#include "CustomCuTest.h"
#include "CustomHelperFunctions.h"

#include "linkAPI.h"

#include <stdio.h>

/*
 * ---------------- TEST CASES -------------------------------
 */

void TestSettersSuite_setUiTick(CuTest* tc) {
	lm->uiTick = 0;
	LINKAPI_NATIVE_DWORD tick = 123;
	LINKAPI_NATIVE_DWORD tickb = 123;
	LINKAPI_NATIVE_DWORD tick2 = 125;
	LINKAPI_NATIVE_DWORD tick2b = 125;

	LINKAPI_ERROR_CODE err = setUiTick(tick);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, tick, lm->uiTick);
	LINKAPI_NATIVE_DWORD actual = getUiTick();
	CuAssertIntEquals(tc, lm->uiTick, actual);
	CuAssertIntEquals(tc, tick, actual);

	err = setUiTick(tick2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, tick2, lm->uiTick);
	actual = getUiTick();
	CuAssertIntEquals(tc, lm->uiTick, actual);
	CuAssertIntEquals(tc, tick2, actual);

	// verify that it is unmodified
	CuAssertIntEquals(tc, tickb, tick);
	CuAssertIntEquals(tc, tick2b, tick2);
}

void TestSettersSuite_setUiVersion(CuTest* tc) {
	lm->uiVersion = 0;
	LINKAPI_NATIVE_UINT32 version = 321;
	LINKAPI_NATIVE_UINT32 versionB = 321;
	LINKAPI_NATIVE_UINT32 version2 = 2;
	LINKAPI_NATIVE_UINT32 version2B = 2;

	LINKAPI_ERROR_CODE err = setUiVersion(version);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, version, lm->uiVersion);
	LINKAPI_NATIVE_UINT32 actual = getUiVersion();
	CuAssertIntEquals(tc, lm->uiVersion, actual);
	CuAssertIntEquals(tc, version, actual);

	err = setUiVersion(version2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertIntEquals(tc, version2, lm->uiVersion);
	actual = getUiVersion();
	CuAssertIntEquals(tc, version2, actual);
	CuAssertIntEquals(tc, lm->uiVersion, actual);

	// verify that it is unmodified
	CuAssertIntEquals(tc, versionB, version);
	CuAssertIntEquals(tc, version2B, version2);
}

void TestSettersSuite_setIdentity(CuTest* tc) {
	wchar_t text[LINKAPI_MAX_IDENTITY_LENGTH] = L"TestIdentity\0";
	wchar_t textB[LINKAPI_MAX_IDENTITY_LENGTH] = L"TestIdentity\0";
	wchar_t text2[LINKAPI_MAX_IDENTITY_LENGTH] = L"SomeTotallyDifferentID\0";
	wchar_t text2B[LINKAPI_MAX_IDENTITY_LENGTH] = L"SomeTotallyDifferentID\0";

	LINKAPI_ERROR_CODE err = setIdentity(text);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, text, lm->identity, LINKAPI_MAX_IDENTITY_LENGTH);
	wchar_t* actual = getIdentity();
	CuAssertWCharTArrayEquals(tc, lm->identity, actual, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertWCharTArrayEquals(tc, text, actual, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, text, actual);

	err = setIdentity(text2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, text2, lm->identity, LINKAPI_MAX_IDENTITY_LENGTH);
	actual = getIdentity();
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
	wchar_t* actual = getName();
	CuAssertWCharTArrayEquals(tc, lm->name, actual, LINKAPI_MAX_NAME_LENGTH);
	CuAssertWCharTArrayEquals(tc, text, actual, LINKAPI_MAX_NAME_LENGTH);
	CuAssertPtrNotEquals(tc, text, actual);

	err = setName(text2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, text2, lm->name, LINKAPI_MAX_NAME_LENGTH);
	CuAssertByteArrayEquals(tc, text2, lm->name, LINKAPI_MAX_NAME_LENGTH * sizeof (wchar_t));
	actual = getName();
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
	wchar_t* actual = getDescription();
	CuAssertWCharTArrayEquals(tc, lm->description, actual, LINKAPI_MAX_DESCRIPTION_LENGTH);
	CuAssertWCharTArrayEquals(tc, text, actual, LINKAPI_MAX_DESCRIPTION_LENGTH);
	CuAssertPtrNotEquals(tc, text, actual);

	err = setDescription(text2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, lm->description, text2, LINKAPI_MAX_DESCRIPTION_LENGTH);
	actual = getDescription();
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
	LINKAPI_NATIVE_UINT32 actualLen;
	unsigned char* actual = getContext(&actualLen);
	CuAssertIntEquals(tc, lm->context_len, actualLen);
	CuAssertIntEquals(tc, len, actualLen);
	CuAssertCharArrayEquals(tc, lm->context, actual, len);
	CuAssertCharArrayEquals(tc, text, actual, len);
	CuAssertPtrNotEquals(tc, text, actual);

	err = setContext(text2, len2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertCharArrayEquals(tc, text2, lm->context, len2);
	actual = getContext(&actualLen);
	CuAssertIntEquals(tc, lm->context_len, actualLen);
	CuAssertIntEquals(tc, len2, actualLen);
	CuAssertCharArrayEquals(tc, lm->context, actual, len2);
	CuAssertCharArrayEquals(tc, text2, actual, len2);
	CuAssertPtrNotEquals(tc, text2, actual);

	err = setContext(text3, len3Excerpt);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertCharArrayEquals(tc, text3, lm->context, len3Excerpt);
	actual = getContext(&actualLen);
	CuAssertIntEquals(tc, lm->context_len, actualLen);
	CuAssertIntEquals(tc, len3Excerpt, actualLen);
	CuAssertCharArrayEquals(tc, lm->context, actual, len3Excerpt);
	CuAssertCharArrayEquals(tc, text3Excerpt, actual, len3Excerpt);
	CuAssertPtrNotEquals(tc, text3, actual);

	err = setContext(text, LINKAPI_MAX_CONTEXT_LENGTH + 10);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_CONTEXT_LENGTH_EXCEEDED, err);
	CuAssertCharArrayEquals(tc, text3Excerpt, lm->context, len3Excerpt);
	actual = getContext(&actualLen);
	CuAssertIntEquals(tc, lm->context_len, actualLen);
	CuAssertIntEquals(tc, len3Excerpt, actualLen);
	CuAssertCharArrayEquals(tc, lm->context, actual, len3Excerpt);
	CuAssertCharArrayEquals(tc, text3Excerpt, actual, len3Excerpt);
	CuAssertPtrNotEquals(tc, text3, actual);

	unsigned char* contextOnlyActual = getContext(NULL);
	CuAssertCharArrayEquals(tc, lm->context, contextOnlyActual, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertCharArrayEquals(tc, actual, contextOnlyActual, LINKAPI_MAX_CONTEXT_LENGTH);
	CuAssertPtrEquals(tc, actual, contextOnlyActual);

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

	LINKAPI_ERROR_CODE err = setIdentityAndContext(identity, text, actualLen);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, identity, lm->identity, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertCharArrayEquals(tc, text, lm->context, actualLen);
	unsigned char* actual = getContext(NULL);
	CuAssertCharArrayEquals(tc, lm->context, actual, actualLen);
	CuAssertCharArrayEquals(tc, text, actual, actualLen);
	CuAssertPtrNotEquals(tc, text, actual);
	wchar_t* actualId = getIdentity();
	CuAssertWCharTArrayEquals(tc, lm->identity, actualId, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertWCharTArrayEquals(tc, identity, actualId, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, identity, actualId);

	err = setIdentityAndContext(identity2, text2, actualLen2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, identity2, lm->identity, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertCharArrayEquals(tc, text2, lm->context, actualLen2);
	actual = getContext(NULL);
	CuAssertCharArrayEquals(tc, lm->context, actual, actualLen2);
	CuAssertCharArrayEquals(tc, text2, actual, actualLen2);
	CuAssertPtrNotEquals(tc, text2, actual);
	actualId = getIdentity();
	CuAssertWCharTArrayEquals(tc, lm->identity, actualId, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertWCharTArrayEquals(tc, identity2, actualId, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertPtrNotEquals(tc, identity2, actualId);

	err = setIdentityAndContext(identity, text3, actualLen3Excerpt);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertWCharTArrayEquals(tc, identity, lm->identity, LINKAPI_MAX_IDENTITY_LENGTH);
	CuAssertCharArrayEquals(tc, text3, lm->context, actualLen3Excerpt);
	actual = getContext(NULL);
	CuAssertCharArrayEquals(tc, lm->context, actual, actualLen3Excerpt);
	CuAssertCharArrayEquals(tc, text3Excerpt, actual, actualLen3Excerpt);
	CuAssertPtrNotEquals(tc, text3, actual);
	actualId = getIdentity();
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
	data.context_len = LINKAPI_MAX_CONTEXT_LENGTH;
	LINKAPI_LINKED_MEMORY dataB;
	memcpy(&dataB, &data, lmSize);


	LINKAPI_LINKED_MEMORY data2 = {
		.context = "Context From setData\0",
		.context_len = LINKAPI_MAX_CONTEXT_LENGTH,
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

	LINKAPI_LINKED_MEMORY data2b = {
		.context = "Context From setData\0",
		.context_len = LINKAPI_MAX_CONTEXT_LENGTH,
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

	LINKAPI_ERROR_CODE err = setData(&data);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertByteArrayEquals(tc, &data, lm, lmSize);
	LINKAPI_LINKED_MEMORY* actual = getData();
	CuAssertByteArrayEquals(tc, lm, actual, lmSize);
	CuAssertByteArrayEquals(tc, &data, actual, lmSize);
	CuAssertPtrNotEquals(tc, &data, actual);

	err = setData(&data2);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);
	CuAssertByteArrayEquals(tc, &data2, lm, lmSize);
	actual = getData();
	CuAssertByteArrayEquals(tc, lm, actual, lmSize);
	CuAssertByteArrayEquals(tc, &data2, actual, lmSize);
	CuAssertPtrNotEquals(tc, &data2, actual);

	float expAF[LINKAPI_VECTOR_LENGTH] = {1.1, 2.1, 3.1};
	CuAssertVecEquals(tc, expAF, getAvatarFront(), LINKAPI_VECTOR_LENGTH);
	float expAP[LINKAPI_VECTOR_LENGTH] = {4.1, 5.1, 6.1};
	CuAssertVecEquals(tc, expAP, getAvatarPosition(), LINKAPI_VECTOR_LENGTH);
	float expAT[LINKAPI_VECTOR_LENGTH] = {7.1, 8.1, 9.1};
	CuAssertVecEquals(tc, expAT, getAvatarTop(), LINKAPI_VECTOR_LENGTH);

	// verify that it is unmodified
	CuAssertByteArrayEquals(tc, &dataB, &data, lmSize);
	CuAssertByteArrayEquals(tc, &data2b, &data2, lmSize);
}

void TestSettersSuite_setVectors(CuTest* tc) {
	float fAvatarFront [LINKAPI_VECTOR_LENGTH] = {1.1, 2.1, 3.1};
	float fAvatarFrontB[LINKAPI_VECTOR_LENGTH] = {1.1, 2.1, 3.1};
	float fAvatarPosition [LINKAPI_VECTOR_LENGTH] = {4.1, 5.1, 6.1};
	float fAvatarPositionB[LINKAPI_VECTOR_LENGTH] = {4.1, 5.1, 6.1};
	float fAvatarTop [LINKAPI_VECTOR_LENGTH] = {7.1, 8.1, 9.1};
	float fAvatarTopB[LINKAPI_VECTOR_LENGTH] = {7.1, 8.1, 9.1};
	float fCameraFront [LINKAPI_VECTOR_LENGTH] = {10.1, 11.1, 12.1};
	float fCameraFrontB[LINKAPI_VECTOR_LENGTH] = {10.1, 11.1, 12.1};
	float fCameraPosition [LINKAPI_VECTOR_LENGTH] = {13.1, 14.1, 15.1};
	float fCameraPositionB[LINKAPI_VECTOR_LENGTH] = {13.1, 14.1, 15.1};
	float fCameraTop [LINKAPI_VECTOR_LENGTH] = {16.1, 17.1, 18.1};
	float fCameraTopB[LINKAPI_VECTOR_LENGTH] = {16.1, 17.1, 18.1};


	LINKAPI_ERROR_CODE err = setVectors(fAvatarPosition, fAvatarFront, fAvatarTop, fCameraPosition, fCameraFront, fCameraTop);
	CuAssertVecEqualsDefault(tc, fAvatarPosition, lm->fAvatarPosition);
	CuAssertVecEqualsDefault(tc, fAvatarFront, lm->fAvatarFront);
	CuAssertVecEqualsDefault(tc, fAvatarTop, lm->fAvatarTop);

	CuAssertVecEqualsDefault(tc, fCameraPosition, lm->fCameraPosition);
	CuAssertVecEqualsDefault(tc, fCameraFront, lm->fCameraFront);
	CuAssertVecEqualsDefault(tc, fCameraTop, lm->fCameraTop);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);

	float* actual = getAvatarFront();
	CuAssertVecEquals(tc, lm->fAvatarFront, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertVecEquals(tc, fAvatarFront, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarFront, actual);

	actual = getAvatarPosition();
	CuAssertVecEquals(tc, lm->fAvatarPosition, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertVecEquals(tc, fAvatarPosition, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarPosition, actual);

	actual = getAvatarTop();
	CuAssertVecEquals(tc, lm->fAvatarTop, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertVecEquals(tc, fAvatarTop, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarTop, actual);


	actual = getCameraFront();
	CuAssertVecEquals(tc, lm->fCameraFront, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertVecEquals(tc, fCameraFront, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fCameraFront, actual);

	actual = getCameraPosition();
	CuAssertVecEquals(tc, lm->fCameraPosition, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertVecEquals(tc, fCameraPosition, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fCameraPosition, actual);

	actual = getCameraTop();
	CuAssertVecEquals(tc, lm->fCameraTop, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertVecEquals(tc, fCameraTop, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fCameraTop, actual);

	// verify that it is unmodified
	CuAssertVecEqualsDefault(tc, fAvatarFrontB, fAvatarFront);
	CuAssertVecEqualsDefault(tc, fAvatarPositionB, fAvatarPosition);
	CuAssertVecEqualsDefault(tc, fAvatarTopB, fAvatarTop);
	CuAssertVecEqualsDefault(tc, fCameraFrontB, fCameraFront);
	CuAssertVecEqualsDefault(tc, fCameraPositionB, fCameraPosition);
	CuAssertVecEqualsDefault(tc, fCameraTopB, fCameraTop);
}

void TestSettersSuite_setVectorsByAvatar(CuTest* tc) {
	float fAvatarFront [LINKAPI_VECTOR_LENGTH] = {1.1, 2.1, 3.1};
	float fAvatarFrontB[LINKAPI_VECTOR_LENGTH] = {1.1, 2.1, 3.1};
	float fAvatarPosition [LINKAPI_VECTOR_LENGTH] = {4.1, 5.1, 6.1};
	float fAvatarPositionB[LINKAPI_VECTOR_LENGTH] = {4.1, 5.1, 6.1};
	float fAvatarTop [LINKAPI_VECTOR_LENGTH] = {7.1, 8.1, 9.1};
	float fAvatarTopB[LINKAPI_VECTOR_LENGTH] = {7.1, 8.1, 9.1};


	LINKAPI_ERROR_CODE err = setVectorsAvatarAsCamera(fAvatarPosition, fAvatarFront, fAvatarTop);
	CuAssertIntEquals(tc, LINKAPI_ERROR_CODE_NO_ERROR, err);

	float* actual = getAvatarFront();
	CuAssertVecEquals(tc, lm->fAvatarFront, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertVecEquals(tc, fAvatarFront, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarFront, actual);

	actual = getAvatarPosition();
	CuAssertVecEquals(tc, lm->fAvatarPosition, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertVecEquals(tc, fAvatarPosition, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarPosition, actual);

	actual = getAvatarTop();
	CuAssertVecEquals(tc, lm->fAvatarTop, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertVecEquals(tc, fAvatarTop, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarTop, actual);


	actual = getCameraFront();
	CuAssertVecEquals(tc, lm->fAvatarFront, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertVecEquals(tc, fAvatarFront, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarFront, actual);

	actual = getCameraPosition();
	CuAssertVecEquals(tc, lm->fAvatarPosition, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertVecEquals(tc, fAvatarPosition, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarPosition, actual);

	actual = getCameraTop();
	CuAssertVecEquals(tc, lm->fAvatarTop, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertVecEquals(tc, fAvatarTop, actual, LINKAPI_VECTOR_LENGTH);
	CuAssertPtrNotEquals(tc, fAvatarTop, actual);

	// verify that it is unmodified
	CuAssertVecEqualsDefault(tc, fAvatarFrontB, fAvatarFront);
	CuAssertVecEqualsDefault(tc, fAvatarPositionB, fAvatarPosition);
	CuAssertVecEqualsDefault(tc, fAvatarTopB, fAvatarTop);
}

/*
 * --------------------------- HELPER FUNCTIONS --------------------------------
 */
typedef LINKAPI_ERROR_CODE(*SetterFunction)(float x, float y, float z);
typedef float* (*GetterFunction)();

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
	float* actual = getter();
	CuAssertDblEquals_Msg(tc, name, x, actual[0], delta);
	CuAssertDblEquals_Msg(tc, name, y, actual[1], delta);
	CuAssertDblEquals_Msg(tc, name, z, actual[2], delta);

	err = setter(x2, y2, z2);
	CuAssertIntEquals_Msg(tc, name, err, LINKAPI_ERROR_CODE_NO_ERROR);
	actual = getter();
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