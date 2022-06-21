#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_31;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_33;
extern const bool __static_condition_default_21;
extern const bool __static_condition_default_22;
extern const bool __static_condition_default_17;
extern const bool __static_condition_default_32;
void __static_initializer_default() {
__static_renaming("____assert_fail_4", "__assert_fail");
__static_renaming("____assert_perror_fail_9", "__assert_perror_fail");
__static_renaming("____assert_13", "__assert");
__static_renaming("__nondet_14", "nondet");
__static_renaming("__nondet_15", "nondet");
__static_renaming("__preempt_counter_18", "preempt_counter");
__static_renaming("__tcp_free_md5sig_pool_19", "tcp_free_md5sig_pool");
__static_renaming("__tcp_put_md5sig_pool_20", "tcp_put_md5sig_pool");
__static_renaming("__tcp_twsk_destructor_23", "tcp_twsk_destructor");
__static_renaming("__twsk_destructor_24", "twsk_destructor");
__static_renaming("__inet_twsk_free_25", "inet_twsk_free");
__static_renaming("__inet_twsk_put_26", "inet_twsk_put");
__static_renaming("__inet_twdr_do_twkill_work_27", "inet_twdr_do_twkill_work");
__static_renaming("__inet_twdr_hangman_28", "inet_twdr_hangman");
__static_renaming("__preempt_count_29", "preempt_count");
__static_renaming("____run_timers_30", "__run_timers");
__static_renaming("__main_34", "main");

__static_condition_renaming("__static_condition_default_16", "!(defined NDEBUG) && (defined _ASSERT_H_DECLS) || (defined NDEBUG)");
__static_condition_renaming("__static_condition_default_17", "!(defined NDEBUG) && !(defined _ASSERT_H_DECLS)");
__static_condition_renaming("__static_condition_default_21", "!(defined CONFIG_PREEMPT)");
__static_condition_renaming("__static_condition_default_22", "(defined CONFIG_PREEMPT)");
__static_condition_renaming("__static_condition_default_31", "(defined NDEBUG)");
__static_condition_renaming("__static_condition_default_32", "!(defined NDEBUG) && !(defined _ASSERT_H_DECLS)");
__static_condition_renaming("__static_condition_default_33", "!(defined NDEBUG) && (defined _ASSERT_H_DECLS)");

};

extern void  (____assert_fail_4) (const char  * (____assertion_0), const char  * (____file_1), unsigned int  ____line_2, const char  * (____function_3));// L69:L71
extern void  (____assert_perror_fail_9) (int  ____errnum_5, const char  * (____file_6), unsigned int  ____line_7, const char  * (____function_8));// L74:L76
extern void  (____assert_13) (const char  * (____assertion_10), const char  * (____file_11), int  ____line_12);// L81:L82
int  (__nondet_14) () {

if (__static_condition_default_16) {

{
{



return 42 ;// L3
}
}


}
}
int  (__nondet_15) () {

if (__static_condition_default_17) {

{
{



return 42 ;// L3
}
}


}
}
static int  __preempt_counter_18= 0;// L5
static inline void  (__tcp_free_md5sig_pool_19) (void  ) {

{
{



 ; // L21
}
}


}
static inline void  (__tcp_put_md5sig_pool_20) (void  ) {

{
{



if (__static_condition_default_21) {
 ; // L26
}
if (__static_condition_default_22) {
(  __preempt_counter_18  -- ) ; // L10:L26
}
}
}


}
void  (__tcp_twsk_destructor_23) () {

{
{



if (__static_condition_default_16) {
if (  __nondet_14 ( ) )// L32
{
 __tcp_put_md5sig_pool_20 ( ) ; // L33
}
}
if (__static_condition_default_17) {
if (  __nondet_15 ( ) )// L32
{
 __tcp_put_md5sig_pool_20 ( ) ; // L33
}
}
}
}


}
static inline void  (__twsk_destructor_24) () {

{
{



 __tcp_twsk_destructor_23 ( ) ; // L39
}
}


}
static void  (__inet_twsk_free_25) () {

{
{



 __twsk_destructor_24 ( ) ; // L44
}
}


}
void  (__inet_twsk_put_26) () {

{
{



 __inet_twsk_free_25 ( ) ; // L49
}
}


}
static int  (__inet_twdr_do_twkill_work_27) () {

{
{



 __inet_twsk_put_26 ( ) ; // L54
return 0 ;// L55
}
}


}
void  (__inet_twdr_hangman_28) () {

{
{



 __inet_twdr_do_twkill_work_27 ( ) ; // L60
}
}


}
static inline void  (____run_timers_30) () {

{
{



int  __preempt_count_29= (  __preempt_counter_18  );// L65

 __inet_twdr_hangman_28 ( ) ; // L66
if (  __preempt_count_29  != (  __preempt_counter_18  ) )// L67
{

{
{



if (__static_condition_default_31) {
( ( void   ) ( 0 ) ) ; // L50:L68
}
if (__static_condition_default_32) {
( ( 0 ) ? ( void   ) ( 0 ) :  ____assert_fail_4  ("0","/home/kisamefishfry/Documents/xtc-dev/fonda/cpp_testsuite/varBugs/LINUX/657e9649e74.c",68, __PRETTY_FUNCTION__ ) ) ; // L68:L91
}
if (__static_condition_default_33) {
__static_type_error("type error") ; // L68:L91
}
}
}
}
}
}


}
int  (__main_34) (void  ) {

{
{



 ____run_timers_30 ( ) ; // L74
return 0 ;// L75
}
}


}

