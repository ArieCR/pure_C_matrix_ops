CC = gcc
CFLAGS = -g -Wall # -Werror
OBJ = main.o matrix.o graph.o

matrix: $(OBJ)
	$(CC) $(CFLAGS) -o matrix $(OBJ)

matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c matrix.c

main.o: main.c matrix.h graph.h
	$(CC) $(CFLAGS) -c main.c

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c
test.o: test.c matrix.h
	$(CC) $(CFLAGS) -c test.c
clean:
	rm -f *.o matrix
test: matrix.o test.o
	$(CC) $(CFLAGS) -o OUT matrix.o test.o
	./OUT


