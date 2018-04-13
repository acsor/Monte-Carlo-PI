#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"


typedef int (*test_function) (void);


int test_RANDRANGE();


int main (int argc, char *argv[]) {
	test_function tests[] = {
		test_RANDRANGE
	};
	test_function current_test;

	int i;
	size_t tests_no = sizeof(tests) / sizeof(test_function);

	for (i = 0; i < tests_no; i++) {
		current_test = tests[i];

		if (current_test() == 0) {
			printf("Test %d... OK\n", i + 1);
		} else {
			fprintf(stderr, "Test %d... FAILED\n", i + 1);
		}
	}

	return EXIT_SUCCESS;
}


int test_RANDRANGE() {
	int tries = 100000, i, max = 490;
	int r;

	for (i = 0; i < tries; i++) {
		r = RANDRANGE(490);

		assert(r >= 0);
		assert(r < max);
	}

	return 0;
}
