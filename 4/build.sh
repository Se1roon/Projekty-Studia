#!/bin/sh

gcc -o program ./src/*.c ./Stack/Array/src/*.c ./Stack/LList/src/*.c -I./include/ -I./Stack/Array/include/ -I./Stack/LList/include/ -std=c99
