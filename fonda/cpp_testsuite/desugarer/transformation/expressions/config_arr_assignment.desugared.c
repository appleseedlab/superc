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
__static_renaming("__arr_1", "arr");
__static_renaming("__main_2", "main");

__static_condition_renaming("__static_condition_default_3", "A");
__static_condition_renaming("__static_condition_default_4", "!A");

};

int  __main_2 (void  ) {

{



int  __x_0= 2;// L2

int  (__arr_1[5]);// L3

if (__static_condition_default_3) {
 __arr_1  [ 1 ] = 7 ; // L6
}
if (__static_condition_default_4) {
 __arr_1  [  __x_0  ] = 3 ; // L8
}
return 0 ;// L11
}



}

