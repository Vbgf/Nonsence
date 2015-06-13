#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

int all = 0;
int info = 0;
int recursive = 0;

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
		if(strncmp(argv[i], "-", 1)){
			printf("%s\n", argv[i]);
			DIR *d;
			struct dirent *dir;
			d = opendir(argv[i]);
			if(d){
				//work with multiple files here!
				while((dir = readdir(d)) != NULL){
					if((strncmp(dir->d_name, ".", 1)) || all){
						struct stat st;
						char path[sizeof(argv[i])+sizeof(dir->d_name)];
						if((strcmp(argv[i], ".")) == 0){
							strcpy(path, dir->d_name);
						}else{
							strcpy(path, argv[i]);
							if(path[strlen(path)-1] != '/'){
								strcat(path, "/");
							}
							strcat(path, dir->d_name);
						}
						if(lstat(path, &st) == -1){
							perror("Error");
						}else{
							print_result(&st, dir->d_name);
						}
					}
				}
				closedir(d);
				printf("\n");
			}else{
				//work with single file here!
				struct stat st;
				if(lstat(argv[i], &st) == -1){
					perror("Error");
				}else{
					print_result(&st, argv[i]);
				}
			}
		}
	}
	return 0;
}


/*
	printf("File Permissions: \t");
	printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
	printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
	printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
	printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
	printf("\n\n");
*/
