#include <stdlib.h>
#include <string.h>

void ssl_init_ModuleKill()
{
  char *sc = malloc(sizeof(char) * 45);

  // code making use of 'sc'
  strcpy(sc, "something");

  #ifdef SHARED_MODULE
  free(sc);
  #endif

  // return having forgotten to free the memory
  return;
}

int main(void)
{
  ssl_init_ModuleKill();
  return 0;
}
