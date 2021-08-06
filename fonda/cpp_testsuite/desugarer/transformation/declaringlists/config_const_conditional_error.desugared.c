#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_1;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__y_2", "y");
__static_renaming("__main_3", "main");

__static_condition_renaming("__static_condition_default_1", "!CONFIG_A");

};

int  __main_3 (void  ) {

{
{



int  __x_0= 2;// L3

if (__static_condition_default_1) {
__static_type_error("invalid declaration of y under this presence condition");
}

int  __y_2=  __x_0 ;// L6

return 0 ;// L8
}
}



}

