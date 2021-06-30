#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_3;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_1", "x");
__static_renaming("__main_2", "main");

__static_condition_renaming("__static_condition_default_3", "A");
__static_condition_renaming("__static_condition_default_4", "!A");

};

 int  __main_2 (void  ) {

{
if (__static_condition_default_3) {

{



int  __x_0;

return 0 ;
}


}

if (__static_condition_default_4) {

{



char  __x_1;

return 1 ;
}


}

}
}

