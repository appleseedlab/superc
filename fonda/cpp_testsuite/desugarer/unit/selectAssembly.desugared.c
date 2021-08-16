#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__fd_set_2", "fd_set");
__static_renaming("__x_3", "x");
__static_renaming("____d0_4", "__d0");
__static_renaming("____d1_5", "__d1");
__static_renaming("__main_6", "main");


};
struct ____fd_set_0 {
int  (__fds_bits_1[4]);// L3
};
typedef struct ____fd_set_0  __fd_set_2;// L1:L4

// typedef moved to top of scope
int  __main_6 () {

{
{



__fd_set_2  __x_3;// L19

do
{

{
{



int  ____d0_4;// L9

int  ____d1_5;// L9

__asm__  __volatile__   ( "cld; rep; ""stosq" : "=c" (  ____d0_4  ) , "=D" (  ____d1_5  ) : "a" ( 0 ) , "0" ( ( sizeof(int  ([4])) ) ) , "1" ( & ( ( &  __x_3  ) -> __fds_bits_1 ) [ 0 ] ) : "memory" );
}
}
}
while( 0 );// L15:L20
}
}


}

