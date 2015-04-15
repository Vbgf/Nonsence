//-----------------------------------------------------
// NAME: Vasil Kolev
// CLASS: XI B
// NUMBER: 6
// PROBLEM: #3
// FILE NAME: main.c
// FILE PURPOSE:
// This is the only file dedicated to
// solving problem No3. It has everything!
//-----------------------------------------------------

//-----------------------------------------------------
// All the required libraries
// NOTE: when using pthread,
// use -pthread as a parameter when compiling
//-----------------------------------------------------
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#define MAX_THREADS 200
#define NUM_THREADS 5
#define START_MINERALS 5000

//-----------------------------------------------------
// All the required data containers.
// threads - all the current threads (scv, cc, win_con)
// minerals - all info for the minerals:
// minerals[0] - the start minerals
// minerals[1] - current map minerlas
// minerals[2] - current available (collected) minerals
// minerals[3] - spent minerlas
//-----------------------------------------------------
pthread_t threads[MAX_THREADS];
int minerals[4] = {START_MINERALS, START_MINERALS, 0, 0};

//-----------------------------------------------------
// FUNCTION: scv
// Simulates all SCV actions(gather&return)
// PARAMETERS:
// NONE for now. Update at latere date.
//-----------------------------------------------------
void scv(){

}

//-----------------------------------------------------
// FUNCTION: cc
// Simulates Command Center actions
// (user imput & errors)
// PARAMETERS:
// NONE for now. Update at latere date.
//-----------------------------------------------------
void cc(){

}

//-----------------------------------------------------
// FUNCTION: win_con
// Checks for win condition, (build 20 marines)
// PARAMETERS:
// NONE for now. Update at latere date.
//-----------------------------------------------------
void win_con(){

}

//-----------------------------------------------------
// FUNCTION: main
// Initializes all the threads
// PARAMETERS:
// char* argv[] - all the parameters in order
// int argc - number of given parameters,
// the first parameter is always the executable file
// when no parameters =>(argc = 1 ; argv[0] = ./a.out)
//-----------------------------------------------------

/*
int main(){
	return 0;
}
*/


/* Some pthread tests, don't worry about it :D

void* print_hello(void *thread_id){
	int tid;
	tid = (int) thread_id;
	printf("Thread No%d here? Yes!\n", tid);
	pthread_exit(NULL);
}

int main(int argc, char* argv[]){
	pthread_t threads[NUM_THREADS];
	int t;
	for(t=0; t<NUM_THREADS; t++){
		printf("MAIN HERE!, Creating thread No%d\n", t);
		int rc = pthread_create(&threads[t], NULL, print_hello, (void*)t);
		if(rc){
			printf("ERROR! pthread_create() return %d\n", rc);
			exit(-1);
		}		
	}
	printf("Main gonna exit now\n");
	pthread_exit(NULL);
	return 0;
}
*/


