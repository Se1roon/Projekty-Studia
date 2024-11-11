#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

	// ['S', 'i', 'e', 'm', 'a', ' ', 'c', 'o', ' ', 't', 'a', 'm', '\0']
    //                       p    c    
	//
	// words_len = 2
	// words -> ['addr1',   'addr2', 'buff']
	//			-> 'dada\0'


char **fetch_words(char *line, char **words_out, int *words_out_len) {
	int word_len = 0; // Length of the current word
	char *current_word = (char *)calloc(word_len, sizeof(char)); // Space for the new word
	char c = ' ';
	char p = ' ';

	// Copy all the pointers from the old array
	char **words = (char **)calloc(*words_out_len, sizeof(char*));
	for (int i = 0; i < *words_out_len; i++)
		words[i] = words_out[i];

	free(words_out); // Free the old pointer to the array

	int i = 0;
	do {
		// I go character after character and create a new word
		c = line[i];
		if ((p == ' ' && c != ' ' && c != '\0') || (p != ' ' && c != ' ' && c != '\0')) /*Here we enter a word*/ {
			current_word = realloc(current_word, (word_len + 1) * sizeof(char));
			current_word[word_len++] = c;
		} else if ((p != ' ' && c == ' ') || (p != ' ' && c == '\0')) /*And here exist out of the word*/ {
			// Here I add the new word to the array
			
			current_word = realloc(current_word, (word_len+1)*sizeof(char));
			current_word[word_len] = '\0';

			char *buff = (char *)calloc(word_len, sizeof(char));
			strncpy(buff, current_word, word_len);

			// Append pointer to the new word
			words = (char **)realloc(words, (*words_out_len + 1) * sizeof(char*));
			words[*words_out_len] = buff;
			(*words_out_len)++;
		
			free(current_word);
			current_word = (char*)calloc(0, sizeof(char));
			word_len = 0;
		}

		p = c;
		i++;
	} while (c != '\0');

	free(current_word);

	return words;
}


char **sort_words(char **strs, int strs_size) {
	char **strings = (char **)calloc(strs_size, sizeof(char *));
	for (int i = 0; i < strs_size; i++)	strings[i] = strs[i];
	free(strs);

	for (int i = 0; i < strs_size; i++) {
		char *current = strings[i];

		char *min = current;
		int min_index = i;
		int min_length = strlen(min);
		for (int j = i + 1; j < strs_size; j++) {
			int l = strlen(strings[j]);

			// Convert strings to lowercase for comparison
			char *min_lower = (char*)calloc(min_length + 1, sizeof(char));
			char *str_lower = (char*)calloc(l + 1, sizeof(char));
			
			for (int x = 0; x < min_length; x++)
				min_lower[x] = tolower(min[x]);
			for (int y = 0; y < l; y++)
				str_lower[y] = tolower(strings[j][y]);

			if (l < min_length) {
				if (strncmp(str_lower, min_lower, l) < 0) {
					min = strings[j];
					min_index = j;
				}
			} else {
				if (strncmp(str_lower, min_lower, min_length) < 0) {
					min = strings[j];
					min_index = j;
				}
			}
			
			free(min_lower);
			free(str_lower);
		}

		strings[i]	= min;
		strings[min_index] = current;
	}

	return strings;
}
