/*
 * @Author: your name
 * @Date: 2021-07-31 14:05:59
 * @LastEditTime: 2021-07-31 18:06:51
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /xv6-labs-2020/user/pingpong.c
 */
// #include "../kernel/types.h"
// #include "../kernel/stat.h"
// #include "../user/user.h"

// #define STDIN_FILENO 0
// #define STDOUT_FILENO 1
// #define STDDER_FILENO 2

// #define READEND 0
// #define WRITEEND 1

// typedef int pid_t;

// int main(void)
// {
//   // build two pipe
//   int pfd[2];
//   int cfd[2];

//   char buf[10];
//   pid_t pid;

//   pipe(pfd);
//   pipe(cfd);

//   if ((pid = fork()) < 0)
//   {
//     fprintf(STDDER_FILENO, "fork error\n");
//     exit(1);
//   }
//   else if (pid == 0) // child process
//   {
//     close(pfd[WRITEEND]);
//     close(cfd[READEND]);
//     read(pfd[READEND], buf, 4);
//     printf("%d: received %s\n", getpid(), buf);
//     write(cfd[WRITEEND], "pong", 4);
//     close(cfd[WRITEEND]);
//   }
//   else // parent process
//   {
//     close(pfd[READEND]);
//     close(cfd[WRITEEND]);
//     write(pfd[WRITEEND], "ping", 4);
//     close(pfd[WRITEEND]);
//     read(cfd[READEND], buf, 4);
//     printf("%d: received %s\n", getpid(), buf);
//   }
//   exit(0);
// }

#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"

int main(int argc, char *argv[])
{
  int fd[2];
  char buf[10];
  pipe(fd);

  if (fork() == 0)
  {
    /* read的第三个参数还是不要算来 ~.~ */
    if (read(fd[0], buf, 4) == 0)
      printf("child read error\n");
    close(fd[0]);
    printf("%d: received %s\n", getpid(), buf);
    write(fd[1], "pong", 4);
    close(fd[1]);
  }
  else
  {

    write(fd[1], "ping", 4);
    close(fd[1]);
    wait(0);
    if (read(fd[0], buf, 4) == 0)
      printf("child read error\n");
    read(fd[0], buf, strlen(buf));
    printf("%d: received %s\n", getpid(), buf);
    close(fd[0]);
  }
  exit(0);
}
