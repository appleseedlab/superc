#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_3;
extern const bool __static_condition_default_1;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_2", "x");
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_1", "A");
__static_condition_renaming("__static_condition_default_3", "!A");

};

int  __main_4 (void  ) {

{
if (__static_condition_default_1) {
{
int  __x_0;

if (__static_condition_default_1) {
return 0 ;

}
}

}

if (__static_condition_default_3) {
{
char  __x_2;

if (__static_condition_default_3) {
return 1 ;

}
}

}

}
}

