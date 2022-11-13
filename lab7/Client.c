//#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
// using namespace std;

int main()
{
    char buff[100];
    // ftok to generate unique key
    // key_t key = ftok("shmfile",65);
    key_t key = 1122;

    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0666);

    // shmat to attach to shared memory
    char *str = (char *)shmat(shmid, NULL, 0);

    printf("Data read from memory: %s\n", str);

    // detach from shared memory
    shmdt(str);

    return 0;
}