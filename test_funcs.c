#define Green "\033[0;32m"
#define Red "\033[0;31m"
#define Reset "\033[0m"
#include "test_funcs.h"
double ABS(double a){
	if(a>0) return a;
	return -a;
}

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
	while(counter!=line && x != EOF){
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
		if(x == ',' || x == '}') {
			ret_val[counter] = atof(buffer);
			counter++; 
			char_zero(buffer,50);
			continue;
		}
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
int *name_to_nums(const char *str){
	char *temp = malloc(sizeof(str));
	strcpy(temp,str);
	int count = strcocc(temp,'_');
	int *arr = (int*)malloc(sizeof(int)*count);
	char * pch = strtok(temp,"_");
	count = 0;
	while(pch!=NULL){
		if(atoi(pch)!= 0) arr[count++] = atoi(pch);
		pch = strtok(NULL,"_");
	}
	free (temp);
	return arr;
}
void free_arrays(arrays *A){
	if(A ==NULL) return;
	if(!A->data){
		for(int i=0;A->num_arrays;i++) if(!A->data[i]) free(A->data[i]);
	}
	if(!A->arrays_sizes) free(A->arrays_sizes);
	if(!A->type) free(A->type);
}


arrays file_to_arrays(char* filename){
	double **arr = NULL;
	char *type = NULL;
	int size;
	arrays temp ={arr,type,NULL,3};
	arr = malloc(sizeof(double*)*3);
	if(malloc_failed(arr)==NULL) return temp;
	int *arrays_sizes = name_to_nums(filename);
	temp.arrays_sizes = arrays_sizes;
	if(malloc_failed(arrays_sizes) == NULL) return temp;
	int count = 0;
	if(NULL!=strstr(filename,"inverse")){
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
			return temp;
		}
		size = sizeof("inverse");
		type = malloc(size);
		strcpy(type,"inverse");
	}
	else if (NULL!=strstr(filename,"mult")){
		count = 0;
		while(count != 3){
			arr[count] = file_line_to_array(filename,count);
			if(arr[count] == NULL) break;
			count++;
		}
		if(count!=3) {
			for(int i = 0; i<count; i++) if (arr[i] == NULL) free(arr[i]);
			free (arr);
			printf("malloc failed");
			return temp;
		}
		size = sizeof("mult");
		type = malloc(size);
		strcpy(type,"mult");
	}
	temp.data = arr;
	temp.type =type;
	return temp;
	
}
bool compare_and_free(matrix A,matrix B){
	double max = 0;
	for(int i = 0; i <A._rows; i++){
		for(int j =0; j<A._cols; j++){
			if( ABS (A.data[i][j] - B.data[i][j]) > max) max = ABS(A.data[i][j] - B.data[i][j]);
		}
	}
	matrix_free(A); matrix_free(B);
	if(max >0.0001)
		return false;
	return true;
}
void matrix_test(char *str){
	arrays arrs = file_to_arrays(str);
	if (!arrs.type || !arrs.data||!arrs.arrays_sizes) return; 
	int a = arrs.arrays_sizes[0], b = arrs.arrays_sizes[1],c = arrs.arrays_sizes[2];

	if(!strcmp(arrs.type,"mult")){
		matrix A = array_to_matrix(arrs.data[0],a*b,a,b);
		matrix B = array_to_matrix(arrs.data[1],b*c,b,c);
		matrix expected = array_to_matrix(arrs.data[2],a*c,a,c);
		matrix result = matrix_mult(A,B);
		matrices_print(4,A,B,expected,result);
		if(compare_and_free(expected,result)) printf("success!!\n");
		else printf(":( \n");
	}
	else if(!strcmp(arrs.type,"inverse")){
		matrix A = array_to_matrix(arrs.data[0],a*a,a,a);
		matrix expected = array_to_matrix(arrs.data[1],a*a,a,a);
		matrix result = matrix_invert(A);
		matrices_print(3,A,expected,result);
		if(compare_and_free(expected,result)) printf("success!!\n");
		else printf(":( \n");
	}
}
