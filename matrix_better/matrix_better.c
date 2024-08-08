#ifndef MATRIX_C
#define MATRIX_C
#include "matrix_better.h"
void malloc_fail(){
	printf("malloc didn't work");
}

matrix* matrix_create(int rows,int cols){
	matrix* return_mat = (matrix*)malloc(sizeof(matrix));
	if(return_mat == NULL){
		malloc_fail();
		return NULL;
	}
	return_mat->data = (double**)malloc(sizeof(double)*rows);
	if(return_mat->data == NULL) {
		free(return_mat);
		malloc_fail();
		return NULL;
	}
	int i;
	for(i = 0; i<rows;i++){
		return_mat->data[i] = (double*)malloc(sizeof(double)*cols);
		if(return_mat->data[i] == NULL) break;
	}
	return_mat->_rows = rows;
	return_mat->_cols = cols;
	if(i!=rows){
		matrix_free(return_mat);
		return NULL;		
	}
	return return_mat;
}
void matrix_free(matrix* mat){
	for(int i = 0; i < mat->_rows;i++){
		if(NULL != mat->data[i]) free(mat->data[i]);
	}
	free(mat->data);
	free(mat);
}
bool is_matrix_data_valid(matrix *mat){
	if(mat == NULL) return false;
	if(mat->data == NULL) return false;
	for(int i = 0; i < mat->_rows; i++) if(NULL == mat->data[i]) return false;
	return true;
}
bool matrix_set(matrix* mat,int row,int col,double value){
	if(!is_matrix_data_valid(mat)) return false;
	mat->data[row][col] = value;
	return true;
}
matrix* matrix_mult(matrix* A,matrix* B){
	if(!is_matrix_data_valid(A) || !is_matrix_data_valid(B)) return NULL;
	if(A->_cols != B->_rows) return NULL;
	matrix *C = matrix_create(A->_rows,B->_cols);
	if(C == NULL) return NULL;
	for(int i = 0; i<A->_rows;i++){
		double value = 0;
		for(int j = 0; j<B->_cols; j++){
			for(int k =0; k < A->_cols; k++) value += A->data[i][k]*B->data[k][j];
			C->data[i][j] = value;
			}
	}
	return C;

}
void matrix_print(matrix* A){
	for(int i = 0; i<A->_rows;i++){
		for(int j = 0; j<A->_cols; j++){
			printf("%lf ",A->data[i][j]);
		}
		printf("\n");
	}
}

matrix *array_to_matrix(double *arr,int size,int rows, int cols){
	if(size != rows*cols) return NULL;
	matrix *A = matrix_create(rows,cols);
	if(A == NULL) return NULL;
	for(int i=0; i<cols*rows; i++){
		A->data[i/cols][i%cols] = *(arr+i);
	}
	return A;
}
matrix *matrix_minor(matrix *A,int i,int j){
	if(A == NULL) return NULL;
	if(A->_cols!= A->_rows || i >= A->_rows || j >= A->_cols) return NULL;
	if(!is_matrix_data_valid(A)) return NULL;
	if(A->_cols<2) return NULL;
	
	matrix *B =matrix_create(A->_rows-1,A->_cols-1);
	if(B == NULL) return NULL;
	/********************
    	1 1 1 1 * 2 2 2 2 
    	1 1 1 1 * 2 2 2 2 
    	1 1 1 1 * 2 2 2 2 
   	1 1 1 1 * 2 2 2 2 
	* * * * * * * * *
	3 3 3 3 * 4 4 4 4 		
	3 3 3 3 * 4 4 4 4 		
	3 3 3 3 * 4 4 4 4 		
	3 3 3 3 * 4 4 4 4 		
	*********************/
	int a,b;
	//1	
	for( a = 0; a < i ; a++){
		for( b=0 ; b < j ; b++){
			B->data[a][b] = A->data[a][b];
			//*(B->data + a*B->_cols +b) = *(A->data + a*A->_cols +b); 		
		} 
	}
	//2
	for( a = 0; a < i ; a++){
		for( b=j+1 ; b < A->_cols ; b++){
			B->data[a][b-1] = A->data[a][b];
			//*(B->data + a*B->_cols +b-1) = *(A->data + a*A->_cols +b); 		
		} 
	}
	//3	
	for( a = i + 1; a < A->_rows ; a++){
		for( b=0 ; b < j ; b++){
			B->data[a-1][b] = A->data[a][b];
		//	*(B->data + (a-1)*B->_cols +b) = *(A->data + a*A->_cols +b); 		
		} 
	}


	//4
	for( a = i + 1; a < A->_rows ; a++){
		for( b=j+1 ; b < A->_cols ; b++){
			B->data[a-1][b-1] = A->data[a][b];
		//	*(B->data + (a-1)*B->_cols +b-1) = *(A->data + a*A->_cols +b); 		
		} 
	}
	return B;

}

double matrix_det_recursive(matrix *A){
	if (A == NULL || A->_cols!=A->_rows || A->_cols < 2) return 0;
	
	if (A->_cols == 2) return A->data[0][0] * A->data[1][1] - A->data[0][1]*A->data[1][0];
	double sum = 0;
	for(int i = 0; i < A->_cols;i++){
		matrix *B = matrix_minor(A,0,i);
		if(B==NULL) return 0;
		sum+=matrix_det_recursive(B)*(1 - (i%2)*2)*(A->data[0][i]);
		matrix_free(B);
	}
	return sum;
	
}
bool is_det_small(double x){
	if( x< 00000.1 && x > -0.00001) return true;
	return false;
}
matrix* matrix_invert(matrix *A){
	if (A == NULL || A->data == NULL || A->_cols!=A->_rows || A->_cols < 2) return NULL;
	if (! is_matrix_data_valid(A)) return NULL;
	matrix* B = matrix_create(A->_rows,A->_cols);
	if(B ==NULL) return NULL;
	double det = matrix_det_recursive(A);
	if(is_det_small(det)) {
		matrix_free(B);
		return NULL;
	}
	for(int i = 0; i<A->_rows;i++){
		for(int j=0; j<A->_cols; j++){
			matrix *C = matrix_minor(A,j,i);
			B->data[i][j] =(1-((i+j)%2)*2)*matrix_det_recursive(C)*(1/det);
			matrix_free(C); 
			//*(B->data+ i*B->_cols+j) =(1-((i+j)%2)*2)* matrix_det_recursive(C)*(1/det);
			//matrix_free(C);
			
		}	
	}
	return B;
}



#endif
