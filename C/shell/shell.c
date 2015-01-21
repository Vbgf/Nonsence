//--------------------------------------------
// NAME: Vasil Kolev
// CLASS: XIb
// NUMBER: 6
// PROBLEM: #1
// FILE NAME: shell.c (unix file name)
// FILE PURPOSE:
// This is an "sucessful" attempt at shell.
//---------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 65536
#define MAX_WORD_SIZE 64

//--------------------------------------------
// FUNCTION: char** parse_cmdline(const char* cmdline)
// Reworks input string and splits it into a char**.
// PARAMETERS:
// const char* cmdline - the input string.
//----------------------------------------------

char** parse_cmdline(const char* cmdline){
	int i;
	char cmd_return[MAX_WORD_SIZE][MAX_BUFFER_SIZE];
	int counter=0, word=0, last_space_pos=0;
	for(i=0; i<MAX_BUFFER_SIZE; i++){
		if(cmdline[i]=='\n'){
			for(counter=0;;counter++){
				if(cmdline[counter]=='\n'){
					cmd_return[word][counter-last_space_pos] = '\0';
					break;
				}else{
					if(cmdline[counter] == ' '){
						cmd_return[word][counter-last_space_pos] = '\0';
						word++;
						last_space_pos=counter;
					}else{
						cmd_return[word][counter-last_space_pos] = cmdline[counter];
					}
				}
			}
		break;
		}
	}
	if(counter != 0){  //incase there is only 1 word in the input string
		word++;
		char** result = malloc(word* sizeof(char*));
		for(i = 0; i < word; i++){
			result[i] = malloc(sizeof(cmd_return[i]));
			result[i] = cmd_return[i];
		}
		return result;
	}else{
		perror("No arguments error"); //This could use some work
	}
	return;
}

//--------------------------------------------
// FUNCTION: int main()
// Reads from stdin, calls parse_cmdline, and makes a child process.
// The child works on the input commands.
// PARAMETERS:
// None.
//----------------------------------------------

int main(){
	char buff[MAX_BUFFER_SIZE];
	char** argv;
	int eof = 0;
	while(!eof){
		int status_read = read(STDIN_FILENO, buff, MAX_BUFFER_SIZE);
		if(status_read == -1){
			if(errno==EINTR){
				status_read = 0;
			}else{
				perror("Reading from cmdline");			
				return 1;
			}
		}else if(status_read == 0){
			eof = 1;
			break;
		}
		argv = parse_cmdline(buff);
		if(argv!='\0'){			//I have no clue from here,
			pid_t pid = fork();			//process id of child
			int status;
			if(pid == -1) 
				wait(NULL);
			else if(pid == 0){
				int execv_res = execv(argv[0],argv);
				if(execv_res == -1)
					perror(argv[0]);
			} else {
				pid_t endPid = waitpid(pid, &status, WNOHANG|WUNTRACED);
				if(endPid == -1) {
					perror("waitpid error");
					exit(EXIT_FAILURE);
				}
			}					//to here...
		}
	}
	return 0;
}
