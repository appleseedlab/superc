#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_1", "x");
__static_renaming("__x_2", "x");
__static_renaming("__main_3", "main");

__static_condition_renaming("__static_condition_default_4", "(defined A) && !(defined B)");
__static_condition_renaming("__static_condition_default_5", "!(defined A) && !(defined B)");
__static_condition_renaming("__static_condition_default_6", "(defined B)");

};

 int  __x_0;
char  __x_1;
 int  __main_3 () {

{



float  __x_2;

if (__static_condition_default_4) {
 __x_0  ++ ;
}
if (__static_condition_default_5) {
 __x_1  ++ ;
}
if (__static_condition_default_6) {
 __x_2  ++ ;
}
}



}

