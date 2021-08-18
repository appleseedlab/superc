#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_16;
extern const bool __static_condition_default_15;
extern const bool __static_condition_default_13;
void __static_initializer_default() {
__static_renaming("__this_9", "this");
__static_renaming("__i_10", "i");
__static_renaming("__wlen_11", "wlen");
__static_renaming("__i_12", "i");
__static_renaming("__foo_14", "foo");

__static_condition_renaming("__static_condition_default_13", "!(defined X)");
__static_condition_renaming("__static_condition_default_15", "(defined X)");
__static_condition_renaming("__static_condition_default_16", "!(defined X)");

};
struct ____anonymous_tag_0_1 {
int  __num_2;// L10
};
struct ____anonymous_tag_3_4 {
int  __x_5;// L14
};
union __u_6 {
struct ____anonymous_tag_0_1  __a_7;// L8
struct ____anonymous_tag_3_4  __b_8;// L12
};

union __u_6  __this_9;// L7:L16
void  __foo_14 () {

{
{



int  __i_10;// L20

int  __wlen_11=  __this_9  . __a_7 . __num_2;// L20


int  __i_12;// L20


if (__static_condition_default_13) {
__static_type_error("invalid declaration of wlen under this presence condition");
}

if (__static_condition_default_15) {
for (  __i_10  ;  ;  )// L22
{

{
{




flush_0:
{
 __i_10  = 2 ; // L24
}
}
}
}
}
if (__static_condition_default_16) {
for (  __i_12  ;  ;  )// L22
{

{
{




flush_1:
{
 __i_12  = 2 ; // L24
}
}
}
}
}
}
}


}

