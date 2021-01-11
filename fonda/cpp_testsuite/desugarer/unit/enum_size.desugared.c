#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_9();

void __static_initializer_9() {
__static_renaming("__printf_1", "printf");
__static_renaming("__x_2", "x");
__static_renaming("__main_7", "main");
__static_renaming("__y_8", "y");


};
int  __main_7 ();

enum E {
__A_3 /* = 0x01FFFFFFFFFFFFFF */,
__B_4,
__C_5,
__D_6 /* = - 10 */,
};
extern int  __printf_1 (const char  (* __restrict  ____format_0),  ... );
enum   E  __x_2;
enum   E ;
int  __main_7 () {
{
__static_type_error("type error");

int  __y_8=  __x_2 ;
 __printf_1  ( "%016llx\n",  __A_3  ) ;

 __printf_1  ( "%016llx\n",  __B_4  ) ;

 __printf_1  ( "%016llx\n",  __C_5  ) ;

 __printf_1  ( "%016llx\n",  __x_2  ) ;

 __printf_1  ( "%016llx\n",  __y_8  ) ;

 __printf_1  ( "%d\n",  __D_6  ) ;

__static_type_error("type error");

 __printf_1  ( "%016llx\n",  __x_2  ) ;

return 0 ;

}


}

