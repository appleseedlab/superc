#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
extern const bool __static_condition_default_11;
extern const bool __static_condition_default_12;
void __static_initializer_default() {
__static_renaming("____u64_0", "__u64");
__static_renaming("__parm_block_1", "parm_block");
__static_renaming("__buf_3", "buf");
__static_renaming("__i_4", "i");
__static_renaming("__prng_seed_5", "prng_seed");
__static_renaming("__main_9", "main");
__static_renaming("__main_10", "main");

__static_condition_renaming("__static_condition_default_6", "(defined CONFIG_S390_PRNG)");
__static_condition_renaming("__static_condition_default_11", "!(defined CONFIG_S390_PRNG)");
__static_condition_renaming("__static_condition_default_12", "(defined CONFIG_S390_PRNG)");

};
typedef unsigned long  ____u64_0;// L1

// typedef moved to top of scope
static unsigned char  __parm_block_1[32]=  { 0x0F ,  0x2B ,  0x8E ,  0x63 ,  0x8C ,  0x8E ,  0xD2 ,  0x52 ,  0x64 ,  0xB7 ,  0xA0 ,  0x7B ,  0x75 ,  0x28 ,  0xB8 ,  0xF4 ,  0x75 ,  0x5F ,  0xD2 ,  0xA6 ,  0x8D ,  0x97 ,  0x11 ,  0xFF ,  0x49 ,  0xD8 ,  0x23 ,  0xF3 ,  0x7E ,  0x21 ,  0xEC ,  0xA0 };// L4:L7
void  (__prng_seed_5) (int  __nbytes_2) {

if (__static_condition_default_6) {

{// L10
{



char  __buf_3[16];// L11
{
__buf_3[0] = 0;
__buf_3[1] = 1;
__buf_3[2] = 2;
__buf_3[3] = 3;
__buf_3[4] = 4;
__buf_3[5] = 5;
__buf_3[6] = 6;
__buf_3[7] = 7;
__buf_3[8] = 8;
__buf_3[9] = 9;
__buf_3[10] = 10;
__buf_3[11] = 11;
__buf_3[12] = 12;
__buf_3[13] = 13;
__buf_3[14] = 14;
__buf_3[15] = 15;
}

int  __i_4= 0;// L12

if (  __nbytes_2  > 16 )// L14
{
return  ;// L15
}
while (  __nbytes_2  >= 8 )// L17
{

{// L17
{



* ( ( ____u64_0  * )  __parm_block_1  ) ^= * ( ( ____u64_0  * )  __buf_3  +  __i_4  * 8 ) ; // L18
 __i_4  += 8 ; // L19
 __nbytes_2  -= 8 ; // L20
}
}// L21
}
}
}// L22


}
}
int  (__main_9) (int  __argc_7, char  * (__argv_8[])) {

if (__static_condition_default_11) {

{// L26
{



return 0 ;// L30
}
}// L31


}
}
int  (__main_10) (int  __argc_7, char  * (__argv_8[])) {

if (__static_condition_default_12) {

{// L26
{



 __prng_seed_5  (16) ; // L28
return 0 ;// L30
}
}// L31


}
}

