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
#define MAX_CC_COUNT 12
#define START_MINERALS 5000
#define START_SCV 5
#define START_CC 1
#define MINERAL_CARRY 8
#define MARINE_COST 50
#define SCV_COST 50
#define CC_COST 400
#define WIN_COND 20


//-----------------------------------------------------
// All the required data containers.
//-----------------------------------------------------

pthread_mutex_t cc_available[MAX_CC_COUNT];
pthread_t scv_threads[MAX_THREADS];
int player_minerals = 0;
pthread_mutex_t player_minerals_lock;
int spent_minerals = 0;
int map_minerals = 0;
pthread_mutex_t map_minerals_lock;
int marine_count = 0;
int scv_count = 0;
int cc_count = 0;
/*Defines how long something is built (in seconds for sleep())*/
int sleep_cc = 2;
int sleep_scv = 1;
int sleep_marine = 1;
int scv_mine = 2;
int scv_cc_busy = 1;


//-----------------------------------------------------
// FUNCTION: scv
// Simulates all SCV actions(gather&return)
// PARAMETERS:
// NONE
//-----------------------------------------------------

void* scv(void* arg){
	int scv_number = (int64_t)arg;
	while(1){
		int i;
		int check = 1;
		printf("SCV %d is mining\n",scv_number+1);
		pthread_mutex_lock(&map_minerals_lock);
		if(map_minerals<MINERAL_CARRY){
			pthread_mutex_unlock(&map_minerals_lock);		
			return NULL;
		}
		map_minerals -= MINERAL_CARRY;
		pthread_mutex_unlock(&map_minerals_lock);
		printf("SCV %d is transporting minerals\n",scv_number+1);
		sleep(scv_mine);
		while(check){
			for(i=0; i<cc_count; i++){
				check = pthread_mutex_trylock(&cc_available[i]);
				if (check==0){
					pthread_mutex_lock(&player_minerals_lock);
					player_minerals += MINERAL_CARRY;
					pthread_mutex_unlock(&player_minerals_lock);
					pthread_mutex_unlock(&cc_available[i]);
					printf("SCV %d delivered minerals to Command Center %d\n",
						scv_number+1, i+1);
					break;
				}
			}
			sleep(scv_cc_busy);
		}
	}
}


//-----------------------------------------------------
// FUNCTION: create_cc
// Function that creates command center mutex, if failed - exits program
// PARAMETERS:
// NONE
//-----------------------------------------------------

int create_cc(){
	int err;
	err = pthread_mutex_init(&cc_available[cc_count], NULL);
	if(err){
		fprintf(stderr, "ERROR! create_cc returned %d", err);
		exit(1);
	}
	cc_count ++;
	return 0;
}


//-----------------------------------------------------
// FUNCTION: init_game
// Initializes the game with the defined variables
// PARAMETERS:
// NONE
//-----------------------------------------------------

int init_game(){
	int i;
	int err;	
	map_minerals = START_MINERALS;
	player_minerals = 0;
	spent_minerals = 0;
	marine_count = 0;
	scv_count = 0;
	cc_count = 0;
	err = pthread_mutex_init(&player_minerals_lock, NULL);
	if(err){
		fprintf(stderr, "ERROR! mutex_init returned %d", err);
		exit(1);
	}
	err = pthread_mutex_init(&map_minerals_lock, NULL);
	if(err){
		fprintf(stderr, "ERROR! mutex_init returned %d", err);
		exit(1);
	}
	create_cc();
	for(i=0;i<START_SCV;i++){
		create_scv();
	}
	return 0;
}


//-----------------------------------------------------
// FUNCTION: create_scv
// Creates scv thread and increments worker count
// PARAMETERS:
// NONE
//-----------------------------------------------------

int create_scv(){
	int err;
	err = pthread_create(&scv_threads[scv_count], NULL, scv, (void*)(int64_t)scv_count);
	if(err){
		fprintf(stderr, "ERROR! create_scv returned %d", err);
		exit(1);
	}
	scv_count ++;
	return 0;
}


//-----------------------------------------------------
// FUNCTION: print_game_data
// Prints all the information for the game
// PARAMETERS:
// NONE
//-----------------------------------------------------

void print_game_data(){
	//pthread_mutex_lock(&player_minerals_lock);
	//pthread_mutex_lock(&map_minerals_lock);
	printf("    Map minerals: %d\n", map_minerals);
	printf("    Player minerals: %d\n", player_minerals);
	printf("    Spent minerals: %d\n", spent_minerals);
	printf("    Marine count: %d\n", marine_count);
	printf("    SCV count: %d\n", scv_count);
	printf("    Command Center count: %d\n", cc_count);
	//pthread_mutex_unlock(&player_minerals_lock);
	//pthread_mutex_unlock(&map_minerals_lock);
}


//-----------------------------------------------------
// FUNCTION: build_cc
// Tries to create command center
// PARAMETERS:
// NONE
//-----------------------------------------------------

void build_cc(){
	pthread_mutex_lock(&player_minerals_lock);
	if(player_minerals<CC_COST){
		printf("Not enough minerals.\n");
		pthread_mutex_unlock(&player_minerals_lock);
		return;
	}
	player_minerals -= CC_COST;
	spent_minerals += CC_COST;
	pthread_mutex_unlock(&player_minerals_lock);
	sleep(sleep_cc);
	create_cc();
	printf("Command Center %d created\n", cc_count);
}


//-----------------------------------------------------
// FUNCTION: build_scv
// Tries to create an scv
// PARAMETERS:
// NONE
//-----------------------------------------------------

void build_scv(){
	pthread_mutex_lock(&player_minerals_lock);
	if(player_minerals<SCV_COST){
		printf("Not enough minerals.\n");
		pthread_mutex_unlock(&player_minerals_lock);
		return;
	}
	player_minerals -= SCV_COST;
	spent_minerals += SCV_COST;
	pthread_mutex_unlock(&player_minerals_lock);
	sleep(sleep_scv);
	create_scv();
	printf("SCV %d created\n", scv_count);	
}


//-----------------------------------------------------
// FUNCTION: build_marine
// Tries to create a marine
// PARAMETERS:
// NONE
//-----------------------------------------------------

void build_marine(){
	pthread_mutex_lock(&player_minerals_lock);
	if(player_minerals<MARINE_COST){
		printf("Not enough minerals.\n");
		pthread_mutex_unlock(&player_minerals_lock);
		return;
	}
	player_minerals -= MARINE_COST;
	spent_minerals += MARINE_COST;
	pthread_mutex_unlock(&player_minerals_lock);
	sleep(sleep_marine);
	marine_count++;
	printf("You wanna piece of me, boy?\n");
	if(marine_count==WIN_COND){
		printf("VICTORY!!!\n");
		exit(0);	
	}
}


//-----------------------------------------------------
// FUNCTION: play_game
// Checks for user input
// PARAMETERS:
// NONE
//-----------------------------------------------------

void play_game(){
	while(1){
		int get;		
		get = getchar();
		switch((char)get){
		case'c':
			build_cc();
			break;
		case'm':
			build_marine();
			break;
		case's':
			build_scv();
			break;
		case'i':
			print_game_data();
			break;
		case'\n':
		case'\r':
			break;
		default:
			printf("ERROR: No such command!\n");
		}
	}
}


//-----------------------------------------------------
// FUNCTION: main
// Initializes all the threads, handles all user input
// PARAMETERS:
// char* argv[] - all the parameters in order
// int argc - number of given parameters,
// the first parameter is always the executable file
// when no parameters =>(argc = 1 ; argv[0] = ./a.out)
//-----------------------------------------------------

int main(){
	init_game();
	play_game();
	pthread_exit(NULL);
	return 0;
}


/*
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

