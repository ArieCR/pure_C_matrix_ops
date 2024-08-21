#include "test_funcs.h"
int main(int argc,char * argv[]){
	for(int i= 1; i<argc; i++){ 
		matrix_test(argv[i]);
	}	
	return 0;
};
