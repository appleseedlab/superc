#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__printf_1", "printf");
__static_renaming("__x_3", "x");
__static_renaming("__y_9", "y");
__static_renaming("__main_10", "main");


};
enum __E_8 {
__A_4 = 0x01FFFFFFFFFFFFFF,
__B_5,
__C_6,
__D_7 = - 10,
};

union __forward_tag_reference_2 { // generated union of enum variations
enum __E_8 __E_8;
};

extern int  (__printf_1) (const char  * __restrict  ____format_0,  ... );// L1
union __forward_tag_reference_2  __x_3;// L3
enum __E_8 ;// L5
int  (__main_10) () {

{
{



 __x_3 .__E_8 =  __C_6  ; // L13
int  __y_9=  __x_3 .__E_8;// L14

 __printf_1  ("%016llx\n", __A_4 ) ; // L15
 __printf_1  ("%016llx\n", __B_5 ) ; // L16
 __printf_1  ("%016llx\n", __C_6 ) ; // L17
 __printf_1  ("%016llx\n", __x_3 .__E_8) ; // L18
 __printf_1  ("%016llx\n", __y_9 ) ; // L19
 __printf_1  ("%d\n", __D_7 ) ; // L20
 __x_3 .__E_8 =  __D_7  ; // L21
 __printf_1  ("%016llx\n", __x_3 .__E_8) ; // L22
return 0 ;// L23
}
}


}

