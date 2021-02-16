#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__AES256_CTR_DRBG_Update_3", "AES256_CTR_DRBG_Update");
__static_renaming("__temp_4", "temp");
__static_renaming("__i_5", "i");
__static_renaming("__j_6", "j");
__static_renaming("__i_7", "i");


};

void  __AES256_CTR_DRBG_Update_3 (unsigned char  (* __provided_data_0), unsigned char  (* __Key_1), unsigned char  (* __V_2)) {
{
unsigned char  (__temp_4[48]);
{ int  __i_5= 0;
 for ( ;  __i_5  < 3 ;  __i_5  ++ ) {
{ int  __j_6= 15;
 for ( ;  __j_6  >= 0 ;  __j_6  -- ) {
} }

} }

if (  __provided_data_0  != ( ( void  * ) 0 ) ) { int  __i_7= 0;
 for ( ;  __i_7  < 48 ;  __i_7  ++ ) {
 __temp_4  [  __i_7  ] ^=  __provided_data_0  [  __i_7  ] ;

} }



}


}

