#include<stdbool.h>

#ifdef ULTRA_LCD
void lcd_setstatus(const char* message, const bool persist) {};
// more functions
#else
void lcd_setstatus(const char* message) {};
// more functions
#endif

void getCode()
{
  #ifdef SDSUPPORT
  char time[30] = "time_here";
  lcd_setstatus(time, true); // ERROR
  #endif
}

int main(int argc, char **argv)
{
  getCode();
  return 0;
}
