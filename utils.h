#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <math.h>

#define ASSERT_MSG(expression, msg, code)\
	if (!(expression)) {\
		fprintf(stderr, "Assertion error at %s:%d: %s\n", __FILE__, __LINE__, (msg));\
		exit(code);\
	}

#define RANDMAX(max) random() % max

/**
 * Returns a floating-point pseudo-random value contained within min and max,
 * storing it into result.
 *
 * Returns:
 * 0 on success;
 * -1 if max is not strictly greater than min.
 */
int frandom(long double min, long double max, long double *result);


#endif
