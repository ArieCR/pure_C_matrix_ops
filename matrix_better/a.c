#include <string.h>
#include <stdlib.h>
#include <stdio.h>
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
void print_arr(int arr[],int n){for(int i=0;i<n;i++) printf("%d ",arr[i]); printf("\n"); }
int main(int argc,char *argv[]){
	int* arr = name_to_nums(argv[1]);
	print_arr(arr,3);

}



