#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__x_3", "x");
__static_renaming("__main_4", "main");


};

 int  __main_4 () {

{

struct __s_1 {
int  __y_2;
};

struct __forward_tag_reference_0 { // generated union of struct variations
union {
struct __s_1 __s_1;
};
};


struct __forward_tag_reference_0 ;

struct __s_1 ;

struct __s_1  __x_3;

}



}

