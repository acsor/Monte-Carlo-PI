#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include <pthread.h>


void generate_points(void *args);


int main (int c, char *argv[]) {
	mpf_t v;

	mpf_init(v);
	mpf_set_str(v, "3.141592653589793", 10);

	mpf_clear(v);

	return EXIT_SUCCESS;
}


void generate_points(void *args) {

	pthread_exit(EXIT_SUCCESS);
}
