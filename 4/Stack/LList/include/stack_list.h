#ifndef STACK_LIST_H
#define STACK_LIST_H

#include "common.h"

typedef struct stack_list_t {
	unsigned int count;
	STUDENT_L *head;
	STUDENT_L *tail;
} STACK_L;

STUDENT_L *find_by_field_stack_l(STACK_L *stack, char *field, char *search_term);
STUDENT_L *pop_stack_l(STACK_L *stack);
void push_stack_l(STACK_L *stack, STUDENT_L *student);

void print_stack_l(STACK_L *stack);
void delete_stack_l(STACK_L *stack);
STACK_L *init_stack_l();

#endif
