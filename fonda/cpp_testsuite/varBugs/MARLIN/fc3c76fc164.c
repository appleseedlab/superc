#include <stdbool.h>

#if HAS_HEATER_THERMAL_PROTECTION || HAS_BED_THERMAL_PROTECTION
enum TRState { TRInactive, TRFirstHeating, TRStable };
static bool thermal_runaway = false;
  #if HAS_HEATER_THERMAL_PROTECTION
enum TRState thermal_runaway_state_machine[4] = { TRInactive, TRInactive, TRInactive, TRInactive };
static unsigned long thermal_runaway_timer[4]; // = {0,0,0,0};
  #endif
  #if HAS_BED_THERMAL_PROTECTION
static TRState thermal_runaway_bed_state_machine = { TRInactive, TRInactive, TRInactive, TRInactive };
static unsigned long thermal_runaway_bed_timer;
  #endif
#endif

int main(void)
{
  return 0;
}
