#include <errno.h>
#include <stdio.h>

#define UEVENT_BUFFER_SIZE 2048 /* buffer for the variables */

static char buf[UEVENT_BUFFER_SIZE];
static int buflen = 0;

#if defined(CONFIG_HOTPLUG)
int add_uevent_var()
{
  int len = sprintf(&buf[buflen], "MODALIAS=");
  buflen += len + 1;
  return 0;
}
#else
int add_uevent_var()
{ return 0; } // (2)
#endif

int input_add_uevent_modalias_var()
{
  if (add_uevent_var())
    return -ENOMEM;

  buf[buflen - 1] = 'x'; // ERROR: buflen == 0, so buf[-1] is written.
  return 0;
}

int main(int argc, char** argv)
{
  input_add_uevent_modalias_var(); // (1)
  return 0;
}
