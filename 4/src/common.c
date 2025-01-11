#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

#include "common.h"


char *to_lower_str(char *text) {
	char *output = (char *)calloc(strlen(text) + 1, sizeof(char));
	for (int i = 0; i < strlen(text) + 1; i++) 
		output[i] = tolower(text[i]);

	return output;
}

STUDENT_L *read_student_l_stdin() {
	STUDENT_L *student = (STUDENT_L *)malloc(sizeof(STUDENT_L));
	if (!student) return NULL;
	student->next = NULL;

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
