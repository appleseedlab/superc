#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_11;
extern const bool __static_condition_default_3;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_1;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__omap2_set_globals_242x_0", "omap2_set_globals_242x");
__static_renaming("__omap_h4_map_io_2", "omap_h4_map_io");
__static_renaming("__main_8", "main");
__static_renaming("__main_9", "main");

__static_condition_renaming("__static_condition_default_1", "(defined CONFIG_ARCH_OMAP2420)");
__static_condition_renaming("__static_condition_default_3", "(defined CONFIG_MACH_OMAP_H4)");
__static_condition_renaming("__static_condition_default_4", "(defined CONFIG_ARCH_OMAP2420) && (defined CONFIG_MACH_OMAP_H4)");
__static_condition_renaming("__static_condition_default_5", "!(defined CONFIG_ARCH_OMAP2420) && (defined CONFIG_MACH_OMAP_H4)");
__static_condition_renaming("__static_condition_default_10", "!(defined CONFIG_MACH_OMAP_H4)");
__static_condition_renaming("__static_condition_default_11", "(defined CONFIG_MACH_OMAP_H4)");

};

void  (__omap2_set_globals_242x_0) (void  ) {

if (__static_condition_default_1) {

{// L3
{



return  ;// L4
}
}// L5


}
}
static void  (__omap_h4_map_io_2) (void  ) {

if (__static_condition_default_3) {

{// L10
{



if (__static_condition_default_4) {
 __omap2_set_globals_242x_0 ( ) ; // L11
}
if (__static_condition_default_5) {
__static_type_error("type error") ; // L11
}
}
}// L12


}
}
int  (__main_8) (int  __argc_6, char  * (* (__argv_7))) {

{
if (__static_condition_default_10) {

{// L16
{



}
}// L20


}

}}
int  (__main_9) (int  __argc_6, char  * (* (__argv_7))) {

{
if (__static_condition_default_11) {

{// L16
{



 __omap_h4_map_io_2 ( ) ; // L18
}
}// L20


}

}}

