#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "common.h"
#include "stack_arr.h"


STUDENT *find_by_field_stack_a(STACK_A *stack, char *field, char *search_term) {
	bool is_found = false;
	STUDENT *student = (STUDENT *)malloc(sizeof(STUDENT));
	if (strncmp(field, "imie", strlen(field)) == 0) {
		for (int i = 0; i < stack->count; i++) {
			if (strncmp(stack->students[i].name, search_term, strlen(search_term)) == 0) {
				student_cpy(student, &stack->students[i]);
				is_found = true;
			}
		}
	} else if (strncmp(field, "nazwisko", strlen(field)) == 0) {
		for (int i = 0; i < stack->count; i++) {
			if (strncmp(stack->students[i].surname, search_term, strlen(search_term)) == 0) {
				student_cpy(student, &stack->students[i]);
				is_found = true;
			}
		}
	} else if (strncmp(field, "rok", strlen(field)) == 0) {
		for (int i = 0; i < stack->count; i++) {
			if (stack->students[i].year == atoi(search_term)) {
				student_cpy(student, &stack->students[i]);
				is_found = true;
			}
		}
	} else
		return NULL;	

	return (is_found) ? student : NULL;
}

void remove_items_stack_a(STACK_A *stack) {
	for (int i = 0; i < stack->count; i++)
		del_student(&stack->students[i]);
	stack->students = (STUDENT *)calloc(0, sizeof(STUDENT));
	stack->count = 0;

	return;
}

int size_stack_a(STACK_A *stack) {
	return (stack) ? stack->count : -1;
}

STUDENT *pop_stack_a(STACK_A *stack) {
	if (stack->count <= 0) return NULL;

	STUDENT *student = (STUDENT *)malloc(sizeof(STUDENT));
	memcpy(student, &stack->students[--stack->count], sizeof(STUDENT));
	stack->students = (STUDENT *)realloc(stack->students, stack->count * sizeof(STUDENT)); // Not sure if realloc will free name and sur

	return student;
}

void add_item_a(STACK_A *stack, STUDENT *student) {
	stack->students = (STUDENT *)realloc(stack->students, (++stack->count) * sizeof(STUDENT));
	memcpy(&stack->students[stack->count - 1], student, sizeof(STUDENT));
	free(student);
	
	return;
}

void print_stack_a(STACK_A *stack) {
	printf("Liczba studentow na stosie: %d\n\n", stack->count);
	printf("*\n");
	for (int i = stack->count - 1; i >= 0; i--) {
		printf("imie: %s\n", stack->students[i].name);
		printf("nazwisko: %s\n", stack->students[i].surname);
		printf("rok: %d\n", stack->students[i].year);
		printf("\n");
	}
}

STACK_A *init_stack_a(FILE *in_file) {
	STACK_A *stack = (STACK_A *)malloc(sizeof(STACK_A));
	stack->count = 0;
	stack->students = (STUDENT *)calloc(0, sizeof(STUDENT));

	if (!in_file) return stack;

	STUDENT *s = NULL;
	while ((s = read_student_file(in_file))) {
		stack->students = (STUDENT *)realloc(stack->students, (++stack->count) * sizeof(STUDENT));
		memcpy(&stack->students[stack->count - 1], s, sizeof(STUDENT));
		free(s);
	}

	return stack;
}

void del_stack_a(STACK_A *stack) {
	if (stack) {
		for (int i = 0; i < stack->count; i++)
			del_student(&stack->students[i]);
		free(stack->students);
		free(stack);
	}

	return;
}
