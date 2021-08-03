#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
void __static_initializer_default() {
__static_renaming("__EVP_MD_CTX_new_1", "EVP_MD_CTX_new");
__static_renaming("__mdctx_2", "mdctx");
__static_renaming("__test_function_3", "test_function");

__static_condition_renaming("__static_condition_default_4", "(defined OQS_USE_SHA2_OPENSSL)");

};

struct __forward_tag_reference_0 { // generated union of struct variations
union {
};
};

struct __forward_tag_reference_0 ;// L2147483647:L0
struct __forward_tag_reference_0  (* __EVP_MD_CTX_new_1 (void  ));// L2
void  __test_function_3 () {

if (__static_condition_default_4) {

{



struct __forward_tag_reference_0  (* __mdctx_2);// L6

__static_type_error("type error : no valid expression"); // L7
}


}

}

