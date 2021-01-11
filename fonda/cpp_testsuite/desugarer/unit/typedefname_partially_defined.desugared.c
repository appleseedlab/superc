#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_15;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_14;
extern const bool __static_condition_default_17;
extern const bool __static_condition_default_2;
void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__a_3", "a");
__static_renaming("__a_8", "a");
__static_renaming("__main_9", "main");
__static_renaming("__main_10", "main");
__static_renaming("__a_11", "a");
__static_renaming("__a_12", "a");
__static_renaming("__a_13", "a");

__static_condition_renaming("__static_condition_default_2", "(declare-fun |(defined C)| () Bool)(declare-fun |(defined B)| () Bool)(declare-fun |(defined A)| () Bool)(assert (or (and |(defined A)| |(defined B)|)    (and |(defined A)| (not |(defined B)|) (not |(defined C)|))    (and |(defined A)| (not |(defined B)|) |(defined C)|)))(assert (or (and |(defined B)| (not |(defined C)|)) (and |(defined B)| |(defined C)|)))");
__static_condition_renaming("__static_condition_default_5", "(declare-fun |(defined C)| () Bool)(declare-fun |(defined B)| () Bool)(declare-fun |(defined A)| () Bool)(assert (or (and |(defined A)| |(defined B)|)    (and |(defined A)| (not |(defined B)|) (not |(defined C)|))    (and |(defined A)| (not |(defined B)|) |(defined C)|)))(assert (let ((a!1 (and (or (and |(defined A)| |(defined B)|)                    (and |(defined A)| (not |(defined B)|) (not |(defined C)|))                    (and |(defined A)| (not |(defined B)|) |(defined C)|))                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not a!1)))(assert (let ((a!1 (not (or (and |(defined A)| |(defined B)|)                    (and |(defined A)| (not |(defined B)|) (not |(defined C)|))                    (and |(defined A)| (not |(defined B)|) |(defined C)|)))))(let ((a!2 (and a!1                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not a!2))))(assert |(defined C)|)");
__static_condition_renaming("__static_condition_default_14", "(declare-fun |(defined C)| () Bool)(declare-fun |(defined B)| () Bool)(declare-fun |(defined A)| () Bool)(assert (let ((a!1 (or (and |(defined A)| |(defined B)|)               (and |(defined A)| (not |(defined B)|) (not |(defined C)|))               (and |(defined A)| (not |(defined B)|) |(defined C)|))))(let ((a!2 (and a!1                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|))))      (a!3 (and (not a!1)                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (or a!2 (and a!1 (not a!2) (not a!3) |(defined C)|)))))");
__static_condition_renaming("__static_condition_default_15", "(declare-fun |(defined B)| () Bool)(declare-fun |(defined A)| () Bool)(declare-fun |(defined C)| () Bool)(assert (not (and |(defined A)| |(defined B)|)))(assert (not (and |(defined A)| (not |(defined B)|) (not |(defined C)|))))(assert (not (and |(defined A)| (not |(defined B)|) |(defined C)|)))(assert (let ((a!1 (and (or (and |(defined A)| |(defined B)|)                    (and |(defined A)| (not |(defined B)|) (not |(defined C)|))                    (and |(defined A)| (not |(defined B)|) |(defined C)|))                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not a!1)))(assert (let ((a!1 (not (or (and |(defined A)| |(defined B)|)                    (and |(defined A)| (not |(defined B)|) (not |(defined C)|))                    (and |(defined A)| (not |(defined B)|) |(defined C)|)))))(let ((a!2 (and a!1                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not a!2))))(assert (let ((a!1 (or (and |(defined A)| |(defined B)|)               (and |(defined A)| (not |(defined B)|) (not |(defined C)|))               (and |(defined A)| (not |(defined B)|) |(defined C)|))))(let ((a!2 (and a!1                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|))))      (a!3 (and (not a!1)                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not (and a!1 (not a!2) (not a!3) |(defined C)|)))))(assert (let ((a!1 (or (and |(defined A)| |(defined B)|)               (and |(defined A)| (not |(defined B)|) (not |(defined C)|))               (and |(defined A)| (not |(defined B)|) |(defined C)|))))(let ((a!2 (and a!1                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|))))      (a!3 (and (not a!1)                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not (and (not a!1) (not a!2) (not a!3) |(defined C)|)))))");
__static_condition_renaming("__static_condition_default_16", "(declare-fun |(defined C)| () Bool)(assert (not |(defined C)|))");
__static_condition_renaming("__static_condition_default_17", "(declare-fun |(defined C)| () Bool)(assert |(defined C)|)");

};
typedef int  __a_0;

typedef char  __a_3;

typedef char char  __a_6;

typedef char char  __a_8;

// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
int  __main_9 () {

if (__static_condition_default_16) {
{
const __a_0  __a_11;
const __a_3  __a_12;
const __a_8  __a_13;
if (__static_condition_default_14) {
__static_type_error("invalid declaration of a under this presence condition");
}
if (__static_condition_default_15) {
__static_type_error("invalid declaration of a under this presence condition");
}
}

}

}
int  __main_10 () {

if (__static_condition_default_17) {
{
const __a_0  __a_11;
const __a_3  __a_12;
const __a_8  __a_13;
if (__static_condition_default_14) {
__static_type_error("invalid declaration of a under this presence condition");
}
if (__static_condition_default_15) {
__static_type_error("invalid declaration of a under this presence condition");
}
}

}

}

