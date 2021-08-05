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
__static_renaming("__aa_3", "aa");
__static_renaming("__bb_4", "bb");
__static_renaming("__bb_5", "bb");
__static_renaming("__a_6", "a");
__static_renaming("__a_7", "a");
__static_renaming("__main_8", "main");


};

extern int  __get_0 (char  *, char  *);// L3
extern int  __get_1 (const char  *, const char  *);// L5
int  __main_8 () {

{



char  (* __x_2);// L9

int  __a_6= ( 
{



typeof ( 5 )  __aa_3= 5;// L1

typeof (  __get_0  (  __x_2 , "44" ) )  __bb_4=  __get_0  (  __x_2 , "44" );// L1

 __aa_3  >  __bb_4  ?  __aa_3  :  __bb_4  ; // L1
}
 );// L10

int  __a_7= ( 
{



typeof ( 5 )  __aa_3= 5;// L1

typeof (  __get_1  (  __x_2 , "44" ) )  __bb_5=  __get_1  (  __x_2 , "44" );// L1

 __aa_3  >  __bb_5  ?  __aa_3  :  __bb_5  ; // L1
}
 );// L10

return 0 ;// L11
}



}

