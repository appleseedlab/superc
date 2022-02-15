#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_4;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__foo_2", "foo");
__static_renaming("__foo_3", "foo");
__static_renaming("__main_6", "main");

__static_condition_renaming("__static_condition_default_4", "!(defined A)");
__static_condition_renaming("__static_condition_default_5", "(defined A)");

};
const char  __x_0= 'c';// L2


void  (__foo_2) (char  __c_1[4]) {

if (__static_condition_default_4) {

{
{



return  ;// L7
}
}


}
}
void  (__foo_3) (char  __c_1[4]) {

if (__static_condition_default_5) {

{
{



return  ;// L7
}
}


}
}
int  (__main_6) () {

{
{



if (__static_condition_default_5) {
 __foo_3  (( char  [] ) { 'a' ,  'b' ,   __x_0  ,  'd' }) ; // L12
}
if (__static_condition_default_4) {
__static_type_error("type error") ; // L12
}
return 0 ;// L13
}
}


}

