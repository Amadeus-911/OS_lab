#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)

        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

int main()
{
    char buff[100];

    int arr[10];
    // ftok to generate unique key
    // key_t key = ftok("shmfile",65);
    key_t key = 1122;

    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    int *buff_arr = (int *)shmat(shmid, NULL, 0);

    printf("Write Data : ");

    // read
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        scanf("%d", &arr[i]);
    }

    // sort
    bubbleSort(arr, sizeof(arr) / sizeof(arr[0]));

    // copy
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        buff_arr[i] = arr[i];
    }

    // print
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        printf("%d ", buff_arr[i]);
    }

    // detach from shared memory
    shmdt(buff_arr);

    return 0;
}