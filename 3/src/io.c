#include <stdio.h>

#include "common.h"
#include "io.h"

int open_file(char *filepath, char *mode, FILE **f_out) {
	FILE *f = fopen(filepath, mode);
	if (!f) return STATUS_ERROR;

	*f_out = f;

	return STATUS_SUCCESS;
}
