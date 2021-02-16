#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_2;
extern const bool __static_condition_default_3;
void __static_initializer_default() {
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_2", "(defined _LIBC)");
__static_condition_renaming("__static_condition_default_3", "!(defined _LIBC)");

};

int  __main_4 () {
{
return 0 ;

}


}

