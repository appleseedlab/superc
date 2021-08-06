#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_2;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__arr_1", "arr");
__static_renaming("__main_3", "main");

__static_condition_renaming("__static_condition_default_2", "!A");

};

int  __main_3 (void  ) {

{
{



int  __x_0= 5;// L2

int  (__arr_1[3]);// L5

if (__static_condition_default_2) {
__static_type_error("invalid declaration of arr under this presence condition");
}

return 0 ;// L10
}
}



}

