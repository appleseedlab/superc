#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__serial_echopair_P_l_2", "serial_echopair_P_l");
__static_renaming("__Config_PrintSettings_4", "Config_PrintSettings");
__static_renaming("__main_9", "main");

__static_condition_renaming("__static_condition_default_5", "!(defined MESH_BED_LEVELING)");
__static_condition_renaming("__static_condition_default_6", "(defined MESH_BED_LEVELING)");

};

void  (__serial_echopair_P_l_2) (const char  * (__s_P_0), unsigned long  __v_1) {

{
{



__static_type_error("type error : no valid expression"); // L7
__static_type_error("type error : no valid expression"); // L7
}
}


}
void  (__Config_PrintSettings_4) (unsigned short  __forReplay_3) {

{
if (__static_condition_default_5) {

{
{



}
}


}

if (__static_condition_default_6) {

{
{



do
{

{
{



 __serial_echopair_P_l_2  (" X",7) ; // L5
}
}
}
while( 0 );// L5:L14
do
{

{
{



 __serial_echopair_P_l_2  (" Y",7) ; // L5
}
}
}
while( 0 );// L5:L15
}
}


}

}}
int  (__main_9) (int  __argc_7, char  * (* (__argv_8))) {

{
{



 __Config_PrintSettings_4  (0) ; // L24
return 0 ;// L25
}
}


}

