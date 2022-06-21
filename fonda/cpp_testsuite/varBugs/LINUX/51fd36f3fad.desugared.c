#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_33;
extern const bool __static_condition_default_43;
extern const bool __static_condition_default_42;
void __static_initializer_default() {
__static_renaming("__int8_t_0", "int8_t");
__static_renaming("__int16_t_1", "int16_t");
__static_renaming("__int32_t_2", "int32_t");
__static_renaming("__int64_t_3", "int64_t");
__static_renaming("__uint8_t_4", "uint8_t");
__static_renaming("__uint16_t_5", "uint16_t");
__static_renaming("__uint32_t_6", "uint32_t");
__static_renaming("__uint64_t_7", "uint64_t");
__static_renaming("__int_least8_t_8", "int_least8_t");
__static_renaming("__int_least16_t_9", "int_least16_t");
__static_renaming("__int_least32_t_10", "int_least32_t");
__static_renaming("__int_least64_t_11", "int_least64_t");
__static_renaming("__uint_least8_t_12", "uint_least8_t");
__static_renaming("__uint_least16_t_13", "uint_least16_t");
__static_renaming("__uint_least32_t_14", "uint_least32_t");
__static_renaming("__uint_least64_t_15", "uint_least64_t");
__static_renaming("__int_fast8_t_16", "int_fast8_t");
__static_renaming("__int_fast16_t_17", "int_fast16_t");
__static_renaming("__int_fast32_t_18", "int_fast32_t");
__static_renaming("__int_fast64_t_19", "int_fast64_t");
__static_renaming("__uint_fast8_t_20", "uint_fast8_t");
__static_renaming("__uint_fast16_t_21", "uint_fast16_t");
__static_renaming("__uint_fast32_t_22", "uint_fast32_t");
__static_renaming("__uint_fast64_t_23", "uint_fast64_t");
__static_renaming("__intptr_t_24", "intptr_t");
__static_renaming("__uintptr_t_25", "uintptr_t");
__static_renaming("__intmax_t_26", "intmax_t");
__static_renaming("__uintmax_t_27", "uintmax_t");
__static_renaming("__s32_28", "s32");
__static_renaming("__s64_29", "s64");
__static_renaming("__u64_30", "u64");
__static_renaming("__ktime_set_32", "ktime_set");
__static_renaming("__tmp_35", "tmp");
__static_renaming("__sec_36", "sec");
__static_renaming("__ktime_add_ns_37", "ktime_add_ns");
__static_renaming("__time_delta_38", "time_delta");
__static_renaming("__expires_39", "expires");
__static_renaming("__tick_nohz_stop_sched_tick_40", "tick_nohz_stop_sched_tick");
__static_renaming("__tick_nohz_stop_sched_tick_41", "tick_nohz_stop_sched_tick");
__static_renaming("__main_46", "main");

__static_condition_renaming("__static_condition_default_33", "!(defined CONFIG_64BIT) && !(defined CONFIG_KTIME_SCALAR)");
__static_condition_renaming("__static_condition_default_42", "!(defined CONFIG_64BIT) && (defined CONFIG_KTIME_SCALAR) || (defined CONFIG_64BIT)");
__static_condition_renaming("__static_condition_default_43", "!(defined CONFIG_64BIT) && !(defined CONFIG_KTIME_SCALAR)");

};
typedef signed char  __int8_t_0;// L36
typedef short int  __int16_t_1;// L37
typedef int  __int32_t_2;// L38
typedef long int  __int64_t_3;// L40
typedef unsigned char  __uint8_t_4;// L48
typedef unsigned short int  __uint16_t_5;// L49
typedef unsigned int  __uint32_t_6;// L51
typedef unsigned long int  __uint64_t_7;// L55
typedef signed char  __int_least8_t_8;// L65
typedef short int  __int_least16_t_9;// L66
typedef int  __int_least32_t_10;// L67
typedef long int  __int_least64_t_11;// L69
typedef unsigned char  __uint_least8_t_12;// L76
typedef unsigned short int  __uint_least16_t_13;// L77
typedef unsigned int  __uint_least32_t_14;// L78
typedef unsigned long int  __uint_least64_t_15;// L80
typedef signed char  __int_fast8_t_16;// L90
typedef long int  __int_fast16_t_17;// L92
typedef long int  __int_fast32_t_18;// L93
typedef long int  __int_fast64_t_19;// L94
typedef unsigned char  __uint_fast8_t_20;// L103
typedef unsigned long int  __uint_fast16_t_21;// L105
typedef unsigned long int  __uint_fast32_t_22;// L106
typedef unsigned long int  __uint_fast64_t_23;// L107
typedef long int  __intptr_t_24;// L119
typedef unsigned long int  __uintptr_t_25;// L122
typedef long int  __intmax_t_26;// L134
typedef unsigned long int  __uintmax_t_27;// L135
typedef __int32_t_2  __s32_28;// L4
typedef __int64_t_3  __s64_29;// L5
typedef __uint64_t_7  __u64_30;// L6

// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
static inline __s64_29  (__ktime_set_32) (const long  __secs_31) {

if (__static_condition_default_33) {

{
{



return ( __s64_29   )  __secs_31  * 1000000000L ;// L31
}
}


}
}
__s64_29  (__ktime_add_ns_37) (__u64_30  __nsec_34) {

if (__static_condition_default_33) {

{
{



__s64_29  __tmp_35;// L36

if (  __nsec_34  < 1000000000L )// L38
{

{
{



 __tmp_35  =  __nsec_34  ; // L39
}
}
}
else
{

{
{



unsigned long  __sec_36=  __nsec_34  / 1000000000L;// L41

 __tmp_35  =  __ktime_set_32  (( __s32_28   )  __sec_36 ) ; // L42
}
}
}
return  __tmp_35  ;// L45
}
}


}
}
static __u64_30  (__tick_nohz_stop_sched_tick_40) () {

if (__static_condition_default_42) {

{
{



__u64_30  __time_delta_38= ( __u64_30   ) 7881299347898368000;// L52

__s64_29  __expires_39;// L53

if (  __time_delta_38  < ( ( __s64_29   ) ~ ( ( __u64_30   ) 1 << 63 ) ) )// L55
{
 __expires_39  = (  __time_delta_38  ) ; // L25:L56
}
else
{
if (__static_condition_default_42) {
 __expires_39  = ( ( __s64_29   ) ~ ( ( __u64_30   ) 1 << 63 ) ) ; // L16:L58
}
}
return  __expires_39  ;// L60
}
}


}
}
static __u64_30  (__tick_nohz_stop_sched_tick_41) () {

if (__static_condition_default_43) {

{
{



__u64_30  __time_delta_38= ( __u64_30   ) 7881299347898368000;// L52

__s64_29  __expires_39;// L53

if (  __time_delta_38  < ( ( __s64_29   ) ~ ( ( __u64_30   ) 1 << 63 ) ) )// L55
{
 __expires_39  =  __ktime_add_ns_37  ( __time_delta_38 ) ; // L56
}
else
{
if (__static_condition_default_43) {
 __expires_39  = ( ( __s64_29   ) ~ ( ( __u64_30   ) 1 << 63 ) ) ; // L16:L58
}
}
return  __expires_39  ;// L60
}
}


}
}
int  (__main_46) (int  __argc_44, char  * (* (__argv_45))) {

{
{



if (__static_condition_default_42) {
 __tick_nohz_stop_sched_tick_40 ( ) ; // L65
}
if (__static_condition_default_43) {
 __tick_nohz_stop_sched_tick_41 ( ) ; // L65
}
return 0 ;// L66
}
}


}

