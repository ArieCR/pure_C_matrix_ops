CC = gcc
CFLAGS = -g -Wall
OBJ_MAIN = main.o matrix_better.o test_funcs.o
OBJ_TEST = test.o test_funcs.o matrix_better.o

# Build the main executable
matrix_better: $(OBJ_MAIN)
	$(CC) $(CFLAGS) -o matrix_better $(OBJ_MAIN)

# Build the test executable
test: $(OBJ_TEST)
	$(CC) $(CFLAGS) -o OUT $(OBJ_TEST)
	./OUT

# Object file compilation
matrix_better.o: matrix_better.c matrix_better.h
	$(CC) $(CFLAGS) -c matrix_better.c

main.o: main.c matrix_better.h
	$(CC) $(CFLAGS) -c main.c

test.o: test.c test_funcs.h matrix_better.h
	$(CC) $(CFLAGS) -c test.c

test_funcs.o: test_funcs.c test_funcs.h matrix_better.h
	$(CC) $(CFLAGS) -c test_funcs.c

# Clean up
clean:
	rm -f *.o matrix_better OUT
