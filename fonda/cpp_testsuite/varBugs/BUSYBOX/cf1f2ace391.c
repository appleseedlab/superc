#include <stdio.h>
#include <unistd.h>

#define SIGTERM     15/* software termination signal from kill */
#define SIGUSR1     30/* user defined signal 1 */
#define SIGUSR2     31/* user defined signal 2 */

#ifndef ENABLE_DEBUG_INIT
void shutdown_signal(int sig)
{
  char *m;

  if (sig == SIGTERM) {
    m = "reboot";
  } else if (sig == SIGUSR2) {
    m = "poweroff";
  } else {
    m = "halt";
  }
  printf("Requesting system %s.", m);
}
#endif

void open_new_terminal()
{
  shutdown_signal(SIGUSR1); //ERROR
}

void run()
{
  open_new_terminal();
}

void run_actions()
{
  run();
}

int main(int argc, char** argv)
{
  run_actions();
  return 0;
}
