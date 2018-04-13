#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "utils.h"


typedef int (*test_function) (void);


int test_RANDMAX();
int test_frandom();
/**
 * Tests the insertion of invalid data into frandom
 */
int test_frandom_boundaries();
int test_point_random();
int test_point_random_boundaries();


int main (int argc, char *argv[]) {
	test_function tests[] = {
		test_RANDMAX, test_frandom, test_frandom_boundaries,
		test_point_random, test_point_random_boundaries
	};
	test_function current_test;

	int i;
	size_t tests_no = sizeof(tests) / sizeof(test_function);

	for (i = 0; i < tests_no; i++) {
		current_test = tests[i];

		if (current_test() == 0) {
			fprintf(stderr, "Test %d... OK\n", i + 1);
		} else {
			fprintf(stderr, "Test %d... FAILED\n", i + 1);
		}
	}

	return EXIT_SUCCESS;
}


int test_RANDMAX() {
	int tries = pow(10, 6), max = 490;
	int i, r;

	for (i = 0; i < tries; i++) {
		r = RANDMAX(max);

		assert(r >= 0);
		assert(r < max);
	}

	return 0;
}

int test_frandom() {
	int tries = pow(10, 6);
	float min = -5, max = 5;
	double r;
	int i;

	for (i = 0; i < tries; i++) {
		assert(frandom(min, max, &r) >= 0);

		assert(min <= r);
		assert(r <= max);
	}

	return 0;
}

int test_frandom_boundaries () {
	double r = 0;

	assert(frandom(4, -4, &r) == -1);
	assert(frandom(4, 4, &r) == -1);
	assert(frandom(0, 0, &r) == -1);
	
	// Ensure r is not modified after all these calls
	assert(r == 0);
	
	return 0;
}

int test_point_random() {
	int tries = pow(10, 6);
	float min = -5, max = 5;
	point_t p;
	int i;

	for (i = 0; i < tries; i++) {
		assert(point_random(min, max, &p) >= 0);
		printf("(%f, %f)\n", p.xcord, p.ycord);

		assert(min <= p.xcord && p.xcord <= max);
		assert(min <= p.ycord && p.ycord <= max);
	}

	return 0;
}

int test_point_random_boundaries() {
	point_t p = {0, 0};
	
	assert(point_random(4, -4, &p) == -1);
	assert(point_random(4, 4, &p) == -1);
	assert(point_random(0, 0, &p) == -1);

	assert(p.xcord == 0);
	assert(p.ycord == 0);

	return 0;
}
