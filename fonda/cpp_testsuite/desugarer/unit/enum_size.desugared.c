#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__printf_1", "printf");
__static_renaming("__x_2", "x");
__static_renaming("__y_7", "y");
__static_renaming("__main_8", "main");


};
enum E {
__A_3 = 0x01FFFFFFFFFFFFFF,
__B_4,
__C_5,
__D_6 = - 10,
};

extern int  __printf_1 (const char  (* __restrict  ____format_0),  ... );// L1
enum E  __x_2;// L3
enum E ;// L5
int  __main_8 () {

{
{



 __x_2  =  __C_5  ; // L13
int  __y_7=  __x_2 ;// L14

 __printf_1  ( "%016llx\n",  __A_3  ) ; // L15
 __printf_1  ( "%016llx\n",  __B_4  ) ; // L16
 __printf_1  ( "%016llx\n",  __C_5  ) ; // L17
 __printf_1  ( "%016llx\n",  __x_2  ) ; // L18
 __printf_1  ( "%016llx\n",  __y_7  ) ; // L19
 __printf_1  ( "%d\n",  __D_6  ) ; // L20
 __x_2  =  __D_6  ; // L21
 __printf_1  ( "%016llx\n",  __x_2  ) ; // L22
return 0 ;// L23
}
}



}

