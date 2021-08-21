#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
extern const bool __static_condition_default_3;
extern const bool __static_condition_default_4;
void __static_initializer_default() {
__static_renaming("__x_1", "x");
__static_renaming("__x_2", "x");
__static_renaming("__main_5", "main");

__static_condition_renaming("__static_condition_default_3", "(defined A)");
__static_condition_renaming("__static_condition_default_4", "!(defined A)");
__static_condition_renaming("__static_condition_default_6", "!(defined A)");

};

int  (__x_1) () {

{
if (__static_condition_default_3) {

{
{



return 1 ;// L4
}
}


}

}}
char  (__x_2) (int  __y_0) {

{
if (__static_condition_default_4) {

{
{



return  __y_0  ;// L8
}
}


}

}}
int  (__main_5) () {

{
{



if (__static_condition_default_3) {
 __x_1 ( ) ; // L16
}
if (__static_condition_default_6) {
__static_type_error("type error") ; // L16
}
if (__static_condition_default_6) {
 __x_2  (2) ; // L17
}
if (__static_condition_default_3) {
__static_type_error("type error") ; // L17
}
}
}


}

