#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_1;
extern const bool __static_condition_default_0;
void __static_initializer_default() {

__static_condition_renaming("__static_condition_default_0", "!(defined _DIRENT_H) && (defined __USE_XOPEN) && !(defined __ino_t_defined) || !(defined _DIRENT_H) && (defined __USE_XOPEN) && (defined __ino_t_defined) && !(defined __ino64_t_defined)");
__static_condition_renaming("__static_condition_default_1", "!(defined _DIRENT_H) && (defined __USE_XOPEN) && !(defined __ino_t_defined)");

if (__static_condition_default_1)
{
__static_parse_error("Unable to parse");
}
};


