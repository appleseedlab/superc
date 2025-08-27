#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_3;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_8;
void __static_initializer_default() {
__static_renaming("__ap_get_server_module_loglevel_0", "ap_get_server_module_loglevel");
__static_renaming("__main_1", "main");
__static_renaming("__main_2", "main");

__static_condition_renaming("__static_condition_default_3", "!(defined HAVE_SYSLOG)");
__static_condition_renaming("__static_condition_default_4", "!(defined HAVE_SYSLOG) && !(defined APLOG_MAX_LOGLEVEL)");
__static_condition_renaming("__static_condition_default_5", "!(defined HAVE_SYSLOG) && (defined APLOG_MAX_LOGLEVEL)");
__static_condition_renaming("__static_condition_default_6", "(defined HAVE_SYSLOG)");
__static_condition_renaming("__static_condition_default_7", "(defined HAVE_SYSLOG) && (defined AP_DEBUG) && !(defined APLOG_MAX_LOGLEVEL)");
__static_condition_renaming("__static_condition_default_8", "(defined HAVE_SYSLOG) && (defined AP_DEBUG) && (defined APLOG_MAX_LOGLEVEL)");
__static_condition_renaming("__static_condition_default_9", "(defined HAVE_SYSLOG) && !(defined AP_DEBUG) && !(defined APLOG_MAX_LOGLEVEL)");
__static_condition_renaming("__static_condition_default_10", "(defined HAVE_SYSLOG) && !(defined AP_DEBUG) && (defined APLOG_MAX_LOGLEVEL)");

};

void  (__ap_get_server_module_loglevel_0) ();// L7
int  (__main_1) (void  ) {

if (__static_condition_default_3) {

{// L14
{



if (__static_condition_default_4) {
if ( 1 <= 2 )// L16
{
__static_type_error("type error") ; // L17
}
}
if (__static_condition_default_5) {
if ( 1 <= 3 )// L16
{
__static_type_error("type error") ; // L20
}
}
return 0 ;// L23
}
}// L24


}
}
int  (__main_2) (void  ) {

if (__static_condition_default_6) {

{// L14
{



if (__static_condition_default_7) {
if ( 1 <= 2 )// L16
{
 __ap_get_server_module_loglevel_0 ( ) ; // L17
}
}
if (__static_condition_default_8) {
if ( 1 <= 3 )// L16
{
 __ap_get_server_module_loglevel_0 ( ) ; // L20
}
}
if (__static_condition_default_9) {
if ( 1 <= 2 )// L16
{
do
{

{// L9
{



}
}// L9
}
while( 0 );// L9:L17
}
}
if (__static_condition_default_10) {
if ( 1 <= 3 )// L16
{
do
{

{// L9
{



}
}// L9
}
while( 0 );// L9:L20
}
}
return 0 ;// L23
}
}// L24


}
}

