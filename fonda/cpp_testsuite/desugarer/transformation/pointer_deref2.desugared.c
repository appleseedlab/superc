#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__RSA_3", "RSA");
__static_renaming("__RSA_new_4", "RSA_new");
__static_renaming("___libssh2_rsa_new_6", "_libssh2_rsa_new");
__static_renaming("__e_7", "e");


};
struct __rsa_st_1 {
struct __forward_tag_reference_0  (* __e_2);
};
typedef struct __rsa_st_1  __RSA_3;

struct __forward_tag_reference_0 { // generated union of struct variations
union {
};
};

struct __forward_tag_reference_0 ;
struct __rsa_st_1 ;
// typedef moved to top of scope
extern __RSA_3  (* __RSA_new_4 (void  ));
void  ___libssh2_rsa_new_6 (__RSA_3  (* __rsa_5)) {
{
struct __forward_tag_reference_0  (* __e_7);
 __rsa_5  =  __RSA_new_4  ( ) ;

( *  __rsa_5  ) . __e_2 =  __e_7  ;

}


}

