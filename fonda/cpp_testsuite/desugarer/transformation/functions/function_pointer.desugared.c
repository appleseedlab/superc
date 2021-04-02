#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__fun_1", "fun");
__static_renaming("__main_2", "main");
__static_renaming("__fun_ptr_3", "fun_ptr");


};

void  __fun_1 (int  __a_0) {
{
__static_type_error("type error : no valid expression");

}


}
int  __main_2 () {
{
void  (* __fun_ptr_3) (int  )= &  __fun_1 ;
( *  __fun_ptr_3  ) ( 10 ) ;

return 0 ;

}


}

