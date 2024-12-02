#!/bin/sh

gcc -o ./bin/main ./src/*.c -I./include -lm -std=c99 -Wall -Wextra

if [ "$1" == "run" ]; then
	printf "Układ:\n" && cat tests/r$2.txt && printf "\n" && ./bin/main -f tests/r$2.txt
fi

