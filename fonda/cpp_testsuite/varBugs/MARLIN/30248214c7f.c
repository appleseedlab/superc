#include <stdio.h>

unsigned long millis = 123456789l;
#if defined (THERMAL_RUNAWAY_PROTECTION_PERIOD) && THERMAL_RUNAWAY_PROTECTION_PERIOD > 0
void thermal_runaway_protection(int *state, unsigned long *timer, float temperature, float target_temperature, int heater_id, int period_seconds, int hysteresis_degc)
{
  if (temperature >= (target_temperature - hysteresis_degc))
    {
      *timer = 123456782l;
    }
  else if ( (millis - *timer) > (period_seconds) * 1000)
    {
      printf("%s","Thermal Runaway, system stopped! Heater_ID: ");
      printf("%d",(int)heater_id);
      printf("%s","THERMAL RUNAWAY");
    }
}
#endif

int main(void){
  thermal_runaway_protection(0, 123456783, 145.0f, 200.0f, 1, 10, 1);
  return 0;
}
