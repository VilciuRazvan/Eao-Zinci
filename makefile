CC = gcc
FLAGS = -g -o
CFLAGS = -g -w
EXECUTABLE = avion


build: BST.o files.o graph.o functions.o
	$(CC) BST.o files.o graph.o functions.o  avion.c $(FLAGS) $(EXECUTABLE)

BST.o: BST.c
files.o: files.c
graph.o: graph.c
functions.o: functions.c

clean:
	rm *.o avion