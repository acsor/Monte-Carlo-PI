#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <gmp.h>
#include <pthread.h>
#include "utils.h"


typedef void (*void_procedure)(void);

void add();
void test_center_set();
void test_mpf_sub();
void test_gmp_sscanf();
void random_point_display();


int main (int c, char *argv[]) {
	void_procedure procedures[] = {
		add, test_center_set, test_mpf_sub, test_gmp_sscanf, random_point_display
	};
	const size_t n = sizeof(procedures) / sizeof(void_procedure);
	int choice, buffsize = 256;
	char input[buffsize];

	do {
		printf("THIS FILE CONTAINS EXPERIMENTATION CODE, OF EXCLUSIVE INTEREST FOR DEVELOPERS.\n");
		printf("Which procedure do you wish to run? [%d - %lu] ", 0, n - 1);

		fgets(input, buffsize, stdin);
		choice = atoi(input);
		
		puts("");
	} while (choice < 0 || n < choice);

	procedures[choice]();

	return EXIT_SUCCESS;
}


void add() {
	mpf_t a, b, result;
	mpf_inits(a, b, result, NULL);
	int read = 0;

	puts("a + b = ?");

	do {
		read = gmp_scanf("%Ff + %Ff", a, b);
	} while (read != 2);
	mpf_add(result, a, b);

	gmp_printf("%.Ff + %.Ff = %.Ff\n", a, b, result);

	mpf_clears(a, b, result, NULL);
}

void test_center_set() {
	point_t c;

	point_init(&c);
	point_set(&c, "0", "0");

	gmp_printf("c = (%Ff, %Ff)\n", c.x, c.y);
}

void test_mpf_sub() {
	mpf_t minuend, subtraend, diff;

	mpf_inits(minuend, subtraend, diff, NULL);

	puts("a - b = ?");
	gmp_scanf("%Ff - %Ff", minuend, subtraend);

	mpf_sub(diff, minuend, subtraend);
	gmp_printf("%Ff - %Ff = %Ff\n", minuend, subtraend, diff);

	mpf_clears(minuend, subtraend, diff, NULL);
}

void test_gmp_sscanf() {
	char radius[256];
	int zone;
	mpf_t cx, cy, px, py;
	char *sample_line = "0,0,0.5,-0.9510565162951535,0.3090169943749475,1";

	mpf_inits(cx, cy, px, py, NULL);

	gmp_sscanf(sample_line, "%Ff,%Ff,%s,%Ff,%Ff,%d", cx, cy, radius, px, py, &zone);
	gmp_printf("%Ff,%Ff,%Fs,%Ff,%Ff,%d\n", cx, cy, radius, px, py, &zone);

	mpf_clears(cx, cy, px, py, NULL);
}

void random_point_display() {
	char *pass = "\n", *exit = "n\n";
	int buffsize = 256;
	char input[buffsize];
	point_t p;
	gmp_randstate_t rstate;

	gmp_randinit_default(rstate);
	point_init(&p);

	gmp_randseed_ui(rstate, random());
	strncpy(input, "\n", buffsize);

	while (strncmp(input, pass, buffsize) == 0) {
		assert(point_random(&p, rstate, "-100", "100") >= 0);

		gmp_printf("Here's a random point: (%Ff, %Ff). Want another? [<Enter>/n] ", p.x, p.y);

		fgets(input, buffsize, stdin);

		while (
				strncmp(input, pass, buffsize) != 0 &&
				strncmp(input, exit, buffsize) != 0
		) {
			printf("Try again: ");
			fgets(input, buffsize, stdin);
			puts("");
		}
	}

	point_free(&p);
	gmp_randclear(rstate);
}
