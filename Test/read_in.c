#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"
int main()
{
  char buf[23];
  printf("begin\n");
  if (!fork())
  {
    printf("son:hello\n");
    int i=0;
    while(1)
    {
      if(read(0, &buf[i], 1)==0 || buf[i]=='\n')
      break;
      
      i++;
    }

    printf("son:%s\n", buf);

  }
  else
  {
    wait(0);
      printf("father:hello\n");
        int i=0;
    while(1)
    {
      if(read(0, &buf[i], 1)==0 || buf[i]=='\n')
      break;
      
      i++;
    }
    printf("father:%s\n", buf);
    exit(0);
  }
}
