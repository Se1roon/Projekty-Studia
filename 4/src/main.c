#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "interface.h"

enum INTER_DS {
	DS_PAD, // not important
	STACK_ARRAY,
	STACK_LLIST,
	QUEUE_ARRAY,
	QUEUE_LLIST,
	QUIT,
	DS_TOT
};

char menu_ds[5][23] = {
	"1 - stos (tablica)",
	"2 - stos (lista)",
	"3 - kolejka (tablica)",
	"4 - kolejka (lista)",
	"5 - zakoncz program"
};

int main(void) {
	int inter_ds = -1;
	do {
		for (int i = 0; i < 5; i++)
			printf("%s\n", menu_ds[i]);
		printf("> ");

		char *ds_inp = get_line(stdin);
		inter_ds = atoi(ds_inp);
		free(ds_inp);

		printf("\n");
		switch (inter_ds) {
			case STACK_ARRAY:
				handle_stack_array();
				break;
			case STACK_LLIST:
				handle_stack_list();
				break;
			case QUEUE_ARRAY:
				handle_queue_array();
				break;
			case QUEUE_LLIST:
				handle_queue_list();
				break;
			case QUIT:
				exit(0);
			default:
				fprintf(stderr, "Nie wiem o co ci chodzi\n");
		}
	} while (1);

	return 0;
}
