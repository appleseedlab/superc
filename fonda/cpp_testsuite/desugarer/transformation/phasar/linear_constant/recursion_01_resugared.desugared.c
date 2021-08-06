#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_3;
extern const bool __static_condition_default_2;
void __static_initializer_default() {
__static_renaming("__factorial_1", "factorial");
__static_renaming("__x_4", "x");
__static_renaming("__main_5", "main");

__static_condition_renaming("__static_condition_default_2", "(defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_3", "!(defined CONFIG_A)");

};

unsigned  __factorial_1 (unsigned  __n_0) {

{
{



if (__static_condition_default_2) {
if (  __n_0  <= 1 )// L3
{

{
{



return 1 ;// L4
}
}
}
}
if (__static_condition_default_2) {
__static_type_error("invalid type found in return expression");
}
if (__static_condition_default_3) {
return  __n_0  ;// L8
}
}
}



}
int  __main_5 () {

{
{



int  __x_4= 5;// L13

 __x_4  =  __factorial_1  (  __x_4  ) ; // L14
return  __x_4  ;// L15
}
}



}

