#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_8;
void __static_initializer_default() {
__static_renaming("__var_6", "var");
__static_renaming("__main_7", "main");

__static_condition_renaming("__static_condition_default_5", "!(defined A)");
__static_condition_renaming("__static_condition_default_8", "(defined A)");

};
struct __x_0 {
int  __a_1;// L5
int  __b_2[255];// L6
int  __c_4;// L7
};

struct __x_0 ;// L4

const struct __x_0  * (__var_6);// L10
int  (__main_7) () {

{
{



if (__static_condition_default_8) {
( * ( struct __x_0  * (*) ) &  __var_6  ) = ( void  * ) 0 ; // L14
}
if (__static_condition_default_5) {
__static_type_error("type error") ; // L14
}
return 0 ;// L15
}
}


}

