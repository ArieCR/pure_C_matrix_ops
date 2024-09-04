#ifndef TEST_C
#define TEST_C
#include "stdio.h"
#include "matrix.h"
#include <string.h>
#include "stdlib.h"
typedef struct {
	double **data;
	char *type;
	int *arrays_sizes;
	int num_arrays;
} arrays;
double ABS(double a);
void* malloc_failed(void* ptr);
void char_append(char str[],int n,char x);
void char_zero(char str[],int n);
arrays file_to_arrays(char* filename);
int strcocc(char*s, char target);
int *name_to_nums(const char *str);
void free_arrays(arrays *A);
arrays file_to_arrays(char* filename);
bool compare_and_free(matrix A,matrix B);
void matrix_test(char *str);
#endif
