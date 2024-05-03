#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_8;
extern const bool __static_condition_default_14;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_13;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__max8660_pdata_from_dt_2", "max8660_pdata_from_dt");
__static_renaming("__max8660_pdata_from_dt_3", "max8660_pdata_from_dt");
__static_renaming("__pdata_of_6", "pdata_of");
__static_renaming("__max8660_probe_7", "max8660_probe");
__static_renaming("__main_11", "main");
__static_renaming("__main_12", "main");

__static_condition_renaming("__static_condition_default_4", "(defined CONFIG_REGULATOR_MAX8660) && (defined CONFIG_OF)");
__static_condition_renaming("__static_condition_default_5", "(defined CONFIG_REGULATOR_MAX8660) && !(defined CONFIG_OF)");
__static_condition_renaming("__static_condition_default_8", "(defined CONFIG_REGULATOR_MAX8660)");
__static_condition_renaming("__static_condition_default_9", "(defined CONFIG_REGULATOR_MAX8660) && (defined CONFIG_OF)");
__static_condition_renaming("__static_condition_default_10", "(defined CONFIG_REGULATOR_MAX8660) && !(defined CONFIG_OF)");
__static_condition_renaming("__static_condition_default_13", "!(defined CONFIG_REGULATOR_MAX8660)");
__static_condition_renaming("__static_condition_default_14", "(defined CONFIG_REGULATOR_MAX8660)");

};

int  (__max8660_pdata_from_dt_2) (int  * (__pdata_0)) {

{
if (__static_condition_default_4) {

{// L4
{



*  __pdata_0  ++ ; // L5
return 0 ;// L6
}
}// L7


}

}}
int  (__max8660_pdata_from_dt_3) (int  * (* (__pdata_1))) {

{
if (__static_condition_default_5) {

{// L10
{



return 0 ;// L11
}
}// L12


}

}}
int  (__max8660_probe_7) () {

if (__static_condition_default_8) {

{// L16
{



int  __pdata_of_6= 0;// L17

if (__static_condition_default_9) {
 __max8660_pdata_from_dt_2  (&  __pdata_of_6 ) ; // L18
}
if (__static_condition_default_10) {
__static_type_error("type error") ; // L18
}
return 0 ;// L19
}
}// L20


}
}
int  (__main_11) () {

if (__static_condition_default_13) {

{// L23
{



return 0 ;// L27
}
}// L28


}
}
int  (__main_12) () {

if (__static_condition_default_14) {

{// L23
{



 __max8660_probe_7 ( ) ; // L25
return 0 ;// L27
}
}// L28


}
}

