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
__static_renaming("__y_1", "y");
__static_renaming("__y_2", "y");
__static_renaming("__main_3", "main");

__static_condition_renaming("__static_condition_default_4", "(defined A)");
__static_condition_renaming("__static_condition_default_5", "!(defined A)");

};

int  __main_3 () {

{



int  __x_0;// L4

int  __y_1;// L6

int  __y_2;// L6

if (__static_condition_default_4) {
 __y_2  = &  __x_0  ; // L7
}
if (__static_condition_default_5) {
__static_type_error("type error") ; // L7
}
return 0 ;// L8
}



}

