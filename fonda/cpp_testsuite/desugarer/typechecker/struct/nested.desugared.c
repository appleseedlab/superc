#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_9();

void __static_initializer_9() {
__static_renaming("__main_5", "main");
__static_renaming("__head_6", "head");
__static_renaming("__tail_7", "tail");
__static_renaming("__current_8", "current");


};
struct __contents_0 {
};
struct __list_2 {
struct __contents_0  __data_3;
struct __forward_tag_reference_1  (* __next_4);
};
int  __main_5 ();

struct __forward_tag_reference_1 { // generated union of struct variations
union {
struct __list_2 __list_2;
};
};

struct __list_2 ;
int  __main_5 () {
{
struct __list_2  __head_6;
struct __list_2  __tail_7;
__static_type_error("type error");

__static_type_error("type error");

__static_type_error("type error");

__static_type_error("type error");

struct __list_2  (* __current_8)= &  __head_6 ;
while ( 0 !=  __current_8  ) {
__static_type_error("type error");

__static_type_error("type error");

}

return 0 ;

}


}

