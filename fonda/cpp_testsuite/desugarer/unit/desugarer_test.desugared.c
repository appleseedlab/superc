#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__t_16", "t");
__static_renaming("__main_17", "main");


};
struct ____anonymous_tag_0_1 {
int  __x_2;// L4
};
struct ____anonymous_tag_3_4 {
char  __x_5;// L7
};
struct ____anonymous_tag_6_7 {
char  __y_8;// L10
};
union ____anonymous_tag_9_10 {
struct ____anonymous_tag_0_1  __s1_11;// L3
struct ____anonymous_tag_3_4  __s2_12;// L6
struct ____anonymous_tag_6_7  __s3_13;// L9
};
struct __s_14 {
union ____anonymous_tag_9_10  __anon_id_0_15;// L2
};

struct __s_14 ;// L1
int  __main_17 () {

{
{



struct __s_14  __t_16;// L16

 __t_16  . __anon_id_0_15 . __s1_11 . __x_2 = 1 ; // L17
 __t_16  . __anon_id_0_15 . __s3_13 . __y_8 = 2 ; // L18
}
}


}

