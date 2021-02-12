#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_17;
extern const bool __static_condition_default_18;
extern const bool __static_condition_default_19;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_15;
void __static_initializer_default() {
__static_renaming("__foo_10", "foo");
__static_renaming("__foo_11", "foo");
__static_renaming("__foo_12", "foo");
__static_renaming("__foo_13", "foo");
__static_renaming("__foo_14", "foo");
__static_renaming("__main_20", "main");

__static_condition_renaming("__static_condition_default_15", "!(defined A)");
__static_condition_renaming("__static_condition_default_16", "(defined A) && !(defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_17", "(defined A) && (defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_18", "(defined A) && (defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_19", "(defined A) && !(defined B) && !(defined C)");

};

int  __foo_10 (int  __w_7) {

if (__static_condition_default_15) {
{
return 0 ;

}

}

}
int  __foo_11 (int  __y_1, int  __z_5, int  __w_9) {

if (__static_condition_default_16) {
{
return 0 ;

}

}

}
int  __foo_12 (int  __x_0, int  __y_2, int  __z_4, int  __w_9) {

if (__static_condition_default_17) {
{
return 0 ;

}

}

}
int  __foo_13 (int  __x_0, int  __z_3, int  __w_9) {

if (__static_condition_default_18) {
{
return 0 ;

}

}

}
int  __foo_14 (int  __z_6, int  __w_8) {

if (__static_condition_default_19) {
{
return 0 ;

}

}

}
int  __main_20 () {
{
return 0 ;

}


}

