#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include "in_out.h"

int get_fd(char *filepath, int flags) {
	int fd = open(filepath, flags);
	if (fd < 0) {
		fprintf(stderr, "ERROR <get_fd>: Provided file doesn't exist or is inaccessible!\n");
		return -1;
	}

	return fd;
}

void output_to_file(int fd, char **words, int words_count) {
	for (int i = 0; i < words_count; i++) {
		write(fd, words[i], strlen(words[i]));
		write(fd, "\n", 1);
	}

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

