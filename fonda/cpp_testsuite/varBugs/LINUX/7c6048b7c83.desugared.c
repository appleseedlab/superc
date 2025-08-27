#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_12;
extern const bool __static_condition_default_14;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_13;
extern const bool __static_condition_default_1;
extern const bool __static_condition_default_3;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_11;
void __static_initializer_default() {
__static_renaming("__backlight_device_unregister_0", "backlight_device_unregister");
__static_renaming("__acpi_video_bus_put_one_device_2", "acpi_video_bus_put_one_device");
__static_renaming("__main_8", "main");
__static_renaming("__main_9", "main");

__static_condition_renaming("__static_condition_default_1", "(defined CONFIG_BACKLIGHT_CLASS_DEVICE)");
__static_condition_renaming("__static_condition_default_3", "!(defined CONFIG_ACPI) && (defined CONFIG_ACPI_VIDEO) || (defined CONFIG_ACPI) && !(defined CONFIG_STUB_POULSBO) && (defined CONFIG_ACPI_VIDEO) || (defined CONFIG_ACPI) && (defined CONFIG_STUB_POULSBO)");
__static_condition_renaming("__static_condition_default_4", "!(defined CONFIG_ACPI) && (defined CONFIG_BACKLIGHT_CLASS_DEVICE) && (defined CONFIG_ACPI_VIDEO) || (defined CONFIG_ACPI) && !(defined CONFIG_STUB_POULSBO) && (defined CONFIG_BACKLIGHT_CLASS_DEVICE) && (defined CONFIG_ACPI_VIDEO) || (defined CONFIG_ACPI) && (defined CONFIG_STUB_POULSBO) && (defined CONFIG_BACKLIGHT_CLASS_DEVICE)");
__static_condition_renaming("__static_condition_default_5", "!(defined CONFIG_ACPI) && !(defined CONFIG_BACKLIGHT_CLASS_DEVICE) && (defined CONFIG_ACPI_VIDEO) || (defined CONFIG_ACPI) && !(defined CONFIG_STUB_POULSBO) && !(defined CONFIG_BACKLIGHT_CLASS_DEVICE) && (defined CONFIG_ACPI_VIDEO) || (defined CONFIG_ACPI) && (defined CONFIG_STUB_POULSBO) && !(defined CONFIG_BACKLIGHT_CLASS_DEVICE)");
__static_condition_renaming("__static_condition_default_10", "!(defined CONFIG_ACPI) && !(defined CONFIG_ACPI_VIDEO) || (defined CONFIG_ACPI) && !(defined CONFIG_STUB_POULSBO) && !(defined CONFIG_ACPI_VIDEO)");
__static_condition_renaming("__static_condition_default_11", "!(defined CONFIG_ACPI) && (defined CONFIG_ACPI_VIDEO) || (defined CONFIG_ACPI) && !(defined CONFIG_STUB_POULSBO) && (defined CONFIG_ACPI_VIDEO) || (defined CONFIG_ACPI) && (defined CONFIG_STUB_POULSBO)");
__static_condition_renaming("__static_condition_default_12", "(defined CONFIG_ACPI) && (defined CONFIG_STUB_POULSBO)");
__static_condition_renaming("__static_condition_default_13", "!(defined CONFIG_ACPI) && (defined CONFIG_ACPI_VIDEO) || (defined CONFIG_ACPI) && !(defined CONFIG_STUB_POULSBO) && (defined CONFIG_ACPI_VIDEO)");
__static_condition_renaming("__static_condition_default_14", "(defined CONFIG_ACPI) && (defined CONFIG_STUB_POULSBO)");

};

void  (__backlight_device_unregister_0) () {

if (__static_condition_default_1) {

{// L7
{



return  ;// L8
}
}// L9


}
}
static int  (__acpi_video_bus_put_one_device_2) () {

if (__static_condition_default_3) {

{// L14
{



if (__static_condition_default_4) {
 __backlight_device_unregister_0 ( ) ; // L15
}
if (__static_condition_default_5) {
__static_type_error("type error") ; // L15
}
return 0 ;// L16
}
}// L17


}
}
int  (__main_8) (int  __argc_6, char  * (* (__argv_7))) {

if (__static_condition_default_10) {

{// L21
{



return 0 ;// L25
}
}// L26


}
}
int  (__main_9) (int  __argc_6, char  * (* (__argv_7))) {

if (__static_condition_default_11) {

{// L21
{



if (__static_condition_default_12) {
 __acpi_video_bus_put_one_device_2 ( ) ; // L23
}
if (__static_condition_default_13) {
return 0 ;// L25
}
if (__static_condition_default_14) {
return 0 ;// L25
}
}
}// L26


}
}

