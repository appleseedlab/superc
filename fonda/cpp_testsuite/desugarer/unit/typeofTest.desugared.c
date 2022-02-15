#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
extern const bool __static_condition_default_8;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_1", "x");
__static_renaming("__y_4", "y");
__static_renaming("__y_5", "y");
__static_renaming("__main_6", "main");

__static_condition_renaming("__static_condition_default_7", "(defined A)");
__static_condition_renaming("__static_condition_default_8", "!(defined A)");

};

int  (__main_6) () {

{
{

typeof(int)__typeofStandin_2;
typeof(int)__typeofStandin_3;


typeof ( int  * )  __x_0;// L3:L9

typeof ( char  * )  __x_1;// L3:L9

typeof ( __typeofStandin_2 )  __y_4;// L10

typeof ( __typeofStandin_3 )  __y_5;// L10

if (__static_condition_default_7) {
 __y_4  = 0 ; // L11
}
if (__static_condition_default_8) {
 __y_5  = 0 ; // L11
}
return 0 ;// L12
}
}


}

