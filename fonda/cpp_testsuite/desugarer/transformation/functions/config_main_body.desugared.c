#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_2;
void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__x_1", "x");
__static_renaming("__x_3", "x");

__static_condition_renaming("__static_condition_default_2", "(declare-fun A () Bool)(assert A)");
__static_condition_renaming("__static_condition_default_4", "(declare-fun A () Bool)(assert (not A))");

};

int  __main_0 (void  ) {

{
if (__static_condition_default_2) {
{
int  __x_1;

if (__static_condition_default_2) {
return 0 ;

}
}

}

if (__static_condition_default_4) {
{
char  __x_3;

if (__static_condition_default_4) {
return 1 ;

}
}

}

}
}

