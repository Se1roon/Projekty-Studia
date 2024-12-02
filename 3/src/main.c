#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "parse.h"
#include "io.h"
#include "calc.h"

/* TODO: Być w stanie stwierdzić czy układ jest sprzeczny czy nieoznaczony
 * TODO: Odpowiednio się zachować gdy 1 kolumna jest cała 0
 */ 

int clear(FILE *, double **A, double **B, int A_rows);
void print_results(double **A, double **B, int A_rows);
void print_matrices(double **A, double **B, int, int);
void print_usage(char *argv[]);


int main(int argc, char *argv[]) {
	char *filepath = NULL;
	FILE *input_file = NULL;

	if (parse_options(argc, argv, &filepath) == STATUS_ERROR) {
		print_usage(argv);
		return STATUS_ERROR;
	}

	if (!filepath) {
		printf("Ścieżka do pliku z równaniami nie została podana!\n");
		print_usage(argv);
		return STATUS_ERROR;
	}

	if (open_file(filepath, "r", &input_file) == STATUS_ERROR) {
		fprintf(stderr, "Podany plik nie istnieje!\n");
		return STATUS_ERROR;
	}


	double **A = NULL;
	double **B = NULL;
	int A_rows, A_cols = -1;
	if (parse_matrices(input_file, &A, &B, &A_rows, &A_cols) == STATUS_ERROR) {
		fprintf(stderr, "Nie jestem w stanie rozpoznać podanych równań!\n");
		fclose(input_file);
		return STATUS_ERROR;
	}
	
	if (validate_matrices(A, B, A_rows, A_cols) == STATUS_ERROR) {
		clear(input_file, A, B, A_rows);
		return STATUS_ERROR;
	}


	print_results(A, B, A_rows);


	clear(input_file, A, B, A_rows);
	return STATUS_SUCCESS;
}


void print_results(double **A, double **B, int size) {
	for (int i = 0; i < size; i++) {
		if (i == size - 1) printf("x%d = %lf\n", i, calc_x(A, B, i, size));
		else printf("x%d = %lf, ", i, calc_x(A, B, i, size));
	}

	return;
}

void print_matrices(double **A, double **B, int rows, int cols) {
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			if (col == cols - 1) printf("A[%d][%d] = %lf\n", row, col, A[row][col]);
			else printf("A[%d][%d] = %lf, ", row, col, A[row][col]);
		}
	}
	
	for (int row = 0; row < rows; row++)
		printf("B[%d][0] = %lf\n", row, B[row][0]);

	return;
}

void print_usage(char *argv[]) {
	printf("Usage: %s -f <plik z równaniami>\n", argv[0]);
	return;
}

int clear(FILE *f, double **A, double **B, int A_rows) {
	fclose(f);

	for (int row = 0; row < A_rows; row++) free(A[row]);
	free(A);

	for (int row = 0; row < A_rows; row++) free(B[row]);
	free(B);

	return STATUS_SUCCESS;
}
