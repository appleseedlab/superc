#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_25;
extern const bool __static_condition_default_30;
extern const bool __static_condition_default_18;
extern const bool __static_condition_default_31;
extern const bool __static_condition_default_20;
extern const bool __static_condition_default_23;
extern const bool __static_condition_default_24;
extern const bool __static_condition_default_19;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_15;
extern const bool __static_condition_default_26;
extern const bool __static_condition_default_11;
extern const bool __static_condition_default_27;
extern const bool __static_condition_default_14;
void __static_initializer_default() {
__static_renaming("____assert_fail_4", "__assert_fail");
__static_renaming("__nondet_5", "nondet");
__static_renaming("___omap3_sram_configure_core_dpll_6", "_omap3_sram_configure_core_dpll");
__static_renaming("__omap3_configure_core_dpll_7", "omap3_configure_core_dpll");
__static_renaming("__some_int_9", "some_int");
__static_renaming("__omap3_sram_restore_context_10", "omap3_sram_restore_context");
__static_renaming("__omap3_core_dpll_m2_set_rate_12", "omap3_core_dpll_m2_set_rate");
__static_renaming("__omap3_core_dpll_m2_set_rate_13", "omap3_core_dpll_m2_set_rate");
__static_renaming("__v_16", "v");
__static_renaming("___omap2_init_reprogram_sdrc_17", "_omap2_init_reprogram_sdrc");
__static_renaming("__omap34xx_sram_init_21", "omap34xx_sram_init");
__static_renaming("__omap34xx_sram_init_22", "omap34xx_sram_init");
__static_renaming("__omap_sram_init_28", "omap_sram_init");
__static_renaming("__omap_sdrc_init_29", "omap_sdrc_init");
__static_renaming("__omap3pandora_init_32", "omap3pandora_init");
__static_renaming("__main_33", "main");

__static_condition_renaming("__static_condition_default_8", "(defined CONFIG_ARCH_OMAP3)");
__static_condition_renaming("__static_condition_default_11", "(defined CONFIG_ARCH_OMAP3) && (defined CONFIG_PM)");
__static_condition_renaming("__static_condition_default_14", "(defined CONFIG_ARCH_OMAP3) && !(defined CONFIG_PM)");
__static_condition_renaming("__static_condition_default_15", "(defined CONFIG_ARCH_OMAP3) && (defined CONFIG_PM)");
__static_condition_renaming("__static_condition_default_18", "(defined CONFIG_ARCH_OMAP3)");
__static_condition_renaming("__static_condition_default_19", "(defined CONFIG_ARCH_OMAP3) && !(defined CONFIG_PM)");
__static_condition_renaming("__static_condition_default_20", "(defined CONFIG_ARCH_OMAP3) && (defined CONFIG_PM)");
__static_condition_renaming("__static_condition_default_23", "!(defined CONFIG_ARCH_OMAP3)");
__static_condition_renaming("__static_condition_default_24", "(defined CONFIG_ARCH_OMAP3)");
__static_condition_renaming("__static_condition_default_25", "(defined CONFIG_ARCH_OMAP3) && (defined CONFIG_PM)");
__static_condition_renaming("__static_condition_default_26", "(defined CONFIG_ARCH_OMAP3) && !(defined CONFIG_PM)");
__static_condition_renaming("__static_condition_default_27", "(defined CONFIG_ARCH_OMAP3) && (defined CONFIG_PM)");
__static_condition_renaming("__static_condition_default_30", "!(defined CONFIG_ARCH_OMAP3)");
__static_condition_renaming("__static_condition_default_31", "(defined CONFIG_ARCH_OMAP3)");

};

extern void  (____assert_fail_4) (const char  * (____assertion_0), const char  * (____file_1), unsigned int  ____line_2, const char  * (____function_3));// L1:L3
int  (__nondet_5) () {

{
{



return 42 ;// L5
}
}


}
static int  * (___omap3_sram_configure_core_dpll_6);// L9
int  (__omap3_configure_core_dpll_7) () {

if (__static_condition_default_8) {

{
{



( (  ___omap3_sram_configure_core_dpll_6  ) ? ( void   ) ( 0 ) :  ____assert_fail_4  ("_omap3_sram_configure_core_dpll","63878ac.c",16, __PRETTY_FUNCTION__ ) ) ; // L13:L15
return *  ___omap3_sram_configure_core_dpll_6  ;// L16
}
}


}
}
static int  __some_int_9= 1;// L20
void  (__omap3_sram_restore_context_10) (void  ) {

if (__static_condition_default_11) {

{
{



 ___omap3_sram_configure_core_dpll_6  = &  __some_int_9  ; // L24
}
}


}
}
int  (__omap3_core_dpll_m2_set_rate_12) () {

if (__static_condition_default_14) {

{
{



 __omap3_configure_core_dpll_7 ( ) ; // L30
return 0 ;// L31
}
}


}
}
int  (__omap3_core_dpll_m2_set_rate_13) () {

if (__static_condition_default_15) {

{
{



 __omap3_configure_core_dpll_7 ( ) ; // L30
return 0 ;// L31
}
}


}
}
int  (___omap2_init_reprogram_sdrc_17) (void  ) {

if (__static_condition_default_18) {

{
{



int  __v_16;// L36

if (__static_condition_default_19) {
 __v_16  =  __omap3_core_dpll_m2_set_rate_12 ( ) ; // L38
}
if (__static_condition_default_20) {
 __v_16  =  __omap3_core_dpll_m2_set_rate_13 ( ) ; // L38
}
return  __v_16  ;// L40
}
}


}
}
int  (__omap34xx_sram_init_21) (void  ) {

if (__static_condition_default_23) {

{
{



return 0 ;// L49
}
}


}
}
int  (__omap34xx_sram_init_22) (void  ) {

if (__static_condition_default_24) {

{
{



if (__static_condition_default_25) {
 __omap3_sram_restore_context_10 ( ) ; // L47
}
if (__static_condition_default_26) {
return 0 ;// L49
}
if (__static_condition_default_27) {
return 0 ;// L49
}
}
}


}
}
int  (__omap_sram_init_28) (void  ) {

{
{



if (  __nondet_5 ( ) )// L54
{
if (__static_condition_default_23) {
 __omap34xx_sram_init_21 ( ) ; // L55
}
if (__static_condition_default_24) {
 __omap34xx_sram_init_22 ( ) ; // L55
}
}
return 0 ;// L57
}
}


}
void  (__omap_sdrc_init_29) () {

{
{



 __omap_sram_init_28 ( ) ; // L62
if (  __nondet_5 ( ) )// L64
{
if (__static_condition_default_30) {

{
{



}
}
}
if (__static_condition_default_31) {

{
{



 ___omap2_init_reprogram_sdrc_17 ( ) ; // L66
}
}
}
}
}
}


}
void  (__omap3pandora_init_32) (void  ) {

{
{



 __omap_sdrc_init_29 ( ) ; // L73
}
}


}
int  (__main_33) (void  ) {

{
{



 __omap3pandora_init_32 ( ) ; // L78
return 0 ;// L79
}
}


}

