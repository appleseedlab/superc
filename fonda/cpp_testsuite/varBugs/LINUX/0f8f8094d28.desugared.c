#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_2;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_1;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_11;
extern const bool __static_condition_default_0;
void __static_initializer_default() {
__static_renaming("__init_node_lock_keys_3", "init_node_lock_keys");
__static_renaming("__init_node_lock_keys_4", "init_node_lock_keys");
__static_renaming("__init_lock_keys_7", "init_lock_keys");
__static_renaming("__kmem_cache_init_late_8", "kmem_cache_init_late");
__static_renaming("__main_9", "main");

__static_condition_renaming("__static_condition_default_0", "(defined CONFIG_FORCE_MAX_ZONEORDER) && (defined CONFIG_SLAB) && !(defined CONFIG_SLOB)");
__static_condition_renaming("__static_condition_default_1", "!(defined CONFIG_FORCE_MAX_ZONEORDER) && (defined CONFIG_SLAB) && !(defined CONFIG_SLOB)");
__static_condition_renaming("__static_condition_default_2", "!(defined CONFIG_SLAB) && !(defined CONFIG_SLOB)");
__static_condition_renaming("__static_condition_default_5", "(defined CONFIG_SLOB)");
__static_condition_renaming("__static_condition_default_6", "!(defined CONFIG_SLOB)");
__static_condition_renaming("__static_condition_default_10", "!(defined CONFIG_SLOB)");
__static_condition_renaming("__static_condition_default_11", "(defined CONFIG_SLOB)");

};

int  (__init_node_lock_keys_3) () {

if (__static_condition_default_5) {

{
{



}
}


}
}
int  (__init_node_lock_keys_4) () {

if (__static_condition_default_6) {

{
{



}
}


}
}
void  (__init_lock_keys_7) (void  ) {

{
{



}
}


}
void  (__kmem_cache_init_late_8) (void  ) {

{
{



 __init_lock_keys_7 ( ) ; // L61
}
}


}
int  (__main_9) (void  ) {

{
{



if (__static_condition_default_10) {
 __kmem_cache_init_late_8 ( ) ; // L67
}
if (__static_condition_default_11) {
return 0 ;// L69
}
if (__static_condition_default_10) {
return 0 ;// L69
}
}
}


}

