#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_8;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_10;
void __static_initializer_default() {
__static_renaming("__f_5", "f");
__static_renaming("__f_6", "f");
__static_renaming("__f_7", "f");

__static_condition_renaming("__static_condition_default_8", "(defined B) && (defined A)");
__static_condition_renaming("__static_condition_default_9", "(defined B) && !(defined A)");
__static_condition_renaming("__static_condition_default_10", "!(defined B)");

};

int  (__f_5) (int  __x_0, int  __y_1, int  __z_3) {

if (__static_condition_default_8) {

{
{



}
}


}
}
int  (__f_6) (int  __x_0, int  __z_2) {

if (__static_condition_default_9) {

{
{



}
}


}
}
int  (__f_7) (int  __a_4) {

if (__static_condition_default_10) {

{
{



}
}


}
}

