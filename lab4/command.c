#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h>     /* Standard I/O functions */
#include <stdlib.h>    /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>    /* Prototypes for many system calls */
#include <errno.h>     /* Declares errno and defines error constants */
#include <string.h>    /* Commonly used string-handling functions */
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int showCommand()
{
    printf("List of Commands\n");
    printf("-----------------\n");

    printf("ls\n");
    printf("vim\n");
    printf("myTouch\n");
    printf("myCat\n");
    printf("myCp\n");
    printf("exit\n");
    // printf("Press Enter After Each command and Argument Progamm is not programmed with single line in mind\n");
}

int LS()
{
    char *binaryPath = "/bin/ls";
    char *arg2 = "/home/_ifty/_programm/_oslab/lab4";

    execl(binaryPath, binaryPath, arg2, NULL);
}

int VIM(char argv[])
{
    char *binaryPath = "/bin/vim";
    // char *arg2 = "/home/_ifty/_programm/_oslab/lab4";

    execl(binaryPath, binaryPath, argv, NULL);
}
int myTouch(char argv[])
{
    int fd = open(argv, O_RDONLY);
    if (fd < 3)
    {
        // printf("%d", fd);
        int fd = open(argv, O_CREAT);
    }
    else
    {
        close(fd);
    }
}

int myCat(char argv[])
{
    char *c = (char *)calloc(1000, sizeof(char));
    int fd = open(argv, O_RDONLY);

    if (fd < 3)
    {
        printf("%d", fd);
        printf("File Does not Exist");
        return 0;
    }

    int sz = read(fd, c, 1000);
    printf(" %s", c);
}

int myCp(char argv[], char argc[])
{
    char *c = (char *)calloc(1000, sizeof(char));
    int fd = open(argv, O_RDONLY);
    int fd2 = open(argc, O_RDONLY | O_CREAT | O_WRONLY);

    if (fd < 3)
    {
        printf("File Does not Exist");
        return 0;
    }

    int sz = read(fd, c, 1000);
    // printf("%d", sz);
    int sz2 = write(fd2, c, 1000);
    // printf("%d", sz2);
}

int main()
{

    pid_t pid1, pid2;
    showCommand();

    pid1 = fork();
    if (pid1 < 0)
        printf("Forking Failed\n");

    else if (pid1 == 0)
    {
        // childProcess
        char arg[7];
        scanf("%s", &arg);

        // if (strcmp(arg, "exit"))
        // {
        //     return 0;
        // }

        if (strcmp(arg, "ls") == 0)
        {
            LS();
            printf("h");
        }
        if (strcmp(arg, "vim") == 0)
        {
            char argv[15];
            scanf("%s", argv);
            VIM(argv);
        }
        if (strcmp(arg, "myTouch") == 0)
        {
            char argq[15];
            scanf("%s", argq);
            myTouch(argq);
        }
        if (strcmp(arg, "myCat") == 0)
        {
            char argv[15];
            scanf("%s", argv);
            myCat(argv);
        }
        if (strcmp(arg, "myCp") == 0)
        {
            char argv[15];
            scanf("%s", argv);
            char argc[15];
            scanf("%s", argc);
            myCp(argv, argc);
        }
    }

    else if (pid1 > 0)
    {
        wait(NULL);
        // main();
        return 0;
    }
}