#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_1", "x");
__static_renaming("__main_2", "main");
__static_renaming("__x_3", "x");

__static_condition_renaming("__static_condition_default_4", "(declare-fun |(defined A)| () Bool)(assert (not |(defined A)|))");
__static_condition_renaming("__static_condition_default_5", "(declare-fun |(defined A)| () Bool)(assert |(defined A)|)");

};

int  __x_0;
char  __x_1;
int  __main_2 () {
{
float  __x_3;

{
if (__static_condition_default_4) {
 __x_1  ++ ;

}

if (__static_condition_default_5) {
 __x_3  ++ ;

}

}}


}

