#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "common.h"
#include "parse.h"
#include "io.h"
#include "calc.h"

// TODO: Extract error handling logic to separate module

int clear(FILE *, double **A, double **B, int size);

int main(int argc, char *argv[]) {
	char *filepath = NULL;
	
	if (parse_options(argc, argv, &filepath) == STATUS_ERROR) return STATUS_ERROR;
	if (!filepath) {
		printf("Ścieżka do pliku z równaniami nie została podana!\n");
		print_usage(argv);
		return STATUS_ERROR;
	}

	FILE *input_file = NULL;
	if (open_file(filepath, "r", &input_file) == STATUS_ERROR) {
		fprintf(stderr, "Podany plik nie istnieje!\n");
		return STATUS_ERROR;
	}

	double **A = NULL;
	double **B = NULL;
	int A_size = -1;
	if (parse_matrices(input_file, &A, &B, &A_size) == STATUS_ERROR) {
		fprintf(stderr, "Nie jestem w stanie rozpoznać podanych równań!\n");
		fclose(input_file);
		return STATUS_ERROR;
	}

	// TODO: Output to file & maybe make the output prettier

	for (int i = 0; i < A_size; i++) {
		if (i == A_size - 1) printf("x%d = %lf\n", i, calc_x(A, B, i, A_size));
		else printf("x%d = %lf, ", i, calc_x(A, B, i, A_size));
	}

	clear(input_file, A, B, A_size);
	return STATUS_SUCCESS;
}

int clear(FILE *f, double **A, double **B, int size) {
	fclose(f);

	for (int i = 0; i < size; i++)
		free(A[i]);
	free(A);

	for (int i = 0; i < size; i++)
		free(B[i]);
	//free(B); TODO: Tu jest bug jakiś z przykładem r2

	return STATUS_SUCCESS;
}
