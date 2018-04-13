#include "utils.h"

int frandom(float min, float max, double *result) {
	float width = max - min;

	if (min >= max) {
		return -1;
	}

	*result = random() * width / RAND_MAX;
	*result -= fabs(min);
		
	return 0;
}

int point_random(float min, float max, point_t *result) {
	if (max <= min) {
		return -1;
	}

	frandom(min, max, &result->xcord);
	frandom(min, max, &result->ycord);

	return 0;
}
