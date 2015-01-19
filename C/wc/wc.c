//--------------------------------------------
// NAME: Vasil Kolev
// CLASS: XIb
// NUMBER: 6
// PROBLEM: #1
// FILE NAME: wc.c (unix file name)
// FILE PURPOSE:
// This file is the source code for the standard wc command in unix. 
//---------------------------------------------

#include<stdio.h>
#include<string.h>

//--------------------------------------------
// FUNCTION: void read_stdin()
// Reads stdin and counts number of chars, words and lines.
// PARAMETERS:
// None.
//----------------------------------------------

void read_stdin(){
	printf("You just entered read_stdin()\n");
}

//--------------------------------------------
// FUNCTION: void read_file(char argv[])
// Reads file and counts number of chars, words and lines.
// PARAMETERS:
// char argv - the name of the file that needs to be opened.
//----------------------------------------------

void read_file(char argv[]){
	printf("You just entered read_file() with %s\n", argv);
}

//--------------------------------------------
// FUNCTION: int main(int argc, char *argv[])
// The main function. Filters inputs and loops 
// untill all files/commands are processed. 
// PARAMETERS:
// int argc - number of arguments given from the user.
// char *argv[] - array of all the arguments 
// including the name of the program as argv[0].
//----------------------------------------------

int main(int argc, char *argv[]){
	int i;
	for(i=0; i<argc; ++i){
		if ((argc==1) || (strncmp(argv[i], "-", 1) == 0)){
			read_stdin();
		}else{
			if(argv[0]!=argv[i]){
				read_file(argv[i]);
			}
		}
	}
	return 0;
}
