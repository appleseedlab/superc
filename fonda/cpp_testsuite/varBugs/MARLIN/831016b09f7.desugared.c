#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_3;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__lcd_setstatus_2", "lcd_setstatus");
__static_renaming("__lcd_setstatus_5", "lcd_setstatus");
__static_renaming("__getCode_7", "getCode");
__static_renaming("__main_10", "main");

__static_condition_renaming("__static_condition_default_3", "(defined ULTRA_LCD)");
__static_condition_renaming("__static_condition_default_6", "!(defined ULTRA_LCD)");

};

void  (__lcd_setstatus_2) (const char  * (__message_0), const _Bool  __persist_1) {

if (__static_condition_default_3) {

{
{



}
}


}
}
void  (__lcd_setstatus_5) (const char  * (__message_4)) {

if (__static_condition_default_6) {

{
{



}
}


}
}
;;void  (__getCode_7) () {

{
{



}
}


}
int  (__main_10) (int  __argc_8, char  * (* (__argv_9))) {

{
{



 __getCode_7 ( ) ; // L21
return 0 ;// L22
}
}


}

