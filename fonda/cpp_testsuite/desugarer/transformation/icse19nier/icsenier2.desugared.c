#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
extern const bool __static_condition_default_8;
void __static_initializer_default() {
__static_renaming("__main_4", "main");
__static_renaming("__var_5", "var");
__static_renaming("__var_6", "var");

__static_condition_renaming("__static_condition_default_7", "(defined CONFIG_QUOTA)");
__static_condition_renaming("__static_condition_default_8", "!(defined CONFIG_QUOTA)");

};
struct __t_0 {
};
struct __t_1 {
int  __i_inline_size_2;
int  __i_reserved_quota_3;
};

struct __t_0 ;struct __t_1 ;
int  __main_4 () {
{
struct __t_0  __var_5;
struct __t_1  __var_6;

{
if (__static_condition_default_7) {
 __var_6  . __i_reserved_quota_3 = 1 ;

}

if (__static_condition_default_8) {
__static_type_error("type error") ;

}

}}


}

