#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__head_6", "head");
__static_renaming("__tail_7", "tail");
__static_renaming("__current_8", "current");
__static_renaming("__main_9", "main");


};
struct __anonymous_tag_0 {
char  __p_1;
};
struct __list_3 {
struct __anonymous_tag_0  __data_4;
struct __forward_tag_reference_2  (* __next_5);
};

struct __forward_tag_reference_2 { // generated union of struct variations
union {
struct __list_3 __list_3;
};
};

struct __list_3 ;// L1
int  __main_9 () {

{



struct __list_3  __head_6;// L9

struct __list_3  __tail_7;// L10

 __head_6  . __data_4 . __p_1 = 'a' ; // L12
 __head_6  . __next_5 = &  __tail_7  ; // L13
 __tail_7  . __data_4 . __p_1 = 'b' ; // L14
 __tail_7  . __next_5 = 0 ; // L15
struct __list_3  (* __current_8)= &  __head_6 ;// L17

while ( 0 !=  __current_8  )// L18

{



 __current_8  -> __data_4 . __p_1 = 'a' ; // L19
 __current_8  =  __current_8  -> __next_5 ; // L20
}
return 0 ;// L23
}



}

