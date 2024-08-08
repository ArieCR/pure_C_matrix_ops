CC = gcc
CFLAGS = -g -Wall # -Werror
OBJ = main.o matrix_better.o 

matrix_better: $(OBJ)
	$(CC) $(CFLAGS) -o matrix_better $(OBJ)

matrix_better.o: matrix_better.c matrix_better.h
	$(CC) $(CFLAGS) -c matrix_better.c

main.o: main.c matrix_better.h
	$(CC) $(CFLAGS) -c main.c

#graph.o: graph.c graph.h
#	$(CC) $(CFLAGS) -c graph.c
test.o: test.c matrix_better.h
	$(CC) $(CFLAGS) -c test.c
clean:
	rm -f *.o matrix_better
test: matrix_better.o test.o
	$(CC) $(CFLAGS) -o OUT matrix_better.o test.o
	./OUT


