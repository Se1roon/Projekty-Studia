#!/bin/sh

gcc -o ./bin/main ./src/*.c -I./include -lm -std=c99

if [ "$1" == "run" ]; then
	printf "Układ:\n" && cat tests/r$2* && printf "\n" && ./bin/main -f tests/r$2*
fi

