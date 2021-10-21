#include <stdlib.h>

#ifdef CONFIG_FEATURE_LS_TIMESTAMPS
#define TIME_MASK       (3U<<23)
#endif

#define LIST_FILENAME(1U<<11)

static unsigned int all_fmt;

int main(int argc, char** argv)
{
  all_fmt = LIST_FILENAME;

  if (rand() % 2) {
    all_fmt &= ~TIME_MASK;
  }

  return 0;
}
