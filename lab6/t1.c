#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h>     /* Standard I/O functions */
#include <stdlib.h>    /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>    /* Prototypes for many system calls */
#include <errno.h>     /* Declares errno and defines error constants */
#include <string.h>    /* Commonly used string-handling functions */
#include <sys/wait.h>

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

int binarySearch(int array[], int x, int low, int high)
{

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

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
    int fds[2];
    int fds2[2];
    int status;
    int status2;
    int pid;
    int arr[5];
    int rarr[5];
    int sVal;
    int rVal;

    status = pipe(fds);
    if (status == -1)
    {
        printf("Unable to create pipe");
        return 1;
    }

    status2 = pipe(fds2);
    if (status2 == -1)
    {
        printf("Unable to create pipe");
        return 1;
    }

    pid = fork();

    if (pid < 0)
    {
        printf("Fork Failed");
        return 1;
    }

    // child
    else if (pid == 0)
    {

        wait(NULL);
        read(fds2[0], rarr, sizeof(rarr));
        read(fds2[0], &rVal, sizeof(rVal));

        bubbleSort(rarr, sizeof(rarr) / sizeof(rarr[0]));

        write(fds[1], rarr, sizeof(rarr));

        write(fds[1], &rVal, sizeof(rVal));
        close(fds[1]);
    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            scanf(" %d", &arr[i]);
        }

        scanf("%d", &sVal);

        write(fds2[1], arr, sizeof(arr));

        write(fds2[1], &sVal, sizeof(sVal));
        close(fds2[1]);

        wait(NULL);
        read(fds[0], rarr, sizeof(rarr));
        read(fds[0], &rVal, sizeof(rVal));

        for (int i = 0; i < 5; i++)
        {
            printf("%d ", rarr[i]);
        }
        int n = binarySearch(rarr, rVal, 0, sizeof(rarr) / sizeof(rarr[0]) - 1);
        printf("Result = %d", n);
    }
}