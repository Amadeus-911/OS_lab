#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    char *c = (char *)calloc(100, sizeof(char));
    int fd = open("task1.txt", O_RDONLY | O_CREAT);
    int x = close(fd);
    int sz = read(fd, c, 100);
    int sz = write(fd, c, 100);
}