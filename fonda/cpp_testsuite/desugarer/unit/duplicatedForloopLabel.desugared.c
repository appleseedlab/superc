#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_11;
extern const bool __static_condition_default_14;
extern const bool __static_condition_default_13;
void __static_initializer_default() {
__static_renaming("__this_7", "this");
__static_renaming("__i_8", "i");
__static_renaming("__wlen_9", "wlen");
__static_renaming("__i_10", "i");
__static_renaming("__foo_12", "foo");

__static_condition_renaming("__static_condition_default_11", "!(defined X)");
__static_condition_renaming("__static_condition_default_13", "(defined X)");
__static_condition_renaming("__static_condition_default_14", "!(defined X)");

};
struct __anonymous_tag_0 {
int  __num_1;
};
struct __anonymous_tag_2 {
int  __x_3;
};
union __u_4 {
struct __anonymous_tag_0  __a_5;
struct __anonymous_tag_2  __b_6;
};

union __u_4  __this_7;// L7:L16
void  __foo_12 () {

{
{



int  __i_8;// L20

int  __wlen_9=  __this_7  . __a_5 . __num_1;// L20


int  __i_10;// L20


if (__static_condition_default_11) {
__static_type_error("invalid declaration of wlen under this presence condition");
}

if (__static_condition_default_13) {
for (  __i_8  ;  ;  )// L22
{

{
{




flush_0:
{
 __i_8  = 2 ; // L24
}
}
}
}
}
if (__static_condition_default_14) {
for (  __i_10  ;  ;  )// L22
{

{
{




flush_1:
{
 __i_10  = 2 ; // L24
}
}
}
}
}
}
}


}

