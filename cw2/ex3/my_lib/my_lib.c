#define DATA_SIZE 256*1024
#define PRIVATE_DIRTY_DATA_SIZE 128*1024

char data[DATA_SIZE] = {1};

void func() {
    for(int i = 0; i < PRIVATE_DIRTY_DATA_SIZE; i++) {
        data[i] = 'a';
    }
}