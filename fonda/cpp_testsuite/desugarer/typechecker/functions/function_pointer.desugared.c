#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__fun_ptr_0", "fun_ptr");


if (0)
{
__static_parse_error("Unable to parse");
}
};

void  (* __fun_ptr_0) (int  );

