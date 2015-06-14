//--------------------------------------------
// NAME: Vasil Kolev
// CLASS: XI B
// NUMBER: 6
// PROBLEM: #4
// FILE NAME: ls.c
// FILE PURPOSE:
// This is the only file dedicated to
// solving problem No4. It has everything!
//---------------------------------------------


//-----------------------------------------------------
// All the required libraries
//-----------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>


//-----------------------------------------------------
// Definitions of some colors.
//-----------------------------------------------------

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"


//-----------------------------------------------------
// All the required flags.
// all              =  -a
// info             =  -l
// recursive        =  -R
//-----------------------------------------------------

int all = 0;
int info = 0;
int recursive = 0;


//-----------------------------------------------------
// FUNCTION: advanced
// Handles the optional flag -l
// Prints the "advanced" options of the file like:
// 1. read/write/execute
// 2. number of links
// 3. owner name (ID)
// 4. owner group (ID)
// 5. file size (in bytes)
// 6. date of last change
// 7. file name
// 
// PARAMETERS:
// struct stat *st  -  all the info about the file
// char* name       -  the name of the current file
//-----------------------------------------------------

void advanced(struct stat *st, char* name){
	printf( (st->st_mode & S_IRUSR) ? "r" : "-");
	printf( (st->st_mode & S_IWUSR) ? "w" : "-");
	printf( (st->st_mode & S_IXUSR) ? "x" : "-");
	printf( (st->st_mode & S_IRGRP) ? "r" : "-");
	printf( (st->st_mode & S_IWGRP) ? "w" : "-");
	printf( (st->st_mode & S_IXGRP) ? "x" : "-");
	printf( (st->st_mode & S_IROTH) ? "r" : "-");
	printf( (st->st_mode & S_IWOTH) ? "w" : "-");
	printf( (st->st_mode & S_IXOTH) ? "x" : "-");

	printf(" %zu", st->st_nlink);
	//char command[50];
	//sprintf(command, "getent passwd %d | cut -d: -f1", st->st_uid);
	//system(command);
	printf(" %d", st->st_uid);
	//char command[50];
	//sprintf(command, "getent group %d | cut -d: -f1", st->st_uid);
	//system(command);
	printf(" %d", st->st_gid);
	printf(" %zu", st->st_size);
	char time[50];
	strcpy(time, ctime(&st->st_mtime));
	time[strlen(time)-1] = '\0';
	printf(" %s", time);
}


//-----------------------------------------------------
// FUNCTION: print_result
// Handles the normal output in the console:
// 1. type of file
// 2. file name
// PARAMETERS:
// struct stat *st  -  all the info about the file
// char* name       -  the name of the current file
//-----------------------------------------------------

void print_result(struct stat *st, char* name){
	if(S_ISDIR(st->st_mode)){
		printf("d");
		if(info){
			advanced(st, name);
		}
		printf(" %s%s%s\n", KBLU, name, RESET);
		return;
	}
	if(S_ISREG(st->st_mode)){
		printf("-");
		if(info){
			advanced(st, name);
		}
		printf(" %s%s%s\n", KNRM, name, RESET);
		return;
	}
	if(S_ISCHR(st->st_mode)){
		printf("c");
		if(info){
			advanced(st, name);
		}
		printf(" %s%s%s\n", KYEL, name, RESET);
		return;
	}
	if(S_ISBLK(st->st_mode)){
		printf("b");
		if(info){
			advanced(st, name);
		}
		printf(" %s%s%s\n", KYEL, name, RESET);
		return;
	}
	if(S_ISFIFO(st->st_mode)){
		printf("p");
		if(info){
			advanced(st, name);
		}
		printf(" %s%s%s\n", KYEL, name, RESET);
		return;
	}
	if(S_ISLNK(st->st_mode)){
		printf("l");
		if(info){
			advanced(st, name);
		}
		printf(" %s%s%s\n", KCYN, name, RESET);
		return;
	}
	if(S_ISSOCK(st->st_mode)){
		printf("s");
		if(info){
			advanced(st, name);
		}
		printf(" %s%s%s\n", KMAG, name, RESET);
		return;
	}
}


//-----------------------------------------------------
// FUNCTION: open_dir
// Opens the directory for reading
// and all the info regarding it.
// Then it process it and calls the necessary print.
// All error checking is done in this function.
// PARAMETERS:
// char* folder     -  the path of the folder
//-----------------------------------------------------

void open_dir(char* folder){
	if(strncmp(folder, "-", 1)){
		printf("%s\n", folder);
		DIR *d;
		struct dirent *dir;
		d = opendir(folder);
		if(d){
			int size_ = 10;
			int top_ = 0;
			char** stack = malloc(size_*sizeof(char*));
			if(stack == NULL){
				printf("There was a problem allocating memory! ");
				printf("Will show only nonrecursive options!\n");
				perror("Error");
				recursive = 0;
			}
			while((dir = readdir(d)) != NULL){
				if((strncmp(dir->d_name, ".", 1)) || all){
					struct stat st;
					char path[sizeof(folder)+sizeof(dir->d_name)];
					if((strcmp(folder, ".")) == 0){
						strcpy(path, dir->d_name);
					}else{
						strcpy(path, folder);
						if(path[strlen(path)-1] != '/'){
							strcat(path, "/");
						}
						strcat(path, dir->d_name);
					}
					if(lstat(path, &st) == -1){
						if(errno == 13){
							perror("Cannot open file or dierctory");
						}else if(errno == 2){
							perror("Cannot acess file or directory");
						}else{
							perror("Error");
						}
					}else{
						if(S_ISDIR(st.st_mode) && recursive && path[strlen(path)-1] != '.'){
							if(top_ == size_){
								stack = realloc(stack, 2*size_*sizeof(char*));
								if(stack == NULL){
									printf("There was a problem allocating memory! ");
									printf("Will show only nonrecursive options!\n");
									perror("Error");
									recursive = 0;
								}else{
									size_*=2;
								}
							}
							stack[top_] = strdup(path);
							if(stack[top_] == NULL){
								printf("There was a problem allocating memory! ");
								printf("Will show only nonrecursive options!\n");
								perror("Error");
								recursive = 0;
							}
							top_++;
						}
						print_result(&st, dir->d_name);
					}
				}
			}
			closedir(d);
			printf("\n");
			int i;
			for(i=0;i<top_;i++){
				open_dir(stack[i]);
			}
			free(stack);
		}else{
			struct stat st;
			if(lstat(folder, &st) == -1){
				if(errno == 13){
					perror("Cannot open file or dierctory");
				}else if(errno == 2){
					perror("Cannot acess file or directory");
				}else{
					perror("Error");
				}
			}else{
				print_result(&st, folder);
			}
		}
	}
}

//-----------------------------------------------------
// FUNCTION: main
// Handles all user input and checks for flags -
// (commands like -l, -R, -a).
// PARAMETERS:
// int argc         -  number of given parameters
// char* argv[]     -  all the parameters in order
//-----------------------------------------------------

int main(int argc, char* argv[]){
	int i;
	for(i=1;i<argc;i++){
		if(!strncmp(argv[i], "-", 1)){
			if(strchr(argv[i], 'a')){
				all = 1;
			}
			if(strchr(argv[i], 'l')){
				info = 1;
			}
			if(strchr(argv[i], 'R')){
				recursive = 1;
			}
		}
	}
	for(i=1;i<argc;i++){
		open_dir(argv[i]);
	}
	return 0;
}
