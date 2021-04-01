#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__main_12", "main");
__static_renaming("__t_13", "t");


};
struct __anonymous_tag_0 {
int  __x_1;
};
struct __anonymous_tag_2 {
char  __x_3;
};
struct __anonymous_tag_4 {
char  __y_5;
};
union __anonymous_tag_6 {
struct __anonymous_tag_0  __s1_7;
struct __anonymous_tag_2  __s2_8;
struct __anonymous_tag_4  __s3_9;
};
struct __s_10 {
union __anonymous_tag_6  __anon_id_0_11;
};

struct __s_10 ;
int  __main_12 () {
{
struct __s_10  __t_13;
 __t_13  . __anon_id_0_11 . __s1_7 . __x_1 = 1 ;

 __t_13  . __anon_id_0_11 . __s3_9 . __y_5 = 2 ;

}


}

