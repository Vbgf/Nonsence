#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 4096

int open_file(char argv[]){
	int eof = 0;
	char buff[BUFFER_SIZE];
	int i;
	int fd = open(argv, O_RDONLY);
	if(fd==-1){
		return 1;
	}
	while(!eof){
		int status_read = read(fd, buff, BUFFER_SIZE);
		if(status_read==-1){
			return 1;
		}else if(status_read==0){
			eof = 1;
			break;
		}
		for(i=0; i<status_read; i++){
			printf("%c", buff[i]);
		}
	}
}

int main (int argc, char *argv[]){
	int i;
	int errors;
	for(i=1;i<argc;++i){
		errors = open_file(argv[i]);
	}
	if(errors!=0){
		return 1;
	}else{
		return 0;
	}
}
