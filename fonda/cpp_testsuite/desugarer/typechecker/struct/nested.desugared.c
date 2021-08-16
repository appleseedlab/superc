#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__printf_1", "printf");
__static_renaming("__head_7", "head");
__static_renaming("__tail_8", "tail");
__static_renaming("__current_9", "current");
__static_renaming("__main_10", "main");


};
struct __contents_2 {
};
struct __list_4 {
struct __contents_2  __data_5;// L3
struct __forward_tag_reference_3  (* __next_6);// L0
};

struct __forward_tag_reference_3 { // generated union of struct variations
union {
struct __list_4 __list_4;
};
};

extern int  __printf_1 (const char  (* __format_0),  ... );// L1
struct __list_4 ;// L2
int  __main_10 () {

{
{



struct __list_4  __head_7;// L9

struct __list_4  __tail_8;// L10

__static_type_error("type error : no valid expression"); // L12
 __head_7  . __next_6 = &  __tail_8  ; // L13
__static_type_error("type error : no valid expression"); // L14
 __tail_8  . __next_6 = 0 ; // L15
struct __list_4  (* __current_9)= &  __head_7 ;// L17

while ( 0 !=  __current_9  )// L18
{

{
{



 __printf_1  ("data: %d\n", __current_9  -> __data_5) ; // L19
 __current_9  =  __current_9  -> __next_6 ; // L20
}
}
}
return 0 ;// L23
}
}


}

