#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_10;
extern const bool __static_condition_default_13;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_1;
extern const bool __static_condition_default_2;
extern const bool __static_condition_default_12;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_11;
void __static_initializer_default() {
__static_renaming("__i2c_dw_init_0", "i2c_dw_init");
__static_renaming("__i2c_dw_init_3", "i2c_dw_init");
__static_renaming("__main_5", "main");
__static_renaming("__main_6", "main");

__static_condition_renaming("__static_condition_default_1", "(defined CONFIG_I2C_DESIGNWARE_PLATFORM)");
__static_condition_renaming("__static_condition_default_2", "(defined CONFIG_I2C_DESIGNWARE_PLATFORM) && (defined CONFIG_I2C_DESIGNWARE_PCI)");
__static_condition_renaming("__static_condition_default_4", "!(defined CONFIG_I2C_DESIGNWARE_PLATFORM) && (defined CONFIG_I2C_DESIGNWARE_PCI)");
__static_condition_renaming("__static_condition_default_7", "!(defined CONFIG_I2C_DESIGNWARE_PCI)");
__static_condition_renaming("__static_condition_default_8", "(defined CONFIG_I2C_DESIGNWARE_PLATFORM) && !(defined CONFIG_I2C_DESIGNWARE_PCI)");
__static_condition_renaming("__static_condition_default_9", "!(defined CONFIG_I2C_DESIGNWARE_PLATFORM) && !(defined CONFIG_I2C_DESIGNWARE_PCI)");
__static_condition_renaming("__static_condition_default_10", "(defined CONFIG_I2C_DESIGNWARE_PLATFORM) && !(defined CONFIG_I2C_DESIGNWARE_PCI)");
__static_condition_renaming("__static_condition_default_11", "(defined CONFIG_I2C_DESIGNWARE_PCI)");
__static_condition_renaming("__static_condition_default_12", "!(defined CONFIG_I2C_DESIGNWARE_PLATFORM) && (defined CONFIG_I2C_DESIGNWARE_PCI)");
__static_condition_renaming("__static_condition_default_13", "(defined CONFIG_I2C_DESIGNWARE_PLATFORM) && (defined CONFIG_I2C_DESIGNWARE_PCI)");

};

int  (__i2c_dw_init_0) () {

if (__static_condition_default_1) {

{// L3
{



return 0 ;// L4
}
}// L5


}
}
int  (__i2c_dw_init_3) () {

if (__static_condition_default_4) {

{// L10
{



return 0 ;// L11
}
}// L12


}
}
int  (__main_5) (void  ) {

if (__static_condition_default_7) {

{// L17
{



if (__static_condition_default_8) {
 __i2c_dw_init_0 ( ) ; // L19
}
if (__static_condition_default_9) {
return 0 ;// L21
}
if (__static_condition_default_10) {
return 0 ;// L21
}
}
}// L22


}
}
int  (__main_6) (void  ) {

if (__static_condition_default_11) {

{// L17
{



if (__static_condition_default_12) {
 __i2c_dw_init_3 ( ) ; // L19
}
if (__static_condition_default_13) {
__static_type_error("type error") ; // L19
}
return 0 ;// L21
}
}// L22


}
}

