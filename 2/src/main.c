#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "ops.h"

#define LINE_BUF_LEN	1024

int main(int argc, char *argv[]) {
	char *filepath = NULL;
	if (cli_get_filepath(argc, argv, &filepath) < 0) return -1;

	FILE *fd = get_fd(filepath, "r");
	if (fd == NULL) return -1;

	int words_count = 0; // How many words I have
	char **words = (char **)calloc(words_count, sizeof(char *)); // Array holding the pointers to all the words in the file

	char *line = (char *)calloc(LINE_BUF_LEN, sizeof(char)); // Buffer for holding the line (1kB in size)
	while (fgets(line, LINE_BUF_LEN, fd) /* Reads in the line */) {
		int line_len = strlen(line);
		if (line[line_len - 1] == '\n') line[line_len - 1] = '\0'; // Remove \n character

		words = fetch_words(line, words, &words_count); // Add new words to the array
	}
	free(line); // At this point I do not need this buffer

	words = sort_words(words, words_count);

	for (int i = 0; i < words_count; i++)
		printf("%s\n", words[i]);

	for (int i = 0; i < words_count; i++)
		free(words[i]);
	free(words);

	return 0;
}
