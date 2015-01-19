//--------------------------------------------
// NAME: Vasil Kolev
// CLASS: XIb
// NUMBER: 6
// PROBLEM: #1
// FILE NAME: wc.c (unix file name)
// FILE PURPOSE:
// This file is the source code for the standard wc command in unix. 
//---------------------------------------------

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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

int read_file(char argv[]){
	printf("You just entered read_file() with %s\n", argv);
	
	char buff[200];
	int fd;
	fd=open(argv, O_RDONLY);
	if(fd==-1){
		perror(argv);
		return 1;
	}
	printf("Working on %s\n", argv);
	int lines, words, chars;
	int eof = 0;
	while(!eof){
		int status_read = read(fd, buff, 200);
		if(status_read == -1){
			if(errno==EINTR){
				status_read = 0;
			}else{
				perror(argv);
				return 1;
			}
		}else if(status_read == 0){
			eof = 1;
			break;
		}
		int written=0;
		while(written < status_read){
			int status_write = write(STDOUT_FILENO, buff + written, status_read - written);
			if(status_write == -1){
				if(errno == EINTR){
					status_write = 0;
				}else{
					perror(argv);
					return 1;	
				}
			}
			written += status_write;
		}
	}
	
	int close_status = close(fd);
	if(close_status == -1){
		perror(argv);
		return 1;
	}
	printf("%d %d %d %s\n", lines, words, chars, argv);
	return 0;
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
