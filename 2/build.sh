#!/bin/sh

gcc -o ./bin/main ./src/*.c -I./include/ -std=c99 -Wall -Wextra

./bin/main -f test2.txt
