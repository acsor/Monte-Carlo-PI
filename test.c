#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <gmp.h>
#include "point.h"
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
/**
 * Tests the is_within_circle() primitive, loading data from a fixture
 * where coordinates of various center points, radiuses and other points are
 * stored
 */
int test_is_within_circle();
int test_urandomb_between();


int main (int argc, char *argv[]) {
	test_function tests[] = {
		test_RANDMAX, test_frandom, test_frandom_boundaries,
		test_point_random, test_point_random_boundaries, test_is_within_circle,
		test_urandomb_between
	};
	test_function current_test;

	size_t tests_no = sizeof(tests) / sizeof(test_function);
	int i;

	for (i = 0; i < tests_no; i++) {
		current_test = tests[i];

		fprintf(stderr, "Test %d... ", i + 1);

		if (current_test() == 0) {
			fputs("OK\n", stderr);
		} else {
			fputs("failed\n", stderr);
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
	long int tries = pow(10, 6);
	float min = -5, max = 5;
	long double r;
	long int i; 
	for (i = 0; i < tries; i++) {
		assert(frandom(min, max, &r) >= 0);

		assert(min <= r);
		assert(r <= max);
	}

	return 0;
}

int test_frandom_boundaries() {
	long double r = 0;

	assert(frandom(4, -4, &r) == -1);
	assert(frandom(4, 4, &r) == -1);
	assert(frandom(0, 0, &r) == -1);
	
	// Ensure r is not modified after all these calls
	assert(r == 0);
	
	return 0;
}

int test_point_random() {
	point_t p;
	char *mins = "-100", *maxs = "100";
	double min = atof(mins), max = atof(maxs);
	int tries = pow(10, 5), i;
	gmp_randstate_t rstate;

	gmp_randinit_default(rstate);
	point_init(&p);

	gmp_randseed_ui(rstate, random());

	for (i = 0; i < tries; i++) {
		assert(point_random(&p, rstate, mins, maxs) >= 0);

		assert(mpf_cmp_d(p.x, min) > 0 && mpf_cmp_d(p.x, max) < 0);
		assert(mpf_cmp_d(p.y, min) > 0 && mpf_cmp_d(p.y, max) < 0);
	}

	point_free(&p);
	gmp_randclear(rstate);

	return 0;
}

int test_point_random_boundaries() {
	point_t p;
	gmp_randstate_t rstate;

	gmp_randinit_default(rstate);
	point_init(&p);

	point_set(&p, "0", "0");
	
	assert(point_random(&p, rstate, "4", "-4") == -1);
	assert(point_random(&p, rstate, "4", "4") == -1);
	assert(point_random(&p, rstate, "0", "0") == -1);

	assert(mpf_cmp_d(p.x, 0) == 0);
	assert(mpf_cmp_d(p.y, 0) == 0);

	point_free(&p);
	gmp_randclear(rstate);

	return 0;
}

int test_is_within_circle() {
	point_t center, p;
	int buff_size = 256;
	long double radius;
	char sradius[buff_size];
	// Can only belong to {-1, 0, 1} in the .csv file were its value is stored
	int zone;

	char *filename = "fixtures/test_is_within_circle.csv",
		 line_buffer[buff_size], error_msg[buff_size];
	int result, read_values, lineno = 1;
	FILE *test_data_fp;

	point_init(&center);
	point_init(&p);

	test_data_fp = fopen(filename, "r");

	if (test_data_fp == NULL) {
		snprintf(error_msg, buff_size, "Error opening file \"%s\"", filename);
		perror(error_msg);

		return -1;
	}

	while (fgets(line_buffer, buff_size, test_data_fp)) {
		line_buffer[strlen(line_buffer) - 1] = '\0';

		read_values = gmp_sscanf(
			line_buffer,
			"%Ff,%Ff,%Lf,%Ff,%Ff,%d",
			center.x, center.y, &radius, p.x, p.y, &zone
		);
		snprintf(sradius, buff_size, "%Lf", radius);

		assert(read_values == 6);

		/*
			result, as "returned" by is_within_circle(), is negative if the
			point belongs to the interior points of the circle, zero if it lies over
			its boundary, and greater than zero if it belongs to the exterior
			points. The zone variable, however, can assume values only in {-1,
			0, 1}
		*/
		is_within_circle(center, sradius, p, &result);

		gmp_snprintf(
			error_msg, buff_size,
			"Error reading line %d (\"%s\"): center = (%Ff, %Ff) p = (%Ff, %Ff) result == %d != zone == %d",
			lineno, line_buffer, center.x, center.y, p.x, p.y, result, zone
		);
		ASSERT_MSG(result == zone, error_msg, 1);

		lineno++;
	}

	if (fclose(test_data_fp) == EOF) {
		snprintf(error_msg, buff_size, "Error while closing file \"%s\"", filename);
		perror(error_msg);
	}

	point_free(&p);
	point_free(&center);

	return 0;
}

int test_urandomb_between() {
	long int tries = pow(10, 5);
	const char *min = "-10", *max = "10";
	long int i;
	gmp_randstate_t rstate;
	mpf_t rvalue;

	gmp_randinit_default(rstate);
	mpf_inits(rvalue, NULL);

	// Prepares random state
	// TO-DO Use another seed. For Linux systems /dev/random should be a rather
	// good choice
	gmp_randseed_ui(rstate, random());

	for (i = 0; i < tries; i++) {
		mpf_urandomb_between(rvalue, rstate, min, max);

		if (mpf_cmp_d(rvalue, atof(min)) < 0 || mpf_cmp_d(rvalue, atof(max)) > 0) {
			gmp_fprintf(stderr, "%L <= %Ff <= %L not true\n", min, rvalue, max);
			return -1;
		}
	}

	mpf_clears(rvalue, NULL);
	gmp_randclear(rstate);

	return 0;
}
