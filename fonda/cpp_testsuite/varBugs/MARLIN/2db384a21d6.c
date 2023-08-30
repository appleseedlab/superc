#ifdef MESH_BED_LEVELING
#define MESH_NUM_X_POINTS 7
#define MESH_NUM_Y_POINTS 7
#endif
#define SERIAL_ECHOPAIR(name,value) do{ serial_echopair_P_l(name,value); }while(0)

void serial_echopair_P_l(const char *s_P, unsigned long v) { printf("%s", s_P); printf("%l", v);}

#ifndef DISABLE_M503

void Config_PrintSettings(unsigned short forReplay){

  #ifdef MESH_BED_LEVELING
  SERIAL_ECHOPAIR(" X", MESH_NUM_X_POINTS); // ERROR
  SERIAL_ECHOPAIR(" Y", MESH_NUM_Y_POINTS); // ERROR
  #endif

}

#endif

int main(int argc, char **argv)
{
  Config_PrintSettings(0);
  return 0;
}
