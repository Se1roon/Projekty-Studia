#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "common.h"
#include "parse.h"
#include "validate.h"
#include "meth.h"

int main(int argc, char *argv[]) {
	OPTIONS *options = parse_options(argc, argv);
	if (validate_options(options) == -1) {
		free(options);
		return -1;
	}

	double x;
	double step = fabs(options->a - options->b) / options->n; // TODO: If step == 0 there is an infinite loop fix that.
	for (x = options->a; x <= options->b; x += step) {
		short stop;
		int liczba_elementów;

		double precise = pow((1 + x), -1.0/3);
		double szereg = calculate_sum(options, x, precise, &stop, &liczba_elementów);

		// TODO: Create a function for outputing the results to stdin and file.
		printf("x=%lf\tp=%.10lf\ts=%.10lf", x, precise, szereg);
		if (stop < 0)
			printf("\tWarunek: Limit\n");
		else printf("\tWarunek: Dokladnosc");
		printf("\tLiczba elementów = %d\n", liczba_elementów);
	}

	free(options);
	return 0;
}

