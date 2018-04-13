#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <math.h>

#define RANDMAX(max) random() % max

typedef struct {
	double xcord;
	double ycord;
} point_t;

/**
 * Returns a floating-point pseudo-random value contained within min and max,
 * storing it into result.
 *
 * Returns:
 * 0 on success;
 * -1 if max is not strictly greater than min.
 */
int frandom(float min, float max, double *result);
/**
 * Returns a floating-point bidimensional point_t value with pseudo random
 * components, both bounded by min and max.
 *
 * Returns:
 * 0 on success;
 * -1 if max is not strictly greater than min.
 */
int point_random(float min, float max, point_t *result);


#endif
