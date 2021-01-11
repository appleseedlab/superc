#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_8();

extern const bool __static_condition_7;
void __static_initializer_8() {
__static_renaming("__main_5", "main");
__static_renaming("__usedUnion_6", "usedUnion");

__static_condition_renaming("__static_condition_7", "(declare-fun A () Bool)(assert A)");

};
union __intCharFloat_0 {
int  __integer_1;
char  __character_2;
float  __floating_3;
float  __floating_4;
};
int  __main_5 (void  );

union __intCharFloat_0 ;
int  __main_5 (void  ) {
{
union __intCharFloat_0  __usedUnion_6;

if (__static_condition_7) {
 __usedUnion_6  . __integer_1 = 1 ;

}

if (__static_condition_7) {
 __usedUnion_6  . __character_2 = 'h' ;

}
return 0 ;

}


}

