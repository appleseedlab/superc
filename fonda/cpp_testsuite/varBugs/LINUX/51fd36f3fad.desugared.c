#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_51;
extern const bool __static_condition_default_43;
extern const bool __static_condition_default_56;
extern const bool __static_condition_default_52;
extern const bool __static_condition_default_29;
extern const bool __static_condition_default_36;
extern const bool __static_condition_default_39;
extern const bool __static_condition_default_58;
extern const bool __static_condition_default_53;
extern const bool __static_condition_default_57;
extern const bool __static_condition_default_61;
extern const bool __static_condition_default_31;
extern const bool __static_condition_default_55;
extern const bool __static_condition_default_59;
extern const bool __static_condition_default_50;
extern const bool __static_condition_default_54;
extern const bool __static_condition_default_45;
extern const bool __static_condition_default_42;
extern const bool __static_condition_default_44;
extern const bool __static_condition_default_60;
extern const bool __static_condition_default_35;
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
__static_renaming("__s64_30", "s64");
__static_renaming("__u64_32", "u64");
__static_renaming("__ktime_set_34", "ktime_set");
__static_renaming("__tmp_38", "tmp");
__static_renaming("__sec_40", "sec");
__static_renaming("__ktime_add_ns_41", "ktime_add_ns");
__static_renaming("__time_delta_46", "time_delta");
__static_renaming("__expires_47", "expires");
__static_renaming("__tick_nohz_stop_sched_tick_48", "tick_nohz_stop_sched_tick");
__static_renaming("__tick_nohz_stop_sched_tick_49", "tick_nohz_stop_sched_tick");
__static_renaming("__main_64", "main");

__static_condition_renaming("__static_condition_default_29", "(defined __int8_t_defined)");
__static_condition_renaming("__static_condition_default_31", "(defined __int8_t_defined)");
__static_condition_renaming("__static_condition_default_35", "(defined __int8_t_defined) && !(defined CONFIG_64BIT) && !(defined CONFIG_KTIME_SCALAR)");
__static_condition_renaming("__static_condition_default_36", "!(defined __int8_t_defined) && !(defined CONFIG_64BIT) && !(defined CONFIG_KTIME_SCALAR)");
__static_condition_renaming("__static_condition_default_39", "(defined __int8_t_defined) && !(defined CONFIG_64BIT) && !(defined CONFIG_KTIME_SCALAR)");
__static_condition_renaming("__static_condition_default_42", "(defined __int8_t_defined) && !(defined CONFIG_64BIT) && !(defined CONFIG_KTIME_SCALAR)");
__static_condition_renaming("__static_condition_default_43", "!(defined __int8_t_defined) && !(defined CONFIG_64BIT) && !(defined CONFIG_KTIME_SCALAR)");
__static_condition_renaming("__static_condition_default_44", "!(defined __int8_t_defined) && !(defined CONFIG_64BIT) && !(defined CONFIG_KTIME_SCALAR)");
__static_condition_renaming("__static_condition_default_45", "!(defined __int8_t_defined) && !(defined CONFIG_64BIT) && !(defined CONFIG_KTIME_SCALAR)");
__static_condition_renaming("__static_condition_default_50", "!(defined CONFIG_64BIT) && (defined CONFIG_KTIME_SCALAR) || (defined CONFIG_64BIT)");
__static_condition_renaming("__static_condition_default_51", "!(defined __int8_t_defined) && !(defined CONFIG_64BIT) && (defined CONFIG_KTIME_SCALAR) || !(defined __int8_t_defined) && (defined CONFIG_64BIT)");
__static_condition_renaming("__static_condition_default_52", "!(defined __int8_t_defined) && !(defined CONFIG_64BIT) && (defined CONFIG_KTIME_SCALAR) || !(defined __int8_t_defined) && (defined CONFIG_64BIT)");
__static_condition_renaming("__static_condition_default_53", "(defined __int8_t_defined) && !(defined CONFIG_64BIT) && (defined CONFIG_KTIME_SCALAR) || (defined __int8_t_defined) && (defined CONFIG_64BIT)");
__static_condition_renaming("__static_condition_default_54", "!(defined __int8_t_defined) && !(defined CONFIG_64BIT) && (defined CONFIG_KTIME_SCALAR) || !(defined __int8_t_defined) && (defined CONFIG_64BIT)");
__static_condition_renaming("__static_condition_default_55", "(defined __int8_t_defined) && !(defined CONFIG_64BIT) && (defined CONFIG_KTIME_SCALAR) || (defined __int8_t_defined) && (defined CONFIG_64BIT)");
__static_condition_renaming("__static_condition_default_56", "!(defined CONFIG_64BIT) && !(defined CONFIG_KTIME_SCALAR)");
__static_condition_renaming("__static_condition_default_57", "!(defined __int8_t_defined) && !(defined CONFIG_64BIT) && !(defined CONFIG_KTIME_SCALAR)");
__static_condition_renaming("__static_condition_default_58", "!(defined __int8_t_defined) && !(defined CONFIG_64BIT) && !(defined CONFIG_KTIME_SCALAR)");
__static_condition_renaming("__static_condition_default_59", "(defined __int8_t_defined) && !(defined CONFIG_64BIT) && !(defined CONFIG_KTIME_SCALAR)");
__static_condition_renaming("__static_condition_default_60", "!(defined __int8_t_defined) && !(defined CONFIG_64BIT) && !(defined CONFIG_KTIME_SCALAR)");
__static_condition_renaming("__static_condition_default_61", "(defined __int8_t_defined) && !(defined CONFIG_64BIT) && !(defined CONFIG_KTIME_SCALAR)");

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
typedef __int64_t_3  __s64_30;// L5
typedef __uint64_t_7  __u64_32;// L6

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
static inline __s64_30  (__ktime_set_34) (const long  __secs_33) {

if (__static_condition_default_36) {

{// L30
{



return ( __s64_30   )  __secs_33  * 1000000000L ;// L31
}
}// L32


}
}
__s64_30  (__ktime_add_ns_41) (__u64_32  __nsec_37) {

if (__static_condition_default_43) {

{// L35
{



__s64_30  __tmp_38;// L36

if (  __nsec_37  < 1000000000L )// L38
{
if (__static_condition_default_44) {

{// L38
{



 __tmp_38  =  __nsec_37  ; // L39
}
}// L40
}
}
else// L40
{
if (__static_condition_default_45) {

{// L40
{



unsigned long  __sec_40=  __nsec_37  / 1000000000L;// L41

 __tmp_38  =  __ktime_set_34  (( __s32_28   )  __sec_40 ) ; // L42
}
}// L43
}
}
return  __tmp_38  ;// L45
}
}// L46


}
}
static __u64_32  (__tick_nohz_stop_sched_tick_48) () {

if (__static_condition_default_50) {

{// L51
{



__u64_32  __time_delta_46= ( __u64_32   ) 7881299347898368000;// L52

__s64_30  __expires_47;// L53

if (__static_condition_default_31) {
__static_type_error("invalid declaration of expires under this presence condition");
}

if (__static_condition_default_51) {
if (  __time_delta_46  < ( ( __s64_30   ) ~ ( ( __u64_32   ) 1 << 63 ) ) )// L55
{
 __expires_47  = (  __time_delta_46  ) ; // L25:L56
}
else// L57
{
if (__static_condition_default_52) {
 __expires_47  = ( ( __s64_30   ) ~ ( ( __u64_32   ) 1 << 63 ) ) ; // L16:L58
}
}
}
if (__static_condition_default_53) {
__static_type_error("invalid type found in ifelse statement");
}
if (__static_condition_default_54) {
return  __expires_47  ;// L60
}
if (__static_condition_default_55) {
__static_type_error("invalid type found in return expression");
}
}
}// L61


}
}
static __u64_32  (__tick_nohz_stop_sched_tick_49) () {

if (__static_condition_default_56) {

{// L51
{



__u64_32  __time_delta_46= ( __u64_32   ) 7881299347898368000;// L52

__s64_30  __expires_47;// L53

if (__static_condition_default_31) {
__static_type_error("invalid declaration of expires under this presence condition");
}

if (__static_condition_default_57) {
if (  __time_delta_46  < ( ( __s64_30   ) ~ ( ( __u64_32   ) 1 << 63 ) ) )// L55
{
 __expires_47  =  __ktime_add_ns_41  ( __time_delta_46 ) ; // L56
}
else// L57
{
if (__static_condition_default_58) {
 __expires_47  = ( ( __s64_30   ) ~ ( ( __u64_32   ) 1 << 63 ) ) ; // L16:L58
}
}
}
if (__static_condition_default_59) {
__static_type_error("invalid type found in ifelse statement");
}
if (__static_condition_default_60) {
return  __expires_47  ;// L60
}
if (__static_condition_default_61) {
__static_type_error("invalid type found in return expression");
}
}
}// L61


}
}
int  (__main_64) (int  __argc_62, char  * (* (__argv_63))) {

{// L64
{



if (__static_condition_default_50) {
 __tick_nohz_stop_sched_tick_48 ( ) ; // L65
}
if (__static_condition_default_56) {
 __tick_nohz_stop_sched_tick_49 ( ) ; // L65
}
return 0 ;// L66
}
}// L67


}

