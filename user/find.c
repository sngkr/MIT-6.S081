#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"
#include "../kernel/fs.h"

char *
fmtname(char *path) /* 得到路径最后一个/后的文件名字，可能是目录文件，可能是普通文件 ，switch中已经判断*/
{
  char *p;

  // Find first character after last slash.
  for (p = path + strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;
  return p;
}
void find(char *path, char *filename)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if ((fd = open(path, 0)) < 0)
  {
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  if (fstat(fd, &st) < 0)
  {
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch (st.type)
  {
  case T_FILE:
    if (strcmp(fmtname(path), filename) == 0)
    /* 这个是打印出path 不是filename */
      printf("%s\n", path);
    break;
  case T_DIR:
    if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
    {
      printf("ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    /* 将当前路径弄得到buf上 */
    p = buf + strlen(buf);
    /* 再在buf后strlen(buf)的长度上加上 / */
    *p++ = '/';
    while (read(fd, &de, sizeof(de)) == sizeof(de))
    {                                                                              /* “对于内核而言，所有打开的文件都通过文件描述符引用” */
      if (de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) //inum==0表明这是一个无效的entry
        continue;
      /* name 的长度统一为14 */
      /* 14个内存单元不一定全部被使用， fntname将指针指向最后一个/后，输出这个指针时%s不会管后面为0的元素，所以不会有影响结果 */
      memmove(p, de.name, DIRSIZ);
      /* 将p后的第DIRSIZ(14)元素设为0 ，因为memmove没有管后面的那个终结符，注意自己添加，去掉也可过，怎么说呢，eee安全问题 */
      p[DIRSIZ] = 0;

      find(buf, filename);
    }
    break;
  }

  close(fd);
}

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    fprintf(2, "usage: find <path> <filename>\n");
    exit(1);
  }
  find(argv[1], argv[2]);
  exit(0);
}
