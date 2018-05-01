#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <gmp.h>
#include "point.h"

typedef struct {
	// Number of points to compute
	unsigned long int target_points;
	// Number of points computed
	unsigned long int computed_points;
	// Number of points not belonging to the interior points of the circle or
	// its boundary
	unsigned long int points_out;
	// Length of the square enclosing the circle, from which the circle's
	// radius is computed
	long double square_length;
} points;

typedef void* (*thread_routine)(void*);

pthread_mutex_t args_m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t progress_c = PTHREAD_COND_INITIALIZER;

void* generate_points(void *args);
void* display_progress(void *args);
/**
 * Returns a boolean-equivalent TRUE if there are still points to compute for
 * the worker threads, a boolean-equivalent FALSE otherwise.
 */
#define points_has_next(worker_args) (worker_args->computed_points < worker_args->target_points)
void compute_pi(mpf_t rop, points *a);


/**
 * TO-DO Add command-line option parameters.
 */
int main (int c, char *argv[]) {
	thread_routine thread_routines[] = {
		generate_points,
		generate_points,
		generate_points,
		generate_points,
		generate_points,
		display_progress
	};
	unsigned int nthreads = sizeof(thread_routines) / sizeof(thread_routine);
	pthread_t thread_ids[nthreads];
	points args = {
		pow(10, 7), 0, 0, 1
	};
	int i;

	for (i = 0; i < nthreads; i++) {
		pthread_create(thread_ids + i, NULL, thread_routines[i], (void*)&args);
	}

	for (i = 0; i < nthreads; i++) {
		if (pthread_join(thread_ids[i], NULL)) {
			perror("Error occured during pthread_join()");
		}
	}

	return EXIT_SUCCESS;
}


/**
 * TO-DO More points than are intended are generated when running
 * generate_points() in multiple threads. Fix this.
 */
void* generate_points(void *args) {
	points *a = (points*)args;
	point_t p, center;
	gmp_randstate_t rstate;

	// update_threshold sets the interval at which the generate_points() threads
	// synchronously broadcasts other threads that relevant updates have
	// happened
	long int update_threshold = floor(a->target_points / 10);
	int buffsize = 64, result;
	char smin[buffsize], smax[buffsize];

	gmp_randinit_default(rstate);
	point_init(&p);
	point_init(&center);

	gmp_randseed_ui(rstate, random());
	point_set(&center, "0", "0");

	snprintf(smin, buffsize, "%Lf", -(a->square_length / 2));
	snprintf(smax, buffsize, "%Lf", a->square_length / 2);

	while (points_has_next(a)) {
		pthread_mutex_lock(&args_m);

		point_random(&p, rstate, smin, smax);
		a->computed_points++;
		// Checks whether p is within center and stores the result into
		// &result
		is_within_circle(center, smax, p, &result);

		if (result >= 0)
			a->points_out++;

		if ((a->computed_points % update_threshold) == 0) {
			pthread_cond_broadcast(&progress_c);
		}

		pthread_mutex_unlock(&args_m);
	}

	point_free(&center);
	point_free(&p);
	gmp_randclear(rstate);

	pthread_exit(EXIT_SUCCESS);
}

void* display_progress(void *args) {
	points *a = (points*)args;
	mpf_t pi, percentage;

	mpf_inits(pi, percentage, NULL);

	pthread_mutex_lock(&args_m);

	while (points_has_next(a)) {
		pthread_cond_wait(&progress_c, &args_m);
		compute_pi(pi, a);

		mpf_set_ui(percentage, a->computed_points);
		mpf_div_ui(percentage, percentage, a->target_points);
		mpf_mul_ui(percentage, percentage, 100);

		gmp_printf(
			"[%.2Ff%% %ld/%ld points] PI = %.Ff\n",
			percentage, a->computed_points, a->target_points, pi
		);
	}

	pthread_mutex_unlock(&args_m);
	mpf_clears(pi, percentage, NULL);

	pthread_exit(EXIT_SUCCESS);
}

void compute_pi(mpf_t rop, points *a) {
	// Sets rop to the number of interior points
	mpf_set_d(rop, a->computed_points - a->points_out);
	// Divides rop by the number of all points computed
	mpf_div_ui(rop, rop, a->computed_points);
	mpf_mul_ui(rop, rop, 4);
}
