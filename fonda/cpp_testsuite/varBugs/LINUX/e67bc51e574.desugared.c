#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_3;
void __static_initializer_default() {
__static_renaming("__trace_dump_stack_1", "trace_dump_stack");
__static_renaming("__trace_dump_stack_2", "trace_dump_stack");
__static_renaming("__main_7", "main");

__static_condition_renaming("__static_condition_default_3", "(defined CONFIG_TRACING)");
__static_condition_renaming("__static_condition_default_4", "!(defined CONFIG_TRACING)");
__static_condition_renaming("__static_condition_default_8", "!(defined CONFIG_TRACING)");

};

void  (__trace_dump_stack_1) (int  __skip_0) {

{
if (__static_condition_default_3) {

{
{



return  ;// L4
}
}


}

}}
static inline void  (__trace_dump_stack_2) (void  ) {

{
if (__static_condition_default_4) {

{
{



}
}


}

}}
int  (__main_7) (int  __argc_5, char  * (* (__argv_6))) {

{
{



if (__static_condition_default_3) {
 __trace_dump_stack_1  (0) ; // L11
}
if (__static_condition_default_8) {
__static_type_error("type error") ; // L11
}
return 0 ;// L12
}
}


}

