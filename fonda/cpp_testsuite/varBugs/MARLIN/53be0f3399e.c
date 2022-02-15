#include <util/delay.h> // http://download.savannah.gnu.org/releases/avr-libc/binary-releases/ for the util/delay library
#include <stdbool.h>
#include <stdio.h>

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

#define X 0
#define Y 1
#define Z 2

void enable_x()
{
  printf("%s", "enabling x axis");
}

void enable_y()
{
  printf("%s", "enabling y axis");
}

void enable_z()
{
  printf("%s", "enabling z axis");
}

#ifdef BABYSTEPPING

// MUST ONLY BE CALLED BY AN ISR,
// No other ISR should ever interrupt this!

void babystep(const uint8_t axis, const bool direction) {

#define BABYSTEP_AXIS(axis, AXIS, INVERT) { \
    enable_## axis(); \
    uint8_t old_pin = AXIS; \
    /* more functions here */ \
    _delay_us(1U); \
    /* more functions here */ \
  }

  switch(axis) {

  case X_AXIS:
    BABYSTEP_AXIS(x, X, false);
    break;

  case Y_AXIS:
    BABYSTEP_AXIS(y, Y, false);
    break;

  case Z_AXIS: {

            #ifndef DELTA

    BABYSTEP_AXIS(z, Z, false);

#else // DELTA

    enable_x();
    enable_y();
    enable_z();
    //setup new step
    //functions to move the x,y,z axis
    _delay_us(1U);
    //functions to move the x,y,z axis

            #endif

  } break;

  default: break;
  }
}

#endif //BABYSTEPPING

int main(void)
{
  #ifdef BABYSTEPPING
  babystep(0, false);
  #endif
  return 0;
}
