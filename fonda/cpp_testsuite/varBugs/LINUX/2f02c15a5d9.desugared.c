#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_11;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_1;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_3;
void __static_initializer_default() {
__static_renaming("__ssb_extif_gpio_in_0", "ssb_extif_gpio_in");
__static_renaming("__bcm47xx_gpio_get_value_2", "bcm47xx_gpio_get_value");
__static_renaming("__main_8", "main");
__static_renaming("__main_9", "main");

__static_condition_renaming("__static_condition_default_1", "(defined CONFIG_SSB_DRIVER_EXTIF)");
__static_condition_renaming("__static_condition_default_3", "(defined CONFIG_BCM47XX)");
__static_condition_renaming("__static_condition_default_4", "(defined CONFIG_SSB_DRIVER_EXTIF) && (defined CONFIG_BCM47XX)");
__static_condition_renaming("__static_condition_default_5", "!(defined CONFIG_SSB_DRIVER_EXTIF) && (defined CONFIG_BCM47XX)");
__static_condition_renaming("__static_condition_default_10", "!(defined CONFIG_BCM47XX)");
__static_condition_renaming("__static_condition_default_11", "(defined CONFIG_BCM47XX)");

};

int  (__ssb_extif_gpio_in_0) () {

if (__static_condition_default_1) {

{// L3
{



return 0 ;// L4
}
}// L5


}
}
int  (__bcm47xx_gpio_get_value_2) () {

if (__static_condition_default_3) {

{// L10
{



if (__static_condition_default_4) {
return  __ssb_extif_gpio_in_0 ( ) ;// L11
}
if (__static_condition_default_5) {
__static_type_error("invalid type found in return expression");
}
}
}// L12


}
}
int  (__main_8) (int  __argc_6, char  * (* (__argv_7))) {

if (__static_condition_default_10) {

{// L16
{



return 0 ;// L20
}
}// L21


}
}
int  (__main_9) (int  __argc_6, char  * (* (__argv_7))) {

if (__static_condition_default_11) {

{// L16
{



 __bcm47xx_gpio_get_value_2 ( ) ; // L18
return 0 ;// L20
}
}// L21


}
}

