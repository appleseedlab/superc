#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_4;
void __static_initializer_default() {
__static_renaming("__num_0", "num");
__static_renaming("__main_1", "main");
__static_renaming("__x_2", "x");
__static_renaming("__x_3", "x");

__static_condition_renaming("__static_condition_default_4", "(defined A)");
__static_condition_renaming("__static_condition_default_5", "!(defined A)");

};

int  __num_0= 5;
int  __main_1 () {
{
int  (* __x_2);
char  (__x_3[5]);

{
if (__static_condition_default_4) {
 __x_2  [ 2 ] ;

}

if (__static_condition_default_5) {
 __x_3  [ 2 ] ;

}

}return 0 ;

}


}
