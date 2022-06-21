#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_2;
extern const bool __static_condition_default_3;
void __static_initializer_default() {
__static_renaming("__sendfile_nonblocking_0", "sendfile_nonblocking");
__static_renaming("__send_brigade_nonblocking_1", "send_brigade_nonblocking");
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_2", "!APR_HAS_SENDFILE");
__static_condition_renaming("__static_condition_default_3", "APR_HAS_SENDFILE");

};

void  (__sendfile_nonblocking_0) ();// L1
void  (__send_brigade_nonblocking_1) () {

{
if (__static_condition_default_2) {

{
{



}
}


}

if (__static_condition_default_3) {

{
{



 __sendfile_nonblocking_0 ( ) ; // L6
}
}


}

}}
int  (__main_4) (void  ) {

{
{



 __send_brigade_nonblocking_1 ( ) ; // L12
return 0 ;// L13
}
}


}

