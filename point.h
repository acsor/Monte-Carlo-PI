#ifndef POINT_H
#define POINT_H

#include <math.h>
#include <gmp.h>

#define FLOAT_PRECISION 32

typedef struct {
	mpf_t x, y;
} point_t;

void point_init(point_t *p);
void point_set(point_t *p, const char *x, const char *y);
/**
 * Subtracts p2 from p1 and stores the result to dest.
 */
void point_sub(point_t *dest, point_t p1, point_t p2);
/**
 * Returns the vectorial norm of p, storing it into result. At the moment
 * only bidimensional vectors are supported, so the returned value will be the
 * direct application of Pythagoras' theorem.
 */
void point_modulus(mpf_t result, point_t p);
void point_free(point_t *p);
/**
 * Returns an arbitrarily-precision floating-point bidimensional point_t value with pseudo random
 * components, both bounded by min and max.
 *
 * Returns:
 * 0 on success;
 * -1 if max is not strictly greater than min.
 */
int point_random(point_t *result, const char *min, const char *max);
/**
 * Stores a return value result such that:
 *  result > 0 if the point_t p is outside the circle described by center and radius;
 *  result == 0 if it occurs over its boundary;
 *  result < 0 if it is enclosed in the area of the circle.
 *
 *  Returns:
 *  -1 if radius <= 0;
 *  0 on success.
 */
int is_within_circle(point_t center, const char *radius, point_t p, int *result);

#endif
