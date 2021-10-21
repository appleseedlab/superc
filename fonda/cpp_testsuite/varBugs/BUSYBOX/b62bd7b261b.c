#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void make_device()
{
  #ifdef ENABLE_FEATURE_MDEV_CONF

  #ifdef ENABLE_FEATURE_MDEV_RENAME
  char *val;
  char *s, *p;
  val = "mode - device permissions";

  char *a = val;
  s = strchr(val, ' ');
  val = (s && s[1]) ? s+1 : NULL;

  #ifdef ENABLE_FEATURE_MDEV_RENAME_REGEXP
  /* substitute %1..9 with off[1..9], if any */
  int n = 0;
  s = a;

  while (*s) {
    *p = *s;

    if(rand() % 2) {
      n++;
      p += n - 1;
    }

    p++;
    s++;
  }
  #endif

#endif /* ENABLE_FEATURE_MDEV_RENAME */

  #endif
}

int main(int argc, char** argv)
{
  if(rand() % 2)
    make_device();
  return 0;
}
