#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_10;
extern const bool __static_condition_default_31;
extern const bool __static_condition_default_29;
extern const bool __static_condition_default_39;
extern const bool __static_condition_default_33;
extern const bool __static_condition_default_38;
extern const bool __static_condition_default_26;
extern const bool __static_condition_default_30;
extern const bool __static_condition_default_32;
void __static_initializer_default() {
__static_renaming("__malloc_1", "malloc");
__static_renaming("__free_3", "free");
__static_renaming("__strcmp_6", "strcmp");
__static_renaming("__linked_7", "linked");
__static_renaming("__sysfs_link_sibling_9", "sysfs_link_sibling");
__static_renaming("__sysfs_unlink_sibling_12", "sysfs_unlink_sibling");
__static_renaming("__sysfs_create_dir_14", "sysfs_create_dir");
__static_renaming("__kobject_add_16", "kobject_add");
__static_renaming("__kobj_18", "kobj");
__static_renaming("__retval_19", "retval");
__static_renaming("__kobject_create_and_add_20", "kobject_create_and_add");
__static_renaming("__kobj_22", "kobj");
__static_renaming("__class_compat_register_23", "class_compat_register");
__static_renaming("__class_compat_unregister_25", "class_compat_unregister");
__static_renaming("__switch_class_27", "switch_class");
__static_renaming("__create_extcon_class_28", "create_extcon_class");
__static_renaming("__extcon_class_init_34", "extcon_class_init");
__static_renaming("__extcon_class_exit_35", "extcon_class_exit");
__static_renaming("__main_36", "main");
__static_renaming("__main_37", "main");

__static_condition_renaming("__static_condition_default_10", "!(defined CONFIG_ANDROID) && (defined CONFIG_SYSFS) || (defined CONFIG_ANDROID)");
__static_condition_renaming("__static_condition_default_26", "!(defined CONFIG_ANDROID) && (defined CONFIG_SYSFS) || (defined CONFIG_ANDROID)");
__static_condition_renaming("__static_condition_default_29", "(defined CONFIG_EXTCON)");
__static_condition_renaming("__static_condition_default_30", "(defined CONFIG_ANDROID) && (defined CONFIG_EXTCON)");
__static_condition_renaming("__static_condition_default_31", "(defined CONFIG_ANDROID) && (defined CONFIG_EXTCON)");
__static_condition_renaming("__static_condition_default_32", "!(defined CONFIG_ANDROID) && (defined CONFIG_EXTCON)");
__static_condition_renaming("__static_condition_default_33", "(defined CONFIG_ANDROID) && (defined CONFIG_EXTCON)");
__static_condition_renaming("__static_condition_default_38", "!(defined CONFIG_EXTCON)");
__static_condition_renaming("__static_condition_default_39", "(defined CONFIG_EXTCON)");

};
static const char  * (__linked_7)= ( void  * ) 0;// L18

extern void  * ((__malloc_1) (unsigned long  ____size_0));// L10
extern void  (__free_3) (void  * (____ptr_2));// L12
extern int  (__strcmp_6) (const char  * (____s1_4), const char  * (____s2_5));// L14:L15

int  (__sysfs_link_sibling_9) (const char  * (__s_name_8)) {

if (__static_condition_default_10) {

{// L21
{



if (  __linked_7  != ( void  * ) 0 )// L22
{
return ( !  __strcmp_6  ( __s_name_8 , __linked_7 ) ) ? - 17 : - 12 ;// L23
}
 __linked_7  =  __s_name_8  ; // L25
return 0 ;// L26
}
}// L27


}
}
void  (__sysfs_unlink_sibling_12) (const char  * (__s_name_11)) {

if (__static_condition_default_10) {

{// L30
{



if (  __linked_7  != ( void  * ) 0 && !  __strcmp_6  ( __s_name_11 , __linked_7 ) )// L31
{
 __linked_7  = ( void  * ) 0 ; // L8:L32
}
}
}// L33


}
}
int  (__sysfs_create_dir_14) (const char  * (__name_13)) {

if (__static_condition_default_10) {

{// L36
{



return  __sysfs_link_sibling_9  ( __name_13 ) ;// L37
}
}// L38


}
}
int  (__kobject_add_16) (const char  * (__name_15)) {

if (__static_condition_default_10) {

{// L41
{



return  __sysfs_create_dir_14  ( __name_15 ) ;// L42
}
}// L43


}
}
int  * ((__kobject_create_and_add_20) (const char  * (__name_17))) {

if (__static_condition_default_10) {

{// L46
{



int  * (__kobj_18)= ( int  * ) malloc (sizeof(int));// L47

if ( !  __kobj_18  )// L48
{
return ( void  * ) 0 ;// L49
}
int  __retval_19=  __kobject_add_16  ( __name_17 );// L51

if (  __retval_19  )// L52
{

{// L53
{



free ( __kobj_18 ) ; // L54
 __kobj_18  = ( void  * ) 0 ; // L8:L55
}
}// L56
}
return  __kobj_18  ;// L58
}
}// L59


}
}
int  * ((__class_compat_register_23) (const char  * (__name_21))) {

if (__static_condition_default_10) {

{// L62
{



int  * (__kobj_22);// L63

 __kobj_22  =  __kobject_create_and_add_20  ( __name_21 ) ; // L65
if ( !  __kobj_22  )// L66
{
return ( void  * ) 0 ;// L67
}
return  __kobj_22  ;// L69
}
}// L70


}
}
void  (__class_compat_unregister_25) (const char  * (__name_24)) {

if (__static_condition_default_26) {

{// L73
{



free ( __name_24 ) ; // L74
}
}// L75


}
}
static int  * (__switch_class_27);// L80
int  (__create_extcon_class_28) (void  ) {

if (__static_condition_default_29) {

{// L84
{



if (__static_condition_default_30) {
 __switch_class_27  =  __class_compat_register_23  ("switch") ; // L86
}
if (__static_condition_default_31) {
if ( !  __switch_class_27  )// L87
{
return - 12 ;// L88
}
}
if (__static_condition_default_32) {
return 0 ;// L90
}
if (__static_condition_default_33) {
return 0 ;// L90
}
}
}// L91


}
}
int  (__extcon_class_init_34) (void  ) {

if (__static_condition_default_29) {

{// L94
{



return  __create_extcon_class_28 ( ) ;// L95
}
}// L96


}
}
void  (__extcon_class_exit_35) (void  ) {

if (__static_condition_default_29) {

{// L99
{



return  ;// L100
}
}// L101


}
}
int  (__main_36) (void  ) {

if (__static_condition_default_38) {

{// L105
{



return 0 ;// L111
}
}// L112


}
}
int  (__main_37) (void  ) {

if (__static_condition_default_39) {

{// L105
{



 __extcon_class_init_34 ( ) ; // L107
 __extcon_class_exit_35 ( ) ; // L108
 __extcon_class_init_34 ( ) ; // L109
return 0 ;// L111
}
}// L112


}
}

