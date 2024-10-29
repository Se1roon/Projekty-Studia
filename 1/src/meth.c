#include <stdio.h>
#include <math.h>

#include "common.h"
#include "meth.h"

double calculate_sum(OPTIONS *opts, double x, short *warunek, int *liczba_elementów) {
	double licznik = 1.0;
	double mianownik = 1.0;
	double suma = 0;
	double element;
	int num_elementu = 0;

	do {
		element = licznik/mianownik * pow(x, num_elementu);
		
		if (num_elementu == 0) licznik = -1;
		else licznik = pow(-1, num_elementu-1) * (fabs(licznik) * (3 * num_elementu + 1));
		mianownik *= (3 * (num_elementu + 1));

		suma += element;
		num_elementu++;
	} while (num_elementu <= M && fabs(element) > opts->e);

	if (num_elementu >= M && fabs(element) <= opts->e) *warunek = 2; // Oba
	else if (num_elementu >= M && fabs(element) > opts->e) *warunek = 1; // Limit
	else *warunek = 0; // Dok

//	*warunek = (num_elementu >= M) ? -1 : 1;
	*liczba_elementów = num_elementu;

	return suma;
}
