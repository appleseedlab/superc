#include <string.h>

static char *strchr_pointer = "eiffel~1.gco*57";

void process_commands()
{
  char *starpos = NULL;
  #ifdef SDSUPPORT
  starpos = (strchr(strchr_pointer + 4,'*'));
  if(starpos!=NULL)
    *(starpos-1)='\0'; //ERROR
  assert(strcmp(strchr_pointer,"eiffel~1.gco"));
  #endif
}

int main(int argc, char** argv)
{
  process_commands();
  return 0;
}
