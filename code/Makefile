all: main

tree_test: all.h
	gcc `pkg-config --cflags gtk+-3.0` -o tree_test tree_test.c `pkg-config --libs gtk+-3.0`

main: task.o rbtree.o main.c all.h
	gcc task.o rbtree.o main.c -o main -lm

task.o: task.c all.h
	gcc -c task.c -lm

rbtree.o: rbtree.c all.h
	gcc -c rbtree.c
