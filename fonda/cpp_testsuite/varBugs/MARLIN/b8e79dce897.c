#include <stdio.h>

#define MSG_NOZZLE       "Nozzle"
#define HEATER_0_MAXTEMP 275

#ifdef ULTRA_LCD
#define MENU_ITEM(type, label, args...) do { \
  printf("menu item");\
  } while(0)

#define MENU_MULTIPLIER_ITEM(type, label, args...) do { \
  printf("menu multiplier item");\
  } while(0)

#ifdef ENCODER_RATE_MULTIPLIER
#define MENU_MULTIPLIER_ITEM_EDIT(type, label, args...) MENU_MULTIPLIER_ITEM(setting_edit_ ## type, label, ## args )
#else
#define MENU_ITEM_EDIT(type, label, args...) MENU_ITEM(setting_edit_ ## type, label, ## args )
#endif

#endif

static void lcd_tune_menu()
{
  #ifdef ULTRA_LCD
  #if TEMP_SENSOR_0 != 0
  MENU_MULTIPLIER_ITEM_EDIT(3, MSG_NOZZLE, 0, 0, HEATER_0_MAXTEMP - 15);
  #endif
  #endif
}
int main(void)
{
  lcd_tune_menu();
  return 0;
}
