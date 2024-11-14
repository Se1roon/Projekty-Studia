#ifndef OPS_H
#define OPS_H

int compare_words(char *w1, char *w2);
char **fetch_words(char *line, char **words_out, int *current_word_index);
char **sort_words(char **words, int words_count);

#endif
