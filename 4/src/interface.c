#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "interface.h"
#include "stack_arr.h"
#include "stack_list.h"
#include "queue_arr.h"
#include "queue_list.h"


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

void handle_queue_array() {
	QUEUE_A *queue = init_queue_a();

	int inter_op = -1;
	while (1) {
		print_menu();
		char *op_inp = get_line(stdin);
		inter_op = atoi(op_inp);
		free(op_inp);

		printf("\n");
		switch (inter_op) {
			case PUSH:
				STUDENT *new_student = read_student_stdin();
				if (!new_student) {
					fprintf(stderr, "Nie udalo sie wczytac studenta!\n\n");
					break;
				}
				
				enqueue_a(queue, new_student);
				print_queue_a(queue);
				break;
			case POP:
				STUDENT *student = dequeue_a(queue);
				if (!student) {
					fprintf(stderr, "Nie udalo sie pobrac studenta!\n\n");
					break;
				}

				printf("Pobralem studenta: %s\n", student->name);
				print_queue_a(queue);
	
				free(student->name);
				free(student->surname);
				free(student);
				break;
			case CLEAR:
				delete_queue_a(queue);
				queue = init_queue_a();
				print_queue_a(queue);
				break;
			case FIND:
				printf("Podaj pole do wyszukania> ");
				char *field_temp = get_line(stdin);
				char *field = to_lower_str(field_temp);
				free(field_temp);

				printf("Podaj %s> ", field);
				char *search_term = get_line(stdin);
			
				printf("\n");
				STUDENT *found_student = find_by_field_queue_a(queue, field, search_term);
				if (found_student) {
					printf("Znaleziono:\n");
					printf("imie: %s\n", found_student->name);
					printf("nazwisko: %s\n", found_student->surname);
					printf("rok: %d\n\n", found_student->year);

					free(found_student->name);
					free(found_student->surname);
					free(found_student);
				} else 
					printf("Nie znaleziono takiego studenta.\n\n");

				
				free(field);
				free(search_term);
				break;
			case SAVE_TO_FILE: 
				break;
			case READ_FROM_FILE: 
				break;
			case FINISH:
				delete_queue_a(queue);
				return;
			default:
				fprintf(stderr, "Nie wiem o co ci chodzi\n\n");
		}
	}

	return;
}

void handle_queue_list() {
	QUEUE_L *queue = init_queue_l();

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
					fprintf(stderr, "Nie udalo sie wczytac studenta!\n\n");
					break;
				}
				
				enqueue_l(queue, new_student);
				print_queue_l(queue);
				break;
			case POP:
				STUDENT_L *student = dequeue_l(queue);
				if (!student) {
					printf("Nie moge pobrac studenta z pustego stosu\n\n");
					break;
				}

				printf("Pobralem studenta: %s\n", student->name);
				print_queue_l(queue);

				free(student->name);
				free(student->surname);
				free(student);
				break;
			case CLEAR:
				delete_queue_l(queue);
				queue = init_queue_l();
				print_queue_l(queue);
				break;
			case FIND:
				printf("Podaj pole do wyszukania> ");
				char *field_temp = get_line(stdin);
				char *field = to_lower_str(field_temp);
				free(field_temp);

				printf("Podaj %s> ", field);
				char *search_term = get_line(stdin);
			
				printf("\n");

				int found_students_count = -1;
				// this doesn't make a copy of found students
				STUDENT_L **found_students = find_by_field_queue_l(queue, field, search_term, &found_students_count); 
				if (found_students) {
					printf("Znaleziono:\n");
					for (int i = 0; i < found_students_count; i++) {
						printf("imie: %s\n", found_students[i]->name);
						printf("nazwisko: %s\n", found_students[i]->surname);
						printf("rok: %d\n\n", found_students[i]->year);
					}
					free(found_students);
				} else 
					printf("Nie znaleziono takiego studenta.\n\n");

				free(field);
				free(search_term);
				break;
			case SAVE_TO_FILE: 
				if (queue->count == 0) {
					printf("Nie ma czego zapisywac\n\n");
					break;
				}

				printf("Podaj nazwe pliku do zapisania> ");
				char *save_file = get_line(stdin);

				printf("\n");
				if (save_file_queue_l(queue, save_file) < 0) {
					fprintf(stderr, "Nie udalo sie zapisac danych do pliku\n\n");
					free(save_file);
					break;
				}
				
				free(save_file);
				break;
			case READ_FROM_FILE: 
				delete_queue_l(queue);
				queue = init_queue_l();

				printf("Podaj nazwe pliku do wczytania> ");
				char *read_file = get_line(stdin);

				if (read_file_queue_l(queue, read_file) < 0) {
					fprintf(stderr, "\nNie udalo sie odczytac danych z pliku\n\n");
					free(read_file);
					break;
				}

				print_queue_l(queue);

				free(read_file);
				break;
			case FINISH:
				delete_queue_l(queue);
				return;
			default:
				fprintf(stderr, "Nie wiem o co ci chodzi\n\n");
		}
	}

	return;
}

void handle_stack_list() {
	STACK_L *stack = init_stack_l();

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
					fprintf(stderr, "Nie udalo sie wczytac studenta!\n\n");
					break;
				}
				
				push_stack_l(stack, new_student);
				print_stack_l(stack);
				break;
			case POP:
				STUDENT_L *student = pop_stack_l(stack);
				if (!student) {
					printf("Nie moge pobrac studenta z pustego stosu\n\n");
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
				stack = init_stack_l();
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

				int found_students_count = -1;
				// this doesn't make a copy of found students
				STUDENT_L **found_students = find_by_field_stack_l(stack, field, search_term, &found_students_count); 
				if (found_students) {
					printf("Znaleziono:\n");
					for (int i = 0; i < found_students_count; i++) {
						printf("imie: %s\n", found_students[i]->name);
						printf("nazwisko: %s\n", found_students[i]->surname);
						printf("rok: %d\n\n", found_students[i]->year);
					}
					free(found_students);
				} else 
					printf("Nie znaleziono takiego studenta.\n\n");

				free(field);
				free(search_term);
				break;
			case SAVE_TO_FILE: 
				if (stack->count == 0) {
					printf("Nie ma czego zapisywac\n\n");
					break;
				}

				printf("Podaj nazwe pliku do zapisania> ");
				char *save_file = get_line(stdin);

				printf("\n");
				if (save_file_stack_l(stack, save_file) < 0) {
					fprintf(stderr, "Nie udalo sie zapisac danych do pliku\n\n");
					free(save_file);
					break;
				}
				
				free(save_file);
				break;
			case READ_FROM_FILE: 
				delete_stack_l(stack);
				stack = init_stack_l();

				printf("Podaj nazwe pliku do wczytania> ");
				char *read_file = get_line(stdin);

				if (read_file_stack_l(stack, read_file) < 0) {
					fprintf(stderr, "\nNie udalo sie odczytac danych z pliku\n\n");
					free(read_file);
					break;
				}

				print_stack_l(stack);

				free(read_file);
				break;
			case FINISH:
				delete_stack_l(stack);
				return;
			default:
				fprintf(stderr, "Nie wiem o co ci chodzi\n\n");
		}
	}

	return;
}

void handle_stack_array() {
	STACK_A *stack = init_stack_a();

	int inter_op = -1;
	while (1) {
		print_menu();
		char *op_inp = get_line(stdin);
		inter_op = atoi(op_inp);
		free(op_inp);

		printf("\n");
		switch (inter_op) {
			case PUSH:
				STUDENT *new_student = read_student_stdin();
				if (!new_student) {
					fprintf(stderr, "Nie udalo sie wczytac studenta!\n\n");
					break;
				}
				
				push_stack_a(stack, new_student);
				print_stack_a(stack);
				break;
			case POP:
				STUDENT *student = pop_stack_a(stack);
				if (!student) {
					printf("Nie moge pobrac studenta z pustego stosu\n\n");
					break;
				}

				printf("Pobralem studenta: %s\n", student->name);
				print_stack_a(stack);

				free(student->name);
				free(student->surname);
				free(student);
				break;
			case CLEAR:
				delete_stack_a(stack);
				stack = init_stack_a();
				print_stack_a(stack);
				break;
			case FIND:
				break;
			case SAVE_TO_FILE: 
				break;
			case READ_FROM_FILE: 
				break;
			case FINISH:
				delete_stack_a(stack);
				return;
			default:
				fprintf(stderr, "Nie wiem o co ci chodzi\n\n");
		}
	}

	return;
}
