#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__main_0", "main");


};

int  __main_0 () {
{struct __s1_2 {
int  __data_3;
struct __forward_tag_reference_1  (* __next_4);
};
struct __s2_5 {
int  __data_6;
struct __s1_2  (* __next_7);
};

struct __forward_tag_reference_1 { // generated union of struct variations
union {
struct __s2_5 __s2_5;
};
};

struct __s1_2 ;
struct __s2_5 ;
}


}

