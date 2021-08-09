#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__local_var_1", "local_var");
__static_renaming("__main_4", "main");


};
struct __s_5 {
int  __x_6;
};

int  __main_4 () {

{
{

struct __s_2 {
char  __y_3;
};

struct __forward_tag_reference_0 { // generated union of struct variations
union {
struct __s_2 __s_2;
};
};


struct __forward_tag_reference_0  (* __local_var_1);// L2

struct __s_2 ;// L4

return  __local_var_1  -> __s_2 . __y_3 ;// L8
}
}


}
struct __s_5 ;// L11

