#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__increment_1", "increment");
__static_renaming("__main_2", "main");
__static_renaming("__x_3", "x");

__static_condition_renaming("__static_condition_default_4", "(declare-fun |(defined CONFIG_A)| () Bool)(assert |(defined CONFIG_A)|)");
__static_condition_renaming("__static_condition_default_5", "(declare-fun |(defined CONFIG_A)| () Bool)(assert (not |(defined CONFIG_A)|))");

};

int  __increment_1 (int  __i_0) {
{
return ++  __i_0  ;

}


}
int  __main_2 () {
{
int  __x_3= 99;

if (__static_condition_default_4) {
 __x_3  =  __increment_1  (  __x_3  ) ;

}

{
if (__static_condition_default_5) {
return  __x_3  ;

}

if (__static_condition_default_4) {
return  __x_3  ;

}

}}


}

