#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_3;
void __static_initializer_default() {
__static_renaming("__z_0", "z");
__static_renaming("__main_1", "main");
__static_renaming("__main_2", "main");

__static_condition_renaming("__static_condition_default_3", "!(defined XX) && !(defined YY) && !(defined ZZ) || !(defined XX) && (defined YY) || (defined XX)");
__static_condition_renaming("__static_condition_default_4", "!(defined XX) && !(defined YY) && (defined ZZ)");

};

int  __z_0;// L6
int  (__main_1) () {

if (__static_condition_default_3) {

{// L12
{



__static_type_error("type error") ; // L13
return 0 ;// L14
}
}// L15


}
}
int  (__main_2) () {

if (__static_condition_default_4) {

{// L12
{



 __z_0  += 3 ; // L13
return 0 ;// L14
}
}// L15


}
}

