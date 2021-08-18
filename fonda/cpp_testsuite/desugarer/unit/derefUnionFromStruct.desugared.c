#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__x_10", "x");
__static_renaming("__a_11", "a");
__static_renaming("__a_12", "a");
__static_renaming("__main_13", "main");


};
union ____anonymous_tag_0_1 {
int  __c_2;// L6
short  __c_3;// L9
long  (* (__d_4));// L7
int  (* (__d_5));// L10
};
struct __x_6 {
int  __a_7;// L2
int  __b_8;// L3
union ____anonymous_tag_0_1  __anon_id_0_9;// L4
};

struct __x_6 ;// L1
int  __main_13 () {

{
{



struct __x_6  __x_10;// L17

int  __a_11=  __x_10  . __anon_id_0_9 . __c_2;// L18

int  __a_12=  __x_10  . __anon_id_0_9 . __c_3;// L18

return 0 ;// L19
}
}


}

