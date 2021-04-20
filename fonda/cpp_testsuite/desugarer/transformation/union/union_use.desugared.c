#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__usedUnion_4", "usedUnion");
__static_renaming("__main_5", "main");


};
union __intCharFloat_0 {
int  __integer_1;
char  __character_2;
float  __floating_3;
};

union __intCharFloat_0 ;
int  __main_5 (void  ) {
{
union __intCharFloat_0  __usedUnion_4;
 __usedUnion_4  . __integer_1 = 1 ;

 __usedUnion_4  . __character_2 = 'h' ;

return 0 ;

}


}

