#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__size_t_0", "size_t");
__static_renaming("__malloc_2", "malloc");
__static_renaming("__EVP_CIPHER_CTX_4", "EVP_CIPHER_CTX");
__static_renaming("__Buffer_8", "Buffer");
__static_renaming("__len_9", "len");
__static_renaming("__DoEncryption_10", "DoEncryption");


};
typedef long unsigned int  __size_t_0;// L1
typedef struct __forward_tag_reference_3  __EVP_CIPHER_CTX_4;// L4

struct __forward_tag_reference_3 { // generated union of struct variations
union {
};
};

// typedef moved to top of scope
void  (* __malloc_2 (__size_t_0  __n_1));// L2
struct __forward_tag_reference_3 ;// L0
// typedef moved to top of scope
char  (* __DoEncryption_10 (__EVP_CIPHER_CTX_4  (* __CTX_5), const char  (* __Msg_6), __size_t_0  __MsgLen_7)) {

{
{



 __malloc_2  (( __size_t_0   ) 1) ; // L6
char  (* __Buffer_8)=  __malloc_2  ((  __MsgLen_7  + 16 ) % - 16);// L7

__size_t_0  __len_9;// L8

*  __Buffer_8  =  __len_9  ; // L9
return  __Buffer_8  ;// L10
}
}


}

