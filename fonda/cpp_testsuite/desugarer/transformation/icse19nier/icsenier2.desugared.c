#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_9;
extern const bool __static_condition_default_8;
void __static_initializer_default() {
__static_renaming("__main_5", "main");
__static_renaming("__var_6", "var");
__static_renaming("__var_7", "var");

__static_condition_renaming("__static_condition_default_8", "(defined CONFIG_QUOTA)");
__static_condition_renaming("__static_condition_default_9", "!(defined CONFIG_QUOTA)");

};
struct __t_0 {
int  __i_inline_size_1;
};
struct __t_2 {
int  __i_inline_size_3;
int  __i_reserved_quota_4;
};

struct __t_0 ;struct __t_2 ;
int  __main_5 () {
{
struct __t_0  __var_6;
struct __t_2  __var_7;

{
if (__static_condition_default_8) {
 __var_7  . __i_reserved_quota_4 = 1 ;

}

if (__static_condition_default_9) {
__static_type_error("type error") ;

}

}}


}

