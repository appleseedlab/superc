#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_3;
extern const bool __static_condition_default_4;
void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__x_1", "x");
__static_renaming("__y_2", "y");

__static_condition_renaming("__static_condition_default_3", "(defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_4", "!(defined CONFIG_A)");

};

int  __main_0 () {
{
int  __x_1;
int  __y_2= 210;

{
if (__static_condition_default_3) {
 __x_1  = 42 ;

}

if (__static_condition_default_4) {
 __x_1  = 13 ;

}

}return  __x_1  ;

}


}

