#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__size_t_0", "size_t");
__static_renaming("__malloc_2", "malloc");
__static_renaming("__EVP_CIPHER_CTX_4", "EVP_CIPHER_CTX");
__static_renaming("__DoEncryption_8", "DoEncryption");
__static_renaming("__Buffer_9", "Buffer");


};
typedef long unsigned int  __size_t_0;
typedef struct __forward_tag_reference_3  __EVP_CIPHER_CTX_4;

struct __forward_tag_reference_3 { // generated union of struct variations
union {
};
};

// typedef moved to top of scope
void  (* __malloc_2 (__size_t_0  __n_1));
struct __forward_tag_reference_3 ;
// typedef moved to top of scope
char  (* __DoEncryption_8 (__EVP_CIPHER_CTX_4  (* __CTX_5), const char  (* __Msg_6), __size_t_0  __MsgLen_7)) {
{
 __malloc_2  ( ( __size_t_0   ) 1 ) ;

char  (* __Buffer_9)=  __malloc_2  ( (  __MsgLen_7  + 16 ) % - 16 );
return  __Buffer_9  ;

}


}

