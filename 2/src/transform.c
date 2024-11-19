#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "transform.h"

char **fetch_words(char *line, int *words_out_len) {
	int word_len = 0; // Length of the current word
	char *current_word = (char *)calloc(word_len, sizeof(char)); // Space for the new word
	char c = ' ';
	char p = ' ';

	char **words = (char **)calloc(*words_out_len, sizeof(char*));

	int i = 0;
	do {
		// I go character after character and create a new word
		c = line[i];
		if ((p == ' ' && c != ' ' && c != '\0') || (p != ' ' && c != ' ' && c != '\0')) /*Here we enter a word*/ {
			current_word = realloc(current_word, (word_len + 1) * sizeof(char));
			current_word[word_len++] = c;
		} else if ((p != ' ' && c == ' ') || (p != ' ' && c == '\0')) /*And here exist out of the word*/ {
			// Here I add the new word to the array
			
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


char **sort_words(char **words, int words_count) {
	for (int i = 0; i + 1 < words_count; i++) {
		char *current = words[i];

		int highest_index = i + 1;
		char *highest = words[highest_index];
		for (int j = i + 1; j < words_count; j++) {
			if (compare_words(words[j], highest) > 0) {
				highest = words[j];
				highest_index = j;
			}
		}

		if (compare_words(highest, current) > 0) {
			words[i] = highest;
			words[highest_index] = current;
		}
	}

	return words;
}


int compare_words(char *w1, char *w2) {
	// 1. Jeżeli mamy ascii od 32 do 64 i od 91 do 96 i od 123 do 255 oraz <0 (nwm co to) ma być na końcu
	// 2. Sprawdzić czy mam do czynienia z 2 dużymi jednym malym i duzym czy 2 malymi
	//
	// Jeżeli maly - duzy == 32 to sa tej samej klasy duzy > maly
	// Jezeli maly - duzy > 32 to duzy > maly
	// jezeli maly - duzy < 32 to maly > duzy

	char c1 = w1[0]; // "points" to the characters in w1
	char c2 = w2[0]; // the same but to w2
	
	int w1_len = strlen(w1);
	int w2_len = strlen(w2);

	int i = 1;
	while (c1 != 0 && c2 != 0) {
		if ((c1 >= 65 && c1 <= 90) && (c2 >= 97 && c2 <= 122)) {
			// c1 upper and c2 lower
			if (c2 - c1 >= 32) return 1; // 120 - 80 = 40 => w1 > w2
			if (c2 - c1 != 0) return -1;
		} else if ((c2 >= 65 && c2 <= 90) && (c1 >= 97 && c1 <= 122)) {
			// c1 lower and c2 upper
			if (c1 - c2 >= 32) return -1;
			if (c1 - c2 != 0) return 1;
		} else if ((c1 >= 65 && c1 <= 90) && (c2 >= 65 && c2 <= 90)) {
			if (c1 != c2) return c1 - c2 < 0 ? 1 : -1; // both upper
		} else if ((c1 >= 97 && c1 <= 122) && (c2 >= 97 && c2 <= 122)) {
			if (c1 != c2) return c1 - c2 < 0 ? 1 : -1; // both lower
		} else {
			if ((c1 >= 65 && c1 <= 90) || (c1 >= 97 && c1 <= 122)) return 1;  // c1 normal c2 weid
			if ((c2 >= 65 && c2 <= 90) || (c2 >= 97 && c2 <= 122)) return -1; // c1 weird c2 normal

			// c1 i c2 sa weird
			if (c1 != c2) return c1 - c2 < 0 ? 1 : -1;
		}

		c1 = w1[i];
		c2 = w2[i];
		i++;
	}

	return (w1_len == w2_len) ? 0 : (w1_len > w2_len) ? 1 : -1;
}
