#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
void __static_initializer_default() {
__static_renaming("__cpu_load_update_active_2", "cpu_load_update_active");
__static_renaming("__cpu_load_update_active_3", "cpu_load_update_active");

__static_condition_renaming("__static_condition_default_4", "!(defined CONFIG_SMP)");

};

extern void  __cpu_load_update_active_2 (int  __this_rq_0);
static inline void  __cpu_load_update_active_3 (int  __this_rq_1) {

if (__static_condition_default_4) {

{



}


}

}

