#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__x1_9", "x1");
__static_renaming("__main_10", "main");


};
struct ____s_1_1 {
int  __data_2;// L2
struct __forward_tag_reference_0  (* __next_3);// L0
};
union ____anonymous_tag_4_5 {
struct ____s_1_1  ____s_1_6;// L8
};
struct __s_7 {
union ____anonymous_tag_4_5  __anon_id_0_8;// L7
};

struct __forward_tag_reference_0 { // generated union of struct variations
union {
struct __s_7 __s_7;
};
};

struct ____s_1_1 ;// L1
struct __s_7 ;// L6
struct __s_7 ;// L13
struct __s_7  __x1_9;// L16
int  __main_10 () {

{
{



struct __s_7 ;// L19

return  __x1_9  . __anon_id_0_8 . ____s_1_6 . __data_2 ;// L20
}
}


}

