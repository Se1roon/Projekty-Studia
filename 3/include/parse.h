#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>

int validate_matrices(double **A, double **B, int A_rows, int A_cols);
int parse_matrices(FILE *f, double ***A, double ***B, int *A_rows, int *A_cols);
int parse_options(int argc, char *argv[], char **filepath);

#endif
