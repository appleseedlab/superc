#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_17;
extern const bool __static_condition_default_15;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_14;
void __static_initializer_default() {
__static_renaming("__malloc_1", "malloc");
__static_renaming("__free_3", "free");
__static_renaming("__nondet_4", "nondet");
__static_renaming("__hdr_8", "hdr");
__static_renaming("__mod_9", "mod");
__static_renaming("__err_10", "err");
__static_renaming("__ptr_11", "ptr");
__static_renaming("__dest_12", "dest");
__static_renaming("__load_module_13", "load_module");
__static_renaming("__main_18", "main");

__static_condition_renaming("__static_condition_default_14", "(defined CONFIG_MODULE_UNLOAD) && (defined CONFIG_SMP)");
__static_condition_renaming("__static_condition_default_15", "!(defined CONFIG_MODULE_UNLOAD) || (defined CONFIG_MODULE_UNLOAD) && !(defined CONFIG_SMP)");
__static_condition_renaming("__static_condition_default_16", "(defined CONFIG_MODULE_UNLOAD) && (defined CONFIG_SMP)");
__static_condition_renaming("__static_condition_default_17", "!(defined CONFIG_MODULE_UNLOAD) || (defined CONFIG_MODULE_UNLOAD) && !(defined CONFIG_SMP)");

};

extern void  * ((__malloc_1) (unsigned long  ____size_0));// L5
extern void  (__free_3) (void  * (____ptr_2));// L7
int  (__nondet_4) () {

{// L9
{



return 42 ;// L9
}
}// L9


}
int  (__load_module_13) () {

{// L18
{



void  * (__hdr_8);// L19

void  * (* (__mod_9));// L20

long  __err_10= 0;// L21

void  * (__ptr_11)= ( void  * ) 0;// L22

if ( (  __hdr_8  = malloc (2 * sizeof(void*)) ) == ( void  * ) 0 )// L24
{
return - 12 ;// L25
}
 __mod_9  = ( void  * )  __hdr_8  ; // L27
if (__static_condition_default_14) {
(  __mod_9  [ 0 ] ) = malloc (32) ; // L14:L30
}
if (__static_condition_default_14) {
if ( ! (  __mod_9  [ 0 ] ) )// L31
{

{// L32
{



 __err_10  = - 12 ; // L1:L33

{
goto free_mod_3;
}
}
}// L35
}
}
if (__static_condition_default_15) {
 __ptr_11  = malloc (512) ; // L38
}
if (__static_condition_default_14) {
 __ptr_11  = malloc (512) ; // L38
}
if ( !  __ptr_11  )// L39
{

{// L39
{



 __err_10  = - 12 ; // L1:L40

{
goto free_percpu_2;
goto free_percpu_5;
}
}
}// L42
}
(  __mod_9  [ 1 ] ) =  __ptr_11  ; // L15:L43
while (  __nondet_4 ( ) )// L45
{

{// L45
{



void  * (__dest_12)= (  __mod_9  [ 1 ] );// L46

__static_type_error("type error : no valid expression"); // L47
 __mod_9  = (  __mod_9  [ 1 ] ) ; // L15:L48
if (  __nondet_4 ( ) )// L49
{
break ; // L50
}
}
}// L51
}
if (  __nondet_4 ( ) )// L53
{

{
goto free_unload_0;
}
}
return 0 ;// L56

free_unload_0:
{

free_core_1:
{
free ((  __mod_9  [ 1 ] )) ; // L60
}
}
if (__static_condition_default_16) {

free_percpu_2:
{
free ((  __mod_9  [ 0 ] )) ; // L63
}
}
if (__static_condition_default_16) {

free_mod_3:
{

free_hdr_4:
{
free ( __hdr_8 ) ; // L67
}
}
}
if (__static_condition_default_17) {

free_percpu_5:
{

free_mod_6:
{

free_hdr_7:
{
free ( __hdr_8 ) ; // L67
}
}
}
}
return  __err_10  ;// L69
}
}// L70


}
int  (__main_18) (void  ) {

{// L72
{



 __load_module_13 ( ) ; // L73
return 0 ;// L74
}
}// L75


}

