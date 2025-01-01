#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

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
	free(student->name);
	free(student->surname);

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
