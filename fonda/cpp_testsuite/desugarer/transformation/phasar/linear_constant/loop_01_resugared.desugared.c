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
__static_renaming("__i_1", "i");
__static_renaming("__main_2", "main");

__static_condition_renaming("__static_condition_default_3", "(defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_4", "!(defined CONFIG_A)");

};

int  __main_2 () {

{



int  __x_0= 0;// L2

if (__static_condition_default_3) {
{ int  __i_1= 0;// L5
 for ( ;  __i_1  < 10 ; ++  __i_1  ) // L5

{



++  __x_0  ; // L6
}
}
}
if (__static_condition_default_4) {
return  __x_0  ;// L10
}
if (__static_condition_default_3) {
return  __x_0  ;// L10
}
}



}

