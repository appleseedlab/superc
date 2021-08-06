#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__main_0", "main");


};

int  __main_0 (void  ) {

{
{



if (1) {
__static_type_error("invalid declaration of a under this presence condition");
}

if (1) {
__static_type_error("invalid declaration of b under this presence condition");
}

if (1) {
__static_type_error("invalid declaration of c under this presence condition");
}

if (1) {
__static_type_error("invalid declaration of d under this presence condition");
}

if (1) {
__static_type_error("invalid declaration of e under this presence condition");
}

return 0 ;// L8
}
}



}

