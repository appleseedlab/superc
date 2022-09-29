#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_2;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_15;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_14;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_13;
extern const bool __static_condition_default_8;
void __static_initializer_default() {
__static_renaming("__i2c_master_send_0", "i2c_master_send");
__static_renaming("__codec_hw_write_1", "codec_hw_write");
__static_renaming("__da7210_init_3", "da7210_init");
__static_renaming("__codec_hw_write_5", "codec_hw_write");
__static_renaming("__ak4642_init_7", "ak4642_init");
__static_renaming("__main_11", "main");
__static_renaming("__main_12", "main");

__static_condition_renaming("__static_condition_default_2", "!(defined CONFIG_SND_FSI_DA7210) && !(defined CONFIG_I2C) && (defined CONFIG_SND_SOC_DA7210) || (defined CONFIG_SND_FSI_DA7210) && !(defined CONFIG_I2C)");
__static_condition_renaming("__static_condition_default_4", "!(defined CONFIG_SND_FSI_DA7210) && (defined CONFIG_SND_SOC_DA7210) || (defined CONFIG_SND_FSI_DA7210)");
__static_condition_renaming("__static_condition_default_6", "!(defined CONFIG_SND_FSI_AK4642) && !(defined CONFIG_I2C) && (defined CONFIG_SND_SOC_AK4642) || (defined CONFIG_SND_FSI_AK4642) && !(defined CONFIG_I2C)");
__static_condition_renaming("__static_condition_default_8", "!(defined CONFIG_SND_FSI_AK4642) && (defined CONFIG_SND_SOC_AK4642) || (defined CONFIG_SND_FSI_AK4642)");
__static_condition_renaming("__static_condition_default_13", "!(defined CONFIG_SND_FSI_AK4642) && !(defined CONFIG_SND_SOC_AK4642)");
__static_condition_renaming("__static_condition_default_14", "!(defined CONFIG_SND_FSI_AK4642) && !(defined CONFIG_SND_FSI_DA7210) && (defined CONFIG_SND_SOC_DA7210) && !(defined CONFIG_SND_SOC_AK4642) || !(defined CONFIG_SND_FSI_AK4642) && (defined CONFIG_SND_FSI_DA7210) && !(defined CONFIG_SND_SOC_AK4642)");
__static_condition_renaming("__static_condition_default_15", "!(defined CONFIG_SND_FSI_AK4642) && (defined CONFIG_SND_SOC_AK4642) || (defined CONFIG_SND_FSI_AK4642)");
__static_condition_renaming("__static_condition_default_16", "!(defined CONFIG_SND_FSI_AK4642) && !(defined CONFIG_SND_FSI_DA7210) && (defined CONFIG_SND_SOC_DA7210) && (defined CONFIG_SND_SOC_AK4642) || !(defined CONFIG_SND_FSI_AK4642) && (defined CONFIG_SND_FSI_DA7210) && (defined CONFIG_SND_SOC_AK4642) || (defined CONFIG_SND_FSI_AK4642) && !(defined CONFIG_SND_FSI_DA7210) && (defined CONFIG_SND_SOC_DA7210) || (defined CONFIG_SND_FSI_AK4642) && (defined CONFIG_SND_FSI_DA7210)");

};

static int  __i2c_master_send_0= 0;// L10
static int  (__da7210_init_3) () {

if (__static_condition_default_4) {

{// L15
{



int  __codec_hw_write_1=  __i2c_master_send_0 ;// L16

if (__static_condition_default_2) {
__static_type_error("invalid declaration of codec_hw_write under this presence condition");
}

return 0 ;// L17
}
}// L18


}
}
static int  (__ak4642_init_7) () {

if (__static_condition_default_8) {

{// L23
{



int  __codec_hw_write_5=  __i2c_master_send_0 ;// L24

if (__static_condition_default_6) {
__static_type_error("invalid declaration of codec_hw_write under this presence condition");
}

return 0 ;// L25
}
}// L26


}
}
int  (__main_11) (int  __argc_9, char  * (* (__argv_10))) {

if (__static_condition_default_13) {

{// L30
{



if (__static_condition_default_14) {
 __da7210_init_3 ( ) ; // L32
}
return 0 ;// L37
}
}// L38


}
}
int  (__main_12) (int  __argc_9, char  * (* (__argv_10))) {

if (__static_condition_default_15) {

{// L30
{



if (__static_condition_default_16) {
 __da7210_init_3 ( ) ; // L32
}
 __ak4642_init_7 ( ) ; // L35
return 0 ;// L37
}
}// L38


}
}

