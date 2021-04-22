#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__ptrdiff_t_0", "ptrdiff_t");
__static_renaming("__size_t_1", "size_t");
__static_renaming("__wchar_t_2", "wchar_t");
__static_renaming("__max_align_t_6", "max_align_t");
__static_renaming("__x_7", "x");


if (0)
{
__static_parse_error("Unable to parse");
}
};
typedef long int  __ptrdiff_t_0;
typedef long unsigned int  __size_t_1;
typedef int  __wchar_t_2;
struct __anonymous_tag_3 {
long long  ____max_align_ll_4;
long double  ____max_align_ld_5;
};
typedef struct __anonymous_tag_3  __max_align_t_6;

// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
__size_t_1  __x_7;

