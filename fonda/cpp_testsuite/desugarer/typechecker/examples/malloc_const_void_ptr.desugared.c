#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("____free_hook_2", "__free_hook");
__static_renaming("____free_hook_3", "__free_hook");
__static_renaming("__main_4", "main");


};

extern void  (* ____free_hook_2) (void  (* ____ptr_0), const void  *);// L12:L14
extern void  (* volatile  ____free_hook_3) (void  (* ____ptr_1), const void  *);// L12:L14
int  __main_4 () {

{
{



return 0 ;// L18
}
}


}

