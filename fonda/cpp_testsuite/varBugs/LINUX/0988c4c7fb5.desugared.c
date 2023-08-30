#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_22;
extern const bool __static_condition_default_27;
extern const bool __static_condition_default_17;
extern const bool __static_condition_default_29;
extern const bool __static_condition_default_26;
extern const bool __static_condition_default_20;
extern const bool __static_condition_default_23;
extern const bool __static_condition_default_24;
extern const bool __static_condition_default_28;
extern const bool __static_condition_default_32;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_21;
extern const bool __static_condition_default_31;
void __static_initializer_default() {
__static_renaming("____assert_fail_4", "__assert_fail");
__static_renaming("____assert_perror_fail_9", "__assert_perror_fail");
__static_renaming("____assert_13", "__assert");
__static_renaming("__nondet_14", "nondet");
__static_renaming("__nondet_15", "nondet");
__static_renaming("__vlan_hwaccel_do_receive_18", "vlan_hwaccel_do_receive");
__static_renaming("__vlan_hwaccel_do_receive_19", "vlan_hwaccel_do_receive");
__static_renaming("____netif_receive_skb_25", "__netif_receive_skb");
__static_renaming("__netif_receive_skb_30", "netif_receive_skb");
__static_renaming("__main_33", "main");

__static_condition_renaming("__static_condition_default_16", "!(defined NDEBUG) && (defined _ASSERT_H_DECLS) || (defined NDEBUG)");
__static_condition_renaming("__static_condition_default_17", "!(defined NDEBUG) && !(defined _ASSERT_H_DECLS)");
__static_condition_renaming("__static_condition_default_20", "(defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_21", "!(defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_22", "(defined NDEBUG) && !(defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_23", "!(defined NDEBUG) && !(defined _ASSERT_H_DECLS) && !(defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_24", "!(defined NDEBUG) && (defined _ASSERT_H_DECLS) && !(defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_26", "!(defined NDEBUG) && (defined _ASSERT_H_DECLS) && (defined CONFIG_VLAN_8021Q) || (defined NDEBUG) && (defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_27", "!(defined NDEBUG) && (defined _ASSERT_H_DECLS) && !(defined CONFIG_VLAN_8021Q) || (defined NDEBUG) && !(defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_28", "!(defined NDEBUG) && !(defined _ASSERT_H_DECLS) && (defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_29", "!(defined NDEBUG) && !(defined _ASSERT_H_DECLS) && !(defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_31", "(defined CONFIG_RPS)");
__static_condition_renaming("__static_condition_default_32", "!(defined CONFIG_RPS)");

};

extern void  (____assert_fail_4) (const char  * (____assertion_0), const char  * (____file_1), unsigned int  ____line_2, const char  * (____function_3));// L69:L71
extern void  (____assert_perror_fail_9) (int  ____errnum_5, const char  * (____file_6), unsigned int  ____line_7, const char  * (____function_8));// L74:L76
extern void  (____assert_13) (const char  * (____assertion_10), const char  * (____file_11), int  ____line_12);// L81:L82
int  (__nondet_14) () {

if (__static_condition_default_16) {

{// L4
{



return 42 ;// L4
}
}// L4


}
}
int  (__nondet_15) () {

if (__static_condition_default_17) {

{// L4
{



return 42 ;// L4
}
}// L4


}
}
_Bool  (__vlan_hwaccel_do_receive_18) () {

{
if (__static_condition_default_20) {

{// L8
{



return 1 ;// L10
}
}// L11


}

}}
_Bool  (__vlan_hwaccel_do_receive_19) () {

{
if (__static_condition_default_21) {

{// L14
{



if (__static_condition_default_22) {
( ( void   ) ( 0 ) ) ; // L15:L50
}
if (__static_condition_default_23) {
( ( 0 ) ? ( void   ) ( 0 ) :  ____assert_fail_4  ("0","/home/kisamefishfry/Documents/xtc-dev/fonda/cpp_testsuite/varBugs/LINUX/0988c4c7fb5.c",15, __PRETTY_FUNCTION__ ) ) ; // L15:L91
}
if (__static_condition_default_24) {
__static_type_error("type error") ; // L15:L91
}
return 0 ;// L16
}
}// L17


}

}}
int  (____netif_receive_skb_25) () {

{// L21
{



if (__static_condition_default_16) {
if (  __nondet_14 ( ) )// L22
{

{// L23
{



if (__static_condition_default_26) {
 __vlan_hwaccel_do_receive_18 ( ) ; // L24
}
if (__static_condition_default_27) {
 __vlan_hwaccel_do_receive_19 ( ) ; // L24
}
}
}// L25
}
}
if (__static_condition_default_17) {
if (  __nondet_15 ( ) )// L22
{

{// L23
{



if (__static_condition_default_28) {
 __vlan_hwaccel_do_receive_18 ( ) ; // L24
}
if (__static_condition_default_29) {
 __vlan_hwaccel_do_receive_19 ( ) ; // L24
}
}
}// L25
}
}
return 0 ;// L26
}
}// L27


}
int  (__netif_receive_skb_30) () {

{// L30
{



if (__static_condition_default_31) {
return  ____netif_receive_skb_25 ( ) ;// L32
}
if (__static_condition_default_32) {
return  ____netif_receive_skb_25 ( ) ;// L34
}
}
}// L36


}
int  (__main_33) (void  ) {

{// L39
{



 __netif_receive_skb_30 ( ) ; // L40
return 0 ;// L41
}
}// L42


}

