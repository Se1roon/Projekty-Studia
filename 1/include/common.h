#ifndef COMMON_H
#define COMMON_H

#define FILEPATH_LEN 128

#define M 16

typedef struct options_t {
	// Zmienne definiujące przedział [a, b]
	double a;
	double b;
	// Liczba podziałów przedziału [a,b]
	double n;
	// Dokładność
	double e;
	// Ścieżka pliku do zapisania resultatów
	char filepath[FILEPATH_LEN];
} OPTIONS;

#endif
