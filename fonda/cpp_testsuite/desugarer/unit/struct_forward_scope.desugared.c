#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__local_var_2", "local_var");


};
struct __s_5 {
int  __x_6;
};

int  __main_0 () {
{struct __s_3 {
char  __y_4;
};

struct __forward_tag_reference_1 { // generated union of struct variations
union {
struct __s_3 __s_3;
};
};

struct __forward_tag_reference_1  (* __local_var_2);
struct __s_3 ;
return  __local_var_2  -> __s_3 . __y_4 ;

}


}
struct __s_5 ;

