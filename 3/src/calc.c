#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "calc.h"


int calc_rank(double **X, int rows, int cols) {
	if (rows == cols && calc_wyz(X, rows, cols) != 0) return rows;

	int max_rank = -1;
	if (rows == cols) {
		int max_minor_dim = rows - 1;
		
		for (int i = 0; i <= 1; i++) {
			for (int j = 0; j <= 1; j++) {
				double **M = (double **)calloc(max_minor_dim, sizeof(double *));
				for (int row = 0; row < max_minor_dim; row++) {
					M[row] = (double *)calloc(max_minor_dim, sizeof(double));
					memcpy(M[row], &X[row + i][j], max_minor_dim * sizeof(double));
				}

				if (calc_rank(M, max_minor_dim, max_minor_dim) > max_rank) max_rank = max_minor_dim;
				for (int row = 0; row < max_minor_dim; row++) free(M[row]);
				free(M);
			}
		}
	} else {
		if (rows < cols) {
			int max_minor_dim = rows;
		
			for (int i = 0; i <= cols - rows; i++) {
				double **M = (double **)calloc(max_minor_dim, sizeof(double *));
				for (int row = 0; row < max_minor_dim; row++) {
					M[row] = (double *)calloc(max_minor_dim, sizeof(double));
					memcpy(M[row], &X[row][i], max_minor_dim * sizeof(double));
				}

				if (calc_rank(M, max_minor_dim, max_minor_dim) > max_rank) max_rank = max_minor_dim;
				for (int row = 0; row < max_minor_dim; row++) free(M[row]);
				free(M);
			}
		} else {
			int max_minor_dim = cols;
			
			for (int i = 0; i <= rows - cols; i++) {
				double **M = (double **)calloc(max_minor_dim, sizeof(double *));
				for (int row = 0; row < max_minor_dim; row++) {
					M[row] = (double *)calloc(max_minor_dim, sizeof(double));
					memcpy(M[row], X[row + i], max_minor_dim * sizeof(double));
				}

				if (calc_rank(M, max_minor_dim, max_minor_dim) > max_rank) max_rank = max_minor_dim;
				for (int row = 0; row < max_minor_dim; row++) free(M[row]);
				free(M);
			}
		}
	}

	return max_rank;
}

double calc_wyz(double **X, int rows, int cols) {
	if (rows == 1 && cols == 1) return X[0][0];
	if (rows == 2 && cols == 2) return (X[0][0] * X[1][1] - X[0][1] * X[1][0]);
	if (rows == 3 && cols == 3) {
		double p = (X[0][0]*X[1][1]*X[2][2] + X[0][1]*X[1][2]*X[2][0] + X[0][2]*X[1][0]*X[2][1]);
		double q = (X[2][0]*X[1][1]*X[0][2] + X[2][1]*X[1][2]*X[0][0] + X[2][2]*X[1][0]*X[0][1]);
		return p - q;
	}

	double wyz = 0;
	for (int i = 0; i < cols; i++) {
		double **Y = (double **)calloc(0, sizeof(double *));
		// Wykrzaczyć minor
		for (int row = 1; row < rows; row++) {
			Y = (double **)realloc(Y, row * sizeof(double *));
			Y[row - 1] = (double *)calloc(0, sizeof(double));

			int c = 0;
			for (int col = 0; col < cols; col++) {
				if (col != i) {
					Y[row - 1] = (double *)realloc(Y[row - 1], (c + 1) * sizeof(double));
					Y[row - 1][c++] = X[row][col];
				}
			}
		}
	
		wyz += pow(-1, 2 + i) * X[0][i] * calc_wyz(Y, rows - 1, cols - 1);

		for (int row = 0; row < rows - 1; row++)
			free(Y[row]);
		free(Y);
	}
	
	return wyz;
}

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
