#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "stack_list.h"

STUDENT_L *read_student_l_file(FILE *file);


STUDENT_L *find_by_field_stack_l(STACK_L *stack, char *field, char *search_term) {
	if (stack->count == 0) return NULL;

	STUDENT_L *student = stack->head;
	if (strncmp(field, "imie", strlen(field)) == 0) {
		while (student)	{
			if (strncmp(student->name, search_term, strlen(search_term)) == 0) return student;
			student = student->next;
		}
	} else if (strncmp(field, "nazwisko", strlen(field)) == 0) {
		while (student) {
			if (strncmp(student->surname, search_term, strlen(search_term)) == 0) return student;
			student = student->next;
		}
	} else if (strncmp(field, "rok", strlen(field)) == 0) {
		while (student) {
			if (student->year == atoi(search_term)) return student;
			student = student->next;
		}
	} else
		fprintf(stderr, "Niepoprawne pole!\n");

	return NULL;
}

STUDENT_L *pop_stack_l(STACK_L *stack) {
	if (stack->count == 0) return NULL;
	
	STUDENT_L *student = stack->head;
	stack->head = student->next;
	student->next = NULL;

	stack->count--;

	return student;
}

void push_stack_l(STACK_L *stack, STUDENT_L *student) {
	if (stack->count == 0)
		stack->head = stack->tail = student;
	else {
		student->next = stack->head;
		stack->head = student;
	}

	stack->count++;
	return;
}

void print_stack_l(STACK_L *stack) {
	printf("\nLiczba studentow na stosie: %d\n\n", stack->count);
	if (stack->count == 0) return;

	STUDENT_L *current = stack->head;
	while (current) {
		printf("imie: %s\n", current->name);
		printf("nazwisko: %s\n", current->surname);
		printf("rok: %d\n\n", current->year);
		current = current->next;
	}
	printf("\n");

	return;
}

void delete_stack_l(STACK_L *stack) {
	if (stack->count > 0) {
		STUDENT_L *current = stack->head;
		while (current) {
			STUDENT_L *next = current->next;
			free(current->name);
			free(current->surname);
			free(current);
			current = next;
		}
	}
	free(stack);

	return;
}

STACK_L *init_stack_l(FILE *file) {
	STACK_L *stack = (STACK_L *)malloc(sizeof(STACK_L));
	if (!stack) {
		perror("malloc");
		return NULL;
	}
	stack->count = 0;
	stack->head = NULL;
	stack->tail = NULL;

	if (!file) return stack;

	STUDENT_L *student = NULL;
	while ((student = read_student_l_file(file)))
		push_stack_l(stack, student);

	return stack;
}


/************************************
 ********* UTILITY FUNCTIONS ********
 ************************************/

STUDENT_L *read_student_l_file(FILE *file) {
	STUDENT_L *student = (STUDENT_L *)malloc(sizeof(STUDENT_L));
	if (!student) {
		perror("malloc");
		return NULL;
	}
	student->next = NULL;
	
	if (!(student->name = get_line(file))) {
		free(student);
		return NULL;
	}

	if (!(student->surname = get_line(file))) {
		free(student->name);
		free(student);
		return NULL;
	}

	char *year_str = get_line(file);
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
