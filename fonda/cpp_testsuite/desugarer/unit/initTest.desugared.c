#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_1;
void __static_initializer_default() {
__static_renaming("__a_0", "a");

__static_condition_renaming("__static_condition_default_1", "!(defined A)");

};

int  (__a_0[1])=  { 1 };// L4

