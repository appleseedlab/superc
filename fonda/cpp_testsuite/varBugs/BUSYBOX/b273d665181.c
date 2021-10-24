#include <stdio.h>
#include <stdlib.h>

void list_single()
{
  #ifdef BB_FEATURE_LS_FILETYPES
  int info;
  #endif

  #ifdef BB_FEATURE_LS_USERNAME
  info = 0;
  #endif

  #ifdef BB_FEATURE_LS_FILETYPES
  if (rand() % 2)
    printf("%d", info); // ERROR
  #endif
}

void showfiles()
{
  list_single();
}

int main(int argc, char** argv)
{
  showfiles();
  return 0;
}
