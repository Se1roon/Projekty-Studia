#ifndef IO_H
#define IO_H

#include <stdio.h>

int cli_get_filepath(int argc, char *argv[], char **filepath);
FILE *output_to_file(FILE *f, char **words, int words_count);
FILE *get_fd(char *filepath, char *mode);

#endif
