#!/bin/sh -x

echo Соберем библиотеку
gcc -shared lib.c -o mylib.so

echo Соберем программу
gcc program.c -o program

echo Запустим программу
./program
echo

echo Запустим программу с LD_PRELOAD
env LD_PRELOAD=`pwd`/mylib.so ./program
echo