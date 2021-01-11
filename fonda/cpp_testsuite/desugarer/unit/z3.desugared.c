#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_3;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__y_1", "y");
__static_renaming("__main_2", "main");

__static_condition_renaming("__static_condition_default_3", "(declare-fun |(defined A)| () Bool)(assert |(defined A)|)");
__static_condition_renaming("__static_condition_default_4", "(declare-fun |(defined A)| () Bool)(assert (not |(defined A)|))");
__static_condition_renaming("__static_condition_default_5", "(declare-fun |(defined A)| () Bool)(declare-fun |(defined B)| () Bool)(assert |(defined A)|)(assert |(defined B)|)");
__static_condition_renaming("__static_condition_default_6", "(declare-fun |(defined B)| () Bool)(declare-fun |(defined A)| () Bool)(assert (or (not |(defined A)|)    (and |(defined A)| (not (and |(defined A)| |(defined B)|)))))");

};

int  __x_0;
char  __y_1;
int  __main_2 () {
{

if (__static_condition_default_3) {
 __x_0  = 10 ;

}

if (__static_condition_default_4) {
 __y_1  = 'c' ;

}

{
if (__static_condition_default_5) {
return 1 ;

}

if (__static_condition_default_6) {
return 0 ;

}

}}


}

