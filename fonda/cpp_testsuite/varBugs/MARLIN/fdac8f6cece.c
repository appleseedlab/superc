#ifdef ENABLE_AUTO_BED_LEVELING
#define Z_PROBE_OFFSET_FROM_EXTRUDER 7
#endif

float zprobe_zoffset;

void Config_ResetDefault()
{
  zprobe_zoffset = -Z_PROBE_OFFSET_FROM_EXTRUDER; // ERROR
}

int main(int argc, char **argv)
{

  Config_ResetDefault();
  return 0;
}
