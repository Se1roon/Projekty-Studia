#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>

int parse_matrices(FILE *f, double ***A, double ***B, int *A_size);
int parse_options(int argc, char *argv[], char **filepath);

#endif
