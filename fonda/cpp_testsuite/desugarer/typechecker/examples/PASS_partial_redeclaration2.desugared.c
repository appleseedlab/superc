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

__static_condition_renaming("__static_condition_default_3", "(declare-fun |(defined OKAY)| () Bool)(declare-fun |(defined A)| () Bool)(assert (or (and |(defined A)| (not |(defined OKAY)|))    (and |(defined A)| |(defined OKAY)|)))(assert |(defined OKAY)|)");
__static_condition_renaming("__static_condition_default_5", "(declare-fun |(defined OKAY)| () Bool)(assert (not |(defined OKAY)|))");
__static_condition_renaming("__static_condition_default_6", "(declare-fun |(defined OKAY)| () Bool)(assert |(defined OKAY)|)");

};

int  __main_0 () {
{
int  __x_1;
if (__static_condition_default_3) {
__static_type_error("redeclaration of local symbol: x");
}

int  __x_4;

{
if (__static_condition_default_5) {
return 0 ;

}

if (__static_condition_default_6) {
return 0 ;

}

}}


}

