#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_1", "x");
__static_renaming("__y_2", "y");
__static_renaming("__main_3", "main");

__static_condition_renaming("__static_condition_default_4", "(defined A)");
__static_condition_renaming("__static_condition_default_5", "!(defined A)");

};

int  __main_3 () {

{
{



int  __x_0;// L4

char  __x_1;// L6

if (__static_condition_default_4) {
 __x_0  = 2 ; // L8
}
if (__static_condition_default_5) {
 __x_1  = 2 ; // L8
}
int  __y_2;// L9

if (  __y_2  )// L10
{
if (__static_condition_default_4) {
 __x_0  ++ ; // L10
}
if (__static_condition_default_5) {
 __x_1  ++ ; // L10
}
}
return 0 ;// L11
}
}



}

