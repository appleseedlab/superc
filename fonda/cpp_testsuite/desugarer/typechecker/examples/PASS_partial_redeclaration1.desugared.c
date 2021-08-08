#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_2;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_3", "x");
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_2", "(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_5", "!(defined B)");
__static_condition_renaming("__static_condition_default_6", "(defined B)");

};

int  __main_4 () {

{
{



int  __x_0;// L4

if (__static_condition_default_2) {
__static_type_error("redeclaration of local symbol: x");
}

char  __x_3;// L7

if (__static_condition_default_5) {
return 0 ;// L9
}
if (__static_condition_default_6) {
return 0 ;// L9
}
}
}



}

