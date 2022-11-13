#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h>     /* Standard I/O functions */
#include <stdlib.h>    /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>    /* Prototypes for many system calls */
#include <errno.h>     /* Declares errno and defines error constants */
#include <string.h>    /* Commonly used string-handling functions */
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int fib(int n)
{
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}

int main()
{
    int n;
    scanf("%d", &n);

    int arr[n];
    // ftok to generate unique key
    // key_t key = ftok("shmfile",65);

    int rarr[n];

    int pid;

    pid = fork();

    if (pid < 0)
    {
        printf("Fork Failed");
        return 1;
    }

    // child
    else if (pid == 0)
    {
        key_t key = 1123;

        // shmget returns an identifier in shmid
        int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

        // shmat to attach to shared memory
        int *buff_arr = (int *)shmat(shmid, NULL, 0);

        printf("%d", n);
        for (int i = 0; i < n; i++)
        {
            arr[i] = fib(i);
        }

        // copy
        for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
        {
            buff_arr[i] = arr[i];
        }
        shmdt(buff_arr);
    }
    else // parent
    {
        key_t key = 1123;

        // shmget returns an identifier in shmid
        int shmid = shmget(key, 1024, 0666);

        // shmat to attach to shared memory
        int *buff_arr = (int *)shmat(shmid, NULL, 0);

        for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
        {
            printf("%d ", buff_arr[i]);
        }
        shmdt(buff_arr);
    }
}