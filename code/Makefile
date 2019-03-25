all: main

main: task.o rbtree.o main.c read_file.o graphics.o all.h graphics.h
	gcc `pkg-config --cflags gtk+-3.0` -o main main.c task.o rbtree.o read_file.o graphics.o -lm `pkg-config --libs gtk+-3.0`

graphics.o: graphics.c graphics.h all.h
	gcc `pkg-config --cflags gtk+-3.0` -c graphics.c -lm `pkg-config --libs gtk+-3.0`

task.o: task.c all.h
	gcc -c task.c -lm

rbtree.o: rbtree.c all.h
	gcc -c rbtree.c

read_file.o: read_file.c
	gcc -c read_file.c
