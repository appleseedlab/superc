#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_4;
void __static_initializer_default() {
__static_renaming("__num_0", "num");
__static_renaming("__x_2", "x");
__static_renaming("__x_3", "x");
__static_renaming("__main_5", "main");

__static_condition_renaming("__static_condition_default_4", "!(defined A)");
__static_condition_renaming("__static_condition_default_6", "(defined A)");
__static_condition_renaming("__static_condition_default_7", "!(defined A)");

};

int  __num_0= 1;// L1
int  * (__x_2);// L4
char  (__x_3) (int  __y_1) {

if (__static_condition_default_4) {

{
{



return  __y_1  ;// L7
}
}


}
}
int  (__main_5) () {

{
{



if (__static_condition_default_6) {
 __x_2  = &  __num_0  ; // L12
}
if (__static_condition_default_7) {
__static_type_error("type error") ; // L12
}
if (__static_condition_default_6) {
*  __x_2  ; // L13
}
if (__static_condition_default_7) {
__static_type_error("type error") ; // L13
}
return 0 ;// L15
}
}


}

