#!/bin/sh

if [ "$1" == "l" ]; then
	gcc -o ./bin/main src/*.c -I./include/ -lm -std=c99 -Wall -Wextra
fi

if [ "$1" == "w" ]; then
	x86_64-w64-mingw32-gcc -o ./bin/winmain src/*.c -I./include/ -std=c99 -Wall -Wextra
fi

