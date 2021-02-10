#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__printf_1", "printf");
__static_renaming("__main_7", "main");
__static_renaming("__head_8", "head");
__static_renaming("__tail_9", "tail");
__static_renaming("__current_10", "current");


};
struct __contents_2 {
};
struct __list_4 {
struct __contents_2  __data_5;
struct __forward_tag_reference_3  (* __next_6);
};

struct __forward_tag_reference_3 { // generated union of struct variations
union {
struct __list_4 __list_4;
};
};

extern int  __printf_1 (const char  (* __format_0),  ... );
struct __list_4 ;
int  __main_7 () {
{
struct __list_4  __head_8;
struct __list_4  __tail_9;
__static_type_error("type error");

 __head_8  . __next_6 = &  __tail_9  ;

__static_type_error("type error");

 __tail_9  . __next_6 = 0 ;

struct __list_4  (* __current_10)= &  __head_8 ;
while ( 0 !=  __current_10  ) {
 __printf_1  ( "data: %d\n",  __current_10  -> __data_5 ) ;

 __current_10  =  __current_10  -> __next_6 ;

}

return 0 ;

}


}

