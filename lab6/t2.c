#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h>     /* Standard I/O functions */
#include <stdlib.h>    /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>    /* Prototypes for many system calls */
#include <errno.h>     /* Declares errno and defines error constants */
#include <string.h>    /* Commonly used string-handling functions */
#include <sys/wait.h>

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
    int rarr[n];

    int fds[2];
    int status;
    int pid;

    status = pipe(fds);
    if (status == -1)
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

    else if (pid == 0)
    {
        printf("%d", n);
        for (int i = 0; i < n; i++)
        {
            arr[i] = fib(i);
        }
        write(fds[1], arr, sizeof(arr));
        close(fds[1]);
    }
    else
    {
        read(fds[0], rarr, sizeof(rarr));
        for (int i = 0; i < n; i++)
        {
            printf("%d ", rarr[i]);
        }
    }
}