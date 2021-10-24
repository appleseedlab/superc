#include <stdio.h>

int main(int argc, char** argv)
{
  int n = -1;

  if (n < 0) { /* error in get_groups() */
    #ifndef ENABLE_DESKTOP
    printf("can't get groups");
    #else
    return EXIT_FAILURE;
    #endif
  }
  return 0;
}
