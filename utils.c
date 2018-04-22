#include "utils.h"


int frandom(long double min, long double max, long double *result) {
	long double width = max - min;

	if (min >= max) {
		return -1;
	}

	*result = random() * width / RAND_MAX;
	*result -= fabs(min);
		
	return 0;
}

int mpf_urandomb_between(mpf_t rop, gmp_randstate_t rstate, const char *min, const char *max) {
	mpf_t mpf_min, mpf_max, width, half_width;

	mpf_inits(mpf_min, mpf_max, width, half_width, NULL);

	// Initializes GMP float variables to argument values
	mpf_set_str(mpf_min, min, 10);
	mpf_set_str(mpf_max, max, 10);

	if (mpf_cmp(mpf_max, mpf_min) <= 0) {
		mpf_clears(mpf_min, mpf_max, width, half_width, NULL);
		return -1;
	}

	// Initializes width and half_width variables, employed
	// in stretching out and shifting the random value to the
	// intended interval
	mpf_sub(width, mpf_max, mpf_min);
	mpf_abs(width, width);
	mpf_div_ui(half_width, width, 2);

	// Calculates the random value and scales and translates it accordingly
	mpf_urandomb(rop, rstate, FLOAT_PRECISION);
	mpf_mul(rop, rop, width);
	mpf_sub(rop, rop, half_width);

	mpf_clears(mpf_min, mpf_max, width, half_width, NULL);

	return 0;
}
