#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_21;
extern const bool __static_condition_default_17;
extern const bool __static_condition_default_20;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_12;
extern const bool __static_condition_default_11;
void __static_initializer_default() {
__static_renaming("__nondet_0", "nondet");
__static_renaming("__some_int_1", "some_int");
__static_renaming("__x_3", "x");
__static_renaming("__pts_sb_from_inode_4", "pts_sb_from_inode");
__static_renaming("__devpts_pty_kill_8", "devpts_pty_kill");
__static_renaming("__pty_close_10", "pty_close");
__static_renaming("__tty_release_14", "tty_release");
__static_renaming("__driver_data_15", "driver_data");
__static_renaming("__ptmx_open_16", "ptmx_open");
__static_renaming("__main_18", "main");
__static_renaming("__main_19", "main");

__static_condition_renaming("__static_condition_default_5", "!(defined CONFIG_DEVPTS_MULTIPLE_INSTANCES)");
__static_condition_renaming("__static_condition_default_6", "(defined CONFIG_DEVPTS_MULTIPLE_INSTANCES)");
__static_condition_renaming("__static_condition_default_11", "!(defined CONFIG_UNIX98_PTYS)");
__static_condition_renaming("__static_condition_default_12", "(defined CONFIG_UNIX98_PTYS)");
__static_condition_renaming("__static_condition_default_17", "(defined CONFIG_UNIX98_PTYS)");
__static_condition_renaming("__static_condition_default_20", "!(defined CONFIG_UNIX98_PTYS)");
__static_condition_renaming("__static_condition_default_21", "(defined CONFIG_UNIX98_PTYS)");

};

int  (__nondet_0) () {

{// L1
{



return 42 ;// L1
}
}// L1


}
int  __some_int_1= 1;// L3
void  (__pts_sb_from_inode_4) (int  * (__inode_2)) {

{
if (__static_condition_default_5) {

{// L6
{



}
}// L10


}

if (__static_condition_default_6) {

{// L6
{



int  __x_3= *  __inode_2 ;// L8

}
}// L10


}

}}
void  (__devpts_pty_kill_8) (int  * (__inode_7)) {

{// L13
{



 __pts_sb_from_inode_4  ( __inode_7 ) ; // L14
}
}// L15


}
void  (__pty_close_10) (int  * (__driver_data_9)) {

{
if (__static_condition_default_11) {

{// L18
{



}
}// L22


}

if (__static_condition_default_12) {

{// L18
{



 __devpts_pty_kill_8  ( __driver_data_9 ) ; // L20
}
}// L22


}

}}
int  (__tty_release_14) (int  * (__driver_data_13)) {

{// L25
{



 __pty_close_10  ( __driver_data_13 ) ; // L26
return 0 ;// L27
}
}// L28


}
int  (__ptmx_open_16) () {

if (__static_condition_default_17) {

{// L32
{



int  * (__driver_data_15);// L33

if (  __nondet_0 ( ) )// L35
{

{// L35
{




{
goto err_release_0;
}
}
}// L37
}
 __driver_data_15  = &  __some_int_1  ; // L39
return 0 ;// L41

err_release_0:
{
 __tty_release_14  ( __driver_data_15 ) ; // L44
}
return - 1 ;// L45
}
}// L46


}
}
int  (__main_18) () {

if (__static_condition_default_20) {

{// L50
{



return 0 ;// L54
}
}// L55


}
}
int  (__main_19) () {

if (__static_condition_default_21) {

{// L50
{



 __ptmx_open_16 ( ) ; // L52
return 0 ;// L54
}
}// L55


}
}

