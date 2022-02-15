#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_0;
void __static_initializer_default() {

__static_condition_renaming("__static_condition_default_0", "(defined __cplusplus)");

if (__static_condition_default_0)
{
__static_parse_error("Unable to parse");
}
};


