#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
extern const bool __static_condition_default_7;
void __static_initializer_default() {
__static_renaming("__serial_echopair_P_l_2", "serial_echopair_P_l");
__static_renaming("__main_5", "main");

__static_condition_renaming("__static_condition_default_6", "(defined DISABLE_M503)");
__static_condition_renaming("__static_condition_default_7", "!(defined DISABLE_M503)");

if (__static_condition_default_7)
{
__static_parse_error("Unable to parse");
}
};

void  (__serial_echopair_P_l_2) (const char  * (__s_P_0), unsigned long  __v_1) {

{
{



__static_type_error("type error : no valid expression"); // L7
__static_type_error("type error : no valid expression"); // L7
}
}


}
int  (__main_5) (int  __argc_3, char  * (* (__argv_4))) {

if (__static_condition_default_6) {

{
{



__static_type_error("type error : no valid expression"); // L24
return 0 ;// L25
}
}


}
}

