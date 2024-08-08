#include "matrix.h"
#include "stdio.h"
#include "graph.h"
int main(){
	double matrixA[] = {
	    1, 2,
	    3, 4
	};
	double matrixB[] = {
 	1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 
	};
	double matrixC[] = {
	5,6,6,8,2,2,2,8,6,6,2,8,2,3,6,7
	};
	matrix *A =  array_to_matrix(matrixA,4,2,2);
	matrix *B = array_to_matrix(matrixB,16,4,4);
	matrix *C =  array_to_matrix(matrixC,16,4,4);
	double x = matrix_det_recursive(C);
	printf("%lf\n",x);
	matrix *D = matrix_invert(C);
	matrix_print(D);
	routine();
	return 0;
}
