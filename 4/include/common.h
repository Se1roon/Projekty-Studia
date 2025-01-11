#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

typedef struct student_t {
	char *name;
	char *surname;
	int year;
} STUDENT;

typedef struct student_list_t {
	char *name;
	char *surname;
	int year;
	struct student_list_t *next;
} STUDENT_L;

char *to_lower_str(char *text);
STUDENT_L *read_student_l_stdin();
STUDENT *read_student_stdin();
char *get_line(FILE *f);

#endif
