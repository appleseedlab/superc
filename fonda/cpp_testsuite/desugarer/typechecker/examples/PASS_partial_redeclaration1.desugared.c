#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_3;
void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__x_1", "x");
__static_renaming("__x_4", "x");

__static_condition_renaming("__static_condition_default_3", "(declare-fun |(defined B)| () Bool)(declare-fun |(defined A)| () Bool)(assert (or (and |(defined A)| (not |(defined B)|)) (and |(defined A)| |(defined B)|)))(assert |(defined B)|)");
__static_condition_renaming("__static_condition_default_5", "(declare-fun |(defined B)| () Bool)(assert (not |(defined B)|))");
__static_condition_renaming("__static_condition_default_6", "(declare-fun |(defined B)| () Bool)(assert |(defined B)|)");

};

int  __main_0 () {
{
int  __x_1;
if (__static_condition_default_3) {
__static_type_error("redeclaration of local symbol: x");
}

char  __x_4;

{
if (__static_condition_default_5) {
return 0 ;

}

if (__static_condition_default_6) {
return 0 ;

}

}}


}

