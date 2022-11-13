//#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
// using namespace std;

int binarySearch(int array[], int x, int low, int high)
{

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        // printf("mid: %d", mid);

        if (array[mid] == x)
            return mid;

        if (array[mid] < x)
            low = mid + 1;

        else
            high = mid - 1;
    }

    return -1;
}

int main()
{
    char buff[100];

    int x;
    printf("Find: ");
    scanf("%d", &x);

    int arr[10];
    // ftok to generate unique key
    // key_t key = ftok("shmfile",65);
    key_t key = 1122;

    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0666);

    // shmat to attach to shared memory
    int *buff_arr = (int *)shmat(shmid, NULL, 0);

    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        printf("%d ", buff_arr[i]);
    }

    // read
    // printf("%d", sizeof(buff_arr) / sizeof(buff_arr[0]));

    int n = binarySearch(buff_arr, x, 0, sizeof(arr) / sizeof(arr[0]) - 1);
    if (n == x)
    {
        printf("found");
    }
    else
    {
        printf("not found");
    }

    // detach from shared memory
    shmdt(buff_arr);

    return 0;
}