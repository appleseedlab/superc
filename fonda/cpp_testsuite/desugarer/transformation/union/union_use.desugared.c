#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__main_4", "main");
__static_renaming("__usedUnion_5", "usedUnion");


};
union __intCharFloat_0 {
int  __integer_1;
char  __character_2;
float  __floating_3;
};

union __intCharFloat_0 ;
int  __main_4 (void  ) {
{
union __intCharFloat_0  __usedUnion_5;
 __usedUnion_5  . __integer_1 = 1 ;

 __usedUnion_5  . __character_2 = 'h' ;

return 0 ;

}


}

