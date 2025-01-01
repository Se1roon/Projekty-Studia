#!/bin/sh

gcc -o program ./src/*.c ./Stack/Array/src/*.c -I./include/ -I./Stack/Array/include/ -std=c99
