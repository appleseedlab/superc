#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_2;
void __static_initializer_default() {
__static_renaming("__AX_0", "AX");
__static_renaming("__x_1", "x");
__static_renaming("__main_3", "main");
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_2", "!(defined A)");
__static_condition_renaming("__static_condition_default_5", "!(defined A)");
__static_condition_renaming("__static_condition_default_6", "(defined A)");

};
typedef int  __AX_0;// L2

// typedef moved to top of scope
int  __main_3 () {

if (__static_condition_default_5) {

{
{



if (__static_condition_default_2) {
__static_type_error("invalid declaration of x under this presence condition");
}

__static_type_error("invalid type found in return expression");
}
}


}

}
int  __main_4 () {

if (__static_condition_default_6) {

{
{



int  __x_1= 5 + sizeof(__AX_0  );// L6

return  __x_1  ;// L7
}
}


}

}

