#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_0;
void __static_initializer_default() {
__static_renaming("__x_1", "x");
__static_renaming("__a_2", "a");
__static_renaming("__main_3", "main");

__static_condition_renaming("__static_condition_default_0", "(defined A)");
__static_condition_renaming("__static_condition_default_4", "!(defined A)");

};

int  __main_3 () {

{
{



if (__static_condition_default_0) {
__static_type_error("invalid declaration of x under this presence condition");
}

int  __x_1= 1;// L3:L7

if (1) {
__static_type_error("invalid declaration of z under this presence condition");
}

int  (__a_2[5]);// L10

if (__static_condition_default_4) {
 __a_2  [  __x_1  ] ; // L11
}
if (__static_condition_default_0) {
__static_type_error("type error") ; // L11
}
__static_type_error("type error : no valid expression"); // L12
return 0 ;// L13
}
}



}

