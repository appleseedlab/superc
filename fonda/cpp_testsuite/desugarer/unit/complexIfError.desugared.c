#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__x_2", "x");
__static_renaming("__x_3", "x");
__static_renaming("__pfd_4", "pfd");
__static_renaming("__main_5", "main");

__static_condition_renaming("__static_condition_default_6", "(defined A)");
__static_condition_renaming("__static_condition_default_7", "!(defined A)");

};
struct __x_0 {
int  __revents_1;// L2
};

struct __x_0 ;// L1
int  __x_2;// L5:L9
int  __x_3 ();// L5:L9
int  __main_5 () {

{
{



struct __x_0  (* (__pfd_4));// L13

if (__static_condition_default_6) {
if ( (  __pfd_4  [ 2 ] . __revents_1 & 0x010 ) &&  __x_3 ( ) == 0 )// L14
{

{
{



}
}
}
}
if (__static_condition_default_7) {
__static_type_error("invalid type found in if statement");
}
}
}


}

