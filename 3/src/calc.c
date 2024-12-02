#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "calc.h"

double calc_x(double **A, double **B, int i, int n) {
	if (i == n - 1) return calc_z(A, B, i);

	double u, x;
	double sum = 0;
	for (int k = i + 1; k <= n - 1; k++) {
		u = calc_u(A, i, k);
		x = calc_x(A, B, k, n);
		
		sum += u * x;
	}

	return calc_z(A, B, i) - sum;
}

double calc_y(double **A, double **B, int i) {
	if (i == 0) return B[0][0];

	double l, y;
	double sum = 0;
	for (int k = 0; k <= i - 1; k++) {
		l = calc_l(A, i, k);
		y = calc_y(A, B, k);

		sum += l * y;
	}

	return B[i][0] - sum;
}

double calc_z(double **A, double **B, int i) {
	return calc_y(A, B, i) / calc_d(A, i);
}

double calc_d(double **A, int i) {
	if (i == 0) return A[0][0];

	double l, u, d;
	double sum = 0;
	for (int k = 0; k <= i - 1; k++) {
		l = calc_l(A, i, k);
		u = calc_u(A, k, i);
		d = calc_d(A, k);
		
		sum += l*u*d;
	}

	return A[i][i] - sum;
}

double calc_l(double **A, int i, int j) {
	if (i > j && j > 0)	{
		double l, u, d;
		double sum = 0;
		for (int k = 0; k <= j - 1; k++) {
			l = calc_l(A, i, k);
			u = calc_u(A, k, j);
			d = calc_d(A, k);

			sum += l*u*d;
		}

		return (A[i][j] - sum) / calc_d(A, j);
	}
	
	return A[i][0] / calc_d(A, 0);
}

double calc_u(double **A, int i, int j) {
	if (0 < i && i < j) {
		double l, u, d;
		double sum = 0;
		for (int k = 0; k <= i - 1; k++) {
			l = calc_l(A, i, k);
			u = calc_u(A, k, j);
			d = calc_d(A, k);

			sum += l*u*d;
		}

		return (A[i][j] - sum) / calc_d(A, i);
	}

	return A[0][j] / calc_d(A, 0);
}
