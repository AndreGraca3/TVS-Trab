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
	// a
	for(int i = 0; i < RSS_INCREASE_SIZE; i++) {
		info[i] = 'a';
	}

	printf("#2 (press ENTER to continue)"); getchar();
	// b
	for(int i = 0; i < PRIVATE_CLEAN_DATA_SIZE; i++) {
		char temp = data[i * PAGE_SIZE];
	}

	printf("#3 (press ENTER to continue)"); getchar();
	// c
	pid_t pid = fork(); 
	sleep(30);
	if (pid == 0) return 0;

	printf("#4 (press ENTER to continue)"); getchar();
	// d
	char *ptr = (char *)malloc(NEW_DATA_REGION_SIZE);

	printf("#5 (press ENTER to continue)"); getchar();
	// e
	for(int i = 0; i < NEW_DATA_REGION_RSS_SIZE; i++) {
		ptr[i] = 'a';
	}

	printf("#6 (press ENTER to continue)"); getchar();
	// f
	void *lib = dlopen("./my_lib/my_lib.so", RTLD_LOCAL | RTLD_NOW);
	if (!lib) {
		printf("Error: %s\n", dlerror());
		return 1;
	}

	printf("#7 (press ENTER to continue)"); getchar();
	// g
	void (*func)() = dlsym(lib, "func");
	if (func == NULL) {
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(lib);
        return 1;
    }
	func();

	printf("END (press ENTER to continue)"); getchar();
	return 0;
}
