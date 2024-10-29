#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#include "common.h"
#include "parse.h"

OPTIONS *parse_options(int argc, char *argv[]) {
	OPTIONS *opts = (OPTIONS *)malloc(sizeof(OPTIONS));

	// Sprawdzam czy user użył jakichś flag (jeżeli nie to wczytuje z stdin)
	if (argc == 1) {
		printf("Początek przedziału: ");
		if (scanf("%lf", &opts->a) != 1) {
			fprintf(stderr, "Początek przedziału musi być liczbą!\n");
			exit(-1);
		}
		printf("Koniec przedziału: ");
		if (scanf("%lf", &opts->b) != 1) {
			fprintf(stderr, "Koniec przedziału musi być liczbą!\n");
			exit(-2);
		}
		printf("Ilość podziałów: ");
		// TODO: Maybe make n double and later validate if it is an int
		// TODO: This method of validation if the type is corrent is not working
		//		 scanf just reads in the first digit
		if (scanf("%d", &opts->n) != 1) {
			fprintf(stderr, "Ilość podziałów musi być liczbą całkowitą!\n");
			exit(-3);
		}
		printf("Dokładność: ");
		if (scanf("%lf", &opts->e) != 1) {
			fprintf(stderr, "Dokładność musi być liczbą\n");
			exit(-4);
		}
		printf("Gdzie zapisać plik: ");
		scanf("%s", opts->filepath);
	} else {
		char current;
		while ((current = getopt(argc, argv, "ha:b:n:e:f:")) != -1) {
			switch (current) {
				case 'h':
					print_usage(argv);
					exit(0);
					break;
				case 'a':
					opts->a = atof(optarg);
					if (opts->a == 0 && strncmp(optarg, "0", 1) != 0) {
						fprintf(stderr, "Wartość dla opcji -a musi być liczbą!\n");
						exit(-1);
					}
					break;
				case 'b':
					opts->b = atof(optarg);
					if (opts->b == 0 && strncmp(optarg, "0", 1) != 0) {
						fprintf(stderr, "Wartość dla opcji -b musi być liczbą!\n");
						exit(-2);
					}
					break;
				case 'n':
					opts->n = atoi(optarg);
					if (opts->n == 0 && strncmp(optarg, "0", 1) != 0) {
						fprintf(stderr, "Wartość dla opcji -n musi być liczbą!\n");
						exit(-3);
					}

					int i = 0;
					char c = optarg[i];
					while (c != '\0') {
						if (c == '.' || c == ',' || c == '/') {
							fprintf(stderr, "Wartość dla opcji -n musi być liczbą całkowitą!\n");
							exit(-4);
						}
						c = optarg[++i];
					}

					break;
				case 'e':
					opts->e = atof(optarg);
					if (opts->e == 0 && strncmp(optarg, "0", 1) != 0) {
						fprintf(stderr, "Wartość dla opcji -e musi być liczbą!\n");
						exit(-4);
					}
					break;
				case 'f':
					strncpy(opts->filepath, optarg, FILEPATH_LEN);
					break;
				case '?':
					fprintf(stderr, "Nieznana opcja -%c\n", current);
					break;
			}
		}
	}

	return opts;
}

void print_usage(char *argv[]) {
	printf("Usage: %s -a <początek> -b <koniec> -n <ilość podziałów> -e <dokładność> -f <ścieżka do zapisu>\n", argv[0]);
	printf("\t-f ~ ścieżka do pliku zapisu (. oznacza ./out.txt)\n");
	printf("\t-a ~ początek przedziału [a,b]\n");
	printf("\t-b ~ koniec przedziału [a,b]\n");
	printf("\t-n ~ ilość częsci podziału przedziału [a,b]\n");
	printf("\t-e ~ dokładność\n");

	return;
}

