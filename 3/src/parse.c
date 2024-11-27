#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

#include "common.h"
#include "parse.h"

// Definitions of utility functions
char *get_line(FILE *f);

int parse_matrices(FILE *f, double ***A_out, double ***B_out, int *A_size) {
	double **A = (double **)calloc(1, sizeof(double));
	double **B = (double **)calloc(1, sizeof(double));

	int line_num = 0; // row
	int col_num = 0;
	char *line = NULL;
	while ((line = get_line(f))) {
		A[line_num] = (double *)calloc(col_num + 1, sizeof(double)); // make space for 1 col in a row

		char *w = strtok(line, " ");
		A[line_num][col_num++] = atof(w);
		
		while ((w = strtok(NULL, " "))) {
			A[line_num] = (double *)realloc(A[line_num], (col_num + 1) * sizeof(double));
			A[line_num][col_num++] = atof(w);
		}

		double last = A[line_num][col_num - 1];
		A[line_num] = (double *)realloc(A[line_num], (col_num - 1) * sizeof(double));

		B[line_num] = (double *)calloc(1, sizeof(double));
		B[line_num][0] = last;

		line_num++;
		col_num = 0;
		free(line);
	}

	*A_out = A;
	*B_out = B;
	*A_size = line_num;

	free(line);
	return STATUS_SUCCESS;
}

int parse_options(int argc, char *argv[], char **filepath) {
	char op;
	while ((op = getopt(argc, argv, "f:")) != -1) {
		switch (op) {
			case 'f':
				*filepath = optarg;
				break;
			case '?':
				printf("Nieznana opcja -%c\n", op);
				print_usage(argv);
				return STATUS_ERROR;
		}
	}

	return STATUS_SUCCESS;
}

char *get_line(FILE *f) {
	int line_len = 1;
	char *line = (char *)calloc(line_len, sizeof(char));
	if (!line) return NULL;

	int c;
	while ((c = fgetc(f)) != '\n') {
		if (c == EOF) {
			free(line);
			return NULL;
		}

		line = (char *)realloc(line, (line_len + 1) * sizeof(char));
		line[line_len++ - 1] = c;
	}
	line[line_len - 1] = '\0';

	return line;
}
