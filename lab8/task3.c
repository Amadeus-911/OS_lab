
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int A[10][10];
int B[10][10];
int C[10][10];

void *func(void *arg)
{
    // detach the current thread from the calling thread
    pthread_detach(pthread_self());

    printf("Inside the thread \n");
    int *arr;
    arr = (int *)arg;

    int i, j, k;
    i = arr[0];
    j = arr[1];
    k = arr[2];

    int n = 10;
    C[i][j] += A[i][k] * B[k][j];
    // exit the current thread

    pthread_exit(NULL);
}

void fun()
{
    pthread_t ptid;

    // Creating a new thread
    pthread_create(&ptid, NULL, func, NULL);
    printf("This line may be printed before thread terminates\n");

    // The following line terminates the thread manually
    // pthread_cancel(ptid);

    int i, j, k;
    int n = 10;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            C[i][j] = 0;
            for (k = 0; k < n; k++)
            {
                int arr[3] = {i, j, k};
                pthread_create(&ptid, NULL, func, (void *)arr);
            }
        }
    }

    // Compare the two threads created
    if (pthread_equal(ptid, pthread_self()))
        printf("Threads are equal \n");
    else
        printf("Threads are not equal \n");

    // Waiting for the created thread to terminate
    pthread_join(ptid, NULL);
    // for (i = 0; i < n; i++)
    // {
    //     for (j = 0; j < n; j++)
    //     {
    //         printf("%d\t", C[i][j]);
    //     }
    //     printf("\n");
    // }

    printf("This line will be printed after thread ends\n");

    pthread_exit(NULL);
}

// Driver code
int main()
{
    int i, j, k;
    int n = 10;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &B[i][j]);
        }
    }

    fun();
    return 0;
}
