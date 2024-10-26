#ifndef FILE_H
#define FILE_H

#define SEPARATOR_LEN	107
#define ROW_ELEM_LEN	15
#define LE_ELEM_LEN		22
#define WARUNEK_ELEM_LEN	27

#include <stdio.h>

void output_to_stdout(double x, double w_ścisła, double suma, short warunek, int liczba_elementów);
void output_to_file(FILE *file, double x, double w_ścisła, double suma, short warunek, int liczba_elementów);

FILE *open_file(char *filepath, char *mode);

#endif
