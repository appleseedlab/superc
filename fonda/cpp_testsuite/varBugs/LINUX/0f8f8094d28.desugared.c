#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_0;
extern const bool __static_condition_default_14;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_2;
extern const bool __static_condition_default_11;
extern const bool __static_condition_default_1;
extern const bool __static_condition_default_13;
void __static_initializer_default() {
__static_renaming("__i_3", "i");
__static_renaming("__init_node_lock_keys_5", "init_node_lock_keys");
__static_renaming("__init_node_lock_keys_6", "init_node_lock_keys");
__static_renaming("__init_lock_keys_8", "init_lock_keys");
__static_renaming("__init_lock_keys_9", "init_lock_keys");
__static_renaming("__kmem_cache_init_late_10", "kmem_cache_init_late");
__static_renaming("__main_12", "main");

__static_condition_renaming("__static_condition_default_0", "(defined CONFIG_FORCE_MAX_ZONEORDER) && (defined CONFIG_SLAB) && !(defined CONFIG_SLOB)");
__static_condition_renaming("__static_condition_default_1", "!(defined CONFIG_SLAB) && !(defined CONFIG_SLOB)");
__static_condition_renaming("__static_condition_default_2", "!(defined CONFIG_FORCE_MAX_ZONEORDER) && (defined CONFIG_SLAB) && !(defined CONFIG_SLOB)");
__static_condition_renaming("__static_condition_default_4", "(defined CONFIG_LOCKDEP)");
__static_condition_renaming("__static_condition_default_7", "!(defined CONFIG_LOCKDEP)");
__static_condition_renaming("__static_condition_default_11", "!(defined CONFIG_LOCKDEP)");
__static_condition_renaming("__static_condition_default_13", "!(defined CONFIG_SLOB)");
__static_condition_renaming("__static_condition_default_14", "(defined CONFIG_SLOB)");

};

static void  (__init_node_lock_keys_5) () {

if (__static_condition_default_4) {

{// L31
{



int  __i_3;// L32

__static_type_error("no valid type in iterationstatement (3)");
}
}// L43


}
}
int  (__init_node_lock_keys_6) () {

if (__static_condition_default_7) {

{// L51
{



}
}// L52


}
}
void  (__init_lock_keys_8) (void  ) {

{
if (__static_condition_default_4) {

{// L46
{



 __init_node_lock_keys_5 ( ) ; // L47
}
}// L48


}

}}
void  (__init_lock_keys_9) (void  ) {

{
if (__static_condition_default_7) {

{// L55
{



}
}// L56


}

}}
void  (__kmem_cache_init_late_10) (void  ) {

{// L60
{



if (__static_condition_default_4) {
 __init_lock_keys_8 ( ) ; // L61
}
if (__static_condition_default_11) {
 __init_lock_keys_9 ( ) ; // L61
}
}
}// L62


}
int  (__main_12) (void  ) {

{// L65
{



if (__static_condition_default_13) {
 __kmem_cache_init_late_10 ( ) ; // L67
}
if (__static_condition_default_14) {
return 0 ;// L69
}
if (__static_condition_default_13) {
return 0 ;// L69
}
}
}// L70


}

