#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/types.h>

void c(int s) {
  printf("catch\n");
  signal(s, c);
}

int main() {
  int fd[2];
  while (pipe(fd) == -1);
  pid_t pid = fork();
  if (!pid) {
    close(fd[1]);
    char buf[4] = { 0 };
    read(fd[0], buf, 4);
    printf("send sigquit\n");
    kill(getppid(), SIGQUIT);
    close(fd[0]);
  } else if (pid > 0) {
    close(fd[0]);
    signal(SIGQUIT, c);
    char *ok = "ok";
    sleep(1);
    write(fd[1], ok, 3);
    close(fd[1]);
    wait(0);
  }
  return  0;
}