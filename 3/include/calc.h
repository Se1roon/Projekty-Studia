#ifndef CALC_H
#define CALC_H

int calc_rank(double **X, int rows, int cols);
double calc_wyz(double **X, int rows, int cols);

double calc_x(double **A, double **B, int i, int n);
double calc_y(double **A, double **B, int i);
double calc_z(double **A, double **B, int i);

double calc_d(double **A, int i);
double calc_l(double **A, int i, int j);
double calc_u(double **A, int i, int j);

#endif
