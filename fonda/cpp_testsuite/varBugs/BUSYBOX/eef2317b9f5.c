#include <stdlib.h>
#include <getopt.h>

int main(int argc, char **argv)
{
  char *buf;
  int bufsize = 8196;
  int i;
  int cmd = 3;

  while ((i = getopt(argc, argv, "cn:s:")) > 0) {
    switch (i) {
    case 'c':
      cmd = 4;
      break;
    case 'n':
      cmd = 8;
      break;
    }
  }

  if (cmd == 8) {
    goto all_done;
  }

  buf = malloc(bufsize);

 all_done:
  #ifdef CONFIG_FEATURE_CLEAN_UP
  if (buf) { //WARNING
    free(buf); //ERROR
  }
  #endif
  return 0;
}
