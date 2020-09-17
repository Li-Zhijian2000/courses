#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

pthread_t tids[8];
char code[8] = "17376283";

void *tfn(void *arg) {
    long i = (long) arg;

    if (i != 0) {
        pthread_join(tids[i - 1], NULL);
    }
    printf("%c", code[i]);
    pthread_exit(NULL);
}

int main() {
    for (int i = 0; i < 8; i++) {
        int ret = pthread_create(tids + i, NULL, tfn, (void *) i);
        if (ret) {
            fprintf(stderr,  "error: %s\n", strerror(ret));
            exit(-1);
        }
    }
    sleep(1);
    printf("\n");
    return 0;
}