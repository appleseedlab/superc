#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_8;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_9;
void __static_initializer_default() {
__static_renaming("__foo_1", "foo");
__static_renaming("__foo_3", "foo");
__static_renaming("__z_6", "z");
__static_renaming("__main_7", "main");

__static_condition_renaming("__static_condition_default_4", "(defined HAS_PARAM)");
__static_condition_renaming("__static_condition_default_5", "!(defined HAS_PARAM)");
__static_condition_renaming("__static_condition_default_8", "(defined HAS_PARAM)");
__static_condition_renaming("__static_condition_default_9", "!(defined HAS_PARAM)");

};

int  (__foo_1) (int  __a_0);// L2
int  (__foo_3) ();// L8
int  (__foo_1) (int  __a_2) {

{
if (__static_condition_default_4) {

{
{



return  __a_2  ;// L5
}
}


}

}}
int  (__foo_3) () {

{
if (__static_condition_default_5) {

{
{



return 1 ;// L11
}
}


}

}}
int  (__main_7) () {

{
{



int  __z_6;// L16

if (__static_condition_default_8) {
 __z_6  =  __foo_1  (10) ; // L18
}
if (__static_condition_default_9) {
 __z_6  =  __foo_3 ( ) ; // L20
}
return  __z_6  ;// L22
}
}


}


int main()
{
  return __main_7();
}
