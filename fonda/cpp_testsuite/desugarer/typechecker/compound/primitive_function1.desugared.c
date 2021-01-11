#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_2;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__x_1", "x");
__static_renaming("__x_3", "x");
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_2", "(declare-fun |(defined A)| () Bool)(assert (not |(defined A)|))");
__static_condition_renaming("__static_condition_default_5", "(declare-fun |(defined A)| () Bool)(assert |(defined A)|)");

};

int  __x_3;
char  __x_1 (int  __y_0) {

if (__static_condition_default_2) {
{

if (__static_condition_default_2) {
return  __y_0  ;

}
}

}

}
int  __main_4 () {
{

{
if (__static_condition_default_2) {
 __x_1  ++ ;

}

if (__static_condition_default_5) {
 __x_3  ++ ;

}

}return 0 ;

}


}

