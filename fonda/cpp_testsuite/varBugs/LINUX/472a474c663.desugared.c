#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
extern const bool __static_condition_default_14;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_15;
void __static_initializer_default() {
__static_renaming("__nondet_0", "nondet");
__static_renaming("__smp_found_config_1", "smp_found_config");
__static_renaming("__c_2", "c");
__static_renaming("__ptr_3", "ptr");
__static_renaming("__enable_IR_x2apic_4", "enable_IR_x2apic");
__static_renaming("__enable_IR_x2apic_5", "enable_IR_x2apic");
__static_renaming("__APIC_init_uniprocessor_8", "APIC_init_uniprocessor");
__static_renaming("__smp_sanity_check_9", "smp_sanity_check");
__static_renaming("__native_smp_prepare_cpus_11", "native_smp_prepare_cpus");
__static_renaming("__main_12", "main");
__static_renaming("__main_13", "main");

__static_condition_renaming("__static_condition_default_6", "!(defined CONFIG_SMP)");
__static_condition_renaming("__static_condition_default_7", "(defined CONFIG_SMP)");
__static_condition_renaming("__static_condition_default_10", "(defined CONFIG_SMP)");
__static_condition_renaming("__static_condition_default_14", "!(defined CONFIG_SMP)");
__static_condition_renaming("__static_condition_default_15", "(defined CONFIG_SMP)");

};

int  (__nondet_0) () {

{// L3
{



return 0 ;// L3
}
}// L3


}
int  __smp_found_config_1;// L6
void  (__enable_IR_x2apic_4) (void  ) {

if (__static_condition_default_6) {

{// L10
{



static char  __c_2;// L11

static char  * (__ptr_3)= &  __c_2 ;// L12

*  __ptr_3  = 'a' ; // L14
if (  __ptr_3  )// L15
{
 __ptr_3  = ( void  * ) 0 ; // L1:L16
}
}
}// L17


}
}
void  (__enable_IR_x2apic_5) (void  ) {

if (__static_condition_default_7) {

{// L10
{



static char  __c_2;// L11

static char  * (__ptr_3)= &  __c_2 ;// L12

*  __ptr_3  = 'a' ; // L14
if (  __ptr_3  )// L15
{
 __ptr_3  = ( void  * ) 0 ; // L1:L16
}
}
}// L17


}
}
int  (__APIC_init_uniprocessor_8) (void  ) {

{// L20
{



if (__static_condition_default_6) {
 __enable_IR_x2apic_4 ( ) ; // L21
}
if (__static_condition_default_7) {
 __enable_IR_x2apic_5 ( ) ; // L21
}
}
}// L22


}
int  (__smp_sanity_check_9) () {

if (__static_condition_default_10) {

{// L26
{



if ( !  __smp_found_config_1  )// L27
{
 __APIC_init_uniprocessor_8 ( ) ; // L28
}
return 0 ;// L29
}
}// L30


}
}
void  (__native_smp_prepare_cpus_11) () {

if (__static_condition_default_10) {

{// L33
{



 __enable_IR_x2apic_5 ( ) ; // L34
 __smp_sanity_check_9 ( ) ; // L35
}
}// L36


}
}
int  (__main_12) (void  ) {

if (__static_condition_default_14) {

{// L40
{



return 0 ;// L45
}
}// L46


}
}
int  (__main_13) (void  ) {

if (__static_condition_default_15) {

{// L40
{



 __smp_found_config_1  =  __nondet_0 ( ) ; // L42
 __native_smp_prepare_cpus_11 ( ) ; // L43
return 0 ;// L45
}
}// L46


}
}

