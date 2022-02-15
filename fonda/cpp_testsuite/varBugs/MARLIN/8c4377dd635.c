#ifndef MARLIN_H
const char echomagic[] ="echo:";
#define SERIAL_ECHO_START (serialprint(echomagic))

void serialprint(const char *str){
  printf("%s\n", str);
}
#endif

void manage_heater(){
  float pid_output = 1;
  int e = 0;
  #ifdef PIDTEMP

  #ifdef PID_DEBUG
  SERIAL_ECHO_START(" PIDDEBUG "); // ERROR
  #endif
  #else
  pid_output = 0;
  #endif

}

int main(int argc, char** argv)
{
  manage_heater();
  return 0;
}
