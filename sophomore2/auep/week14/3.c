#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

pthread_cond_t conds[3] = { PTHREAD_COND_INITIALIZER };
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

char code[8] = "17376283";


void *tfn(void *arg){
    long i = (long) arg;
    long ni = (i + 1) % 3;

    pthread_mutex_lock(&m);
    for (int j = 0; j < 8; j++) {
        pthread_cond_wait(conds + i, &m);
        printf("%c", code[j]);
        pthread_cond_signal(conds + ni);
    }
    pthread_mutex_unlock(&m);
}

int main() {
    pthread_t pid;

    for (int i = 0; i < 3; i++) {
        pthread_create(&pid, NULL, tfn, (void *) i);
        sleep(1);
    }
    pthread_cond_signal(conds);
    sleep(1);
    printf("\n");
    return 0;
}