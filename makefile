CC = gcc
CFLAGS = -g -Wall
OBJ_MAIN = main.o matrix.o test_funcs.o
OBJ_TEST = test.o test_funcs.o matrix.o

# Build the main executable
matrix: $(OBJ_MAIN)
	$(CC) $(CFLAGS) -o matrix $(OBJ_MAIN)

# Build the test executable
test: $(OBJ_TEST)
	$(CC) $(CFLAGS) -o OUT $(OBJ_TEST)
	./OUT

# Object file compilation
matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c matrix.c

main.o: main.c matrix.h
	$(CC) $(CFLAGS) -c main.c

test.o: test.c test_funcs.h matrix.h
	$(CC) $(CFLAGS) -c test.c

test_funcs.o: test_funcs.c test_funcs.h matrix.h
	$(CC) $(CFLAGS) -c test_funcs.c

# Clean up
clean:
	rm -f *.o matrix OUT
