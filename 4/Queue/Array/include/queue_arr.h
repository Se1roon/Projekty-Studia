#ifndef QUEUE_ARR_H
#define QUEUE_ARR_H

#include "common.h"

typedef struct queue_arr_t {
	unsigned int count;
	STUDENT **students;
} QUEUE_A;

STUDENT **find_by_field_queue_a(QUEUE_A *queue, char *field, char *search_term, int *found_count);
STUDENT *dequeue_a(QUEUE_A *queue);
void enqueue_a(QUEUE_A *queue, STUDENT *student);

int save_file_queue_a(QUEUE_A *queue, char *filepath);
int read_file_queue_a(QUEUE_A *queue, char *filepath);

void print_queue_a(QUEUE_A *queue);
void delete_queue_a(QUEUE_A *queue);
QUEUE_A *init_queue_a();

#endif
