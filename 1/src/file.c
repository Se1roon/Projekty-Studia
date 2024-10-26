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


