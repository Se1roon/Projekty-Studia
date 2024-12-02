#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

#include "common.h"
#include "parse.h"

char *get_line(FILE *f);

int validate_matrices(double **A, double **B, int A_rows, int A_cols) {
	if (A_rows != A_cols) {
		printf("Podany układ ma nieskończenie wiele rozwiązań lub jest sprzeczny.\n");
		return STATUS_ERROR;
	}

	if (A[0][0] == 0) {
		// Find row with first element != 0
		int non_zero_row_index = -1;
		for (int row = 1; row < A_rows; row++) {
			if (A[row][0] != 0) {
				non_zero_row_index = row;
				break;
			}
		}

		if (non_zero_row_index < 0) {
			fprintf(stderr, "Nie jestem aktualnie w stanie rozwiązać tego równania :(\n");
			return STATUS_ERROR;
		}

		// Switch rows
		double *t = A[0];
		A[0] = A[non_zero_row_index];
		A[non_zero_row_index] = t;

		t = B[0];
		B[0] = B[non_zero_row_index];
		B[non_zero_row_index] = t;
	}

	return STATUS_SUCCESS;
}

int parse_matrices(FILE *f, double ***A_out, double ***B_out, int *A_rows, int *A_cols) {
	double **A = (double **)calloc(0, sizeof(double *));
	double **B = (double **)calloc(0, sizeof(double *));

	int rows = 0;
	int cols = 0;
	int current_col = 0;
	char *line = NULL;
	while ((line = get_line(f))) {
		A = (double **)realloc(A, (rows + 1) * sizeof(double *));
		B = (double **)realloc(B, (rows + 1) * sizeof(double *));

		char *w = strtok(line, " ");
		while (w) {
			double num = atof(w);
			
			if (current_col > 0) A[rows] = (double *)realloc(A[rows], (current_col + 1) * sizeof(double)); 
			else A[rows] = (double *)calloc(current_col + 1, sizeof(double));
			A[rows][current_col++] = num;

			w = strtok(NULL, " ");
		}
		
		B[rows] = (double *)calloc(1, sizeof(double));
		memcpy(&B[rows][0], &A[rows][current_col - 1], sizeof(double));
		A[rows] = (double *)realloc(A[rows], (current_col - 1) * sizeof(double));
		
		rows++;
		cols = current_col - 1;
		current_col = 0;
		free(line);
	}

	*A_out = A;
	*B_out = B;
	*A_rows = rows;
	*A_cols = cols;

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
