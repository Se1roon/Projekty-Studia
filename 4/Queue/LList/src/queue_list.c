#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "common.h"
#include "queue_list.h"


void add_last_q(QUEUE_L *queue, STUDENT_L *student);
void add_head_q(QUEUE_L *queue, STUDENT_L *student);


STUDENT_L **find_by_field_queue_l(QUEUE_L *queue, char *field, char *search_term, int *found_count) {
	if (queue->count == 0) return NULL;

	int students_count = 0;
	STUDENT_L **students = (STUDENT_L **)calloc(students_count, sizeof(STUDENT_L *));

	STUDENT_L *student = queue->head;
	if (strncmp(field, "imie", strlen(field)) == 0) {
		while (student)	{
			if (strncmp(student->name, search_term, strlen(search_term)) == 0) {
				students = (STUDENT_L **)realloc(students, (++students_count) * sizeof(STUDENT_L *));
				students[students_count - 1] = student;
			}
			student = student->next;
		}
	} else if (strncmp(field, "nazwisko", strlen(field)) == 0) {
		while (student) {
			if (strncmp(student->surname, search_term, strlen(search_term)) == 0) {
				students = (STUDENT_L **)realloc(students, (++students_count) * sizeof(STUDENT_L *));
				students[students_count - 1] = student;
			}
			student = student->next;
		}
	} else if (strncmp(field, "rok", strlen(field)) == 0) {
		while (student) {
			if (student->year == atoi(search_term)) {
				students = (STUDENT_L **)realloc(students, (++students_count) * sizeof(STUDENT_L *));
				students[students_count - 1] = student;	
			}
			student = student->next;
		}
	} else
		fprintf(stderr, "Niepoprawne pole!\n");

	if (!students_count) free(students);

	*found_count = students_count;

	return (!students_count) ? NULL : students;
}

STUDENT_L *dequeue_l(QUEUE_L *queue) {
	if (queue->count == 0) return NULL;

	STUDENT_L *student = queue->head;
	queue->head = student->next;
	student->next = NULL;

	queue->count--;
	return student;
}

void enqueue_l(QUEUE_L *queue, STUDENT_L *student) {
	add_last_q(queue, student);
	return;
}

void print_queue_l(QUEUE_L *queue) {
	printf("\nLiczba studentow w kolejce: %d\n\n", queue->count);
	if (queue->count == 0) return;

	STUDENT_L *current = queue->head;
	while (current) {
		printf("imie: %s\n", current->name);
		printf("nazwisko: %s\n", current->surname);
		printf("rok: %d\n\n", current->year);
		
		current = current->next;
	}

	return;
}

void delete_queue_l(QUEUE_L *queue) {
	if (queue->count > 0) {
		STUDENT_L *current = queue->head;
		while (current) {
			STUDENT_L *next = current->next;

			free(current->name);
			free(current->surname);
			free(current);

			current = next;
		}
	}

	free(queue);
	return;
}

QUEUE_L *init_queue_l() {
	QUEUE_L *queue = (QUEUE_L *)malloc(sizeof(QUEUE_L));
	if (!queue) {
		perror("malloc");
		return NULL;
	}

	queue->count = 0;
	queue->head = queue->tail = NULL;

	return queue;
}

int save_file_queue_l(QUEUE_L *queue, char *filepath) {
	int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0) return -1;

	STUDENT_L *current = queue->head;
	while (current) {
		write(fd, current->name, strlen(current->name) + 1);
		write(fd, current->surname, strlen(current->surname) + 1);
		write(fd, &current->year, sizeof(int));

		current = current->next;
	}

	return 0;
}

int read_file_queue_l(QUEUE_L *queue, char *filepath) {
	int fd = open(filepath, O_RDONLY);
	if (fd < 0) return -1;

	struct stat stat_buf;
	fstat(fd, &stat_buf);

	int file_size = stat_buf.st_size;
	int total_size_read = 0;

	while (total_size_read < file_size) {
		STUDENT_L *student = (STUDENT_L *)malloc(sizeof(STUDENT_L));
		student->name = (char *)calloc(0, sizeof(char));
		student->surname = (char *)calloc(0, sizeof(char));
		student->year = 0;
		student->next = NULL;
	
		int name_len = 0;
		int surname_len = 0;

		char c;
		while (read(fd, &c, sizeof(char))) {
			student->name = (char *)realloc(student->name, (++name_len) * sizeof(char));
			student->name[name_len - 1] = c;
			if (c == 0) break; 
		}
		total_size_read += name_len;

		while (read(fd, &c, sizeof(char))) {
			student->surname = (char *)realloc(student->surname, (++surname_len) * sizeof(char));
			student->surname[surname_len - 1] = c;
			if (c == 0) break;
		}
		total_size_read += surname_len;

		read(fd, &student->year, sizeof(int));
		total_size_read += sizeof(int);

		add_last_q(queue, student);
	}

	return 0;
}


/************************************
 ********* UTILITY FUNCTIONS ********
 ************************************/

void add_last_q(QUEUE_L *queue, STUDENT_L *student) {
	if (queue->count == 0)
		queue->head = queue->tail = student;
	else {
		queue->tail->next = student;
		queue->tail = student;
	}

	queue->count++;
	return;
}

void add_head_q(QUEUE_L *queue, STUDENT_L *student) {
	if (queue->count == 0)
		queue->head = queue->tail = student;
	else {
		student->next = queue->head;
		queue->head = student;
	}

	queue->count++;
	return;
}

