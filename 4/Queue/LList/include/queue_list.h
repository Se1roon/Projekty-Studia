#ifndef QUEUE_LIST_H
#define QUEUE_LIST_H

#include "common.h"

typedef struct queue_list_t {
	unsigned int count;
	STUDENT_L *head;
	STUDENT_L *tail;
} QUEUE_L;

STUDENT_L **find_by_field_queue_l(QUEUE_L *queue, char *field, char *search_term, int *found_count);
STUDENT_L *dequeue_l(QUEUE_L *queue);
void enqueue_l(QUEUE_L *queue, STUDENT_L *student);
void print_queue_l(QUEUE_L *queue);

int save_file_queue_l(QUEUE_L *queue, char *filepath);
int read_file_queue_l(QUEUE_L *queue, char *filepath);

void delete_queue_l(QUEUE_L *queue);
QUEUE_L *init_queue_l();

#endif
