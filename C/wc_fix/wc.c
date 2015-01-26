#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 4096
//#define BUFFER_SIZE 32
int read_file(char argv[]){
	int fd = open(argv, O_RDONLY);
	if (fd==-1){
		perror(argv);
		return 1;
	}
	char buff[BUFFER_SIZE];
	int eof = 0;
	while(!eof){
		int status_read = read(fd, buff, BUFFER_SIZE);
		if(status_read == -1){
			perror(argv);
			return 1;
		}else if(status_read == 0){
			eof=1;
			break;
		}
		printf("Here the buffer starts\n");
		int i;
		for(i=0;i<status_read; i++){
			printf("%c", buff[i]);
		}
		printf("Here the buffer ends\n");
	}
	int close_status = close(fd);
	if(close_status == -1){
		perror(argv);
		return 1;
	}
	return 0;
}

int main(int argc, char *argv[]){
	int i;
	int result;
	for(i=0; i<argc; ++i){
		if ((argc==1) || (strncmp(argv[i], "-", 1) == 0)){
			//total = read_stdin();
		}else{ 
			if(argv[0]!=argv[i]){
				result = read_file(argv[i]);
			}
		}
	}
	if (result !=0){
		return 1;
	} else{
		return 0;
	}
}
