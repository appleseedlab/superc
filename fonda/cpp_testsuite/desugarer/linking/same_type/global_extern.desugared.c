#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_2;
void __static_initializer_default() {
__static_renaming("__f_1", "f");
__static_renaming("__f_4", "f");

__static_condition_renaming("__static_condition_default_2", "(declare-fun |(defined CONFIG_A)| () Bool)(assert |(defined CONFIG_A)|)");

};

extern int  __f_4 (int  __x_3);
int  __f_1 (int  __x_0) {

if (__static_condition_default_2) {
{

if (__static_condition_default_2) {
return  __x_0  + 1 ;

}
}

}

}
extern int  __f_4 (int  __x_3);
int  __f_1 (int  __x_0) {

if (__static_condition_default_2) {
{

if (__static_condition_default_2) {
return  __x_0  + 1 ;

}
}

}

}

