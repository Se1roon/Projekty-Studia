#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "queue_arr.h"


STUDENT *find_by_field_queue_a(QUEUE_A *queue, char *field, char *search_term) {
	if (queue->count == 0) return NULL;

	STUDENT *found_student = (STUDENT *)malloc(sizeof(STUDENT));

	if (strncmp(field, "imie", strlen(field)) == 0) {
		for (int i = 0; i < queue->count; i++) {
			if (strncmp(search_term, queue->students[i].name, strlen(search_term)) == 0) {
				STUDENT *s = &queue->students[i];

				found_student->name = (char *)calloc(strlen(s->name) + 1, sizeof(char));
				found_student->surname = (char *)calloc(strlen(s->surname) + 1, sizeof(char));
				strncpy(found_student->name, s->name, strlen(s->name) + 1);
				strncpy(found_student->surname, s->surname, strlen(s->surname) + 1);
				found_student->year = s->year;
				return found_student;
			}
		}
	} else if (strncmp(field, "nazwisko", strlen(field)) == 0) {
		for (int i = 0; i < queue->count; i++) {
			if (strncmp(search_term, queue->students[i].surname, strlen(search_term)) == 0) {
				STUDENT *s = &queue->students[i];

				found_student->name = (char *)calloc(strlen(s->name) + 1, sizeof(char));
				found_student->surname = (char *)calloc(strlen(s->surname) + 1, sizeof(char));
				strncpy(found_student->name, s->name, strlen(s->name) + 1);
				strncpy(found_student->surname, s->surname, strlen(s->surname) + 1);
				found_student->year = s->year;
				return found_student;
			}
		}
	} else if (strncmp(field, "rok", strlen(field)) == 0) {
		for (int i = 0; i < queue->count; i++) {
			if (queue->students[i].year == atoi(search_term)) {
				STUDENT *s = &queue->students[i];

				found_student->name = (char *)calloc(strlen(s->name) + 1, sizeof(char));
				found_student->surname = (char *)calloc(strlen(s->surname) + 1, sizeof(char));
				strncpy(found_student->name, s->name, strlen(s->name) + 1);
				strncpy(found_student->surname, s->surname, strlen(s->surname) + 1);
				found_student->year = s->year;
				return found_student;
			}
		}
	} else
		fprintf(stderr, "Niepoprawne pole!\n");

	free(found_student);
	return NULL;
}

STUDENT *dequeue_a(QUEUE_A *queue) {
	if (queue->count <= 0) return NULL;

	STUDENT *head = &queue->students[0];

	STUDENT *student = (STUDENT *)malloc(sizeof(STUDENT));
	student->name = (char *)calloc(strlen(head->name) + 1, sizeof(char));
	student->surname = (char *)calloc(strlen(head->surname) + 1, sizeof(char));

	strncpy(student->name, head->name, strlen(head->name) + 1);
	strncpy(student->surname, head->surname, strlen(head->surname) + 1);
	student->year = head->year;

	// Delete head
	
	free(head->name);
	free(head->surname);

	for (int i = 0; i < queue->count - 1; i++) {
		queue->students[i].name = queue->students[i + 1].name;
		queue->students[i].surname = queue->students[i + 1].surname;
		queue->students[i].year = queue->students[i + 1].year;
	}

	queue->students = (STUDENT *)realloc(queue->students, (--queue->count) * sizeof(STUDENT));

	return student;
}

void enqueue_a(QUEUE_A *queue, STUDENT *student) {
	queue->students = (STUDENT *)realloc(queue->students, ++queue->count * sizeof(STUDENT));
	memmove(&queue->students[queue->count - 1], student, sizeof(STUDENT));
	free(student);

	return;
}

void print_queue_a(QUEUE_A *queue) {
	printf("\nLiczba studentow w kolejce: %d\n\n", queue->count);
	if (queue->count == 0) return;

	for (int i = 0; i < queue->count; i++) {
		printf("imie: %s\n", queue->students[i].name);
		printf("nazwisko: %s\n", queue->students[i].surname);
		printf("rok: %d\n\n", queue->students[i].year);
	}

	return;
}

void delete_queue_a(QUEUE_A *queue) {
	if (queue->count > 0) {
		for (int i = 0; i < queue->count; i++) {
			free(queue->students[i].name);
			free(queue->students[i].surname);
		}
	}

	free(queue->students);
	free(queue);

	return;
}

QUEUE_A *init_queue_a() {
	QUEUE_A *queue = (QUEUE_A *)malloc(sizeof(QUEUE_A));
	if (!queue) {
		perror("malloc");
		return NULL;
	}

	queue->count = 0;
	queue->students = (STUDENT *)calloc(0, sizeof(STUDENT));
	if (!queue->students) {
		free(queue);
		perror("calloc");
		return NULL;
	}

	return queue;
}
