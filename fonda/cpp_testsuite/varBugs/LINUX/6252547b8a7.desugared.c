#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_14;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_15;
extern const bool __static_condition_default_16;
void __static_initializer_default() {
__static_renaming("__irq_domain_simple_ops_0", "irq_domain_simple_ops");
__static_renaming("__irq_2", "irq");
__static_renaming("__irq_domain_add_3", "irq_domain_add");
__static_renaming("__ops_5", "ops");
__static_renaming("__twl_probe_6", "twl_probe");
__static_renaming("__main_11", "main");
__static_renaming("__main_12", "main");
__static_renaming("__main_13", "main");

__static_condition_renaming("__static_condition_default_4", "!(defined CONFIG_TWL4030_CORE) && (defined CONFIG_IRQ_DOMAIN) || (defined CONFIG_TWL4030_CORE)");
__static_condition_renaming("__static_condition_default_7", "(defined CONFIG_TWL4030_CORE)");
__static_condition_renaming("__static_condition_default_8", "(defined CONFIG_TWL4030_CORE) && (defined CONFIG_OF_IRQ)");
__static_condition_renaming("__static_condition_default_9", "(defined CONFIG_TWL4030_CORE) && !(defined CONFIG_OF_IRQ)");
__static_condition_renaming("__static_condition_default_10", "(defined CONFIG_TWL4030_CORE) && (defined CONFIG_OF_IRQ)");
__static_condition_renaming("__static_condition_default_14", "!(defined CONFIG_TWL4030_CORE) && (defined CONFIG_IRQ_DOMAIN)");
__static_condition_renaming("__static_condition_default_15", "(defined CONFIG_TWL4030_CORE)");
__static_condition_renaming("__static_condition_default_16", "!(defined CONFIG_TWL4030_CORE) && !(defined CONFIG_IRQ_DOMAIN)");

};

int  __irq_domain_simple_ops_0= 1;// L8
void  (__irq_domain_add_3) (int  * (__ops_1)) {

if (__static_condition_default_4) {

{// L11
{



int  __irq_2= *  __ops_1 ;// L12

}
}// L13


}
}
int  (__twl_probe_6) () {

if (__static_condition_default_7) {

{// L18
{



int  * (__ops_5)= ( void  * ) 0;// L19

if (__static_condition_default_8) {
 __ops_5  = &  __irq_domain_simple_ops_0  ; // L22
}
if (__static_condition_default_9) {
 __irq_domain_add_3  ( __ops_5 ) ; // L25
}
if (__static_condition_default_10) {
 __irq_domain_add_3  ( __ops_5 ) ; // L25
}
}
}// L26


}
}
int  (__main_11) () {

if (__static_condition_default_14) {

{// L30
{



return 0 ;// L34
}
}// L35


}
}
int  (__main_12) () {

if (__static_condition_default_15) {

{// L30
{



 __twl_probe_6 ( ) ; // L32
return 0 ;// L34
}
}// L35


}
}
int  (__main_13) () {

if (__static_condition_default_16) {

{// L30
{



return 0 ;// L34
}
}// L35


}
}

