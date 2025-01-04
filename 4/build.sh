#!/bin/sh

SRC_PATHS="./src/*.c ./Stack/Array/src/*.c ./Stack/LList/src/*.c ./Queue/*/src/*.c"
INC_PATHS="-I./include/ -I./Stack/Array/include/ -I./Stack/LList/include/ -I./Queue/LList/include/"

gcc -o program $SRC_PATHS $INC_PATHS -std=c99
