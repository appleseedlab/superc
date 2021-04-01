#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_3;
void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__x_1", "x");
__static_renaming("__i_2", "i");

__static_condition_renaming("__static_condition_default_3", "(defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_4", "!(defined CONFIG_A)");

};

int  __main_0 () {
{
int  __x_1= 0;

if (__static_condition_default_3) {
{ int  __i_2= 0;
 for ( ;  __i_2  < 10 ; ++  __i_2  ) {

if (__static_condition_default_3) {
++  __x_1  ;

}
} }

}

{
if (__static_condition_default_4) {
return  __x_1  ;

}

if (__static_condition_default_3) {
return  __x_1  ;

}

}}


}

