#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_18;
extern const bool __static_condition_default_17;
void __static_initializer_default() {
__static_renaming("__OPENSSL_cleanse_2", "OPENSSL_cleanse");
__static_renaming("__CRYPTO_free_6", "CRYPTO_free");
__static_renaming("__CRYPTO_malloc_10", "CRYPTO_malloc");
__static_renaming("__error_12", "error");
__static_renaming("__BUFFER_SIZE_13", "BUFFER_SIZE");
__static_renaming("__buffer_14", "buffer");
__static_renaming("__i_15", "i");
__static_renaming("__main_16", "main");

__static_condition_renaming("__static_condition_default_17", "(defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_18", "!(defined CONFIG_A)");

};

void  __OPENSSL_cleanse_2 (void  (* __ptr_0), unsigned int  __len_1);// L5
void  __CRYPTO_free_6 (void  (* __ptr_3), const char  (* __file_4), int  __line_5);// L7
void  (* __CRYPTO_malloc_10 (unsigned int  __num_7, const char  (* __file_8), int  __line_9));// L12
void  __error_12 (const char  (* __fmt_11),  ... );// L17
int  __main_16 () {

{



unsigned int  __BUFFER_SIZE_13= 256;// L3:L20

unsigned char  (* __buffer_14)=  __CRYPTO_malloc_10  (  __BUFFER_SIZE_13 , "", 0 );// L21

{ unsigned int  __i_15= 0;// L3:L22
 for ( ;  __i_15  <  __BUFFER_SIZE_13  ; ++  __i_15  ) // L22

{



 __buffer_14  [  __i_15  ] =  __i_15  ; // L23
}
}
if (__static_condition_default_17) {
 __OPENSSL_cleanse_2  (  __buffer_14 ,  __BUFFER_SIZE_13  ) ; // L27
}
if (__static_condition_default_18) {
 __CRYPTO_free_6  (  __buffer_14 , "", 0 ) ; // L10:L31
}
if (__static_condition_default_17) {
 __CRYPTO_free_6  (  __buffer_14 , "", 0 ) ; // L10:L31
}
return 0 ;// L32
}



}

