#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
extern const bool __static_condition_default_7;
void __static_initializer_default() {
__static_renaming("__foo_4", "foo");
__static_renaming("__foo_5", "foo");
__static_renaming("__main_8", "main");

__static_condition_renaming("__static_condition_default_6", "(defined A)");
__static_condition_renaming("__static_condition_default_7", "!(defined A)");

};

int  __foo_4 (int  __x_0, int  __y_1, char  __z_3) {

if (__static_condition_default_6) {

{
{



return 0 ;// L7
}
}


}
}
int  __foo_5 (int  __x_0, char  __z_2) {

if (__static_condition_default_7) {

{
{



return 0 ;// L7
}
}


}
}
int  __main_8 () {

{
{



return 0 ;// L12
}
}


}

