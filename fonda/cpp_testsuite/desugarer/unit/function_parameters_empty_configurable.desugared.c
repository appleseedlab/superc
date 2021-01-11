#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_10;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_9;
void __static_initializer_default() {
__static_renaming("__f_5", "f");
__static_renaming("__f_6", "f");
__static_renaming("__f_7", "f");

__static_condition_renaming("__static_condition_default_8", "(declare-fun |(defined A)| () Bool)(declare-fun |(defined B)| () Bool)(assert (or (and |(defined B)| |(defined A)|)    (and |(defined B)| (not (and |(defined B)| |(defined A)|)))))(assert |(defined B)|)(assert |(defined A)|)");
__static_condition_renaming("__static_condition_default_9", "(declare-fun |(defined A)| () Bool)(declare-fun |(defined B)| () Bool)(assert (let ((a!1 (or (and |(defined B)| |(defined A)|)               (and |(defined B)| (not (and |(defined B)| |(defined A)|))))))  (not (and a!1 |(defined B)| |(defined A)|))))(assert (or (and |(defined B)| |(defined A)|)    (and |(defined B)| (not (and |(defined B)| |(defined A)|)))))(assert (let ((a!1 (or (and |(defined B)| |(defined A)|)               (and |(defined B)| (not (and |(defined B)| |(defined A)|))))))  (not (and |(defined B)| |(defined A)| a!1))))");
__static_condition_renaming("__static_condition_default_10", "(declare-fun |(defined A)| () Bool)(declare-fun |(defined B)| () Bool)(assert (let ((a!1 (or (and |(defined B)| |(defined A)|)               (and |(defined B)| (not (and |(defined B)| |(defined A)|))))))  (not (and a!1 |(defined B)| |(defined A)|))))(assert (let ((a!1 (or (and |(defined B)| |(defined A)|)               (and |(defined B)| (not (and |(defined B)| |(defined A)|))))))  (not (and (not (and a!1 |(defined B)| |(defined A)|))            a!1            (not (and |(defined B)| |(defined A)| a!1))))))");

};

int  __f_5 (int  __x_0, int  __y_1, int  __z_3) {

if (__static_condition_default_8) {
{
}

}

}
int  __f_6 (int  __z_2) {

if (__static_condition_default_9) {
{
}

}

}
int  __f_7 (int  __a_4) {

if (__static_condition_default_10) {
{
}

}

}

