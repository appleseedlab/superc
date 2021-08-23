#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_15;
extern const bool __static_condition_default_14;
void __static_initializer_default() {
__static_renaming("__bob_1", "bob");
__static_renaming("__main_13", "main");

__static_condition_renaming("__static_condition_default_14", "!(defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_15", "(defined CONFIG_A)");

};
struct __T_2 {
int  __field_t_3;// L4
};
struct __X_4 {
int  __field_x_5;// L7
struct __T_2  __field_struct_t_6;// L9
char  __field_struct_t_7;// L11
};
struct __X_8 {
int  __field_x_9;// L16
};
struct __T_10 {
int  __field_t_11;// L19
struct __X_8  __field_struct_x_12;// L20
};

struct __forward_tag_reference_0 { // generated union of struct variations
union {
struct __T_2 __T_2;
struct __T_10 __T_10;
};
};

struct __forward_tag_reference_0  __bob_1;// L1
struct __T_2 ;// L3
struct __X_8 ;// L15
struct __X_4 ;// L6
struct __T_10 ;// L18
int  (__main_13) () {

{
{



if (__static_condition_default_14) {
 __bob_1  . __T_10 . __field_struct_x_12 ; // L25
}
if (__static_condition_default_15) {
 __bob_1  . __T_2 . __field_t_3 ; // L27
}
}
}


}

