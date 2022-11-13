#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h>     /* Standard I/O functions */
#include <stdlib.h>    /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>    /* Prototypes for many system calls */
#include <errno.h>     /* Declares errno and defines error constants */
#include <string.h>    /* Commonly used string-handling functions */
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    char *c = (char *)calloc(1000, sizeof(char));
    int fd = open(argv[1], O_RDONLY);
    int fd2 = open(argv[2], O_RDONLY | O_CREAT | O_WRONLY);

    if (fd < 3)
    {
        printf("File Does not Exist");
        return 0;
    }

    int sz = read(fd, c, 1000);
    printf("%d", sz);
    int sz2 = write(fd2, c, 1000);
    printf("%d", sz2);
}