#ifndef IO_H
#define IO_H

int cli_get_filepath(int argc, char *argv[], char **filepath);
int get_fd(char *filepath, int flags);

void output_to_file(int fd, char **words, int words_count);

#endif