#!/bin/sh

gcc -o ./bin/main src/*.c -I./include/ -lm -std=c99 -Wall -Wextra
