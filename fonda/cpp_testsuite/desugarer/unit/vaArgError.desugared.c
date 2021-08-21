#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_2;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_10;
void __static_initializer_default() {
__static_renaming("____gnuc_va_list_0", "__gnuc_va_list");
__static_renaming("__va_list_1", "va_list");
__static_renaming("__va_list_3", "va_list");
__static_renaming("__x_5", "x");
__static_renaming("__main_6", "main");
__static_renaming("__main_7", "main");

__static_condition_renaming("__static_condition_default_2", "!(defined _STDARG_H) && !(defined _ANSI_STDARG_H_) && !(defined __need___va_list) && (defined __GNUC_VA_LIST) && !(defined __svr4__) && (defined _SCO_DS) && !(defined __VA_LIST) && !(defined _VA_LIST_) || !(defined _STDARG_H) && !(defined _ANSI_STDARG_H_) && !(defined __need___va_list) && (defined __GNUC_VA_LIST) && (defined __svr4__) && !(defined _VA_LIST_)");
__static_condition_renaming("__static_condition_default_4", "!(defined _STDARG_H) && !(defined _ANSI_STDARG_H_) && !(defined __need___va_list) && (defined __GNUC_VA_LIST) && !(defined __svr4__) && !(defined _SCO_DS) && !(defined _VA_LIST_) && !(defined _VA_LIST) && !(defined _VA_LIST_DEFINED) && !(defined _VA_LIST_T_H) && !(defined __va_list__) || !(defined _STDARG_H) && !(defined _ANSI_STDARG_H_) && !(defined __need___va_list) && (defined __GNUC_VA_LIST) && !(defined __svr4__) && !(defined _SCO_DS) && (defined _VA_LIST_) && !(defined _VA_LIST) && !(defined __BSD_NET2__) && !(defined ____386BSD____) && !(defined __bsdi__) && !(defined __sequent__) && !(defined __FreeBSD__) && (defined WINNT) && !(defined _VA_LIST_DEFINED) && !(defined _VA_LIST_T_H) && !(defined __va_list__) || !(defined _STDARG_H) && !(defined _ANSI_STDARG_H_) && !(defined __need___va_list) && (defined __GNUC_VA_LIST) && !(defined __svr4__) && !(defined _SCO_DS) && (defined _VA_LIST_) && !(defined _VA_LIST) && !(defined __BSD_NET2__) && !(defined ____386BSD____) && !(defined __bsdi__) && !(defined __sequent__) && (defined __FreeBSD__) && !(defined _VA_LIST_DEFINED) && !(defined _VA_LIST_T_H) && !(defined __va_list__) || !(defined _STDARG_H) && !(defined _ANSI_STDARG_H_) && !(defined __need___va_list) && (defined __GNUC_VA_LIST) && !(defined __svr4__) && !(defined _SCO_DS) && (defined _VA_LIST_) && !(defined _VA_LIST) && !(defined __BSD_NET2__) && !(defined ____386BSD____) && !(defined __bsdi__) && (defined __sequent__) && !(defined _VA_LIST_DEFINED) && !(defined _VA_LIST_T_H) && !(defined __va_list__) || !(defined _STDARG_H) && !(defined _ANSI_STDARG_H_) && !(defined __need___va_list) && (defined __GNUC_VA_LIST) && !(defined __svr4__) && !(defined _SCO_DS) && (defined _VA_LIST_) && !(defined _VA_LIST) && !(defined __BSD_NET2__) && !(defined ____386BSD____) && (defined __bsdi__) && !(defined _VA_LIST_DEFINED) && !(defined _VA_LIST_T_H) && !(defined __va_list__) || !(defined _STDARG_H) && !(defined _ANSI_STDARG_H_) && !(defined __need___va_list) && (defined __GNUC_VA_LIST) && !(defined __svr4__) && !(defined _SCO_DS) && (defined _VA_LIST_) && !(defined _VA_LIST) && !(defined __BSD_NET2__) && (defined ____386BSD____) && !(defined _VA_LIST_DEFINED) && !(defined _VA_LIST_T_H) && !(defined __va_list__) || !(defined _STDARG_H) && !(defined _ANSI_STDARG_H_) && !(defined __need___va_list) && (defined __GNUC_VA_LIST) && !(defined __svr4__) && !(defined _SCO_DS) && (defined _VA_LIST_) && !(defined _VA_LIST) && (defined __BSD_NET2__) && !(defined _VA_LIST_DEFINED) && !(defined _VA_LIST_T_H) && !(defined __va_list__) || !(defined _STDARG_H) && !(defined _ANSI_STDARG_H_) && !(defined __need___va_list) && (defined __GNUC_VA_LIST) && !(defined __svr4__) && (defined _SCO_DS) && (defined __VA_LIST) && !(defined _VA_LIST_) && !(defined _VA_LIST) && !(defined _VA_LIST_DEFINED) && !(defined _VA_LIST_T_H) && !(defined __va_list__) || !(defined _STDARG_H) && !(defined _ANSI_STDARG_H_) && !(defined __need___va_list) && (defined __GNUC_VA_LIST) && !(defined __svr4__) && (defined _SCO_DS) && (defined __VA_LIST) && (defined _VA_LIST_) && !(defined _VA_LIST) && !(defined __BSD_NET2__) && !(defined ____386BSD____) && !(defined __bsdi__) && !(defined __sequent__) && !(defined __FreeBSD__) && (defined WINNT) && !(defined _VA_LIST_DEFINED) && !(defined _VA_LIST_T_H) && !(defined __va_list__) || !(defined _STDARG_H) && !(defined _ANSI_STDARG_H_) && !(defined __need___va_list) && (defined __GNUC_VA_LIST) && !(defined __svr4__) && (defined _SCO_DS) && (defined __VA_LIST) && (defined _VA_LIST_) && !(defined _VA_LIST) && !(defined __BSD_NET2__) && !(defined ____386BSD____) && !(defined __bsdi__) && !(defined __sequent__) && (defined __FreeBSD__) && !(defined _VA_LIST_DEFINED) && !(defined _VA_LIST_T_H) && !(defined __va_list__) || !(defined _STDARG_H) && !(defined _ANSI_STDARG_H_) && !(defined __need___va_list) && (defined __GNUC_VA_LIST) && !(defined __svr4__) && (defined _SCO_DS) && (defined __VA_LIST) && (defined _VA_LIST_) && !(defined _VA_LIST) && !(defined __BSD_NET2__) && !(defined ____386BSD____) && !(defined __bsdi__) && (defined __sequent__) && !(defined _VA_LIST_DEFINED) && !(defined _VA_LIST_T_H) && !(defined __va_list__) || !(defined _STDARG_H) && !(defined _ANSI_STDARG_H_) && !(defined __need___va_list) && (defined __GNUC_VA_LIST) && !(defined __svr4__) && (defined _SCO_DS) && (defined __VA_LIST) && (defined _VA_LIST_) && !(defined _VA_LIST) && !(defined __BSD_NET2__) && !(defined ____386BSD____) && (defined __bsdi__) && !(defined _VA_LIST_DEFINED) && !(defined _VA_LIST_T_H) && !(defined __va_list__) || !(defined _STDARG_H) && !(defined _ANSI_STDARG_H_) && !(defined __need___va_list) && (defined __GNUC_VA_LIST) && !(defined __svr4__) && (defined _SCO_DS) && (defined __VA_LIST) && (defined _VA_LIST_) && !(defined _VA_LIST) && !(defined __BSD_NET2__) && (defined ____386BSD____) && !(defined _VA_LIST_DEFINED) && !(defined _VA_LIST_T_H) && !(defined __va_list__) || !(defined _STDARG_H) && !(defined _ANSI_STDARG_H_) && !(defined __need___va_list) && (defined __GNUC_VA_LIST) && !(defined __svr4__) && (defined _SCO_DS) && (defined __VA_LIST) && (defined _VA_LIST_) && !(defined _VA_LIST) && (defined __BSD_NET2__) && !(defined _VA_LIST_DEFINED) && !(defined _VA_LIST_T_H) && !(defined __va_list__)");
__static_condition_renaming("__static_condition_default_8", "!(defined _STDARG_H) && !(defined _ANSI_STDARG_H_) && !(defined __need___va_list) && !(defined A)");
__static_condition_renaming("__static_condition_default_9", "!(defined _STDARG_H) && !(defined _ANSI_STDARG_H_) && !(defined __need___va_list) && (defined A)");
__static_condition_renaming("__static_condition_default_10", "!(defined _STDARG_H) && !(defined _ANSI_STDARG_H_) && (defined __need___va_list) || !(defined _STDARG_H) && (defined _ANSI_STDARG_H_) || (defined _STDARG_H)");

if (__static_condition_default_10)
{
__static_parse_error("Unable to parse");
}
};
typedef __builtin_va_list  ____gnuc_va_list_0;// L40
typedef ____gnuc_va_list_0  __va_list_1;// L79
typedef ____gnuc_va_list_0  __va_list_3;// L99

// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
int  __x_5;// L3
int  (__main_6) () {

if (__static_condition_default_8) {

{
{



__static_type_error("type error") ; // L8:L49
}
}


}
}
int  (__main_7) () {

if (__static_condition_default_9) {

{
{



__builtin_va_arg (  __x_5  , int  * ) ; // L8:L49
}
}


}
}

