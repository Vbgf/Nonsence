#include<stdio.h>
#include<time.h>
#define MEMORIAL_TIME 1413133200

struct date {
	int seconds;
	int minutes;
	int hours;
	int days;
	int months;
	int years;
};

void fill_struct_date (long int data, struct date *date) {
	date->seconds = data%60;
	data = data/60;
	date->minutes = data%60;
	data = data/60;
	date->hours = data%24;
	data = data/24;
	date->days = data%30;
	data = data/30;
	date->months = data%12;
	data = data/12;
	date->years = data;
}

void print_struct_date (struct date *date) {
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("       Time since Katinka Georgieva Vasileva passed away:\n");	
	printf("Years: %d  ", date->years);
	printf("Months: %d  ", date->months);
	printf("Days: %d  ", date->days);
	printf("Hours: %d  ", date->hours);
	printf("Minutes: %d  ", date->minutes);
	printf("Seconds: %d\n", date->seconds);
}

	
int main () {
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("Loading...\n");
	long int time_now = time(NULL);
	int time_since = time_now - MEMORIAL_TIME;
	for(;;){
		if(time_now!=time(NULL)) {
			time_now++;
			time_since++;
			struct date since;
			fill_struct_date (time_since, &since);
			print_struct_date (&since);
		}
	}
	return 0;
}
