#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
extern const bool __static_condition_default_7;
void __static_initializer_default() {
__static_renaming("__f_3", "f");
__static_renaming("__f_4", "f");
__static_renaming("__f_5", "f");

__static_condition_renaming("__static_condition_default_6", "(defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_7", "!(defined CONFIG_A) && CONFIG_B");

};

extern int  __f_3 (int  __x_2);// L11
int  __f_4 (int  __x_0) {

{
if (__static_condition_default_6) {

{



return  __x_0  + 1 ;// L4
}


}

}
}
static int  __f_5 (int  __x_1) {

{
if (__static_condition_default_7) {

{



return  __x_1  + 1 ;// L8
}


}

}
}

