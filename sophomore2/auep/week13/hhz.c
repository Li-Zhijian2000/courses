#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

static int waitsem(int semid, int num) {
    struct sembuf sem_b;
    sem_b.sem_num = num;
    sem_b.sem_op = 1;
    sem_b.sem_flg = SEM_UNDO;
    if (semop(semid, &sem_b, 1) == -1) {
        perror("sem_v err");
        return 0;
    }
    return 1;
}
static int postsem(int semid, int num) {
    struct sembuf sem_b;
    sem_b.sem_num = num;
    sem_b.sem_op = -1;
    sem_b.sem_flg = SEM_UNDO;
    if (semop(semid, &sem_b, 1) == -1) {
        perror("sem_p err");
        return 0;
    }
    return 1;
}

int main() {
    int semid, shmid, i;
    struct shmid_ds buf;
    semid = semget(IPC_PRIVATE, 2, 0664 | IPC_CREAT);
    if (semid == -1) {
        perror("sem_g err");
        exit(-1);
    }
    short semval[2] = {1, 0};
    if (semctl(semid, 2, SETALL, semval) == -1) {
        perror("sem_c err");
        exit(-1);
    }
    shmid = shmget(IPC_PRIVATE, 4096, 0664 | IPC_CREAT);
    if (shmid == -1) {
        perror("shm_g err");
        exit(-1);
    }
    for (i = 0; i < 2; i++) {
        if (fork() == 0) break;
    }
    if (i == 0) {
        int content, i;
        char *write;
        write = (char *)shmat(shmid, NULL, 0);
        srand(17375494);
        for (i = 0; i < 10; i++) {
            postsem(semid, 0);
            content = rand();
            sprintf(write, "%d", content);
            printf("write:   %d\n", content);
            waitsem(semid, 1);
        }
        // shmdt(write);
        exit(0);
    }
    if (i == 1) {
        int content, i;
        char *read;
        read = (char *)shmat(shmid, NULL, SHM_RDONLY);
        for (i = 0; i < 10; i++) {
            postsem(semid, 1);
            sscanf(read, "%d", &content);
            printf("read:    %d\n\n", content);
            waitsem(semid, 0);
        }
        // shmdt(read);
        exit(0);
    }
    if (i == 2) {
        // waitpid(0, NULL, 0);
        int rtn;
        while (wait(&rtn) != -1) continue;
        shmctl(shmid, IPC_RMID, &buf);
        semctl(semid, 0, IPC_RMID);
        return 0;
    }
}
