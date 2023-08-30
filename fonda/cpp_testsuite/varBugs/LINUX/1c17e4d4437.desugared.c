#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_11;
extern const bool __static_condition_default_24;
extern const bool __static_condition_default_23;
extern const bool __static_condition_default_19;
extern const bool __static_condition_default_12;
extern const bool __static_condition_default_18;
extern const bool __static_condition_default_20;
extern const bool __static_condition_default_21;
void __static_initializer_default() {
__static_renaming("__printf_1", "printf");
__static_renaming("__sprintf_4", "sprintf");
__static_renaming("__print_cpu_stall_fast_no_hz_9", "print_cpu_stall_fast_no_hz");
__static_renaming("__print_cpu_stall_fast_no_hz_10", "print_cpu_stall_fast_no_hz");
__static_renaming("__fast_no_hz_14", "fast_no_hz");
__static_renaming("__print_cpu_stall_info_16", "print_cpu_stall_info");
__static_renaming("__print_cpu_stall_info_17", "print_cpu_stall_info");
__static_renaming("__main_22", "main");

__static_condition_renaming("__static_condition_default_11", "(defined CONFIG_RCU_CPU_STALL_INFO) && (defined CONFIG_RCU_FAST_NO_HZ)");
__static_condition_renaming("__static_condition_default_12", "(defined CONFIG_RCU_CPU_STALL_INFO) && !(defined CONFIG_RCU_FAST_NO_HZ)");
__static_condition_renaming("__static_condition_default_18", "(defined CONFIG_RCU_CPU_STALL_INFO)");
__static_condition_renaming("__static_condition_default_19", "(defined CONFIG_RCU_CPU_STALL_INFO) && (defined CONFIG_RCU_FAST_NO_HZ)");
__static_condition_renaming("__static_condition_default_20", "(defined CONFIG_RCU_CPU_STALL_INFO) && !(defined CONFIG_RCU_FAST_NO_HZ)");
__static_condition_renaming("__static_condition_default_21", "!(defined CONFIG_RCU_CPU_STALL_INFO)");
__static_condition_renaming("__static_condition_default_23", "!(defined CONFIG_RCU_CPU_STALL_INFO)");
__static_condition_renaming("__static_condition_default_24", "(defined CONFIG_RCU_CPU_STALL_INFO)");

};

extern int  (__printf_1) (const char  * __restrict  ____format_0,  ... );// L1
extern int  (__sprintf_4) (char  * __restrict  ____s_2, const char  * __restrict  ____format_3,  ... );// L3:L4
void  (__print_cpu_stall_fast_no_hz_9) (char  * (__cp_5), int  __cpu_6) {

{
if (__static_condition_default_11) {

{// L10
{



 __sprintf_4  ( __cp_5 ,"foobar") ; // L11
}
}// L12


}

}}
void  (__print_cpu_stall_fast_no_hz_10) (char  * (__cp_7), int  __cpu_8) {

{
if (__static_condition_default_12) {

{// L15
{



}
}// L16


}

}}
void  (__print_cpu_stall_info_16) (int  __cpu_13) {

{
if (__static_condition_default_18) {

{// L20
{



char  __fast_no_hz_14[72];// L21

if (__static_condition_default_19) {
 __print_cpu_stall_fast_no_hz_9  ( __fast_no_hz_14 , __cpu_13 ) ; // L23
}
if (__static_condition_default_20) {
 __print_cpu_stall_fast_no_hz_10  ( __fast_no_hz_14 , __cpu_13 ) ; // L23
}
 __printf_1  ("\t%d: %s\n", __cpu_13 , __fast_no_hz_14 ) ; // L24
}
}// L25


}

}}
void  (__print_cpu_stall_info_17) (int  __cpu_15) {

{
if (__static_condition_default_21) {

{// L28
{



 __printf_1  (" %d", __cpu_15 ) ; // L29
}
}// L30


}

}}
int  (__main_22) (void  ) {

{// L34
{



if (__static_condition_default_18) {
 __print_cpu_stall_info_16  (0) ; // L36
}
if (__static_condition_default_23) {
return 0 ;// L38
}
if (__static_condition_default_24) {
return 0 ;// L38
}
}
}// L39


}

