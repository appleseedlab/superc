#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__increment_1", "increment");
__static_renaming("__x_2", "x");
__static_renaming("__main_3", "main");

__static_condition_renaming("__static_condition_default_4", "(defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_5", "!(defined CONFIG_A)");

};

int  __increment_1 (int  __i_0) {

{



return ++  __i_0  ;
}



}
int  __main_3 () {

{



int  __x_2= 99;

if (__static_condition_default_4) {
 __x_2  =  __increment_1  (  __x_2  ) ;
}
if (__static_condition_default_5) {
return  __x_2  ;
}
if (__static_condition_default_4) {
return  __x_2  ;
}
}



}

