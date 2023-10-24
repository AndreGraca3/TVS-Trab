#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define DATA_SIZE 16*1024*1024
#define RSS_INCREASE_SIZE 2*1024*1024
#define PRIVATE_CLEAN_DATA_SIZE 128

char info[DATA_SIZE];
char data[DATA_SIZE] = {1};

int main() {
	printf("PID: %u\n", getpid());

	const long PAGE_SIZE = sysconf(_SC_PAGE_SIZE);
	printf("PAGE_SIZE: %ld\n", PAGE_SIZE);

	printf("#1 (press ENTER to continue)"); getchar();

	for(int i = 0; i < RSS_INCREASE_SIZE; i++) {
		info[i] = 'a';
		char temp = info[i];
	}

	printf("#2 (press ENTER to continue)"); getchar();

	// increase private clean pages (not visible in /proc/pid/smaps cuz range is KB)
	for(int i = 0; i < PRIVATE_CLEAN_DATA_SIZE; i++) {
		char temp = data[i];
	}

	printf("#3 (press ENTER to continue)"); getchar();

	pid_t pid = fork(); 
	sleep(30);
	if (pid == 0) return 0;

	printf("#4 (press ENTER to continue)"); getchar();

	// d

	printf("#5 (press ENTER to continue)"); getchar();

	// e

	printf("#6 (press ENTER to continue)"); getchar();

	// f
	
	printf("#7 (press ENTER to continue)"); getchar();

	// g

	printf("END (press ENTER to continue)"); getchar();

	return 0;
}
