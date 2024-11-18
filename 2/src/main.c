#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <locale.h>
#include <sys/stat.h>

#include "in_out.h"
#include "transform.h"

void clear(char **, int, int);

int main(int argc, char *argv[]) {
#ifdef _WIN32
	setlocale(LC_ALL, "pl-PL.1250");
#endif
	// Get the path to the input file from the user
	char *filepath = NULL;
	if (cli_get_filepath(argc, argv, &filepath) < 0) return -1;

	// Get the file descriptor of the input file
	int input_fd = open(filepath, O_RDONLY);
	if (input_fd < 0) return -2;

	// Initialize stat structure to hold the statistics about the input file
	struct stat input_file_stats;
	if (fstat(input_fd, &input_file_stats) < 0) {
		perror("fstat");
		close(input_fd);
		return -3;
	}
	int input_file_size = input_file_stats.st_size;

	// Allocate a buffer of the input file size to store the content of the file
	char *text_buffer = (char*)malloc(input_file_size);
	if (text_buffer == NULL) {
		perror("malloc");
		close(input_fd);
		return -4;
	}
	if (read(input_fd, text_buffer, input_file_size) < 0) {
		perror("read");
		close(input_fd);
		free(text_buffer);
		return -5;
	}
	close(input_fd);

	// Clear any \n with space
	for (int i = 0; i < input_file_size; i++)
		if (text_buffer[i] == '\n') text_buffer[i] = ' ';

	// Fetch words from one long string of text
	int words_count = 0;
	char **words = fetch_words(text_buffer, &words_count);
	free(text_buffer);

	// Sort those words (implement a better algorithm, maybe implement my own strcmp)
	words = sort_words(words, words_count);

	// Print words 
	for (int i = 0; i < words_count; i++)
    	printf("%s\n", words[i]);

	int output_fd = open("out.txt", O_RDWR | O_CREAT, 0644);
	output_to_file(output_fd, words, words_count);

	clear(words, words_count, output_fd);
	return 0;
}

void clear(char **words, int words_len, int f_out) {
	close(f_out);

	for (int i = 0; i < words_len; i++) free(words[i]);
	free(words);

	return;
}
