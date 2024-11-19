#!/bin/sh

if [ $1 == "linux" ]; then
	gcc -o ./bin/main ./src/*.c -I./include/ -std=c99 -Wall -Wextra

	if [ $2 == "run" ]; then
		./bin/main -f ./tests/test1.txt
	fi
fi

if [ $1 == "windows" ]; then
	x86_64-w64-mingw32-gcc -o ./bin/main_win.exe ./src/*.c -I./include -std=c99 -Wall -Wextra

	if [ $2 == "run" ]; then
		wine ./bin/main_win.exe -f ./tests/test1_1250.txt
		iconv -c -f WINDOWS-1250 -t UTF-8 -o out.txt out.txt
	fi
fi

