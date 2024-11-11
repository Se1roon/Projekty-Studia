#ifndef IO_H
#define IO_H

int cli_get_filepath(int argc, char *argv[], char **filepath);
FILE *get_fd(char *filepath, char *mode);

#endif
