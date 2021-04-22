#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_3;
void __static_initializer_default() {
__static_renaming("__increment_1", "increment");
__static_renaming("__x_2", "x");
__static_renaming("__main_5", "main");

__static_condition_renaming("__static_condition_default_3", "(defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_4", "!(defined CONFIG_A)");

if (0)
{
__static_parse_error("Unable to parse");
}
};

int  __increment_1 (int  __i_0) {
{
return ++  __i_0  ;

}


}
int  __main_5 () {
{
int  __x_2= 99;

if (__static_condition_default_3) {
 __x_2  =  __increment_1  (  __x_2  ) ;

}

{
if (__static_condition_default_4) {
return  __x_2  ;

}

if (__static_condition_default_3) {
return  __x_2  ;

}

}}


}

