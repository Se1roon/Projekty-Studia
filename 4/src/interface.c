#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "interface.h"
#include "stack_arr.h"
#include "stack_list.h"


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

void handle_stack_list() {
	STACK_L *stack = init_stack_l(NULL);

	int inter_op = -1;
	while (1) {
		print_menu();
		char *op_inp = get_line(stdin);
		inter_op = atoi(op_inp);
		free(op_inp);

		printf("\n");
		switch (inter_op) {
			case PUSH:
				STUDENT_L *new_student = read_student_l_stdin();
				if (!new_student) {
					fprintf(stderr, "Nie udalo sie wczytac studenta!\n");
					break;
				}
				
				push_stack_l(stack, new_student);
				print_stack_l(stack);
				break;
			case POP:
				STUDENT_L *student = pop_stack_l(stack);
				if (!student) {
					printf("Nie moge pobrac studenta z pustego stosu\n");
					break;
				}

				printf("Pobralem studenta: %s\n", student->name);
				print_stack_l(stack);

				free(student->name);
				free(student->surname);
				free(student);
				break;
			case CLEAR:
				delete_stack_l(stack);
				stack = init_stack_l(NULL);
				print_stack_l(stack);
				break;
			case FIND:
				printf("Podaj pole do wyszukania> ");
				char *field_temp = get_line(stdin);
				char *field = to_lower_str(field_temp);
				free(field_temp);

				printf("Podaj %s> ", field);
				char *search_term = get_line(stdin);
			
				printf("\n");
				STUDENT_L *found_student = find_by_field_stack_l(stack, field, search_term); // this doesn't make a copy
				if (found_student) {
					printf("Znaleziono:\n");
					printf("imie: %s\n", found_student->name);
					printf("nazwisko: %s\n", found_student->surname);
					printf("rok: %d\n\n", found_student->year);
				} else 
					printf("Nie znaleziono takiego studenta.\n\n");

				free(field);
				free(search_term);
				break;
			case SAVE_TO_FILE: 
				if (stack->count == 0) {
					printf("Nie ma czego zapisywac\n");
					break;
				}

				printf("Podaj nazwe pliku do zapisania> ");
				char *save_file = get_line(stdin);

				save_list_file(save_file, stack->head);
				
				free(save_file);
				break;
			case READ_FROM_FILE: break;
			case FINISH:
				delete_stack_l(stack);
				return;
			default:
				fprintf(stderr, "Nie wiem o co ci chodzi\n");
		}
	}

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
			case SAVE_TO_FILE: 
				printf("Podaj nazwe pliku do zapisania> ");
				char *save_file = get_line(stdin);

				save_array_file(save_file, stack->students, stack->count);
				
				free(save_file);
				break;
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
