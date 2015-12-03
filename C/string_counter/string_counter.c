#include<stdio.h>

// No strlen? Well here is my take on that!
// No error checks of any sort.
int lenstr(char* str){
	int i;
	for(i=0;;i++){
		if(str[i] == '\0'){
			return i;
		}
	}
}

// The name is...
int seek(char* str, char* substr){
	int i;
	int j;
	int strlen = lenstr(str);
	int substrlen = lenstr(substr);
	int res = 0;
	int pos;
	int len;

	for(i=0;i<strlen;i++){
		for(j=0;j<substrlen;j++){
			if(str[i]==substr[j]){
				if(j==substrlen-1){
					res++;
					and_destroy(str, i-substrlen+1, substrlen);
				}else{
					i++;
				}
			}else{
				break;
			}
		}
	}

	return res;
}

// ...just for trolls
int and_destroy(char* str, int pos, int len){
	int i;
	for(i=0;i<len;i++){
		str[i+pos] = '0';
	}
	return 0;
}

int main(int argc, char* argv[]){

	if(argc<3){
		printf("Error: not enough parameters given\n");
		printf("Hint! arg1 = string arg2 = substring\n");
		return 0;
	}

	int strlen = lenstr(argv[1]);
	int substrlen = lenstr(argv[2]);

	if(strlen<substrlen){
		printf("Error: substring can't be longer than string\n");
		return 0;
	}

	char str[strlen];
	char substr[substrlen];

	int i;
	for(i=0;i<strlen;i++){
		str[i] = argv[1][i];
	}
	str[strlen] = '\0';

	for(i=0;i<substrlen;i++){
		substr[i] = argv[2][i];
	}
	substr[substrlen] = '\0';

	printf("Result: %d\n", seek(str, substr));
	printf("output string: %s\n", str);
	return 0;
}
