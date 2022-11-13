#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h>     /* Standard I/O functions */
#include <stdlib.h>    /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>    /* Prototypes for many system calls */
#include <errno.h>     /* Declares errno and defines error constants */
#include <string.h>    /* Commonly used string-handling functions */
#include <sys/wait.h>

void childProcess()
{
    fork();
}

void parentProcess()
{
    // printf("process");
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
        parentProcess();
    }
    printf("run\n");
    return 0;
}
