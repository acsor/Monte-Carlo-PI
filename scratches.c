#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include <pthread.h>
#include "utils.h"


typedef void (*void_procedure)(void);

void add();
void test_ASSERT_MSG();
void test_mpf_sub();
void test_gmp_sscanf();


int main (int c, char *argv[]) {
	void_procedure procedures[] = {
		add, test_ASSERT_MSG, test_mpf_sub, test_gmp_sscanf
	};
	const size_t n = sizeof(procedures) / sizeof(void_procedure);
	int choice;

	do {
		printf("Which procedure do you wish to run? [%d - %lu] ", 0, n - 1);
		scanf("%d", &choice);
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

	gmp_printf("%.Ff + %.Ff = %Ff\n", a, b, result);

	mpf_clears(a, b, result, NULL);
}

void test_ASSERT_MSG() {
	ASSERT_MSG(1 == 0, "I'm sorry, I couldn't do it!", 1);
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
