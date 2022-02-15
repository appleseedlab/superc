#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_1();

void __static_initializer_1() {
__static_renaming("__x_0", "x");


};

char char  __x_0;

