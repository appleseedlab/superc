#include <stdlib.h>
#include <string.h>

#if APR_HAS_SHARED_MEMORY
char *ap_scoreboard_shm = NULL;
#endif

int ap_reopen_scoreboard()
{
  char shm[50];

#if APR_HAS_SHARED_MEMORY
  if (rand() % 2) {
      return 1;
        }
        #endif

  if (*shm) {
      *shm = ap_scoreboard_shm;
        }

  return 1;
  }

int main(void)
{
  ap_reopen_scoreboard();
    return 0;
    }