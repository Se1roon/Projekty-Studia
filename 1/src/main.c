#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "common.h"
#include "parse.h"
#include "validate.h"

double suma_szeregu(double x, double precise, double delta, char *warunek);

int main(int argc, char *argv[]) {
	OPTIONS *options = parse_options(argc, argv);
	if (validate_options(options) == -1) {
		free(options);
		return -1;
	}

	double x;
	double step = fabs(options->a - options->b) / options->n; // TODO: If step == 0 there is an infinite loop fix that.
	for (x = options->a; x <= options->b; x += step) {
		char stop;
		double precise = pow((1 + x), -1.0/3);
		double szereg = suma_szeregu(x, precise, options->e, &stop);
		printf("x=%lf\tp=%.10lf\ts=%.10lf", x, precise, szereg);
		if (stop < 0)
			printf("\tWarunek: Limit\n");
		else printf("\tWarunek: Dokladnosc\n");
	}

	free(options);
	return 0;
}

double suma_szeregu(double x, double precise, double delta, char *warunek) {
	double l = 1.0;
	double m = 1.0;
	double sum = 0;
	double elem;
	int num_e = 0;

	do {
		elem = l/m * pow(x, num_e);

		if (num_e == 0) l = -1;
		else l = pow(-1, num_e-1) * (fabs(l) * (3 * num_e + 1));
		m = m * (3 * (num_e + 1));

		sum += elem;
		num_e++;
	} while (num_e <= M && fabs(precise - sum) > delta);

	if (num_e >= M) *warunek = -1;
	else *warunek = 1;

	return sum;
}
