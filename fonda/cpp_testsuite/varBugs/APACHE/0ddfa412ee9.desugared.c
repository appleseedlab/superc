#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
extern const bool __static_condition_default_2;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__ssl_array_index_0", "ssl_array_index");
__static_renaming("__ssl_cmp_alpn_protos_1", "ssl_cmp_alpn_protos");
__static_renaming("__ssl_callback_alpn_select_3", "ssl_callback_alpn_select");
__static_renaming("__main_4", "main");
__static_renaming("__main_5", "main");

__static_condition_renaming("__static_condition_default_2", "(defined HAVE_TLS_ALPN)");
__static_condition_renaming("__static_condition_default_6", "!(defined HAVE_TLS_ALPN)");
__static_condition_renaming("__static_condition_default_7", "(defined HAVE_TLS_ALPN)");

};

void  (__ssl_array_index_0) () {

{// L2
{



}
}// L3


}
void  (__ssl_cmp_alpn_protos_1) () {

if (__static_condition_default_2) {

{// L7
{



 __ssl_array_index_0 ( ) ; // L8
}
}// L9


}
}
void  (__ssl_callback_alpn_select_3) () {

if (__static_condition_default_2) {

{// L12
{



 __ssl_cmp_alpn_protos_1 ( ) ; // L13
}
}// L14


}
}
int  (__main_4) (void  ) {

if (__static_condition_default_6) {

{// L18
{



return 0 ;// L22
}
}// L23


}
}
int  (__main_5) (void  ) {

if (__static_condition_default_7) {

{// L18
{



 __ssl_callback_alpn_select_3 ( ) ; // L20
return 0 ;// L22
}
}// L23


}
}

