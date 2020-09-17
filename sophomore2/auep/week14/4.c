#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

void *pcode(void *arg) {
    char code[8] = "17376283", rcode[8] = "38267371";

    while (1) {
        int val;
        sem_getvalue(&sem, &val);
        printf("%s\n", val == 1 ? code : rcode);
        usleep(100000);
    }
}

void *send(void *arg) {
    while (1) {
        sem_wait(&sem);
        usleep(500000);
        sem_post(&sem);
        usleep(500000);
    }
}

int main() {
    pthread_t pid1, pid2;
    sem_init(&sem, 0, 1);
    pthread_create(&pid1, NULL, pcode, NULL);
    pthread_create(&pid2, NULL, send, NULL);

    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);
}