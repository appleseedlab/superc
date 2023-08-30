#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_12;
extern const bool __static_condition_default_15;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_10;
void __static_initializer_default() {
__static_renaming("__size_t_0", "size_t");
__static_renaming("__malloc_2", "malloc");
__static_renaming("__free_4", "free");
__static_renaming("__wbuf_5", "wbuf");
__static_renaming("__wbuf_verify_6", "wbuf_verify");
__static_renaming("__jffs2_nor_wbuf_flash_setup_7", "jffs2_nor_wbuf_flash_setup");
__static_renaming("__jffs2_nor_wbuf_flash_setup_8", "jffs2_nor_wbuf_flash_setup");
__static_renaming("__jffs2_verify_write_11", "jffs2_verify_write");
__static_renaming("____jffs2_flush_wbuf_13", "__jffs2_flush_wbuf");
__static_renaming("____jffs2_flush_wbuf_14", "__jffs2_flush_wbuf");
__static_renaming("__jffs2_flash_writev_17", "jffs2_flash_writev");
__static_renaming("__jffs2_flash_write_18", "jffs2_flash_write");
__static_renaming("__main_19", "main");

__static_condition_renaming("__static_condition_default_9", "!(defined CONFIG_JFFS2_FS_WBUF_VERIFY)");
__static_condition_renaming("__static_condition_default_10", "(defined CONFIG_JFFS2_FS_WBUF_VERIFY)");
__static_condition_renaming("__static_condition_default_12", "(defined CONFIG_JFFS2_FS_WBUF_VERIFY)");
__static_condition_renaming("__static_condition_default_15", "!(defined CONFIG_JFFS2_FS_WBUF_VERIFY)");
__static_condition_renaming("__static_condition_default_16", "(defined CONFIG_JFFS2_FS_WBUF_VERIFY)");

};
typedef long unsigned int  __size_t_0;// L3

// typedef moved to top of scope
extern void  * ((__malloc_2) (__size_t_0  ____size_1));// L5
extern void  (__free_4) (void  * (____ptr_3));// L7
unsigned char  * (__wbuf_5);// L11
unsigned char  * (__wbuf_verify_6);// L13
int  (__jffs2_nor_wbuf_flash_setup_7) () {

if (__static_condition_default_9) {

{// L16
{



 __wbuf_5  = malloc (32) ; // L17
if ( !  __wbuf_5  )// L18
{
return - 12 ;// L19
}
return 0 ;// L21
}
}// L22


}
}
int  (__jffs2_nor_wbuf_flash_setup_8) () {

if (__static_condition_default_10) {

{// L16
{



 __wbuf_5  = malloc (32) ; // L17
if ( !  __wbuf_5  )// L18
{
return - 12 ;// L19
}
return 0 ;// L21
}
}// L22


}
}
static int  (__jffs2_verify_write_11) () {

if (__static_condition_default_12) {

{// L26
{



return ( int   ) *  __wbuf_verify_6  ;// L27
}
}// L28


}
}
int  (____jffs2_flush_wbuf_13) () {

if (__static_condition_default_15) {

{// L34
{



do
{

{// L30
{



}
}// L30
}
while( 0 );// L30:L35
return 0 ;// L36
}
}// L37


}
}
int  (____jffs2_flush_wbuf_14) () {

if (__static_condition_default_16) {

{// L34
{



 __jffs2_verify_write_11 ( ) ; // L35
return 0 ;// L36
}
}// L37


}
}
int  (__jffs2_flash_writev_17) () {

{// L40
{



if (__static_condition_default_15) {
 ____jffs2_flush_wbuf_13 ( ) ; // L41
}
if (__static_condition_default_16) {
 ____jffs2_flush_wbuf_14 ( ) ; // L41
}
return 0 ;// L42
}
}// L43


}
int  (__jffs2_flash_write_18) () {

{// L46
{



return  __jffs2_flash_writev_17 ( ) ;// L47
}
}// L48


}
int  (__main_19) () {

{// L51
{



if (__static_condition_default_9) {
 __jffs2_nor_wbuf_flash_setup_7 ( ) ; // L52
}
if (__static_condition_default_10) {
 __jffs2_nor_wbuf_flash_setup_8 ( ) ; // L52
}
 __jffs2_flash_write_18 ( ) ; // L53
return 0 ;// L54
}
}// L55


}

