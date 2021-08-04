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
__static_renaming("__x_1", "x");
__static_renaming("__a_2", "a");
__static_renaming("__main_3", "main");

__static_condition_renaming("__static_condition_default_4", "(defined A)");
__static_condition_renaming("__static_condition_default_5", "!(defined A)");

};

int  __x_0;// L1:L5
int  __x_1 ();// L1:L5
int  __main_3 () {

{



char  __a_2;// L9

if (__static_condition_default_4) {
 __a_2  = ( char   )  __x_1 ( ) ; // L10
}
if (__static_condition_default_5) {
__static_type_error("type error") ; // L10
}
return  __a_2  ;// L11
}



}

