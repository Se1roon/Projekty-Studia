#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	FINISH
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

		printf("\n");
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

				STUDENT *student = pop_stack_a(stack);
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
			case FIND: 
				printf("Podaj pole do wyszukania> ");
				char *field_temp = get_line(stdin);
				char *field = to_lower_str(field_temp);
				free(field_temp);

				printf("Podaj %s> ", field);
				char *search_term = get_line(stdin);
			
				printf("\n");
				STUDENT *found_student = find_by_field_stack_a(stack, field, search_term);
				if (!found_student) {
					printf("Nic nie znaleziono :/\n");
				} else {
					printf("Znaleziono:\n");
					printf("imie: %s\n", found_student->name);
					printf("nazwisko: %s\n", found_student->surname);
					printf("rok: %d\n\n", found_student->year);
				}

				free(field);
				free(search_term);

				del_student(found_student);
				free(found_student);
				break;
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