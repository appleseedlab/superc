#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_22;
extern const bool __static_condition_default_34;
extern const bool __static_condition_default_23;
extern const bool __static_condition_default_74;
extern const bool __static_condition_default_42;
extern const bool __static_condition_default_83;
extern const bool __static_condition_default_77;
extern const bool __static_condition_default_24;
extern const bool __static_condition_default_60;
extern const bool __static_condition_default_32;
extern const bool __static_condition_default_58;
extern const bool __static_condition_default_41;
extern const bool __static_condition_default_57;
extern const bool __static_condition_default_33;
extern const bool __static_condition_default_48;
extern const bool __static_condition_default_65;
extern const bool __static_condition_default_70;
extern const bool __static_condition_default_69;
extern const bool __static_condition_default_67;
extern const bool __static_condition_default_68;
extern const bool __static_condition_default_40;
extern const bool __static_condition_default_75;
extern const bool __static_condition_default_25;
extern const bool __static_condition_default_47;
extern const bool __static_condition_default_59;
extern const bool __static_condition_default_81;
extern const bool __static_condition_default_39;
extern const bool __static_condition_default_76;
extern const bool __static_condition_default_66;
extern const bool __static_condition_default_72;
void __static_initializer_default() {
__static_renaming("____assert_fail_4", "__assert_fail");
__static_renaming("____assert_perror_fail_9", "__assert_perror_fail");
__static_renaming("____assert_13", "__assert");
__static_renaming("__gfp_t_14", "gfp_t");
__static_renaming("__gfp_t_15", "gfp_t");
__static_renaming("__irqs_disabled_16", "irqs_disabled");
__static_renaming("__local_irq_disable_17", "local_irq_disable");
__static_renaming("____lockdep_trace_alloc_20", "__lockdep_trace_alloc");
__static_renaming("____lockdep_trace_alloc_21", "__lockdep_trace_alloc");
__static_renaming("__lockdep_trace_alloc_29", "lockdep_trace_alloc");
__static_renaming("__lockdep_trace_alloc_30", "lockdep_trace_alloc");
__static_renaming("__lockdep_trace_alloc_31", "lockdep_trace_alloc");
__static_renaming("____cache_alloc_node_37", "__cache_alloc_node");
__static_renaming("____cache_alloc_node_38", "__cache_alloc_node");
__static_renaming("__kmem_cache_alloc_node_45", "kmem_cache_alloc_node");
__static_renaming("__kmem_cache_alloc_node_46", "kmem_cache_alloc_node");
__static_renaming("__kmem_cache_alloc_node_notrace_53", "kmem_cache_alloc_node_notrace");
__static_renaming("__kmem_cache_alloc_node_notrace_54", "kmem_cache_alloc_node_notrace");
__static_renaming("__kmem_cache_alloc_node_notrace_55", "kmem_cache_alloc_node_notrace");
__static_renaming("__kmem_cache_alloc_node_notrace_56", "kmem_cache_alloc_node_notrace");
__static_renaming("__kmalloc_node_63", "kmalloc_node");
__static_renaming("__kmalloc_node_64", "kmalloc_node");
__static_renaming("__kmalloc_node_71", "kmalloc_node");
__static_renaming("__setup_cpu_cache_73", "setup_cpu_cache");
__static_renaming("__kmem_cache_create_78", "kmem_cache_create");
__static_renaming("__kmem_cache_init_79", "kmem_cache_init");
__static_renaming("__kmem_cache_init_80", "kmem_cache_init");
__static_renaming("__mm_init_82", "mm_init");
__static_renaming("__main_84", "main");

__static_condition_renaming("__static_condition_default_22", "(defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && !(defined NDEBUG) && (defined _ASSERT_H_DECLS) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && (defined NDEBUG)");
__static_condition_renaming("__static_condition_default_23", "(defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && (defined NDEBUG)");
__static_condition_renaming("__static_condition_default_24", "(defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && !(defined NDEBUG) && (defined _ASSERT_H_DECLS)");
__static_condition_renaming("__static_condition_default_25", "(defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && !(defined NDEBUG) && !(defined _ASSERT_H_DECLS)");
__static_condition_renaming("__static_condition_default_32", "(defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && !(defined NDEBUG) && (defined _ASSERT_H_DECLS) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && (defined NDEBUG)");
__static_condition_renaming("__static_condition_default_33", "(defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && !(defined NDEBUG) && !(defined _ASSERT_H_DECLS)");
__static_condition_renaming("__static_condition_default_34", "!(defined CONFIG_LOCKDEP) || (defined CONFIG_LOCKDEP) && !(defined CONFIG_TRACE_IRQFLAGS) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && !(defined CONFIG_PROVE_LOCKING)");
__static_condition_renaming("__static_condition_default_39", "!(defined CONFIG_LOCKDEP) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) || (defined CONFIG_LOCKDEP) && !(defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && !(defined CONFIG_PROVE_LOCKING) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && !(defined NDEBUG) && (defined _ASSERT_H_DECLS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && (defined NDEBUG) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA)");
__static_condition_renaming("__static_condition_default_40", "(defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && !(defined NDEBUG) && (defined _ASSERT_H_DECLS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && (defined NDEBUG) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA)");
__static_condition_renaming("__static_condition_default_41", "!(defined CONFIG_LOCKDEP) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) || (defined CONFIG_LOCKDEP) && !(defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && !(defined CONFIG_PROVE_LOCKING) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA)");
__static_condition_renaming("__static_condition_default_42", "(defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && !(defined NDEBUG) && !(defined _ASSERT_H_DECLS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA)");
__static_condition_renaming("__static_condition_default_47", "!(defined CONFIG_LOCKDEP) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) || (defined CONFIG_LOCKDEP) && !(defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && !(defined CONFIG_PROVE_LOCKING) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && !(defined NDEBUG) && (defined _ASSERT_H_DECLS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && (defined NDEBUG) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA)");
__static_condition_renaming("__static_condition_default_48", "(defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && !(defined NDEBUG) && !(defined _ASSERT_H_DECLS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA)");
__static_condition_renaming("__static_condition_default_57", "!(defined CONFIG_LOCKDEP) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) && (defined CONFIG_KMEMTRACE) || (defined CONFIG_LOCKDEP) && !(defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) && (defined CONFIG_KMEMTRACE) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && !(defined CONFIG_PROVE_LOCKING) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) && (defined CONFIG_KMEMTRACE) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && !(defined NDEBUG) && (defined _ASSERT_H_DECLS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) && (defined CONFIG_KMEMTRACE) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && (defined NDEBUG) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) && (defined CONFIG_KMEMTRACE)");
__static_condition_renaming("__static_condition_default_58", "(defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && !(defined NDEBUG) && !(defined _ASSERT_H_DECLS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) && (defined CONFIG_KMEMTRACE)");
__static_condition_renaming("__static_condition_default_59", "!(defined CONFIG_LOCKDEP) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) && !(defined CONFIG_KMEMTRACE) || (defined CONFIG_LOCKDEP) && !(defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) && !(defined CONFIG_KMEMTRACE) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && !(defined CONFIG_PROVE_LOCKING) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) && !(defined CONFIG_KMEMTRACE) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && !(defined NDEBUG) && (defined _ASSERT_H_DECLS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) && !(defined CONFIG_KMEMTRACE) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && (defined NDEBUG) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) && !(defined CONFIG_KMEMTRACE)");
__static_condition_renaming("__static_condition_default_60", "(defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && !(defined NDEBUG) && !(defined _ASSERT_H_DECLS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) && !(defined CONFIG_KMEMTRACE)");
__static_condition_renaming("__static_condition_default_65", "!(defined CONFIG_LOCKDEP) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) || (defined CONFIG_LOCKDEP) && !(defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && !(defined CONFIG_PROVE_LOCKING) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && !(defined NDEBUG) && (defined _ASSERT_H_DECLS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && (defined NDEBUG) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA)");
__static_condition_renaming("__static_condition_default_66", "!(defined CONFIG_LOCKDEP) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) && (defined CONFIG_KMEMTRACE) || (defined CONFIG_LOCKDEP) && !(defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) && (defined CONFIG_KMEMTRACE) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && !(defined CONFIG_PROVE_LOCKING) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) && (defined CONFIG_KMEMTRACE) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && !(defined NDEBUG) && (defined _ASSERT_H_DECLS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) && (defined CONFIG_KMEMTRACE) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && (defined NDEBUG) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) && (defined CONFIG_KMEMTRACE)");
__static_condition_renaming("__static_condition_default_67", "!(defined CONFIG_LOCKDEP) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) && !(defined CONFIG_KMEMTRACE) || (defined CONFIG_LOCKDEP) && !(defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) && !(defined CONFIG_KMEMTRACE) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && !(defined CONFIG_PROVE_LOCKING) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) && !(defined CONFIG_KMEMTRACE) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && !(defined NDEBUG) && (defined _ASSERT_H_DECLS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) && !(defined CONFIG_KMEMTRACE) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && (defined NDEBUG) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) && !(defined CONFIG_KMEMTRACE)");
__static_condition_renaming("__static_condition_default_68", "(defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && !(defined NDEBUG) && !(defined _ASSERT_H_DECLS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA)");
__static_condition_renaming("__static_condition_default_69", "(defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && !(defined NDEBUG) && !(defined _ASSERT_H_DECLS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) && (defined CONFIG_KMEMTRACE)");
__static_condition_renaming("__static_condition_default_70", "(defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && !(defined NDEBUG) && !(defined _ASSERT_H_DECLS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) && !(defined CONFIG_KMEMTRACE)");
__static_condition_renaming("__static_condition_default_72", "(defined CONFIG_SLAB) && !(defined CONFIG_NUMA)");
__static_condition_renaming("__static_condition_default_74", "(defined CONFIG_SLAB)");
__static_condition_renaming("__static_condition_default_75", "!(defined CONFIG_LOCKDEP) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) || (defined CONFIG_LOCKDEP) && !(defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && !(defined CONFIG_PROVE_LOCKING) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && !(defined NDEBUG) && (defined _ASSERT_H_DECLS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA) || (defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && (defined NDEBUG) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA)");
__static_condition_renaming("__static_condition_default_76", "(defined CONFIG_LOCKDEP) && (defined CONFIG_TRACE_IRQFLAGS) && (defined CONFIG_PROVE_LOCKING) && !(defined NDEBUG) && !(defined _ASSERT_H_DECLS) && (defined CONFIG_SLAB) && (defined CONFIG_NUMA)");
__static_condition_renaming("__static_condition_default_77", "(defined CONFIG_SLAB) && !(defined CONFIG_NUMA)");
__static_condition_renaming("__static_condition_default_81", "!(defined CONFIG_SLAB)");
__static_condition_renaming("__static_condition_default_83", "!(defined CONFIG_SLAB)");

};
typedef int  __gfp_t_14;// L18
typedef int  __gfp_t_15;// L18

extern void  (____assert_fail_4) (const char  * (____assertion_0), const char  * (____file_1), unsigned int  ____line_2, const char  * (____function_3));// L69:L71
extern void  (____assert_perror_fail_9) (int  ____errnum_5, const char  * (____file_6), unsigned int  ____line_7, const char  * (____function_8));// L74:L76
extern void  (____assert_13) (const char  * (____assertion_10), const char  * (____file_11), int  ____line_12);// L81:L82
// typedef moved to top of scope
// typedef moved to top of scope
_Bool  __irqs_disabled_16= 0;// L20:L33
void  (__local_irq_disable_17) (void  ) {

{// L23
{



 __irqs_disabled_16  = 1 ; // L24:L34
}
}// L25


}
static void  (____lockdep_trace_alloc_20) (__gfp_t_14  __gfp_mask_18) {

if (__static_condition_default_22) {

{// L29
{



if ( ! (  __gfp_mask_18  & ( ( __gfp_t_14   ) 0x10u ) ) )// L30
{
return  ;// L31
}
if ( ! (  __gfp_mask_18  & ( ( __gfp_t_14   ) 0x80u ) ) )// L33
{
return  ;// L34
}
if (__static_condition_default_23) {
( ( void   ) ( 0 ) ) ; // L36:L50
}
if (__static_condition_default_24) {
__static_type_error("type error") ; // L36:L91
}
}
}// L37


}
}
static void  (____lockdep_trace_alloc_21) (__gfp_t_15  __gfp_mask_19) {

if (__static_condition_default_25) {

{// L29
{



if ( ! (  __gfp_mask_19  & ( ( __gfp_t_15   ) 0x10u ) ) )// L30
{
return  ;// L31
}
if ( ! (  __gfp_mask_19  & ( ( __gfp_t_15   ) 0x80u ) ) )// L33
{
return  ;// L34
}
( ( !  __irqs_disabled_16  ) ? ( void   ) ( 0 ) :  ____assert_fail_4  ("!irqs_disabled","/home/kisamefishfry/Documents/xtc-dev/fonda/cpp_testsuite/varBugs/LINUX/eb91f1d0a53.c",36, __PRETTY_FUNCTION__ ) ) ; // L36:L91
}
}// L37


}
}
void  (__lockdep_trace_alloc_29) (__gfp_t_14  __gfp_mask_26) {

{
if (__static_condition_default_32) {

{// L40
{



 ____lockdep_trace_alloc_20  ( __gfp_mask_26 ) ; // L41
}
}// L42


}

}}
void  (__lockdep_trace_alloc_30) (__gfp_t_15  __gfp_mask_27) {

{
if (__static_condition_default_33) {

{// L40
{



 ____lockdep_trace_alloc_21  ( __gfp_mask_27 ) ; // L41
}
}// L42


}

}}
void  (__lockdep_trace_alloc_31) (__gfp_t_14  __gfp_mask_28) {

{
if (__static_condition_default_34) {

{// L45
{



}
}// L46


}

}}
void  (____cache_alloc_node_37) (__gfp_t_14  __flags_35) {

if (__static_condition_default_39) {

{// L53
{



if (__static_condition_default_40) {
 __lockdep_trace_alloc_29  ( __flags_35 ) ; // L54
}
if (__static_condition_default_41) {
 __lockdep_trace_alloc_31  ( __flags_35 ) ; // L54
}
}
}// L55


}
}
void  (____cache_alloc_node_38) (__gfp_t_15  __flags_36) {

if (__static_condition_default_42) {

{// L53
{



 __lockdep_trace_alloc_30  ( __flags_36 ) ; // L54
}
}// L55


}
}
void  (__kmem_cache_alloc_node_45) (__gfp_t_14  __flags_43) {

if (__static_condition_default_47) {

{// L58
{



 ____cache_alloc_node_37  ( __flags_43 ) ; // L59
}
}// L60


}
}
void  (__kmem_cache_alloc_node_46) (__gfp_t_15  __flags_44) {

if (__static_condition_default_48) {

{// L58
{



 ____cache_alloc_node_38  ( __flags_44 ) ; // L59
}
}// L60


}
}
void  (__kmem_cache_alloc_node_notrace_53) (__gfp_t_14  __flags_49) {

{
if (__static_condition_default_57) {

{// L64
{



 ____cache_alloc_node_37  ( __flags_49 ) ; // L65
}
}// L66


}

}}
void  (__kmem_cache_alloc_node_notrace_54) (__gfp_t_15  __flags_50) {

{
if (__static_condition_default_58) {

{// L64
{



 ____cache_alloc_node_38  ( __flags_50 ) ; // L65
}
}// L66


}

}}
void  (__kmem_cache_alloc_node_notrace_55) (__gfp_t_14  __flags_51) {

{
if (__static_condition_default_59) {

{// L69
{



 __kmem_cache_alloc_node_45  ( __flags_51 ) ; // L70
}
}// L71


}

}}
void  (__kmem_cache_alloc_node_notrace_56) (__gfp_t_15  __flags_52) {

{
if (__static_condition_default_60) {

{// L69
{



 __kmem_cache_alloc_node_46  ( __flags_52 ) ; // L70
}
}// L71


}

}}
static void  (__kmalloc_node_63) (__gfp_t_14  __gfp_mask_61) {

if (__static_condition_default_65) {

{// L78
{



if (__static_condition_default_66) {
 __kmem_cache_alloc_node_notrace_53  ( __gfp_mask_61 ) ; // L79
}
if (__static_condition_default_67) {
 __kmem_cache_alloc_node_notrace_55  ( __gfp_mask_61 ) ; // L79
}
}
}// L80


}
}
static void  (__kmalloc_node_64) (__gfp_t_15  __gfp_mask_62) {

if (__static_condition_default_68) {

{// L78
{



if (__static_condition_default_69) {
 __kmem_cache_alloc_node_notrace_54  ( __gfp_mask_62 ) ; // L79
}
if (__static_condition_default_70) {
 __kmem_cache_alloc_node_notrace_56  ( __gfp_mask_62 ) ; // L79
}
}
}// L80


}
}
void  (__kmalloc_node_71) () {

if (__static_condition_default_72) {

{// L85
{



return  ;// L86
}
}// L87


}
}
static int  (__setup_cpu_cache_73) () {

if (__static_condition_default_74) {

{// L91
{



if (__static_condition_default_75) {
 __kmalloc_node_63  (( ( ( __gfp_t_14   ) 0x10u ) | ( ( __gfp_t_14   ) 0x40u ) | ( ( __gfp_t_14   ) 0x80u ) )) ; // L92
}
if (__static_condition_default_76) {
 __kmalloc_node_64  (( ( ( __gfp_t_15   ) 0x10u ) | ( ( __gfp_t_15   ) 0x40u ) | ( ( __gfp_t_15   ) 0x80u ) )) ; // L92
}
if (__static_condition_default_77) {
__static_type_error("type error") ; // L92
}
}
}// L93


}
}
void  (__kmem_cache_create_78) () {

if (__static_condition_default_74) {

{// L96
{



 __setup_cpu_cache_73 ( ) ; // L97
}
}// L98


}
}
void  (__kmem_cache_init_79) (void  ) {

{
if (__static_condition_default_74) {

{// L101
{



 __kmem_cache_create_78 ( ) ; // L103
}
}// L105


}

}}
void  (__kmem_cache_init_80) (void  ) {

{
if (__static_condition_default_81) {

{// L108
{



}
}// L109


}

}}
static void  (__mm_init_82) (void  ) {

{// L113
{



if (__static_condition_default_74) {
 __kmem_cache_init_79 ( ) ; // L114
}
if (__static_condition_default_83) {
 __kmem_cache_init_80 ( ) ; // L114
}
}
}// L115


}
int  (__main_84) () {

{// L118
{



 __local_irq_disable_17 ( ) ; // L119
 __mm_init_82 ( ) ; // L120
return 0 ;// L121
}
}// L122


}

