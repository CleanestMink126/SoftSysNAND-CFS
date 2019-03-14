all: main tree_test

tree_test: all.h
	# gcc `pkg-config --cflags gtk+-3.0` -o graphics graphics.c rbtree.o `pkg-config --libs gtk+-3.0`
	# gcc `pkg-config --cflags gtk+-3.0` -o graphicsv2 graphicsv2.c rbtree.o `pkg-config --libs gtk+-3.0`

main: task.o rbtree.o mainv2.c all.h
	# gcc task.o rbtree.o main.c -o main -lm
	# gcc task.o rbtree.o mainv2.c -o mainv2 -lm
	# gcc `pkg-config --cflags gtk+-3.0` -o mainv2 mainv2.c `pkg-config --libs gtk+-3.0`
	# gcc `pkg-config --cflags gtk+-3.0` -o mainv2 mainv2.c -lm rbtree.o task.o `pkg-config --libs gtk+-3.0`
	gcc `pkg-config --cflags gtk+-3.0` -o mainv2 graphicsv2.c task.o rbtree.o -lm `pkg-config --libs gtk+-3.0`


task.o: task.c all.h
	gcc -c task.c -lm

rbtree.o: rbtree.c all.h
	gcc -c rbtree.c
