#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

typedef struct student_t {
	char *name;
	char *surname;
	int year;
} STUDENT;

char *conv_lowercase(char *in);
STUDENT *read_student_stdin();
STUDENT *read_student_file(FILE *f);
void del_student(STUDENT *);
char *get_line(FILE *f);

#endif
