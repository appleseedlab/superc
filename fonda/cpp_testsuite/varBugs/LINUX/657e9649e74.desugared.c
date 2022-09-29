#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_17;
extern const bool __static_condition_default_21;
extern const bool __static_condition_default_27;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_20;
extern const bool __static_condition_default_37;
extern const bool __static_condition_default_39;
extern const bool __static_condition_default_26;
extern const bool __static_condition_default_28;
extern const bool __static_condition_default_38;
extern const bool __static_condition_default_23;
extern const bool __static_condition_default_29;
extern const bool __static_condition_default_24;
void __static_initializer_default() {
__static_renaming("____assert_fail_4", "__assert_fail");
__static_renaming("____assert_perror_fail_9", "__assert_perror_fail");
__static_renaming("____assert_13", "__assert");
__static_renaming("__nondet_14", "nondet");
__static_renaming("__nondet_15", "nondet");
__static_renaming("__preempt_counter_18", "preempt_counter");
__static_renaming("__tcp_free_md5sig_pool_19", "tcp_free_md5sig_pool");
__static_renaming("__tcp_put_md5sig_pool_22", "tcp_put_md5sig_pool");
__static_renaming("__tcp_twsk_destructor_25", "tcp_twsk_destructor");
__static_renaming("__twsk_destructor_30", "twsk_destructor");
__static_renaming("__inet_twsk_free_31", "inet_twsk_free");
__static_renaming("__inet_twsk_put_32", "inet_twsk_put");
__static_renaming("__inet_twdr_do_twkill_work_33", "inet_twdr_do_twkill_work");
__static_renaming("__inet_twdr_hangman_34", "inet_twdr_hangman");
__static_renaming("__preempt_count_35", "preempt_count");
__static_renaming("____run_timers_36", "__run_timers");
__static_renaming("__main_40", "main");

__static_condition_renaming("__static_condition_default_16", "!(defined NDEBUG) && (defined _ASSERT_H_DECLS) || (defined NDEBUG)");
__static_condition_renaming("__static_condition_default_17", "!(defined NDEBUG) && !(defined _ASSERT_H_DECLS)");
__static_condition_renaming("__static_condition_default_20", "(defined CONFIG_TCP_MD5SIG)");
__static_condition_renaming("__static_condition_default_21", "!(defined CONFIG_TCP_MD5SIG)");
__static_condition_renaming("__static_condition_default_23", "!(defined CONFIG_PREEMPT)");
__static_condition_renaming("__static_condition_default_24", "(defined CONFIG_PREEMPT)");
__static_condition_renaming("__static_condition_default_26", "!(defined CONFIG_TCP_MD5SIG)");
__static_condition_renaming("__static_condition_default_27", "(defined CONFIG_TCP_MD5SIG)");
__static_condition_renaming("__static_condition_default_28", "!(defined NDEBUG) && (defined _ASSERT_H_DECLS) && (defined CONFIG_TCP_MD5SIG) || (defined NDEBUG) && (defined CONFIG_TCP_MD5SIG)");
__static_condition_renaming("__static_condition_default_29", "!(defined NDEBUG) && !(defined _ASSERT_H_DECLS) && (defined CONFIG_TCP_MD5SIG)");
__static_condition_renaming("__static_condition_default_37", "(defined NDEBUG)");
__static_condition_renaming("__static_condition_default_38", "!(defined NDEBUG) && !(defined _ASSERT_H_DECLS)");
__static_condition_renaming("__static_condition_default_39", "!(defined NDEBUG) && (defined _ASSERT_H_DECLS)");

};

extern void  (____assert_fail_4) (const char  * (____assertion_0), const char  * (____file_1), unsigned int  ____line_2, const char  * (____function_3));// L69:L71
extern void  (____assert_perror_fail_9) (int  ____errnum_5, const char  * (____file_6), unsigned int  ____line_7, const char  * (____function_8));// L74:L76
extern void  (____assert_13) (const char  * (____assertion_10), const char  * (____file_11), int  ____line_12);// L81:L82
int  (__nondet_14) () {

if (__static_condition_default_16) {

{// L3
{



return 42 ;// L3
}
}// L3


}
}
int  (__nondet_15) () {

if (__static_condition_default_17) {

{// L3
{



return 42 ;// L3
}
}// L3


}
}
static int  __preempt_counter_18= 0;// L5
static inline void  (__tcp_free_md5sig_pool_19) (void  ) {

{// L20
{



if (__static_condition_default_20) {
 ; // L21
}
if (__static_condition_default_21) {
__static_type_error("type error : no valid expression"); // L21
}
}
}// L22


}
static inline void  (__tcp_put_md5sig_pool_22) (void  ) {

{// L25
{



if (__static_condition_default_23) {
 ; // L26
}
if (__static_condition_default_24) {
(  __preempt_counter_18  -- ) ; // L10:L26
}
}
}// L27


}
void  (__tcp_twsk_destructor_25) () {

{
if (__static_condition_default_26) {

{// L30
{



}
}// L35


}

if (__static_condition_default_27) {

{// L30
{



if (__static_condition_default_28) {
if (  __nondet_14 ( ) )// L32
{
 __tcp_put_md5sig_pool_22 ( ) ; // L33
}
}
if (__static_condition_default_29) {
if (  __nondet_15 ( ) )// L32
{
 __tcp_put_md5sig_pool_22 ( ) ; // L33
}
}
}
}// L35


}

}}
static inline void  (__twsk_destructor_30) () {

{// L38
{



 __tcp_twsk_destructor_25 ( ) ; // L39
}
}// L40


}
static void  (__inet_twsk_free_31) () {

{// L43
{



 __twsk_destructor_30 ( ) ; // L44
}
}// L45


}
void  (__inet_twsk_put_32) () {

{// L48
{



 __inet_twsk_free_31 ( ) ; // L49
}
}// L50


}
static int  (__inet_twdr_do_twkill_work_33) () {

{// L53
{



 __inet_twsk_put_32 ( ) ; // L54
return 0 ;// L55
}
}// L56


}
void  (__inet_twdr_hangman_34) () {

{// L59
{



 __inet_twdr_do_twkill_work_33 ( ) ; // L60
}
}// L61


}
static inline void  (____run_timers_36) () {

{// L64
{



int  __preempt_count_35= (  __preempt_counter_18  );// L65

 __inet_twdr_hangman_34 ( ) ; // L66
if (  __preempt_count_35  != (  __preempt_counter_18  ) )// L67
{

{// L67
{



if (__static_condition_default_37) {
( ( void   ) ( 0 ) ) ; // L50:L68
}
if (__static_condition_default_38) {
( ( 0 ) ? ( void   ) ( 0 ) :  ____assert_fail_4  ("0","/home/kisamefishfry/Documents/xtc-dev/fonda/cpp_testsuite/varBugs/LINUX/657e9649e74.c",68, __PRETTY_FUNCTION__ ) ) ; // L68:L91
}
if (__static_condition_default_39) {
__static_type_error("type error") ; // L68:L91
}
}
}// L69
}
}
}// L70


}
int  (__main_40) (void  ) {

{// L73
{



 ____run_timers_36 ( ) ; // L74
return 0 ;// L75
}
}// L76


}

