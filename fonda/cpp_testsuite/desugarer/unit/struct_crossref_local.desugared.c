#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__main_7", "main");


};

int  __main_7 () {

{
{

struct __s1_1 {
int  __data_2;// L3
struct __forward_tag_reference_0  (* __next_3);// L0
};
struct __s2_4 {
int  __data_5;// L8
struct __s1_1  (* __next_6);// L9
};

struct __forward_tag_reference_0 { // generated union of struct variations
union {
struct __s2_4 __s2_4;
};
};


struct __s1_1 ;// L2

struct __s2_4 ;// L7

}
}


}

