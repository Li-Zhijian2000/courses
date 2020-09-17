#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rtn;

    if (fork() == 0) {
        execv("./calc", argv);
        exit(-1);
    } else {
        wait(&rtn);
        if (rtn < 0)
            printf("%d\n", rtn);
    }
    return 0;
}