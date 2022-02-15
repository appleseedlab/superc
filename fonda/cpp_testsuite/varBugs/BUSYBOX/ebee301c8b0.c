#include<stdio.h>
#include<stdlib.h>

#if defined (BB_AR)
void copySubFile(int src, int dst)
{
  printf("Copy readSize bytes between two file descriptors");
}
#endif

#if defined (BB_CP_MV)
void copyFile()
{
  int src, dst;
  src = rand() % 100;
  dst = rand() % 200;

  copySubFile(src, dst);
}
#endif

int main(int argc, char **argv)
{
#if defined (BB_CP_MV)
  copyFile();
  #endif
  return 0;
}
