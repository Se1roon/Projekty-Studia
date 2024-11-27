#!/bin/sh

gcc -o ./bin/main ./src/*.c -I./include -std=c99 -Wall -Wextra

if [ "$1" == "run" ]; then
	./bin/main -f rownania.txt
fi

