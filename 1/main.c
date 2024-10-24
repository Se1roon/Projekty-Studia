#include <stdio.h>
#include <math.h>

#define M 50
#define DIVIDER 3

double suma_szeregu(double x, double precise, double delta);

int main(void) {
	// Create an options to pass command-line arguments (for scripters)
	double a, b, delta;
	int n;
	if (scanf("%lf %lf %d %lf", &a, &b, &n, &delta) != 4) {
		fprintf(stderr, "Niepoprawna liczba danych\n");
		return -1;
	}

	// Validation...

	double x;
	double step = fabs(a - b) / n;
	for (x = a; x <= b; x += step) {
		double precise = pow((1 + x), -1.0/DIVIDER);
		double szereg = suma_szeregu(x, precise, delta);
		printf("x=%lf\tp=%.10lf\ts=%.10lf\n", x, precise, szereg);
	}

	return 0;
}

double suma_szeregu(double x, double precise, double delta) {
	double l = 1.0;
	double m = 1.0;
	double sum = 0;
	double elem;
	int num_e = 0;

	do {
		elem = l/m * pow(x, num_e);
//		printf("l=%lf\nm=%lf\nelem=%lf\nsum=%lf\n\n", l, m, elem, sum);
		if (num_e == 0) l = -1;
		else l = pow(-1, num_e-1) * (fabs(l) * (3 * num_e + 1));
		m = m * (3 * (num_e + 1));
		sum += elem;

		num_e++;
	} while (num_e <= M && fabs(precise - elem) > delta);

	return sum;
}
