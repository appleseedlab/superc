#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__myfirststruct_2", "myfirststruct");
__static_renaming("__example_5", "example");

__static_condition_renaming("__static_condition_default_6", "(defined CONFIG_A)");

};
struct __myfirststruct_0 {
int  __x_1;
};
typedef struct __myfirststruct_0  __myfirststruct_2;

struct __forward_tag_reference_3 { // generated union of struct variations
union {
};
};

// typedef moved to top of scope
struct __forward_tag_reference_3 ;
/* no function due to type errors in the function prototype */

