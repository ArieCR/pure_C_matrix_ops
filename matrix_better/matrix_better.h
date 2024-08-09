#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct{
	int _rows;
	int _cols;
	double **data;
} matrix;
matrix matrix_create(int rows,int cols);
bool compare_and_free(matrix A,matrix B);
void matrix_free(matrix mat);
bool is_matrix_data_valid(matrix A);
bool matrix_set(matrix mat,int row,int col,double value);
matrix matrix_mult(matrix A,matrix B);
matrix matrix_add(matrix A,matrix B);
void matrix_print(matrix A);
matrix array_to_matrix(double *arr,int size,int rows, int cols);
/**
*@param i from 0 to n-1
*@param j same
*/
matrix matrix_minor(matrix A,int i,int j); 
bool is_det_small(double x);
matrix matrix_invert(matrix A);

double matrix_det_recursive(matrix A);
#endif
