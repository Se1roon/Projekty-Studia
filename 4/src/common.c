#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "common.h"


void student_cpy(STUDENT *dest, STUDENT *src) {
	dest->name = (char *)calloc(strlen(src->name) + 1, sizeof(char));
	strncpy(dest->name, src->name, strlen(src->name));

	dest->surname = (char *)calloc(strlen(src->surname) + 1, sizeof(char));
	strncpy(dest->surname, src->surname, strlen(src->surname));

	dest->year = src->year;

	return;
}

char *to_lower_str(char *text) {
	int text_len = strlen(text); // excluding /0
	char *output = (char *)calloc(text_len + 1, sizeof(char));
	int i;
	for (i = 0; i < text_len; i++)
		output[i] = tolower(text[i]);
	output[i] = '\0';

	return output;
}

STUDENT *read_student_stdin() {
	STUDENT *student = (STUDENT *)malloc(sizeof(STUDENT));

	printf("Podaj imie: ");
	if (!(student->name = get_line(stdin))) {
		free(student);
		return NULL;
	}

	printf("Podaj nazwisko: ");
	if (!(student->surname = get_line(stdin))) {
		free(student->name);
		free(student);
		return NULL;
	}

	printf("Podaj rok urodzenia: ");
	char *year_str = get_line(stdin);
	if (!(student->year = atoi(year_str))) {
		free(student->name);
		free(student->surname);
		free(student);
		free(year_str);
		return NULL;
	}
	free(year_str);

	return student;
}

STUDENT *read_student_file(FILE *f) {
	STUDENT *student = (STUDENT *)malloc(sizeof(STUDENT));
	
	if (!(student->name = get_line(f))) {
		free(student);
		return NULL;
	}

	if (!(student->surname = get_line(f))) {
		free(student->name);
		free(student);
		return NULL;
	}

	char *year_str = get_line(f);
	if (!(student->year = atoi(year_str))) {
		free(student->surname);
		free(student->name);
		free(student);
		free(year_str);
		return NULL;
	}
	free(year_str);

	return student;
}

void del_student(STUDENT *student) {
	if (student->name) {
		free(student->name);
		student->name = NULL;
	}
	if (student->surname) {
		free(student->surname);
		student->surname = NULL;
	}

	return;
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