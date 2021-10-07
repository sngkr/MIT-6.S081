#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"

void next(int fp[2])
{
  int fc[2];
  pipe(fc);

  close(fp[1]);
  int prime;
  if (read(fp[0], &prime, sizeof(int)) == 0)
  {
    close(fp[0]); //这个关0 不一定随时发生，所以要确保被关闭
    exit(0);
  }
  else
    printf("prime %d\n", prime);

  if (fork() == 0)
  {
    close(fp[0]); //确保关闭fp[0]
    next(fc);
  }
  else
  {
    close(fc[0]);
    while (1)
    {
      int temp;
      if (read(fp[0], &temp, sizeof(int)) == 0)
      {
        close(fp[0]); /* 确保关闭fp[0] */
        break;
      }
      if (temp % prime != 0)
      {
        write(fc[1], &temp, sizeof(int));
      }
    }
    close(fc[1]);
    wait(0);/* 要注意加上，不然真会错给你看 */
  }

  exit(0);
}

int main(int argc, char *argv[])
{

  int fp[2];
  if (argc != 1)
  {
    printf("Usage: primes\n");
    exit(1);
  }

  pipe(fp);
  if (fork() == 0)
  {
    next(fp);
  }
  else
  {
    close(fp[0]);
    for (int i = 2; i <= 35; i++)
    {
      write(fp[1], &i, sizeof(int));
    }
    close(fp[1]);
    wait(0);/* 要注意加上，不然真会错给你看 */
  }
  exit(0);
}
