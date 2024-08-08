#include "stdio.h"
#include "matrix.h"
#include <string.h>
#include "stdlib.h"
#define Green "\033[0;32m"
#define Red "\033[0;31m"
#define Reset "\033[0m"

int passed = 0,total = 0;
void* malloc_failed(void* ptr){
	if(ptr) return ptr;
	printf("malloc failed :( \n");
	return NULL;
}
int count_char_in_file(char* str,char target){
	
	FILE* fptr;
	fptr = fopen(str,"r");
	if(fptr == NULL) return -1;
	int count = 0;
	char x = 1;
	do {
		x = fgetc(fptr);
		if(x==target) count++;
	} while (x!=EOF);
	fclose(fptr);
	return count;
}

void char_append(char str[],int n,char x){
	for(int i=0; i<n;i++){
		if(str[i] == 0) {
			str[i] = x; 
			str[i+1] = 0;
			return;
		}
	}
}
void char_zero(char str[],int n){for(int i=0; i<n;i++) str[i] = 0;}
double* file_line_to_array(char* str,int line){
	FILE* fptr;
	fptr = fopen(str,"r");
	if(fptr == NULL) return NULL;
	char buffer[50] = {0};
	int size = count_char_in_file(str,',')+1;
	double* ret_val = (double*)malloc(sizeof(double)*size); 
	if(ret_val == NULL) {
		fclose(fptr);
		return NULL;
	}
	int write = 0, counter = 0;
	char x = 1;
	while(counter!=line || x == EOF){
		x = fgetc(fptr);
		if(x == '\n') counter++;
	}
	counter = 0;

	while(x != EOF){
		if(counter == size) {
			printf("error in file handling, size too small\n");
			fclose(fptr);
			return ret_val;
		}
		x = fgetc(fptr);
		if(x == '}') write = 0;
		if(x == '{') {
			write = 1; continue;
		}
		if(x == ',') {ret_val[counter] = atof(buffer); counter++; char_zero(buffer,50); continue;}
		if(write) char_append(buffer,49,x);
	}
	fclose(fptr);
	return ret_val;
}
int strcocc(char*s, char target){
	int x=0;
	while(*s) if(*s++ == target) x++;
	return x;
}
int *name_to_nums(char *str){
	int count = strcocc(str,'_');
	int *arr = (int*)malloc(sizeof(int)*count);
	char * pch = strtok(str,"_");
	count = 0;
	while(pch!=NULL){
		if(atoi(pch)!= 0) arr[count++] = atoi(pch);
		pch = strtok(NULL,"_");
	}
	return arr;
}
typedef struct {
	double **data;
	char *type;
	int *arrays_sizes;
	int num_arrays;
} arrays;
void free_arrays(arrays *A){
	if(A ==NULL) return;
	if(!A->data){
		for(int i=0;A->num_arrays;i++) if(!A->data[i]) free(A->data[i]);
	}
	if(!A->arrays_sizes) free(A->arrays_sizes);
	if(!A->type) free(A->type);
}


arrays *file_to_arrays(char* filename){
	double **arr;
	char *type;
	int size;
	*arr = malloc(sizeof(double*)*3);
	if(malloc_failed(arr)==NULL) return NULL;
	int *arrays_sizes = name_to_nums(filename);
	if(malloc_failed(arrays_sizes) == NULL) return NULL;
	int count = 0;
	if(strstr(filename,"inverse")){
		count = 0;
		while(count != 2){
			arr[count] = file_line_to_array(filename,count);
			if(arr[count] == NULL) break;
			count++;
		}
		if(count!=2) {
			for(int i = 0; i<count; i++) if (arr[i] == NULL) free(arr[i]);
			free (arr);
			printf("malloc failed");
			return NULL;
		}
		size = sizeof("inverse");
		type = malloc(size+1);
		strcpy("inverse",type);
	}
	else if (strstr(filename,"mult")){
		count = 0;
		while(count != 3){
			arr[count] = file_line_to_array(filename,count);
			if(arr[count] == NULL) break;
			count++;
		}
		if(count!=3) {
			for(int i = 0; i<count; i++) if (arr[i] == NULL) free(arr[i]);
			free (*arr);
			printf("malloc failed");
			return NULL;
		}
		size = sizeof("mult");
		type = malloc(size+1);
		strcpy("mult",type);
	}
	arrays* ret_val = malloc(sizeof(arrays));
	if(!ret_val){
		ret_val ={arr,type,arrays_sizes,3};
	}
	return ret_val;
	
}

void matrix_test(char *str){
	arrays* arrs =file_to_arrays(str);
	if (!arrs || !arrs->type || !arrs->data) free_arrays(A);
	else if(!strcmp(arrs->type,"mult")){
		matrix* A = array_to_matrix(arrs->data[0],arrs->);
		matrix* B = array_to_matrix(arrs->data[1]);

	}
	else if(!strcmp(arrs->type,"inverse")){
		
	}
}	

int main(int argc,char * argv[]){
	int size = 0;
	double* arr = file_line_to_array(argv[1],&size);
	for(int i = 0; i<size;i++){
		printf("%lf ",arr[i]);
	}
	printf("\n");	
	matrix_test();	
	return 0;
};
