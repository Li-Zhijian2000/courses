#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int fd = open("file.txt", O_RDWR);

    char text[1024] = "May the force be with you, ";
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    int size = read(fd, buf, 20);
    buf[size - 1] = '\0';
    strcat(text, buf);
    strcat(text, "!\n");

    lseek(fd, 0, 0);
    write(fd, text, strlen(text));

    return 0;
}