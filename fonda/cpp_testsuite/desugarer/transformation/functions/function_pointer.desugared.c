#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__fun_1", "fun");
__static_renaming("__fun_ptr_2", "fun_ptr");
__static_renaming("__main_3", "main");


};

void  __fun_1 (int  __a_0) {

{



__static_type_error("type error : no valid expression"); // L5
}



}
int  __main_3 () {

{



void  (* __fun_ptr_2) (int  )= &  __fun_1 ;

( *  __fun_ptr_2  ) ( 10 ) ; // L19
return 0 ;// L21
}



}

