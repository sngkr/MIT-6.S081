/*
 * @Author: your name
 * @Date: 2021-07-31 13:56:59
 * @LastEditTime: 2021-07-31 18:06:45
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /xv6-labs-2020/user/sleep.c
 */
#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"

int main(int argn, char *argv[])
{
  if (argn != 2)
  {
    fprintf(2, "must 1 argument for sleep\n");
    exit(1);
  }
  int sleepNum = atoi(argv[1]);
  printf("(nothing happens for a little while)\n");
  sleep(sleepNum);
  exit(0);
}
