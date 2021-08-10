#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__x_9", "x");
__static_renaming("__a_10", "a");
__static_renaming("__a_11", "a");
__static_renaming("__main_12", "main");


};
union __anonymous_tag_0 {
int  __c_1;
short  __c_2;
long  (* __d_3);
int  (* __d_4);
};
struct __x_5 {
int  __a_6;
int  __b_7;
union __anonymous_tag_0  __anon_id_0_8;
};

struct __x_5 ;// L1
int  __main_12 () {

{
{



struct __x_5  __x_9;// L17

int  __a_10=  __x_9  . __anon_id_0_8 . __c_1;// L18

int  __a_11=  __x_9  . __anon_id_0_8 . __c_2;// L18

return 0 ;// L19
}
}


}

