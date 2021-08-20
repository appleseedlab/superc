#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_3;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__y_1", "y");
__static_renaming("__main_2", "main");

__static_condition_renaming("__static_condition_default_3", "(defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_4", "!(defined CONFIG_A)");

};

int  __main_2 () {

{
{



int  __x_0;// L2

int  __y_1= 210;// L3

if (__static_condition_default_3) {
 __x_0  = 42 ; // L6
}
if (__static_condition_default_4) {
 __x_0  = 13 ; // L8
}
return  __x_0  ;// L11
}
}


}

