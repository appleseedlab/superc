#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__x_1", "x");
__static_renaming("__y_2", "y");
__static_renaming("__z_3", "z");

__static_condition_renaming("__static_condition_default_4", "(declare-fun |(defined A)| () Bool)(assert |(defined A)|)");
__static_condition_renaming("__static_condition_default_5", "(declare-fun |(defined C)| () Bool)(declare-fun |(defined B)| () Bool)(declare-fun |(defined A)| () Bool)(assert (let ((a!1 (or (and (not |(defined A)|) |(defined B)|)               (and (not |(defined A)|) (not |(defined B)|) |(defined C)|))))  (or (and |(defined A)| |(defined B)|)      (and a!1 |(defined B)|)      (and a!1 (not |(defined B)|) |(defined C)|)      (and |(defined A)| (not |(defined B)|) |(defined C)|))))(assert |(defined B)|)");
__static_condition_renaming("__static_condition_default_6", "(declare-fun |(defined C)| () Bool)(declare-fun |(defined B)| () Bool)(declare-fun |(defined A)| () Bool)(assert (let ((a!1 (or (and (not |(defined A)|) |(defined B)|)               (and (not |(defined A)|) (not |(defined B)|) |(defined C)|))))  (or (and |(defined A)| |(defined B)|)      (and a!1 |(defined B)|)      (and a!1 (not |(defined B)|) |(defined C)|)      (and |(defined A)| (not |(defined B)|) |(defined C)|))))(assert |(defined B)|)(assert |(defined C)|)(assert (let ((a!1 (or (and (not |(defined A)|) |(defined B)|)               (and (not |(defined A)|) (not |(defined B)|) |(defined C)|))))(let ((a!2 (or (and |(defined A)| |(defined B)|)               (and a!1 |(defined B)|)               (and a!1 (not |(defined B)|) |(defined C)|)               (and |(defined A)| (not |(defined B)|) |(defined C)|))))  (or (and a!2 |(defined B)| |(defined C)|)      (and a!2 (not |(defined B)|) |(defined C)|)))))");
__static_condition_renaming("__static_condition_default_7", "(declare-fun |(defined C)| () Bool)(declare-fun |(defined B)| () Bool)(declare-fun |(defined A)| () Bool)(assert (let ((a!1 (or (and (not |(defined A)|) |(defined B)|)               (and (not |(defined A)|) (not |(defined B)|) |(defined C)|))))  (or (and |(defined A)| |(defined B)|)      (and a!1 |(defined B)|)      (and a!1 (not |(defined B)|) |(defined C)|)      (and |(defined A)| (not |(defined B)|) |(defined C)|))))(assert (not |(defined B)|))(assert |(defined C)|)(assert (let ((a!1 (or (and (not |(defined A)|) |(defined B)|)               (and (not |(defined A)|) (not |(defined B)|) |(defined C)|))))(let ((a!2 (or (and |(defined A)| |(defined B)|)               (and a!1 |(defined B)|)               (and a!1 (not |(defined B)|) |(defined C)|)               (and |(defined A)| (not |(defined B)|) |(defined C)|))))  (or (and a!2 |(defined B)| |(defined C)|)      (and a!2 (not |(defined B)|) |(defined C)|)))))");
__static_condition_renaming("__static_condition_default_8", "(declare-fun |(defined C)| () Bool)(declare-fun |(defined B)| () Bool)(declare-fun |(defined A)| () Bool)(assert (let ((a!1 (or (and (not |(defined A)|) |(defined B)|)               (and (not |(defined A)|) (not |(defined B)|) |(defined C)|))))(let ((a!2 (and (or (and |(defined A)| |(defined B)|)                    (and a!1 |(defined B)|)                    (and a!1 (not |(defined B)|) |(defined C)|)                    (and |(defined A)| (not |(defined B)|) |(defined C)|))                |(defined B)|                (not |(defined C)|))))  (or a!2      (and |(defined A)| (not |(defined B)|) (not |(defined C)|))      (and (not |(defined A)|) (not |(defined B)|) (not |(defined C)|))))))");
__static_condition_renaming("__static_condition_default_9", "(declare-fun |(defined C)| () Bool)(declare-fun |(defined B)| () Bool)(declare-fun |(defined A)| () Bool)(assert (let ((a!1 (or (and (not |(defined A)|) |(defined B)|)               (and (not |(defined A)|) (not |(defined B)|) |(defined C)|))))(let ((a!2 (or (and |(defined A)| |(defined B)|)               (and a!1 |(defined B)|)               (and a!1 (not |(defined B)|) |(defined C)|)               (and |(defined A)| (not |(defined B)|) |(defined C)|))))  (or (and a!2 |(defined B)| |(defined C)|)      (and a!2 (not |(defined B)|) |(defined C)|)))))");

};

int  __main_0 () {
{
int  __x_1;
int  __y_2;
int  __z_3;
if (  __x_1  ) 
{
if (__static_condition_default_8) {
{

if (__static_condition_default_4) {
 __x_1  ++ ;

}

if (__static_condition_default_5) {
 __y_2  ++ ;

}
}

}

if (__static_condition_default_9) {
{

if (__static_condition_default_4) {
 __x_1  ++ ;

}

if (__static_condition_default_5) {
 __y_2  ++ ;

}

{
if (__static_condition_default_6) {
 __z_3  ++ ;

}

if (__static_condition_default_7) {
 __z_3  ++ ;

}

}}

}

}

}


}

