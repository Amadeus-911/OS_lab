#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h>     /* Standard I/O functions */
#include <stdlib.h>    /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>    /* Prototypes for many system calls */
#include <errno.h>     /* Declares errno and defines error constants */
#include <string.h>    /* Commonly used string-handling functions */
#include <sys/wait.h>

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

void bubbleSort(int array[], int size)
{
    for (int step = 0; step < size - 1; ++step)
    {
        for (int i = 0; i < size - step - 1; ++i)
        {
            if (array[i] > array[i + 1])
            {
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
        }
    }
}

void childProcess(int arr[], int n)
{
    bubbleSort(arr, n);
}

void parentProcess(int arr[], int n, int x)
{
    int result = binarySearch(arr, x, 0, n - 1);
    if (result == -1)
        printf("Not found");
    else
        printf("Element is found at index %d", result);
    return;
}

int main(int argc, char *argv[])
{
    pid_t pid1, pid2;

    int n, x;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    scanf(" %d", &x);

    pid1 = fork();
    if (pid1 < 0)
        printf("Forking Failed\n");

    else if (pid1 == 0)
    {
        childProcess(arr, n);
        for (int i = 0; i < n; ++i)
        {
            printf("%d ", arr[i]);
        }
    }

    else if (pid1 > 0)
    {
        wait(NULL);
        sleep(2);
        wait(NULL);

        parentProcess(arr, n, x);
    }

    return 0;
}
