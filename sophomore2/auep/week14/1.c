#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

void *tfn(void *arg) {
    printf("child: pid=%d, ppid=%d\n", getpid(), getppid());
    pthread_exit(NULL);
}

int main() {
    pthread_t tid;
    printf("main: pid=%d, ppid=%d\n", getpid(), getppid());
    int ret = pthread_create(&tid, NULL, tfn, NULL);
    if (ret) {
        fprintf(stderr,  "error: %s\n", strerror(ret));
        exit(-1);
    }
    sleep(1);
    return 0;
}