#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "common.h"
#include "file.h"

void output_to_stdout(double x, double w_ścisła, double suma, short warunek, int liczba_elementów) {
	printf("| x=%lf", x);
	if (x < 0) {
		for (int i = 0; i < ROW_ELEM_LEN - 3 - 10; i++)
			printf(" ");
	} else {
		for (int i = 0; i < ROW_ELEM_LEN - 3 - 9; i++)
			printf(" ");
	}

	printf("| f_szereg=%lf ", suma);

	printf("| f_ścisła=%lf ", w_ścisła);

	printf("| liczba_elementów=%d", liczba_elementów);
	if (liczba_elementów >= 100) {
		for (int i = 0; i < LE_ELEM_LEN - 18 - 3; i++)
			printf(" ");
	} else if (liczba_elementów >= 10) {
		for (int i = 0; i < LE_ELEM_LEN - 18 - 2; i++)
			printf(" ");
	} else {
		for (int i = 0; i < LE_ELEM_LEN - 18 - 1; i++)
			printf(" ");
	}

	printf("| warunek_stopu: ");
	if (warunek < 0) {
		printf("Limit");
		for (int i = 0; i < WARUNEK_ELEM_LEN - 16 - 5; i++)
			printf(" ");
	} else
		printf("Dokładność ");

	printf("|\n");

	return;
}

void output_to_file(FILE *file, double x, double w_ścisła, double suma, short warunek, int liczba_elementów) {
	fprintf(file, "| x=%lf", x);
	if (x < 0) {
		for (int i = 0; i < ROW_ELEM_LEN - 3 - 10; i++)
			fprintf(file, " ");
	} else {
		for (int i = 0; i < ROW_ELEM_LEN - 3 - 9; i++)
			fprintf(file, " ");
	}

	fprintf(file, "| f_szereg=%lf ", suma);

	fprintf(file, "| f_ścisła=%lf ", w_ścisła);

	fprintf(file, "| liczba_elementów=%d", liczba_elementów);
	if (liczba_elementów >= 100) {
		for (int i = 0; i < LE_ELEM_LEN - 18 - 3; i++)
			fprintf(file, " ");
	} else if (liczba_elementów >= 10) {
		for (int i = 0; i < LE_ELEM_LEN - 18 - 2; i++)
			fprintf(file, " ");
	} else {
		for (int i = 0; i < LE_ELEM_LEN - 18 - 1; i++)
			fprintf(file, " ");
	}

	fprintf(file, "| warunek_stopu: ");
	if (warunek < 0) {
		fprintf(file, "Limit");
		for (int i = 0; i < WARUNEK_ELEM_LEN - 16 - 5; i++)
			fprintf(file, " ");
	} else
		fprintf(file, "Dokładność ");

	fprintf(file, "|\n");

	return;

}

FILE *open_file(char *filepath, char *mode) {
	FILE *f = fopen(filepath, mode);
	if (f == NULL) {
		printf("Coś poszło nie tak :(\n");
		return NULL;
	}

	return f;
}

