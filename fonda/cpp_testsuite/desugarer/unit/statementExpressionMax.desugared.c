#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__get_0", "get");
__static_renaming("__get_1", "get");
__static_renaming("__x_2", "x");
__static_renaming("__aa_4", "aa");
__static_renaming("__bb_7", "bb");
__static_renaming("__bb_8", "bb");
__static_renaming("__a_9", "a");
__static_renaming("__a_10", "a");
__static_renaming("__main_11", "main");


};

extern int  __get_0 (char  *, char  *);// L3
extern int  __get_1 (const char  *, const char  *);// L5
int  __main_11 () {

{
{



char  (* (__x_2));// L9

int  __a_9= ( 
{

typeof(int)__typeofStandin_3;
typeof(int)__typeofStandin_5;
typeof(int)__typeofStandin_6;


typeof ( __typeofStandin_3 )  __aa_4= 5;// L1

typeof ( __typeofStandin_5 )  __bb_7=  __get_0  ( __x_2 ,"44");// L1

 __aa_4  >  __bb_7  ?  __aa_4  :  __bb_7  ; // L1
}
 );// L10

int  __a_10= ( 
{

typeof(int)__typeofStandin_3;
typeof(int)__typeofStandin_5;
typeof(int)__typeofStandin_6;


typeof ( __typeofStandin_3 )  __aa_4= 5;// L1

typeof ( __typeofStandin_6 )  __bb_8=  __get_1  ( __x_2 ,"44");// L1

 __aa_4  >  __bb_8  ?  __aa_4  :  __bb_8  ; // L1
}
 );// L10

return 0 ;// L11
}
}


}

