#include "../kernel/types.h"
#include "../user/user.h"
#include "../kernel/param.h"

int main(int argc, char *argv[])
{
  char buf[512];
  char *all_argv[MAXARG];
  int i;
  for (i = 1; i < argc; i++)
  {
    all_argv[i - 1] = argv[i];
    //printf("%s\n", argv[i]);
  }

  all_argv[argc] = 0;

  while (1)
  {

    i = 0;
    while (1)
    {
      int len = read(0, &buf[i], 1);
      if (buf[i] == '\n' || len == 0)
        break;
      // printf("%c\n",buf[i]);
      i++;
    }
    /* 退出条件需要学习，思路参考 */
    if (i == 0)
      break;
    buf[i] = 0;

    all_argv[argc - 1] = buf;

    if (fork() == 0)
    {
      exec(all_argv[0], all_argv);
      exit(0);
    }
    else
    {
      wait(0);
    }
  }
  exit(0);
}
