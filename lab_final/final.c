#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h>     /* Standard I/O functions */
#include <stdlib.h>    /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>    /* Prototypes for many system calls */
#include <errno.h>     /* Declares errno and defines error constants */
#include <string.h>    /* Commonly used string-handling functions */
#include <sys/wait.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int type = 0;

isPrime(int n)
{
    int flag;
    if (n == 0 || n == 1)
        flag = 1;

    for (int i = 2; i <= n / 2; ++i)
    {

        // if n is divisible by i, then n is not prime
        // change flag to 1 for non-prime number
        if (n % i == 0)
        {
            flag = 1;
            break;
        }
    }
    return flag;
}

void *func(void *arg)
{
    // detach the current thread from the calling thread
    pthread_detach(pthread_self());

    arg = (int)arg;
    int x = arg;

    if (type == 1)
    {
        printf("Welcome to FIFA World CUP Lucky");
    }

    if (type == 2)
    {
        if (x % 2 == 0)
        {
            printf("Welcome to FIFA World CUP Lucky");
        }
    }

    if (type == 4)
    {
        if (isPrime(x) == 0)
        {
            printf("Welcome to FIFA World CUP Lucky");
        }
        else
        {
            printf("Welcome to FIFA World CUP ");
        }
    }

    // printf("Inside the thread %d\n", pthread_self());

    // exit the current thread
    pthread_exit(NULL);
}

void fun(int seat)
{
    pthread_t ptid;

    // Creating a new thread
    pthread_create(&ptid, NULL, func, (void *)seat);
    // printf("This line may be printed before thread terminates\n");

    // The following line terminates the thread manually
    // pthread_cancel(ptid);

    // Compare the two threads created
    // if (pthread_equal(ptid, pthread_self()))
    //     printf("Threads are equal %d \n", pthread_self());
    // else
    //     printf("Threads are not equal %d \n", ptid);

    // Waiting for the created thread to terminate
    pthread_join(ptid, NULL);

    // printf("This line will be printed after thread ends\n");

    pthread_exit(NULL);
}

int main()
{
    // char str[] = "VIP.txt";
    // printf("%s", str);
    // char *c = (char *)calloc(1000, sizeof(char));
    // int fd = open(str, O_RDONLY);

    // if (fd < 3)
    // {
    //     printf("File Does not Exist");
    //     return 0;
    // }
    // int sz = read(fd, c, 1000);
    // printf("%d", sz);
    // printf("%c", c[2]);
    // if (c == "SRESHTHO")
    // {
    //     printf("heeee");
    // }

    char name[10];
    char name1[10];
    char name2[10];
    char name3[10];
    int seat;
    int fds[2], fds1[2], fds2[2], fds3[2];
    int status;

    scanf("%d", &seat);

    status = pipe(fds);
    if (status == -1)
    {
        printf("Unable to create pipe");
        return 1;
    }

    pipe(fds1);
    pipe(fds2);

    pipe(fds3);

    pid_t pid, pid1, pid2, pid3;

    pid = fork();

    if (pid < 0)
        printf("Forking Failed\n");

    else if (pid == 0)
    {
        // 1st child
        char str[] = "VIP.txt";
        // printf("%s", str);
        char *c = (char *)calloc(1000, sizeof(char));
        int fd = open(str, O_RDONLY);

        if (fd < 3)
        {
            printf("File Does not Exist");
            return 0;
        }
        int sz = read(fd, c, 1000);
        // printf("%d", sz);
        // printf("%s", c);

        write(fds[1], c, sz);
        close(fds[1]);

        // char *nam;
        // for (int i = 0; i < sz; i++)
        // {
        //     nam[i] = c[i];
        // }

        // printf("%c", nam[1]);

        pid1 = fork();
        if (pid1 < 0)
            printf("Forking Failed\n");

        else if (pid1 == 0)
        {
            // 2ndchild

            char str[] = "VVIP.txt";
            // printf("%s", str);
            char *c = (char *)calloc(1000, sizeof(char));
            int fd = open(str, O_RDONLY);

            if (fd < 3)
            {
                printf("File Does not Exist");
                return 0;
            }
            int sz = read(fd, c, 1000);
            // printf("%d", sz);
            // printf("%s", c);

            write(fds1[1], c, sz);
            close(fds1[1]);

            // new fork
            pid2 = fork();
            if (pid2 < 0)
                printf("Forking Failed\n");

            else if (pid2 == 0)
            {
                // 3rd child

                char str[] = "Upper-Tier.txt";
                // printf("%s", str);
                char *c = (char *)calloc(1000, sizeof(char));
                int fd = open(str, O_RDONLY);

                if (fd < 3)
                {
                    printf("File Does not Exist");
                    return 0;
                }
                int sz = read(fd, c, 1000);
                // printf("%d", sz);
                // printf("%s", c);

                write(fds2[1], c, sz);
                close(fds2[1]);

                pid3 = fork();
                if (pid3 < 0)
                    printf("Forking Failed\n");

                else if (pid3 == 0)
                {
                    // 4th child

                    char str[] = "Lower-Tier.txt";
                    // printf("%s", str);
                    char *c = (char *)calloc(1000, sizeof(char));
                    int fd = open(str, O_RDONLY);

                    if (fd < 3)
                    {
                        printf("File Does not Exist");
                        return 0;
                    }
                    int sz = read(fd, c, 1000);
                    // printf("%d", sz);
                    // // printf("%s", c);

                    write(fds3[1], c, sz);
                    close(fds3[1]);
                }

                else if (pid3 > 0)
                {
                    // parent
                }
            }

            else if (pid2 > 0)
            {
                // parent
            }
        }

        else if (pid1 > 0)
        {
            // parent
        }
    }

    else if (pid > 0)
    {
        // parent
        wait(NULL);
        read(fds[0], name, 10);
        read(fds1[0], name1, 10);
        read(fds2[0], name2, 10);
        read(fds3[0], name3, 10);

        // printf("%s", name);
        printf("%s", name1);
        // printf("%s", name2);
        // printf("%s", name3);

        char rname[10] = "MUTI";

        if (name == "MUTI")
        {
            type = 1;
        }
        if (name1 == "MUTI")
        {
            type = 2;
        }
        if (name2 == "MUTI")
        {
            type = 3;
        }
        if (name3 == "MUTI")
        {
            printf("%s", name3);
            type = 4;
        }

        printf("%d", type);
        fun(seat);
    }
}