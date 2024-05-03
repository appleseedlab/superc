#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_8;
void __static_initializer_default() {
__static_renaming("__apr_rmm_init_1", "apr_rmm_init");
__static_renaming("__rmm_lock_2", "rmm_lock");
__static_renaming("__util_ldap_cache_init_3", "util_ldap_cache_init");
__static_renaming("__main_6", "main");
__static_renaming("__main_7", "main");

__static_condition_renaming("__static_condition_default_4", "(defined APU_HAS_LDAP) && !(defined APR_HAS_SHARED_MEMORY)");
__static_condition_renaming("__static_condition_default_5", "(defined APU_HAS_LDAP) && (defined APR_HAS_SHARED_MEMORY)");
__static_condition_renaming("__static_condition_default_8", "!(defined APU_HAS_LDAP)");
__static_condition_renaming("__static_condition_default_9", "(defined APU_HAS_LDAP)");

};

void  (__apr_rmm_init_1) (char  * (__rmm_lock_0)) {

{
{



__static_type_error("type error : no valid expression"); // L5
}
}


}
void  (__util_ldap_cache_init_3) () {

{
if (__static_condition_default_4) {

{
{



char  * (__rmm_lock_2);// L11

}
}


}

if (__static_condition_default_5) {

{
{



char  * (__rmm_lock_2);// L11

 __apr_rmm_init_1  ( __rmm_lock_2 ) ; // L14
}
}


}

}}
int  (__main_6) (void  ) {

if (__static_condition_default_8) {

{
{



return 0 ;// L24
}
}


}
}
int  (__main_7) (void  ) {

if (__static_condition_default_9) {

{
{



 __util_ldap_cache_init_3 ( ) ; // L22
return 0 ;// L24
}
}


}
}

