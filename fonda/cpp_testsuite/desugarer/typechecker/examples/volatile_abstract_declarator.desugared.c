#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("____free_hook_1", "__free_hook");
__static_renaming("__main_2", "main");


};

extern void  (* volatile  ____free_hook_1) (void  (* ____ptr_0), const void  *);
int  __main_2 () {
{
return 0 ;

}


}

