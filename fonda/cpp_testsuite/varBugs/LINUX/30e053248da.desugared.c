#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
extern const bool __static_condition_default_11;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__nondet_0", "nondet");
__static_renaming("__security_old_inode_init_security_3", "security_old_inode_init_security");
__static_renaming("__security_old_inode_init_security_4", "security_old_inode_init_security");
__static_renaming("__error_8", "error");
__static_renaming("__x_9", "x");
__static_renaming("__reiserfs_security_init_10", "reiserfs_security_init");
__static_renaming("__retval_12", "retval");
__static_renaming("__length_13", "length");
__static_renaming("__reiserfs_create_14", "reiserfs_create");
__static_renaming("__main_15", "main");

__static_condition_renaming("__static_condition_default_5", "(defined CONFIG_SECURITY)");
__static_condition_renaming("__static_condition_default_6", "!(defined CONFIG_SECURITY)");
__static_condition_renaming("__static_condition_default_11", "!(defined CONFIG_SECURITY)");

};

int  (__nondet_0) () {

{// L1
{



return 42 ;// L1
}
}// L1


}
int  (__security_old_inode_init_security_3) (int  * (__len_1)) {

{
if (__static_condition_default_5) {

{// L5
{



if (  __nondet_0 ( ) )// L6
{

{// L6
{



*  __len_1  = 0 ; // L7
return 0 ;// L8
}
}// L9
}
else// L10
{
return - 1 ;// L11
}
}
}// L12


}

}}
int  (__security_old_inode_init_security_4) (int  * (__len_2)) {

{
if (__static_condition_default_6) {

{// L15
{



return 0 ;// L16
}
}// L17


}

}}
int  (__reiserfs_security_init_10) (int  * (__length_7)) {

{// L21
{



int  __error_8;// L22

if (__static_condition_default_5) {
 __error_8  =  __security_old_inode_init_security_3  ( __length_7 ) ; // L24
}
if (__static_condition_default_11) {
 __error_8  =  __security_old_inode_init_security_4  ( __length_7 ) ; // L24
}
if (  __error_8  )// L26
{

{// L26
{



*  __length_7  = 0 ; // L27
return  __error_8  ;// L28
}
}// L29
}
int  __x_9= *  __length_7 ;// L31

return 0 ;// L33
}
}// L34


}
int  (__reiserfs_create_14) () {

{// L37
{



int  __retval_12;// L38

int  __length_13;// L39

 __retval_12  =  __reiserfs_security_init_10  (&  __length_13 ) ; // L41
if (  __retval_12  < 0 )// L42
{

{// L43
{



return  __retval_12  ;// L44
}
}// L45
}
return 0 ;// L47
}
}// L48


}
int  (__main_15) (void  ) {

{// L51
{



 __reiserfs_create_14 ( ) ; // L52
return 0 ;// L53
}
}// L54


}

