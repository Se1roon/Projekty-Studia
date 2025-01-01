#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "interface.h"
#include "stack_arr.h"

enum INTER_OP {
	OP_PAD, // not important
	PUSH,
	POP,
	CLEAR,
	FIND,
	SAVE_TO_FILE,
	READ_FROM_FILE,
	FINISH, 
	OP_TOT
};

char menu_op[7][20] = {
	"1 - push",
	"2 - pop",
	"3 - clear",
	"4 - find",
	"5 - save to file",
	"6 - read from file",
	"7 - finish"
};

void print_menu() {
	for (int i = 0; i < 7; i++)
		printf("%s\n", menu_op[i]);
	printf("> ");
	return;
}

void handle_stack_array() {
	STACK_A *stack = init_stack_a(NULL);

	int inter_op = -1;
	do {
		print_menu();
		char *op_inp = get_line(stdin);
		inter_op = atoi(op_inp);
		free(op_inp);

		switch (inter_op) {
			case PUSH:
				STUDENT *new_student = read_student_stdin();
				if (!new_student) {
					fprintf(stderr, "Nie udalo sie wczytac studenta!\n");
					break;
				}
				add_item_a(stack, new_student); // After that call *new_student is freed
				print_stack_a(stack);
				break;
			case POP: 
				if (size_stack_a(stack) <= 0) {
					fprintf(stderr, "Nie moge pobrac studenta z pustego stosu!\n");
					break;
				}

				STUDENT *student = pop_item_a(stack);
				printf("Pobralem studenta: %s\n", student->name);
				print_stack_a(stack);

				del_student(student);
				free(student);
				break;
			case CLEAR: 
				del_stack_a(stack);
				stack = init_stack_a(NULL);
				print_stack_a(stack);
				break;
			case FIND: break;
			case SAVE_TO_FILE: break;
			case READ_FROM_FILE: 
				// Delete previously allocated stack if needed
				// ask for filepath
				// read from it
				break;
			case FINISH:
				del_stack_a(stack);
				return;
			default:
				fprintf(stderr, "Nie wiem o co ci chodzi\n");
		}
	} while (1);

	return;
}
