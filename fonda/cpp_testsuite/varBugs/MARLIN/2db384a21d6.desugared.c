#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_11;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_12;
void __static_initializer_default() {
__static_renaming("__serial_echopair_P_l_2", "serial_echopair_P_l");
__static_renaming("__Config_PrintSettings_4", "Config_PrintSettings");
__static_renaming("__main_9", "main");
__static_renaming("__main_10", "main");

__static_condition_renaming("__static_condition_default_5", "!(defined MESH_BED_LEVELING) && !(defined DISABLE_M503)");
__static_condition_renaming("__static_condition_default_6", "(defined MESH_BED_LEVELING) && !(defined DISABLE_M503)");
__static_condition_renaming("__static_condition_default_11", "(defined DISABLE_M503)");
__static_condition_renaming("__static_condition_default_12", "!(defined DISABLE_M503)");

};

void  (__serial_echopair_P_l_2) (const char  * (__s_P_0), unsigned long  __v_1) {

{// L7
{



__static_type_error("type error : no valid expression"); // L7
__static_type_error("type error : no valid expression"); // L7
}
}// L7


}
void  (__Config_PrintSettings_4) (unsigned short  __forReplay_3) {

{
if (__static_condition_default_5) {

{// L11
{



}
}// L18


}

if (__static_condition_default_6) {

{// L11
{



do
{

{// L5
{



 __serial_echopair_P_l_2  (" X",7) ; // L5
}
}// L5
}
while( 0 );// L5:L14
do
{

{// L5
{



 __serial_echopair_P_l_2  (" Y",7) ; // L5
}
}// L5
}
while( 0 );// L5:L15
}
}// L18


}

}}
int  (__main_9) (int  __argc_7, char  * (* (__argv_8))) {

if (__static_condition_default_11) {

{// L23
{



__static_type_error("type error") ; // L24
return 0 ;// L25
}
}// L26


}
}
int  (__main_10) (int  __argc_7, char  * (* (__argv_8))) {

if (__static_condition_default_12) {

{// L23
{



 __Config_PrintSettings_4  (0) ; // L24
return 0 ;// L25
}
}// L26


}
}

