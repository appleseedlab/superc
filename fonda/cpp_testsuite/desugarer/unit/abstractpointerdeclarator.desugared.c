#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__f_0", "f");
__static_renaming("__g_1", "g");
__static_renaming("__i_2", "i");
__static_renaming("__j_3", "j");
__static_renaming("__k_4", "k");
__static_renaming("__l_5", "l");


};

 int  __f_0 (int  (* (* [4][5])));
 int  __g_1 (int  (* (* [4][5])));
 int  __i_2 (int  (* ((* [4])[5])));
 int  __j_3 (int  ((* *)[4][5]));
 int  __k_4 (int  (* (* [4][5])));
 int  __l_5 (int  (* (* [4][5])));

