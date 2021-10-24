#include <stdbool.h>
#include <stdio.h>

#define PIN_EXISTS(PN) (defined(PN##_PIN) && PN##_PIN >= 0)
#define Z_STEP_PIN 1
#define HAS_Z_MAX (PIN_EXISTS(Z_MAX))
#define HAS_Z_MIN (PIN_EXISTS(Z_MIN))

#define WRITE {printf("making pin high or low");}

#ifdef Z_DUAL_STEPPER_DRIVERS

  #define Z_DUAL_ENDSTOPS

  #ifdef Z_DUAL_ENDSTOPS
    #define Z_MIN 1
    #define Z_MAX -1
  #endif

#endif // Z_DUAL_STEPPER_DRIVERS

#ifdef Z_DUAL_ENDSTOPS
locked_z_motor = false,
  locked_z2_motor = false;
#endif

#if HAS_Z_MIN
static bool old_z_min_endstop = false;
#endif

#if HAS_Z_MAX
static bool old_z_max_endstop = false;
#endif

#ifdef Z_DUAL_ENDSTOPS
static bool old_z2_min_endstop = false;
static bool old_z2_max_endstop = false;
#endif

void function()
{
  #ifdef Z_DUAL_STEPPER_DRIVERS
    #ifdef Z_DUAL_ENDSTOPS
  if (!old_z_max_endstop && !locked_z_motor) WRITE;
  if (!old_z2_max_endstop && !locked_z2_motor) WRITE;
    #endif
  #endif
}

void main(){}
