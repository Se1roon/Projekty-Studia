#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "common.h"
#include "stack_arr.h"


STUDENT **find_by_field_stack_a(STACK_A *stack, char *field, char *search_term, int *found_count) {
	if (stack->count == 0) return NULL;

	int students_count = 0;
	STUDENT **students = (STUDENT **)calloc(students_count, sizeof(STUDENT *));

	if (strncmp(field, "imie", strlen(field)) == 0) {
		for (int i = 0; i < stack->count; i++) {
			STUDENT *student = stack->students[i];
			if (strncmp(student->name, search_term, strlen(search_term)) == 0) {
				students = (STUDENT **)realloc(students, (++students_count) * sizeof(STUDENT *));
				students[students_count - 1] = student;
			}
		}
	} else if (strncmp(field, "nazwisko", strlen(field)) == 0) {
		for (int i = 0; i < stack->count; i++) {
			STUDENT *student = stack->students[i];
			if (strncmp(student->surname, search_term, strlen(search_term)) == 0) {
				students = (STUDENT **)realloc(students, (++students_count) * sizeof(STUDENT *));
				students[students_count - 1] = student;
			}
		}	
	} else if (strncmp(field, "rok", strlen(field)) == 0) {
		for (int i = 0; i < stack->count; i++) {
			STUDENT *student = stack->students[i];
			if (student->year == atoi(search_term)) {
				students = (STUDENT **)realloc(students, (++students_count) * sizeof(STUDENT *));
				students[students_count - 1] = student;
			}
		}
	} else
		fprintf(stderr, "Niepoprawne pole!\n");

	if (!students_count) free(students);

	*found_count = students_count;

	return (!students_count) ? NULL : students;
}

STUDENT *pop_stack_a(STACK_A *stack) {
	if (stack->count == 0) return NULL;

	STUDENT *student = stack->students[--stack->count];
	
	if (stack->count == 0) {
		free(stack->students);
		stack->students = (STUDENT **)calloc(0, sizeof(STUDENT *));
	} else stack->students = (STUDENT **)realloc(stack->students, stack->count * sizeof(STUDENT));

	return student;
}

void push_stack_a(STACK_A *stack, STUDENT *student) {
	stack->students = (STUDENT **)realloc(stack->students, ++stack->count * sizeof(STUDENT));
	stack->students[stack->count - 1] = student;
	
	return;
}

void print_stack_a(STACK_A *stack) {
	printf("\nLiczba studentow na stosie: %d\n\n", stack->count);
	if (stack->count == 0) return;

	for (int i = stack->count - 1; i >= 0; i--)	 {
		printf("imie: %s\n", stack->students[i]->name);
		printf("nazwisko: %s\n", stack->students[i]->surname);
		printf("rok: %d\n\n", stack->students[i]->year);
	}

	return;
}

void delete_stack_a(STACK_A *stack) {
	for (int i = 0; i < stack->count; i++) {
		STUDENT *current = stack->students[i];

		free(current->name);
		free(current->surname);
		free(current);
	}

	free(stack->students);
	free(stack);

	return;
}

STACK_A *init_stack_a() {
	STACK_A *stack = (STACK_A *)malloc(sizeof(STACK_A));
	if (!stack) return NULL;

	stack->count = 0;
	stack->students = (STUDENT **)calloc(0, sizeof(STUDENT *));
	if (!stack->students) {
		free(stack);
		return NULL;
	}

	return stack;
}

int save_file_stack_a(STACK_A *stack, char *filepath) {
	int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0) return -1;

	for (int i = 0; i < stack->count; i++) {
		STUDENT *current = stack->students[i];

		write(fd, current->name, strlen(current->name) + 1);
		write(fd, current->surname, strlen(current->surname) + 1);
		write(fd, &current->year, sizeof(int));
	}

	return 0;
}

int read_file_stack_a(STACK_A *stack, char *filepath) {
	int fd = open(filepath, O_RDONLY);
	if (fd < 0) return -1;

	struct stat stat_buf;
	fstat(fd, &stat_buf);

	int file_size = stat_buf.st_size;
	int total_size_read = 0;

	while (total_size_read < file_size) {
		STUDENT *student = (STUDENT *)malloc(sizeof(STUDENT));
		student->name = (char *)calloc(0, sizeof(char));
		student->surname = (char *)calloc(0, sizeof(char));
		student->year = 0;
	
		int name_len = 0;
		int surname_len = 0;

		char c;
		while (read(fd, &c, sizeof(char))) {
			student->name = (char *)realloc(student->name, (++name_len) * sizeof(char));
			student->name[name_len - 1] = c;
			if (c == 0) break; 
		}
		total_size_read += name_len;

		while (read(fd, &c, sizeof(char))) {
			student->surname = (char *)realloc(student->surname, (++surname_len) * sizeof(char));
			student->surname[surname_len - 1] = c;
			if (c == 0) break;
		}
		total_size_read += surname_len;

		read(fd, &student->year, sizeof(int));
		total_size_read += sizeof(int);

		stack->students = (STUDENT **)realloc(stack->students, ++stack->count * sizeof(STUDENT *));
		stack->students[stack->count - 1] = student;
	}

	return 0;
}
