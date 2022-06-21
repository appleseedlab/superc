#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__trace_dump_stack_1", "trace_dump_stack");
__static_renaming("__main_4", "main");


};

void  (__trace_dump_stack_1) (int  __skip_0) {

{
{



return  ;// L4
}
}


}
int  (__main_4) (int  __argc_2, char  * (* (__argv_3))) {

{
{



 __trace_dump_stack_1  (0) ; // L11
return 0 ;// L12
}
}


}

