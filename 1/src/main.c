#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#include "common.h"
#include "parse.h"
#include "validate.h"
#include "meth.h"
#include "file.h"

int main(int argc, char *argv[]) {
	OPTIONS *options = parse_options(argc, argv);
	if (validate_options(options) == -1) {
		free(options);
		return -1;
	}

	double x;
	double step = fabs(options->a - options->b) / options->n; // TODO: If step == 0 there is an infinite loop fix that.
	printf("===========================================================================================================\n");
	for (x = options->a; x <= options->b; x += step) {
		short stop;
		int liczba_elementów;

		double precise = pow((1 + x), -1.0/3);
		double szereg = calculate_sum(options, x, precise, &stop, &liczba_elementów);

		output_to_stdout(x, precise, szereg, stop, liczba_elementów);
	}
	printf("===========================================================================================================\n");

	free(options);
	return 0;
}

