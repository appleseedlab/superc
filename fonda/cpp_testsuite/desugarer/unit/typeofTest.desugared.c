#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_1", "x");
__static_renaming("__y_2", "y");
__static_renaming("__y_3", "y");
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_5", "(defined A)");
__static_condition_renaming("__static_condition_default_6", "!(defined A)");

};

int  __main_4 () {

{



typeof ( int  * )  __x_0;// L3:L9

typeof ( char  * )  __x_1;// L3:L9

typeof (  __x_0  )  __y_2;// L10

typeof (  __x_1  )  __y_3;// L10

if (__static_condition_default_5) {
 __y_2  = 0 ; // L11
}
if (__static_condition_default_6) {
 __y_3  = 0 ; // L11
}
return 0 ;// L12
}



}

