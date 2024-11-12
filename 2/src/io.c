#include <stdio.h>
#include <getopt.h>

FILE *get_fd(char *filepath, char *mode) {
	FILE *fd = fopen(filepath, mode);
	if (fd == NULL) {
		fprintf(stderr, "ERROR <get_fd>: Provided file doesn't exist or is inaccessible!\n");
		return NULL;
	}

	return fd;
}

void output_to_file(FILE *f, char **words, int words_count) {
	for (int i = 0; i < words_count; i++)
		fprintf(f, "%s\n", words[i]);

	return;
}

int cli_get_filepath(int argc, char *argv[], char **filepath) {
	if (argc < 2) {
		fprintf(stderr, "ERROR <cli_get_filepath>: -f flag is needed: -f <filepath> !\n");
		return -1;
	}

	char c;
	while ((c = getopt(argc, argv, "f:")) != -1) {
		switch (c) {
			case 'f':
				*filepath = optarg;
				break;
			case '?':
				fprintf(stderr, "WARNING <cli_get_filepath>: Unknown option -%c!\n", c);
				return -2;
		}
	}

	return 0;
}
