#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
extern const bool __static_condition_default_3;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__x_1", "x");
__static_renaming("__x_2", "x");
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_3", "!(defined A)");
__static_condition_renaming("__static_condition_default_5", "!(defined A)");
__static_condition_renaming("__static_condition_default_6", "(defined A)");

};

int  __x_1[5];// L2
char  (__x_2) (int  __y_0) {

if (__static_condition_default_3) {

{
{



return  __y_0  ;// L5
}
}


}
}
int  (__main_4) () {

{
{



if (__static_condition_default_5) {
 __x_2  (2) ; // L10
}
if (__static_condition_default_6) {
__static_type_error("type error") ; // L10
}
return 0 ;// L11
}
}


}

