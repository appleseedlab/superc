#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
void __static_initializer_default() {
__static_renaming("__myfirststruct_2", "myfirststruct");
__static_renaming("__func_5", "func");
__static_renaming("__example_6", "example");

__static_condition_renaming("__static_condition_default_7", "(declare-fun |(defined CONFIG_A)| () Bool)(assert |(defined CONFIG_A)|)");

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
// typedef moved to top of scope
struct __forward_tag_reference_3 ;
static inline __myfirststruct_2  (* __func_5 (const struct __forward_tag_reference_3  (* __sk_4))) {

if (__static_condition_default_7) {
{
int  __example_6;

if (__static_condition_default_7) {
return ( __myfirststruct_2  * )  __sk_4  ;

}
}

}

}

