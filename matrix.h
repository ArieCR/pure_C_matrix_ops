#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stdarg.h"
typedef struct{
	int _rows;
	int _cols;
	double **data;
} matrix;
typedef enum {ZERO,UNIT_MAT} MAT_OPTIONS;
matrix matrix_create(int rows,int cols);
bool compare_and_free(matrix A,matrix B);
void matrix_free(matrix mat);
bool is_matrix_data_valid(matrix A);


/**
 * @brief Sets a specific element in a MATRIX at a given position.
 *
 * This function modifies the matrix by setting its value at the specified row and column to the provided value.
 *
 * @param mat The input matrix to be modified.
 * @param row The row index of the position where the value will be set.
 * @param col The column index of the position where the value will be set.
 * @param value The new value that will replace the existing value at the specified position in the matrix.
 *
 * @return void
*/

bool matrix_set(matrix mat,int row,int col,double value);
/**
*@param count number of arguments to be printed
*this function prints a specified amount of matrices on after the other.
*/
void matrices_print(int count, ... );

matrix matrix_mult(matrix A,matrix B);
matrix matrix_add(matrix A,matrix B);
void matrix_init(matrix A,MAT_OPTIONS x);
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
