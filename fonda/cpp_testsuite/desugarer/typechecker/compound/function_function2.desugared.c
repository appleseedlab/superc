#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_8;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__x_3", "x");
__static_renaming("__x_4", "x");
__static_renaming("__main_7", "main");

__static_condition_renaming("__static_condition_default_5", "(defined A)");
__static_condition_renaming("__static_condition_default_6", "!(defined A)");
__static_condition_renaming("__static_condition_default_8", "!(defined A)");

};

float  __x_3 (float  __a_0, float  __b_1) {

{
if (__static_condition_default_5) {

{



return  __a_0  *  __b_1  ;// L3
}


}

}
}
char  __x_4 (int  __y_2) {

{
if (__static_condition_default_6) {

{



return  __y_2  ;// L7
}


}

}
}
int  __main_7 () {

{



if (__static_condition_default_8) {
 __x_4  ( 7 ) ; // L12
}
if (__static_condition_default_5) {
__static_type_error("type error") ; // L12
}
return 0 ;// L13
}



}

