#include <stdlib.h>
#include <string.h>

#ifdef WIN32X
void ap_get_win32_interpreter()
{
  char buffer[1024];

  int i;
  if (rand() % 2) {
    for (i = 0; i < sizeof(buffer); i++) {
      //do something
    }
    buffer[i] = '\0';
  }
}
#endif

int main(void)
{
  #ifdef WIN32X
  ap_get_win32_interpreter();
  #endif
  return 0;
}
