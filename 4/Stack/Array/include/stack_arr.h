#ifndef STACK_ARR_H
#define STACK_ARR_H

#include <stdio.h>

#include "common.h"

typedef struct stack_arr_t {
	unsigned int count;
	STUDENT *students;
} STACK_A;

STUDENT *find_by_field_stack_a(STACK_A *stack, char *field, char *search_term);
STUDENT *pop_stack_a(STACK_A *);
void add_item_a(STACK_A *, STUDENT *);
void print_stack_a(STACK_A *);
void remove_items_stack_a(STACK_A *stack);

int size_stack_a(STACK_A *);
void del_stack_a(STACK_A *);
STACK_A *init_stack_a();

#endif
