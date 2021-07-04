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

struct __list_3 ;
int  __main_9 () {

{



struct __list_3  __head_6;

struct __list_3  __tail_7;

 __head_6  . __data_4 . __p_1 = 'a' ;
 __head_6  . __next_5 = &  __tail_7  ;
 __tail_7  . __data_4 . __p_1 = 'b' ;
 __tail_7  . __next_5 = 0 ;
struct __list_3  (* __current_8)= &  __head_6 ;

while ( 0 !=  __current_8  )

{



 __current_8  -> __data_4 . __p_1 = 'a' ;
 __current_8  =  __current_8  -> __next_5 ;
}
return 0 ;
}



}

