
#include <stdio.h>

#include "CuTest.h"

CuSuite* SettersSuite();
CuSuite* UpdatersSuite();
CuSuite* MiscSuite();

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

int main(void) {
	RunAllTests();
}
