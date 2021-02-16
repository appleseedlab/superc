#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_4();

void __static_initializer_4() {
__static_renaming("__foo_0", "foo");
__static_renaming("__fwo_1", "fwo");
__static_renaming("__fwotwo_2", "fwotwo");
__static_renaming("__main_3", "main");


};
int  __main_3 ();

void  __foo_0 (void  );
void  (* __fwo_1 (void  , void  ));
void  __fwotwo_2 (void  *, void  *);
int  __main_3 () {
{
return 1 ;

}


}

