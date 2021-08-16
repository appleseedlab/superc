#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__bob_5", "bob");
__static_renaming("__main_6", "main");


};
struct ____anonymous_tag_0_1 {
int  __f_2;// L2
};
struct __s_3 {
struct ____anonymous_tag_0_1  (__x_4[4]);// L2
};

struct __s_3  __bob_5=  { .__x_4 = { [0] .__f_2 = 10 } };// L1:L3
int  __main_6 () {

{
{



}
}


}

