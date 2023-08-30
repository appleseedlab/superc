#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_10;
extern const bool __static_condition_default_3;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__lcd_setstatus_2", "lcd_setstatus");
__static_renaming("__lcd_setstatus_5", "lcd_setstatus");
__static_renaming("__time_7", "time");
__static_renaming("__getCode_8", "getCode");
__static_renaming("__main_13", "main");

__static_condition_renaming("__static_condition_default_3", "(defined ULTRA_LCD)");
__static_condition_renaming("__static_condition_default_6", "!(defined ULTRA_LCD)");
__static_condition_renaming("__static_condition_default_9", "!(defined SDSUPPORT)");
__static_condition_renaming("__static_condition_default_10", "(defined SDSUPPORT)");

};

void  (__lcd_setstatus_2) (const char  * (__message_0), const _Bool  __persist_1) {

if (__static_condition_default_3) {

{// L4
{



}
}// L4


}
}
void  (__lcd_setstatus_5) (const char  * (__message_4)) {

if (__static_condition_default_6) {

{// L7
{



}
}// L7


}
}
;;void  (__getCode_8) () {

{
if (__static_condition_default_9) {

{// L12
{



}
}// L17


}

if (__static_condition_default_10) {

{// L12
{



char  __time_7[30]= "time_here";// L14

__static_type_error("type error : no valid expression"); // L15
}
}// L17


}

}}
int  (__main_13) (int  __argc_11, char  * (* (__argv_12))) {

{// L20
{



 __getCode_8 ( ) ; // L21
return 0 ;// L22
}
}// L23


}

