#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__x1_8", "x1");
__static_renaming("__main_9", "main");


};
struct ____s_1_1 {
int  __data_2;
struct __forward_tag_reference_0  (* __next_3);
};
union __anonymous_tag_4 {
struct ____s_1_1  ____s_1_5;
};
struct __s_6 {
union __anonymous_tag_4  ;
};

struct __forward_tag_reference_0 { // generated union of struct variations
union {
struct __s_6 __s_6;
};
};

struct ____s_1_1 ;
struct __s_6 ;
struct __s_6 ;
struct __s_6  __x1_8;
int  __main_9 () {
{
struct __s_6 ;
__static_type_error("invalid type found in return expression");

}


}
