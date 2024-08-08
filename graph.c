#include "graph.h"
#include "stdio.h"
void func(){	
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    printf ("lines %d\n", w.ws_row);
    printf ("columns %d\n", w.ws_col);
    usleep(250000);
    system("clear");
    for(int x = 0; x<ws_col;x++){
       for(int y = 0; y<ws_row;y++){
	printf("*");       
	}
  
    }
int x;
scanf("%d",x);

}
void routine(){
	while(1){
		char choice;
		printf("pick your choice: q for quit, h for print\n");
		scanf("%c",&choice);
		switch(choice){
			case 'q':
				return;
			case 'h':
				func();
				break;
		}
	}
}	 
