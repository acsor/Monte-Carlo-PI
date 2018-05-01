#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include "point.h"

#define ASSERT_MSG(expression, msg, code)\
	if (!(expression)) {\
		fprintf(stderr, "Assertion error at %s:%d: %s\n", __FILE__, __LINE__, (msg));\
		exit(code);\
	}
#define RANDMAX(max) (random() % max)
#define WHERE_AM_I() printf("%s:%u\n", __FILE__, __LINE__)

/**
 * Returns a floating-point pseudo-random value contained within min and max,
 * storing it into result.
 *
 * Returns:
 * 0 on success;
 * -1 if max is not strictly greater than min.
 */
int frandom(long double min, long double max, long double *result);
/**
 * Sets rop to a randomly-computed value between min and max.
 *
 * Returns:
 * 0 on success;
 * -1 if max is equal or less than min.
 */
int mpf_urandomb_between(mpf_t rop, gmp_randstate_t rstate, const char *min, const char *max);


#endif
