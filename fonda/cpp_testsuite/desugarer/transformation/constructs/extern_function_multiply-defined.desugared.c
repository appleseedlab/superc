#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_5();

extern const bool __static_condition_3;
extern const bool __static_condition_4;
void __static_initializer_5() {
__static_renaming("__x_0", "x");
__static_renaming("__x_1", "x");
__static_renaming("__main_2", "main");

__static_condition_renaming("__static_condition_3", "(declare-fun |(defined A)| () Bool)(assert |(defined A)|)");
__static_condition_renaming("__static_condition_4", "(declare-fun |(defined A)| () Bool)(assert (not |(defined A)|))");

};
int  __main_2 ();

extern int  __x_0 ();
extern float  __x_1 ();
int  __main_2 () {
{

{
if (__static_condition_3) {
 __x_0  ( ) ;

}

if (__static_condition_4) {
 __x_1  ( ) ;

}

}}


}

