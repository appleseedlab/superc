#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEMP_RESIDENCY_TIME 30

void process_commands(){
  unsigned long millis = 123456789l;
    #ifdef TEMP_RESIDENCY_TIME
  long residencyStart;
  residencyStart = -1;
  /* continue to loop until we have reached the target temp   
     _and_ until TEMP_RESIDENCY_TIME hasn't passed since we reached it */
  while((residencyStart == -1) ||
        (residencyStart > -1 && (millis - residencyStart) < TEMP_RESIDENCY_TIME*1000) ) { // ERROR if TEMP_RESIDENCY_TIME > 32 => int overflow
          #else
    printf("%s", "Cooling down or heating hotend");
#endif //TEMP_RESIDENCY_TIME

  }
}

int main(int argc, char **argv)
{
    #ifdef TEMP_RESIDENCY_TIME
  process_commands();
    #endif
  return 0;
}
