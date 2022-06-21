#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_3;
extern const bool __static_condition_default_2;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__ap_get_server_module_loglevel_0", "ap_get_server_module_loglevel");
__static_renaming("__main_1", "main");

__static_condition_renaming("__static_condition_default_2", "(defined AP_DEBUG) && !(defined APLOG_MAX_LOGLEVEL)");
__static_condition_renaming("__static_condition_default_3", "(defined AP_DEBUG) && (defined APLOG_MAX_LOGLEVEL)");
__static_condition_renaming("__static_condition_default_4", "!(defined AP_DEBUG) && !(defined APLOG_MAX_LOGLEVEL)");
__static_condition_renaming("__static_condition_default_5", "!(defined AP_DEBUG) && (defined APLOG_MAX_LOGLEVEL)");

};

void  (__ap_get_server_module_loglevel_0) ();// L7
int  (__main_1) (void  ) {

{
{



if (__static_condition_default_2) {
if ( 1 <= 2 )// L16
{
 __ap_get_server_module_loglevel_0 ( ) ; // L17
}
}
if (__static_condition_default_3) {
if ( 1 <= 3 )// L16
{
 __ap_get_server_module_loglevel_0 ( ) ; // L20
}
}
if (__static_condition_default_4) {
if ( 1 <= 2 )// L16
{
do
{

{
{



}
}
}
while( 0 );// L9:L17
}
}
if (__static_condition_default_5) {
if ( 1 <= 3 )// L16
{
do
{

{
{



}
}
}
while( 0 );// L9:L20
}
}
return 0 ;// L23
}
}


}

