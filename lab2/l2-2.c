#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h>     /* Standard I/O functions */
#include <stdlib.h>    /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>    /* Prototypes for many system calls */
#include <errno.h>     /* Declares errno and defines error constants */
#include <string.h>    /* Commonly used string-handling functions */
#include <sys/wait.h>

void childProcess()
{
    int n;
    printf("Child_process Input:");
    scanf(" %d", &n);
    if (n < 0)
    {
        return;
    }
    if (n % 2 == 0)
    {
        n = n + 1;
        for (int i = n; i < n + 10; i += 2)
        {
            printf("%d\n", i);
        }
    }
    else
    {
        for (int i = n; i < n + 10; i += 2)
        {
            printf("%d\n", i);
        }
    }
}

void parentProcess()
{
    int n;
    printf("Parent_process Input:");
    scanf(" %d", &n);
    if (n < 0)
    {
        return;
    }
    if (n % 2 == 0)
    {

        for (int i = n; i < n + 10; i += 2)
        {
            printf("%d\n", i);
        }
    }
    else
    {
        n = n + 1;
        for (int i = n; i < n + 10; i += 2)
        {
            printf("%d\n", i);
        }
    }
}

int main(int argc, char *argv[])
{
    pid_t pid1, pid2;

    pid1 = fork();
    if (pid1 < 0)
        printf("Forking Failed\n");

    else if (pid1 == 0)
    {
        childProcess();
    }

    else if (pid1 > 0)
    {
        wait(NULL);
        parentProcess();
    }

    return 0;
}
