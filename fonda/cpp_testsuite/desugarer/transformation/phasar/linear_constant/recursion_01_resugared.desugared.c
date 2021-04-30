#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_1;
extern const bool __static_condition_default_2;
void __static_initializer_default() {
__static_renaming("__factorial_3", "factorial");
__static_renaming("__x_4", "x");
__static_renaming("__main_5", "main");

__static_condition_renaming("__static_condition_default_1", "(defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_2", "!(defined CONFIG_A)");

};

unsigned  __factorial_3 (unsigned  __n_0) {
{

if (__static_condition_default_1) {
if (  __n_0  <= 1 ) 
if (__static_condition_default_1) {
{

if (__static_condition_default_1) {
return 1 ;

}
}

}


}

{
if (__static_condition_default_1) {
__static_type_error("invalid type found in return expression");

}

if (__static_condition_default_2) {
return  __n_0  ;

}

}}


}
int  __main_5 () {
{
int  __x_4= 5;
 __x_4  =  __factorial_3  (  __x_4  ) ;

return  __x_4  ;

}


}

