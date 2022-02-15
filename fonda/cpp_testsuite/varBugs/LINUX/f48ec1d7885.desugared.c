#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_2;
void __static_initializer_default() {
__static_renaming("__d_0", "d");
__static_renaming("__cfq_scale_slice_1", "cfq_scale_slice");
__static_renaming("__main_3", "main");
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_2", "(defined CONFIG_IOSCHED_CFQ)");
__static_condition_renaming("__static_condition_default_5", "!(defined CONFIG_IOSCHED_CFQ)");
__static_condition_renaming("__static_condition_default_6", "(defined CONFIG_IOSCHED_CFQ)");

};

static long  (__cfq_scale_slice_1) () {

if (__static_condition_default_2) {

{
{



long  __d_0= 1;// L8

__static_type_error("type error : no valid expression"); // L9
return  __d_0  ;// L10
}
}


}
}
int  (__main_3) () {

if (__static_condition_default_5) {

{
{



return 0 ;// L20
}
}


}
}
int  (__main_4) () {

if (__static_condition_default_6) {

{
{



 __cfq_scale_slice_1 ( ) ; // L18
return 0 ;// L20
}
}


}
}

