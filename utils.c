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
