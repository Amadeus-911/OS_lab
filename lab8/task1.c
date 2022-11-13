
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isPrime(int n)
{
    if (n == 1 || n == 0)
        return false;

    for (int i = 2; i < n; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

void *func(void *arg)
{
    // detach the current thread from the calling thread
    pthread_detach(pthread_self());

    arg = (int)arg;
    printf("Inside the thread ID = %d\n", pthread_self());
    printf("%d", arg);

    printf("\n");
    for (int i = 1; i <= arg; i++)
    {
        if (isPrime(i))
            printf("%d ", i);
    }
    // exit the current thread
    pthread_exit(NULL);
}

void fun(int n)
{
    pthread_t ptid;

    // Creating a new thread
    pthread_create(&ptid, NULL, func, (void *)n);
    printf("This line may be printed before thread terminates\n");

    // The following line terminates the thread manually
    // pthread_cancel(ptid);

    // Compare the two threads created
    if (pthread_equal(ptid, pthread_self()))
        printf("Threads are equal %d \n", pthread_self());
    else
        printf("Threads are not equal ID=  %d \n", ptid);

    // Waiting for the created thread to terminate
    pthread_join(ptid, NULL);

    printf("This line will be printed after thread ends\n");

    pthread_exit(NULL);
}

// Driver code
int main()
{
    int n;
    scanf("%d", &n);
    fun(n);
    return 0;
}
