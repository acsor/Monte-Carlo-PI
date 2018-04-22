#include "point.h"


void point_init(point_t *p) {
	mpf_inits(p->x, p->y, NULL);

	// TO-DO Isn't a separate precision for points and other mpf_t variables a
	// likely cause of clashes?
	mpf_set_prec(p->x, FLOAT_PRECISION);
	mpf_set_prec(p->x, FLOAT_PRECISION);
}

void point_set(point_t *p, const char *x, const char *y) {
	mpf_set_str(p->x, x, 10);
	mpf_set_str(p->y, y, 10);
}

void point_sub(point_t *dest, point_t p1, point_t p2) {
	mpf_sub(dest->x, p1.x, p2.x);
	mpf_sub(dest->y, p1.y, p2.y);
}

void point_modulus(mpf_t result, point_t p) {
	mpf_t temp;
	mpf_init(temp);
	mpf_set_str(result, "0", 10);

	mpf_pow_ui(temp, p.x, 2);
	mpf_add(result, result, temp);

	mpf_pow_ui(temp, p.y, 2);
	mpf_add(result, result, temp);

	mpf_sqrt(result, result);
	mpf_clear(temp);
}

void point_free(point_t *p) {
	mpf_clears(p->x, p->y, NULL);
}

int point_random(point_t *result, gmp_randstate_t rstate, const char *min, const char *max) {
	mpf_t gmp_min, gmp_max;
	mpf_inits(gmp_min, gmp_max, NULL);

	mpf_set_str(gmp_min, min, 10);
	mpf_set_str(gmp_max, max, 10);

	// If max <= min
	if (mpf_cmp(gmp_max, gmp_min) <= 0) {
		mpf_clears(gmp_min, gmp_max, NULL);
		return -1;
	}

	mpf_urandomb_between(result->x, rstate, min, max);
	mpf_urandomb_between(result->y, rstate, min, max);

	mpf_clears(gmp_min, gmp_max, NULL);

	return 0;
}

int is_within_circle(point_t center, const char *radius, point_t p, int *result) {
	// difference represents the vectorial difference of p from center
	point_t difference;
	// modulus is the vectorial norm of difference, treated as a vector
	mpf_t mpf_radius, modulus, modulus_diff, abs_modulus_diff, zero_threshold;
	
	mpf_inits(mpf_radius, modulus, modulus_diff, abs_modulus_diff, zero_threshold, NULL);
	point_init(&difference);

	mpf_set_str(zero_threshold, "1E-12", 10);
	mpf_set_str(mpf_radius, radius, 10);

	if (mpf_cmp_d(mpf_radius, 0) <= 0) {
		return -1;
	}

	// Obtains the (point - center_point) vector
	point_sub(&difference, p, center);
	// Obtains the norm (modulus) of the previous vector
	point_modulus(modulus, difference);
	// Stores the difference between the circle's radius and
	// the norm of the (point - center_point) vector, i.e. the
	// difference vector-valued variable
	mpf_sub(modulus_diff, modulus, mpf_radius);
	mpf_abs(abs_modulus_diff, modulus_diff);

	// modulus_diff will hold a difference in the value of two scalars, but we
	// are only interested in wheter it is less than, equal or greater than 0
	if (mpf_cmp(abs_modulus_diff, zero_threshold) <= 0) {
		*result = 0;
	} else {
		*result = mpf_sgn(modulus_diff);
	}

	point_free(&difference);
	mpf_clears(mpf_radius, modulus, modulus_diff, abs_modulus_diff, zero_threshold, NULL);

	return 0;
}
