#include <stdio.h>

#include "common.h"
#include "validate.h"

int validate_options(OPTIONS *opts) {
	if (opts->e < 0) {
		fprintf(stderr, "Dokładność musi być liczbą dodatnią!\n");
		return -1;
	}
	if (opts->n < 0) {
		fprintf(stderr, "Liczba podziałów musi być dodatnia!\n");
		return -1;
	}
	if (opts->a <= -1) {
		opts->a = -1 + opts->e;
		fprintf(stderr, "Dla a <= -1 funkcja jest nieokreślona!\n");
		printf("Wartość a została zawężona do %lf\n", opts->a);
	}
	if (opts->a > opts->b) {
		fprintf(stderr, "Wartość a powinna być mniejsza od b!\n");
		return -1;
	}
	if (opts->b >= 1) {
		opts->b = 1 - opts->e;
		fprintf(stderr, "Dla b >= 1 funkcja jest nieokreślona!\n");
		printf("Wartość b została zawężona do %lf\n", opts->b);
	}

	FILE *f = fopen(opts->filepath, "w+");
	if (f == NULL) {
		fprintf(stderr, "Ścieżka do pliku jest nieprawidłowa!\n");
		fprintf(stderr, "Prawdopodobnie nie istnieje folder, w którym plik ma zostać utworzony, lub opcja nie została podana.\n");
		return -1;
	}
	fclose(f);

	return 0;
}

