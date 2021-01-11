#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__x_4", "x");


};

int  __main_0 () {
{struct __s_2 {
int  __y_3;
};

struct __forward_tag_reference_1 { // generated union of struct variations
union {
struct __s_2 __s_2;
};
};

struct __forward_tag_reference_1 ;
struct __s_2 ;
struct __s_2  __x_4;
}


}

