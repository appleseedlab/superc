#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__num_0", "num");
__static_renaming("__x_1", "x");
__static_renaming("__x_2", "x");
__static_renaming("__main_3", "main");

__static_condition_renaming("__static_condition_default_4", "(defined A)");
__static_condition_renaming("__static_condition_default_5", "!(defined A)");

};

int  __num_0= 5;// L1
int  __main_3 () {

{



int  (* __x_1);// L5

char  (__x_2[5]);// L7

if (__static_condition_default_4) {
 __x_1  [ 2 ] ; // L10
}
if (__static_condition_default_5) {
 __x_2  [ 2 ] ; // L10
}
return 0 ;// L12
}



}

