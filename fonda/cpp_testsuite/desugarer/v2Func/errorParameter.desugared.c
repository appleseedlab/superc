#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
void __static_initializer_default() {
__static_renaming("__foo_2", "foo");
__static_renaming("__a_3", "a");
__static_renaming("__b_5", "b");
__static_renaming("__d_6", "d");
__static_renaming("__main_7", "main");

__static_condition_renaming("__static_condition_default_4", "(defined A)");

};

int  __foo_2 (int  __a_0, int  __b_1) {

{
{



return 0 ;// L3
}
}



}
int  __main_7 () {

{
{



int  __a_3= 1;// L8

if (__static_condition_default_4) {
__static_type_error("invalid declaration of b under this presence condition");
}

int  __b_5= 1;// L9:L13

if (1) {
__static_type_error("invalid declaration of c under this presence condition");
}

int  __d_6=  __foo_2  (  __a_3 ,  __b_5  );// L16

if (__static_condition_default_4) {
__static_type_error("invalid declaration of d under this presence condition");
}

__static_type_error("type error : no valid expression"); // L17
return 0 ;// L18
}
}



}

