#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_1;
extern const bool __static_condition_default_4;
void __static_initializer_default() {
__static_renaming("__f_0", "f");
__static_renaming("__f_2", "f");
__static_renaming("__main_3", "main");

__static_condition_renaming("__static_condition_default_1", "(declare-fun |(defined A)| () Bool)(assert |(defined A)|)");
__static_condition_renaming("__static_condition_default_4", "(declare-fun |(defined A)| () Bool)(assert (not |(defined A)|))");

};

extern int  __f_2;
float  __f_0 () {

if (__static_condition_default_1) {
{

if (__static_condition_default_1) {
return 0 ;

}
}

}

}
int  __main_3 () {
{

{
if (__static_condition_default_1) {
 __f_0  ( ) ;

}

if (__static_condition_default_4) {
 __f_2  ;

}

}return 0 ;

}


}

