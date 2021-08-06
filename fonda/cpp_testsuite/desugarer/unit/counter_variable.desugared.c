#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__temp_3", "temp");
__static_renaming("__i_4", "i");
__static_renaming("__j_5", "j");
__static_renaming("__i_6", "i");
__static_renaming("__AES256_CTR_DRBG_Update_7", "AES256_CTR_DRBG_Update");


};

void  __AES256_CTR_DRBG_Update_7 (unsigned char  (* __provided_data_0), unsigned char  (* __Key_1), unsigned char  (* __V_2)) {

{
{



unsigned char  (__temp_3[48]);// L2

{ int  __i_4= 0;// L3
 for ( ;  __i_4  < 3 ;  __i_4  ++ ) // L3
{

{
{



{ int  __j_5= 15;// L4
 for ( ;  __j_5  >= 0 ;  __j_5  -- ) // L4
{

{
{



}
}
}
}
}
}
}
}
if (  __provided_data_0  != ( ( void  * ) 0 ) )// L7
{
{ int  __i_6= 0;// L8
 for ( ;  __i_6  < 48 ;  __i_6  ++ ) // L8
{

{
{



 __temp_3  [  __i_6  ] ^=  __provided_data_0  [  __i_6  ] ; // L9
}
}
}
}
}
}
}



}

