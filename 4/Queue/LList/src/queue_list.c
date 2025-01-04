#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "queue_list.h"


STUDENT_L *find_by_field_queue_l(QUEUE_L *queue, char *field, char *search_term) {
	if (queue->count == 0) return NULL;

	STUDENT_L *student = queue->head;
	if (strncmp(field, "imie", strlen(field)) == 0) {
		while (student)	{
			if (strncmp(student->name, search_term, strlen(search_term)) == 0) return student;
			student = student->next;
		}
	} else if (strncmp(field, "nazwisko", strlen(field)) == 0) {
		while (student) {
			if (strncmp(student->surname, search_term, strlen(search_term)) == 0) return student;
			student = student->next;
		}
	} else if (strncmp(field, "rok", strlen(field)) == 0) {
		while (student) {
			if (student->year == atoi(search_term)) return student;
			student = student->next;
		}
	} else
		fprintf(stderr, "Niepoprawne pole!\n");

	return NULL;
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
	if (queue->count == 0)
		queue->head = queue->tail = student;
	else {
		queue->tail->next = student;
		queue->tail = student;
	}

	queue->count++;
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
