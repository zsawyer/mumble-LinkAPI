
#include <stdio.h>

#include "CuTest.h"
#include "LinkAPI.h"
#include "CustomHelperFunctions.h"

#ifndef WIN32
#    include <unistd.h> // getuid
#    include <sys/stat.h> // S_IRUSR, S_IWUSR
#    include <fcntl.h> // O_RDWR

#    include <sys/mman.h> // shm_open, PROT_READ, PROT_WRITE, MAP_SHARED mmap
#else
#    include <windows.h>
#endif

CuSuite* SettersSuite();
CuSuite* UpdatersSuite();
CuSuite* MiscSuite();
void initializationFailed(CuTest* tc);

void TestSettersSuite_setName(CuTest* tc);

/**
 * based on CuTest 1.5
 *
 * modified by zsawyer, 2013-07-12
 */
void RunAllTests(void) {
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();

	CuSuiteAddSuite(suite, SettersSuite());
	CuSuiteAddSuite(suite, UpdatersSuite());
	CuSuiteAddSuite(suite, MiscSuite());

	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}

void RunSelectedTest(void) {
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();

	LINKAPI_ERROR_CODE initError = initialize((wchar_t*) "TestName\0", (wchar_t*) "TestDescription\0", 2);
	if (initError == LINKAPI_ERROR_CODE_NO_ERROR) {

		// selected test
		SUITE_ADD_TEST(suite, TestSettersSuite_setName);

	} else {
		SUITE_ADD_TEST(suite, initializationFailed);
	}

	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}


LINKAPI_LINKED_MEMORY* lm = NULL;

int setup(void) {
	int bCreated = 0;
#ifdef WIN32
	HANDLE hMapObject = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, L"MumbleLink");
	if (hMapObject == NULL) {
		hMapObject = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof (LINKAPI_LINKED_MEMORY), L"MumbleLink");
		bCreated = 1;
		if (hMapObject == NULL)
			return 0;
	}
	lm = (LINKAPI_LINKED_MEMORY *) (MapViewOfFile(hMapObject, FILE_MAP_ALL_ACCESS, 0, 0, 0));
	if (lm == NULL) {
		CloseHandle(hMapObject);
		hMapObject = NULL;
		return 0;
	}
	if (bCreated)
		memset(lm, 0, sizeof (LINKAPI_LINKED_MEMORY));
#else
	snprintf(memname, 256, "/MumbleLink.%d", getuid());

	shmfd = shm_open(memname, O_RDWR, S_IRUSR | S_IWUSR);
	if (shmfd < 0) {
		bCreated = true;
		shmfd = shm_open(memname, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	}

	if (shmfd < 0) {
		fprintf(stderr, "Mumble Link plugin: error creating shared memory\n");
		return 0;
	}

	if (bCreated) {
		if (ftruncate(shmfd, sizeof (struct LINKAPI_LINKED_MEMORY)) != 0) {
			fprintf(stderr, "Mumble Link plugin: failed to resize shared memory\n");
			close(shmfd);
			shmfd = -1;
			return 0;
		}
	}

	lm = (LINKAPI_LINKED_MEMORY*) (
			mmap(NULL, sizeof (struct LINKAPI_LINKED_MEMORY), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0));

	if ((lm != lm_invalid) && bCreated)
		memset(lm, 0, sizeof (struct LINKAPI_LINKED_MEMORY));
#endif

	return 1;
}

int main(void) {
	if (setup()) {
		RunAllTests();
		//RunSelectedTest();
	} else {
		printf("Failed to setup test frameworks.");
		return 1;
	}
	return 0;
}

