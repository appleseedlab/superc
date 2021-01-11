#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_19();

extern const bool __static_condition_18;
extern const bool __static_condition_17;
void __static_initializer_19() {
__static_renaming("__OPENSSL_cleanse_2", "OPENSSL_cleanse");
__static_renaming("__CRYPTO_free_6", "CRYPTO_free");
__static_renaming("__CRYPTO_malloc_10", "CRYPTO_malloc");
__static_renaming("__error_12", "error");
__static_renaming("__main_13", "main");
__static_renaming("__BUFFER_SIZE_14", "BUFFER_SIZE");
__static_renaming("__buffer_15", "buffer");
__static_renaming("__i_16", "i");

__static_condition_renaming("__static_condition_17", "(declare-fun |(defined CONFIG_B)| () Bool)(assert |(defined CONFIG_B)|)");
__static_condition_renaming("__static_condition_18", "(declare-fun |(defined CONFIG_B)| () Bool)(assert (not |(defined CONFIG_B)|))");

};
int  __main_13 ();

void  __OPENSSL_cleanse_2 (void  (* __ptr_0), unsigned int  __len_1);
void  __CRYPTO_free_6 (void  (* __ptr_3), const char  (* __file_4), int  __line_5);
void  (* __CRYPTO_malloc_10 (unsigned int  __num_7, const char  (* __file_8), int  __line_9));
void  __error_12 (const char  (* __fmt_11),  ... );
int  __main_13 () {
{
unsigned int  __BUFFER_SIZE_14= 256;
unsigned char  (* __buffer_15)=  __CRYPTO_malloc_10  (  __BUFFER_SIZE_14 , "", 0 );

if (__static_condition_17) {
{ unsigned int  __i_16= 0;
 for ( ;  __i_16  <  __BUFFER_SIZE_14  ; ++  __i_16  ) {

if (__static_condition_17) {
__static_type_error("type error");

}
} }

}

if (__static_condition_17) {
 __OPENSSL_cleanse_2  (  __buffer_15 ,  __BUFFER_SIZE_14  ) ;

}

{
if (__static_condition_18) {
 __CRYPTO_free_6  ( "", 0 ) ;

}

if (__static_condition_17) {
 __CRYPTO_free_6  (  __buffer_15 , "", 0 ) ;

}

}return 0 ;

}


}

