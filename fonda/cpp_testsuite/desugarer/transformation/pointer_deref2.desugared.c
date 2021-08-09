#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__RSA_3", "RSA");
__static_renaming("__RSA_new_4", "RSA_new");
__static_renaming("__e_6", "e");
__static_renaming("___libssh2_rsa_new_7", "_libssh2_rsa_new");


};
struct __rsa_st_1 {
struct __forward_tag_reference_0  (* __e_2);
};
typedef struct __rsa_st_1  __RSA_3;// L5

struct __forward_tag_reference_0 { // generated union of struct variations
union {
};
};

struct __forward_tag_reference_0 ;// L2147483647:L0
struct __rsa_st_1 ;// L2
// typedef moved to top of scope
extern __RSA_3  (* __RSA_new_4 (void  ));// L6
void  ___libssh2_rsa_new_7 (__RSA_3  (* __rsa_5)) {

{
{



struct __forward_tag_reference_0  (* __e_6);// L9

__static_type_error("type error : no valid expression"); // L10
( *  __rsa_5  ) . __e_2 =  __e_6  ; // L11
}
}


}

