#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_11;
extern const bool __static_condition_default_10;
void __static_initializer_default() {
__static_renaming("__foo_1", "foo");
__static_renaming("__foo_3", "foo");
__static_renaming("__z_6", "z");
__static_renaming("__ptr_7", "ptr");
__static_renaming("__ptr_8", "ptr");
__static_renaming("__main_9", "main");

__static_condition_renaming("__static_condition_default_4", "(defined HAS_PARAM)");
__static_condition_renaming("__static_condition_default_5", "!(defined HAS_PARAM)");
__static_condition_renaming("__static_condition_default_10", "(defined HAS_PARAM)");
__static_condition_renaming("__static_condition_default_11", "!(defined HAS_PARAM)");

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
int  (__main_9) () {

{
{



int  __z_6;// L16

int  (* (__ptr_7)) (int  )=  __foo_1 ;// L18

int  (* (__ptr_8)) ()=  __foo_3 ;// L21

if (__static_condition_default_10) {
 __z_6  =  __ptr_7  (10) ; // L19
}
if (__static_condition_default_11) {
 __z_6  =  __ptr_8 ( ) ; // L22
}
return  __z_6  ;// L24
}
}


}

int main () {
  return __main_9();
}
