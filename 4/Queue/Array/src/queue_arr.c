#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "common.h"
#include "queue_arr.h"


STUDENT **find_by_field_queue_a(QUEUE_A *queue, char *field, char *search_term, int *found_count) {
	if (queue->count == 0) return NULL;

	int students_count = 0;
	STUDENT **students = (STUDENT **)calloc(students_count, sizeof(STUDENT *));

	if (strncmp(field, "imie", strlen(field)) == 0) {
		for (int i = 0; i < queue->count; i++) {
			STUDENT *student = queue->students[i];
			if (strncmp(student->name, search_term, strlen(search_term)) == 0) {
				students = (STUDENT **)realloc(students, (++students_count) * sizeof(STUDENT *));
				students[students_count - 1] = student;
			}
		}
	} else if (strncmp(field, "nazwisko", strlen(field)) == 0) {
		for (int i = 0; i < queue->count; i++) {
			STUDENT *student = queue->students[i];
			if (strncmp(student->surname, search_term, strlen(search_term)) == 0) {
				students = (STUDENT **)realloc(students, (++students_count) * sizeof(STUDENT *));
				students[students_count - 1] = student;
			}
		}	
	} else if (strncmp(field, "rok", strlen(field)) == 0) {
		for (int i = 0; i < queue->count; i++) {
			STUDENT *student = queue->students[i];
			if (student->year == atoi(search_term)) {
				students = (STUDENT **)realloc(students, (++students_count) * sizeof(STUDENT *));
				students[students_count - 1] = student;
			}
		}
	} else
		fprintf(stderr, "Niepoprawne pole!\n");

	if (!students_count) free(students);

	*found_count = students_count;

	return (!students_count) ? NULL : students;

	return NULL;
}

STUDENT *dequeue_a(QUEUE_A *queue) {
	STUDENT *student = queue->students[0];

	for (int i = 0; i < queue->count - 1; i++)
		queue->students[i] = queue->students[i + 1];

	queue->students = (STUDENT **)realloc(queue->students, --queue->count * sizeof(STUDENT *));

	return student;
}

void enqueue_a(QUEUE_A *queue, STUDENT *student) {
	queue->students = (STUDENT **)realloc(queue->students, ++queue->count * sizeof(STUDENT));
	queue->students[queue->count - 1] = student;

	return;
}

void print_queue_a(QUEUE_A *queue) {
	printf("\nLiczba studentow w kolejce: %d\n\n", queue->count);
	if (queue->count == 0) return;

	for (int i = 0; i < queue->count; i++) {
		STUDENT *current = queue->students[i];

		printf("imie: %s\n", current->name);
		printf("nazwisko: %s\n", current->surname);
		printf("rok: %d\n\n", current->year);
	}

	return;
}

void delete_queue_a(QUEUE_A *queue) {
	for (int i = 0; i < queue->count; i++) {
		STUDENT *current = queue->students[i];

		free(current->name);
		free(current->surname);
		free(current);
	}

	free(queue->students);
	free(queue);

	return;
}

QUEUE_A *init_queue_a() {
	QUEUE_A *queue = (QUEUE_A *)malloc(sizeof(QUEUE_A));
	if (!queue) return NULL;

	queue->count = 0;
	queue->students = (STUDENT **)calloc(0, sizeof(STUDENT *));
	if (!queue->students) {
		free(queue);
		return NULL;
	}

	return queue;
}

int save_file_queue_a(QUEUE_A *queue, char *filepath) {
	int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0) return -1;

	for (int i = 0; i < queue->count; i++) {
		STUDENT *current = queue->students[i];

		write(fd, current->name, strlen(current->name) + 1);
		write(fd, current->surname, strlen(current->surname) + 1);
		write(fd, &current->year, sizeof(int));
	}

	return 0;
}

int read_file_queue_a(QUEUE_A *queue, char *filepath) {
	int fd = open(filepath, O_RDONLY);
	if (fd < 0) return -1;

	struct stat stat_buf;
	fstat(fd, &stat_buf);

	int file_size = stat_buf.st_size;
	int total_size_read = 0;

	while (total_size_read < file_size) {
		STUDENT *student = (STUDENT *)malloc(sizeof(STUDENT));
		student->name = (char *)calloc(0, sizeof(char));
		student->surname = (char *)calloc(0, sizeof(char));
		student->year = 0;
	
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

		queue->students[queue->count++] = student;
	}

	return 0;
}

