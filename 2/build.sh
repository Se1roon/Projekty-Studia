#!/bin/sh

if [ $1 == "linux" ]; then
	gcc -o ./bin/main ./src/*.c -I./include/ -std=c99 -Wall -Wextra

	if [ $2 == "run" ]; then
		./bin/main -f ./test1.txt
	fi
fi

if [ $1 == "windows" ]; then
	x86_64-w64-mingw32-gcc -o ./bin/main_win.exe ./src/*.c -I./include -std=c99 -Wall -Wextra

	if [ $2 == "run" ]; then
		wine ./bin/main_win.exe -f ./test_win.txt
	fi
fi

