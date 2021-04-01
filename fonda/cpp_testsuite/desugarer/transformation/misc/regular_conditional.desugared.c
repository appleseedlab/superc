#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_2;
extern const bool __static_condition_default_3;
void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__x_1", "x");

__static_condition_renaming("__static_condition_default_2", "(defined B)");
__static_condition_renaming("__static_condition_default_3", "!(defined B)");

};

int  __main_0 () {

{
if (__static_condition_default_3) {
{
int  __x_1;
}

}

if (__static_condition_default_2) {
{
int  __x_1;

if (__static_condition_default_2) {
if (  __x_1  < 100 ) 
if (__static_condition_default_2) {
{
}

}


}
}

}

}
}

