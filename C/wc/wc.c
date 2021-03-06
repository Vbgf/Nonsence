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

#define MAX_BUFFER_SIZE 65536

//--------------------------------------------
// STRUCTURE: total_wc
// Holds the total amount of lines, words, chars
// and also number of errors.
//----------------------------------------------

struct total_wc{
	int lines;
	int words;
	int chars;
	int errors;
};

//--------------------------------------------
// FUNCTION: struct total_wc read_stdin(struct total_wc total)
// Reads stdin and counts number of chars, words and lines.
// PARAMETERS:
// struct total_wc total - refer to structure total_wc (22ln),
// (container for all the "global" variables).
//----------------------------------------------

struct total_wc read_stdin(struct total_wc total){
	char buff[MAX_BUFFER_SIZE];
	int lines = 0;
	int words = 0;
	int chars = 0;
	int eof = 0;
	while(!eof){
		int status_read = read(STDIN_FILENO, buff, MAX_BUFFER_SIZE);
		if(status_read == -1){
			if(errno==EINTR){
				status_read = 0;
			}else{
				perror("Reading from cmdline");
				total.errors++;				
				return total;
			}
		}else if(status_read == 0){
			eof = 1;
			break;
		}
		int i;
		for(i=0; i<MAX_BUFFER_SIZE; i++){
			if((buff[i]!='\0')&&(buff[i]!='\n')){
				chars++;
				total.chars++;
				if(buff[i] == ' '){
					words++;
					total.words++;
				}
			}else if(buff[i]=='\n'){				
				if(i!=0){		/*this line took away 2 hours of my life */
					words++;
					total.words++;
					chars++;
					total.chars++;
				}
				lines++;
				total.lines++;
				break;
			}else break;
		}
	}
	printf("%d %d %d -\n", lines, words, chars);
	return total;
}

//--------------------------------------------
// FUNCTION: struct total_wc read_file(char argv[], struct total_wc total)
// Reads file and counts number of chars, words and lines.
// PARAMETERS:
// struct total_wc total - refer to structure total_wc (22ln),
// (container for all the "global" variables).
//----------------------------------------------

struct total_wc read_file(char argv[], struct total_wc total){
	char buff[MAX_BUFFER_SIZE];
	int fd=open(argv, O_RDONLY);
	if(fd==-1){
		perror(argv);
		total.errors++;
		return total;
	}
	int lines = 0;
	int words = 0;
	int chars = 0;
	int eof = 0;
	while(!eof){
		int status_read = read(fd, buff, MAX_BUFFER_SIZE);
		if(status_read == -1){
			if(errno==EINTR){
				status_read = 0;
			}else{
				perror(argv);
				total.errors++;
				return total;
			}
		}else if(status_read == 0){
			eof = 1;
			break;
		}
	}
	int close_status = close(fd);
	if(close_status == -1){
		perror(argv);
		total.errors++;
		return total;
	}
	int i;
	for(i=0; i<MAX_BUFFER_SIZE; i++){
		if(buff[i]!='\0'){
			chars++;
			total.chars++;
			if(buff[i] == ' '){
				words++;
				total.words++;
			}
			if(buff[i] == '\n'){
				words++;
				total.words++;
				lines++;
				total.lines++;
			}
		}else break;
	}
	printf("%d %d %d %s\n", lines, words, chars, argv);
	return total;
}

//--------------------------------------------
// FUNCTION: int main(int argc, char *argv[])
// The main function. Filters inputs and loops 
// untill all files/commands are processed.
// Also checks for errors, and prints the total wc if necessary.
// PARAMETERS:
// int argc - number of arguments given from the user.
// char *argv[] - array of all the arguments 
// including the name of the program as argv[0].
//----------------------------------------------

int main(int argc, char *argv[]){
	struct total_wc total = {0,0,0,0};
	int i;
	for(i=0; i<argc; ++i){
		if ((argc==1) || (strncmp(argv[i], "-", 1) == 0)){
			total = read_stdin(total);
		}else{
			if(argv[0]!=argv[i]){
				total = read_file(argv[i], total);
			}
		}
	}
	if(argc>1){ 
		printf("%d %d %d total\n", total.lines, total.words, total.chars);
	}
	if(total.errors !=0){
		return 1;
	}else{
		return 0;
	}
}
