#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define KEYPATH "/dev/null"
#define KEYID 1

#define NUMSEMS 2
#define SIZEOFSHMSEG 100

int Semop(int __semid, struct sembuf *__sops, size_t __nsops) {
    int rc = semop(__semid, __sops, __nsops);
    if (rc == -1) {
        perror("semop(): ");
        exit(-1);
    }
    return rc;
}

void P(int id, int sem_num) {
    struct sembuf sb[1] = {sem_num, -1, 0};
    Semop(id, sb, 1);
}

void V(int id, int sem_num) {
    struct sembuf sb[1] = {sem_num, 1, 0};
    Semop(id, sb, 1);
}

int main(int argc, char *argv[]) {
    struct shmid_ds shmid_struct;

    key_t key = ftok(KEYPATH, KEYID);
    if (key == -1) {
        perror("flok(): ");
        exit(-1);
    }
    // printf("%d\n", key);
    int semid = semget(key, NUMSEMS, 0644 | IPC_CREAT | IPC_EXCL);
    if (semid == -1) {
        perror("semget(): ");
        exit(-1);
    }

    short sarray[NUMSEMS] = {1, 0};
    int rc = semctl(semid, NUMSEMS, SETALL, sarray);
    if (rc == -1) {
        perror("semctl(): ");
        exit(-1);
    }

    int shmid = shmget(key, SIZEOFSHMSEG, 0644 | IPC_CREAT | IPC_EXCL);
    if (shmid == -1) {
        perror("shmget(): ");
        exit(-1);
    }

    int i;
    for (i = 0; i < 2; i++) {
        if (fork() == 0) break;
    }

    if (i == 2) {
        int rtn;
        while (wait(&rtn) != -1) continue;
        semctl(semid, 0, IPC_RMID);
        shmctl(shmid, IPC_RMID, &shmid_struct);
        return 0;
    }
    // 消费者
    if (i == 0) {
        char *addr = (char *)shmat(shmid, NULL, 0);
        int rnd;
        for (int i = 0; i < 10; i++) {
            P(semid, 1);
            sscanf(addr, "%d", &rnd);
            printf("read:   %d\n\n", rnd);
            V(semid, 0);
        }

        exit(0);
    }
    // 生产者
    if (i == 1) {
        char *addr = (char *)shmat(shmid, NULL, 0);
        srand(17376283);
        int rnd;
        for (int i = 0; i < 10; i++) {
            rnd = rand();
            P(semid, 0);
            sprintf(addr, "%d", rnd);
            printf("write:  %d\n", rnd);
            V(semid, 1);
        }

        exit(0);
    }
}