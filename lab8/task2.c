
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int fib(int n)
{
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}

void *func(void *arg)
{
    // detach the current thread from the calling thread
    pthread_detach(pthread_self());

    int *arr;
    arr = (int *)arg;
    printf("Inside the thread \n");

    printf("\n");

    for (int i = 1; i < arr[0]; i++)
    {
        arr[i] = fib(i);
    }
    // exit the current thread
    pthread_exit(NULL);
}

void fun(int arr[])
{
    pthread_t ptid;

    // Creating a new thread
    pthread_create(&ptid, NULL, func, (void *)arr);
    printf("This line may be printed before thread terminates\n");

    // The following line terminates the thread manually
    // pthread_cancel(ptid);

    // Compare the two threads created
    if (pthread_equal(ptid, pthread_self()))
        printf("Threads are equal  \n", pthread_self());
    else
        printf("Threads are not equal  \n");

    // Waiting for the created thread to terminate
    pthread_join(ptid, NULL);

    for (int i = 1; i < arr[0]; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("This line will be printed after thread ends\n");

    pthread_exit(NULL);
}

// Driver code
int main()
{
    int n;
    scanf("%d", &n);
    int arr[n + 1];
    arr[0] = n;
    fun(arr);
    return 0;
}
