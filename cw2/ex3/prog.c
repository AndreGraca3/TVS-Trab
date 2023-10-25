#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <dlfcn.h>

#define DATA_SIZE 16*1024*1024
#define RSS_INCREASE_SIZE 2*1024*1024
#define PRIVATE_CLEAN_DATA_SIZE 128
#define CODE_REGION_SIZE 4 * 1024
#define DATA_REGION_SIZE 256 * 1024
#define NEW_DATA_REGION_SIZE 512*1024
#define NEW_DATA_REGION_RSS_SIZE 256*1024

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

	for(int i = 0; i < PRIVATE_CLEAN_DATA_SIZE; i++) {
		char temp = data[i * (DATA_SIZE / PAGE_SIZE)];
	}

	printf("#3 (press ENTER to continue)"); getchar();

	pid_t pid = fork(); 
	//sleep(30);
	if (pid == 0) return 0;

	printf("#4 (press ENTER to continue)"); getchar();

	char *ptr = (char *)malloc(NEW_DATA_REGION_SIZE);

	printf("#5 (press ENTER to continue)"); getchar();

	for(int i = 0; i < NEW_DATA_REGION_RSS_SIZE; i++) {
		ptr[i] = 'a';
	}

	printf("#6 (press ENTER to continue)"); getchar();

	void *data_region = mmap(NULL, DATA_REGION_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	void *code_region = mmap(NULL, CODE_REGION_SIZE, PROT_EXEC | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	
	printf("#7 (press ENTER to continue)"); getchar();

	// g

	printf("END (press ENTER to continue)"); getchar();

	munmap(code_region, CODE_REGION_SIZE);
    munmap(data_region, DATA_REGION_SIZE);

	return 0;
}
