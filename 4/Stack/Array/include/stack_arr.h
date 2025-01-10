#ifndef STACK_ARR_H
#define STACK_ARR_H

#include <stdio.h>

#include "common.h"


typedef struct stack_arr_t {
	unsigned int count;
	STUDENT **students;
} STACK_A;


STUDENT **find_by_field_stack_a(STACK_A *stack, char *field, char *search_term, int *found_count);
STUDENT *pop_stack_a(STACK_A *);
void push_stack_a(STACK_A *, STUDENT *);

int save_file_stack_a(STACK_A *stack, char *filepath);
int read_file_stack_a(STACK_A *stack, char *filepath);

void print_stack_a(STACK_A *);
void delete_stack_a(STACK_A *);
STACK_A *init_stack_a();

#endif
