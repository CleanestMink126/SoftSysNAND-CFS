all: main

main: task.o rbtree.o main.c all.h graphics.h
	gcc `pkg-config --cflags gtk+-3.0` -o main main.c task.o rbtree.o -lm `pkg-config --libs gtk+-3.0`

task.o: task.c all.h
	gcc -c task.c -lm

rbtree.o: rbtree.c all.h
	gcc -c rbtree.c
