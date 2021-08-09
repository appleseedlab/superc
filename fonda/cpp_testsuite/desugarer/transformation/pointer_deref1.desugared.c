#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__RSA_new_3", "RSA_new");
__static_renaming("__e_5", "e");
__static_renaming("___libssh2_rsa_new_6", "_libssh2_rsa_new");


};
struct __rsa_st_1 {
struct __forward_tag_reference_0  (* __e_2);
};

struct __forward_tag_reference_0 { // generated union of struct variations
union {
};
};

struct __forward_tag_reference_0 ;// L2147483647:L0
struct __rsa_st_1 ;// L2
extern struct __rsa_st_1  (* (* __RSA_new_3 (void  )));// L5
void  ___libssh2_rsa_new_6 (struct __rsa_st_1  (* (* __rsa_4))) {

{
{



struct __forward_tag_reference_0  (* __e_5);// L8

__static_type_error("type error : no valid expression"); // L9
( * *  __rsa_4  ) . __e_2 ; // L10
}
}


}

