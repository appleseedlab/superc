#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__f_2", "f");
__static_renaming("__f_3", "f");


};

extern int  __f_2 (int  __x_0);// L3
extern int  __f_3 (int  __x_1);// L5

