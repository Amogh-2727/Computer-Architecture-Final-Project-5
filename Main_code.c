#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 int main (int argc, char *argv[]) {
	  
	   printf("\nThe number of arguements passed are =%d \n", (argc-1));
	   printf("\nThe arguements are passed in the order: PC =  %s \t SP = %s \t Memory file name = %s\n ", argv[1], argv[2],argv[3]);
		 int value;	  
	         char ch;
	         FILE *fp;
	         fp=fopen(argv[3],"r");
	         while ((ch=getc(fp))!=EOF) {



		 putchar(ch);
		 }	 
	         fclose(fp);
       	   return 0;
	        }


