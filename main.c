#include <stdio.h>
#include <stdlib.h>


int main (int c, char *argv[]) {
	int tries = 10;
	int i;

	for (i = 0; i < tries; i++) {
		printf("random() = %12ld\n", random());
	}

	return EXIT_SUCCESS;
}
