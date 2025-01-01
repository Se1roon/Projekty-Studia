#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "stack_arr.h"

// TODO: Maybe add validation to add, pop functions (check for stack and student being NULL etc)

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

STUDENT *pop_item_a(STACK_A *stack) {
	if (stack->count <= 0) {
		fprintf(stderr, "Could not remove an item from empty stack!\n");
		del_stack_a(stack);
		exit(-2);
	} 

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
	printf("Number of students: %d\n\n", stack->count);
	printf("TOP OF THE STACK\n");
	for (int i = stack->count - 1; i >= 0; i--) {
		printf("Name: %s\n", stack->students[i].name);
		printf("Surname: %s\n", stack->students[i].surname);
		printf("Year: %d\n", stack->students[i].year);
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
