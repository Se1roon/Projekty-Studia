#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "common.h"
#include "stack_arr.h"


STUDENT *find_by_field_stack_a(STACK_A *stack, char *field, char *search_term) {
	return NULL;	
}

STUDENT *pop_stack_a(STACK_A *stack) {
	STUDENT *student = stack->students[stack->count - 1];
	
	stack->students = (STUDENT **)realloc(stack->students, --stack->count * sizeof(STUDENT));

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
	stack->students = (STUDENT **)calloc(0, sizeof(STUDENT));
	if (!stack->students) {
		free(stack);
		return NULL;
	}

	return stack;
}
