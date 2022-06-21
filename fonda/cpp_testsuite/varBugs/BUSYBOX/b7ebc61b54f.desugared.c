#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_109;
extern const bool __static_condition_default_151;
extern const bool __static_condition_default_190;
extern const bool __static_condition_default_130;
extern const bool __static_condition_default_149;
extern const bool __static_condition_default_132;
extern const bool __static_condition_default_107;
extern const bool __static_condition_default_261;
extern const bool __static_condition_default_123;
extern const bool __static_condition_default_157;
extern const bool __static_condition_default_260;
extern const bool __static_condition_default_257;
extern const bool __static_condition_default_262;
extern const bool __static_condition_default_155;
extern const bool __static_condition_default_258;
extern const bool __static_condition_default_122;
extern const bool __static_condition_default_259;
void __static_initializer_default() {
__static_renaming("__ptrdiff_t_0", "ptrdiff_t");
__static_renaming("__size_t_1", "size_t");
__static_renaming("__wchar_t_2", "wchar_t");
__static_renaming("__div_t_7", "div_t");
__static_renaming("__ldiv_t_12", "ldiv_t");
__static_renaming("__lldiv_t_17", "lldiv_t");
__static_renaming("____ctype_get_mb_cur_max_18", "__ctype_get_mb_cur_max");
__static_renaming("____ctype_get_mb_cur_max_19", "__ctype_get_mb_cur_max");
__static_renaming("____ctype_get_mb_cur_max_20", "__ctype_get_mb_cur_max");
__static_renaming("____ctype_get_mb_cur_max_21", "__ctype_get_mb_cur_max");
__static_renaming("__atof_23", "atof");
__static_renaming("__atof_24", "atof");
__static_renaming("__atoi_26", "atoi");
__static_renaming("__atoi_27", "atoi");
__static_renaming("__atol_29", "atol");
__static_renaming("__atol_30", "atol");
__static_renaming("__atoll_32", "atoll");
__static_renaming("__atoll_33", "atoll");
__static_renaming("__strtod_36", "strtod");
__static_renaming("__strtof_39", "strtof");
__static_renaming("__strtold_42", "strtold");
__static_renaming("__strtol_46", "strtol");
__static_renaming("__strtoul_50", "strtoul");
__static_renaming("__strtoll_54", "strtoll");
__static_renaming("__strtoull_58", "strtoull");
__static_renaming("__rand_62", "rand");
__static_renaming("__rand_63", "rand");
__static_renaming("__srand_65", "srand");
__static_renaming("__malloc_67", "malloc");
__static_renaming("__malloc_68", "malloc");
__static_renaming("__calloc_71", "calloc");
__static_renaming("__calloc_72", "calloc");
__static_renaming("__realloc_75", "realloc");
__static_renaming("__realloc_76", "realloc");
__static_renaming("__free_78", "free");
__static_renaming("__aligned_alloc_81", "aligned_alloc");
__static_renaming("__aligned_alloc_82", "aligned_alloc");
__static_renaming("__abort_83", "abort");
__static_renaming("__atexit_85", "atexit");
__static_renaming("__at_quick_exit_87", "at_quick_exit");
__static_renaming("__exit_89", "exit");
__static_renaming("__quick_exit_91", "quick_exit");
__static_renaming("___Exit_93", "_Exit");
__static_renaming("__getenv_95", "getenv");
__static_renaming("__getenv_96", "getenv");
__static_renaming("__system_98", "system");
__static_renaming("__system_99", "system");
__static_renaming("____compar_fn_t_100", "__compar_fn_t");
__static_renaming("__bsearch_108", "bsearch");
__static_renaming("__bsearch_110", "bsearch");
__static_renaming("____l_117", "__l");
__static_renaming("____u_118", "__u");
__static_renaming("____idx_119", "__idx");
__static_renaming("____p_120", "__p");
__static_renaming("____comparison_121", "__comparison");
__static_renaming("__qsort_129", "qsort");
__static_renaming("__qsort_131", "qsort");
__static_renaming("__abs_134", "abs");
__static_renaming("__abs_135", "abs");
__static_renaming("__labs_137", "labs");
__static_renaming("__labs_138", "labs");
__static_renaming("__llabs_140", "llabs");
__static_renaming("__llabs_141", "llabs");
__static_renaming("__div_144", "div");
__static_renaming("__div_145", "div");
__static_renaming("__ldiv_148", "ldiv");
__static_renaming("__ldiv_150", "ldiv");
__static_renaming("__lldiv_154", "lldiv");
__static_renaming("__lldiv_156", "lldiv");
__static_renaming("__mblen_160", "mblen");
__static_renaming("__mbtowc_164", "mbtowc");
__static_renaming("__wctomb_167", "wctomb");
__static_renaming("__mbstowcs_171", "mbstowcs");
__static_renaming("__wcstombs_175", "wcstombs");
__static_renaming("____realpath_chk_180", "__realpath_chk");
__static_renaming("____realpath_alias_183", "__realpath_alias");
__static_renaming("____realpath_chk_warn_187", "__realpath_chk_warn");
__static_renaming("____ptsname_r_chk_195", "__ptsname_r_chk");
__static_renaming("____ptsname_r_alias_199", "__ptsname_r_alias");
__static_renaming("____ptsname_r_chk_warn_204", "__ptsname_r_chk_warn");
__static_renaming("____wctomb_chk_212", "__wctomb_chk");
__static_renaming("____wctomb_alias_215", "__wctomb_alias");
__static_renaming("____mbstowcs_chk_222", "__mbstowcs_chk");
__static_renaming("____mbstowcs_alias_226", "__mbstowcs_alias");
__static_renaming("____mbstowcs_chk_warn_231", "__mbstowcs_chk_warn");
__static_renaming("____wcstombs_chk_239", "__wcstombs_chk");
__static_renaming("____wcstombs_alias_243", "__wcstombs_alias");
__static_renaming("____wcstombs_chk_warn_248", "__wcstombs_chk_warn");
__static_renaming("__all_fmt_252", "all_fmt");
__static_renaming("__all_fmt_253", "all_fmt");
__static_renaming("__main_256", "main");

__static_condition_renaming("__static_condition_default_107", "!(defined _FORTIFY_SOURCE) && (defined __COMPAR_FN_T) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && (defined __COMPAR_FN_T) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && (defined __COMPAR_FN_T) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_109", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_122", "(defined __USE_EXTERN_INLINES) && !(defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_123", "(defined __USE_EXTERN_INLINES) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_130", "!(defined __USE_EXTERN_INLINES) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_132", "(defined __USE_EXTERN_INLINES) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_149", "!(defined _FORTIFY_SOURCE) && (defined __ldiv_t_defined) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && (defined __ldiv_t_defined) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && (defined __ldiv_t_defined) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && (defined __ldiv_t_defined)");
__static_condition_renaming("__static_condition_default_151", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && (defined __ldiv_t_defined)");
__static_condition_renaming("__static_condition_default_155", "!(defined _FORTIFY_SOURCE) && (defined __lldiv_t_defined) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && (defined __lldiv_t_defined) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && (defined __lldiv_t_defined) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && (defined __lldiv_t_defined)");
__static_condition_renaming("__static_condition_default_157", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && (defined __lldiv_t_defined)");
__static_condition_renaming("__static_condition_default_190", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_257", "!(defined __USE_EXTERN_INLINES)");
__static_condition_renaming("__static_condition_default_258", "!(defined _FORTIFY_SOURCE) && !(defined __USE_EXTERN_INLINES) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined __USE_EXTERN_INLINES) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined __USE_EXTERN_INLINES) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined __USE_EXTERN_INLINES)");
__static_condition_renaming("__static_condition_default_259", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined __USE_EXTERN_INLINES)");
__static_condition_renaming("__static_condition_default_260", "(defined __USE_EXTERN_INLINES)");
__static_condition_renaming("__static_condition_default_261", "!(defined _FORTIFY_SOURCE) && (defined __USE_EXTERN_INLINES) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && (defined __USE_EXTERN_INLINES) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && (defined __USE_EXTERN_INLINES) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && (defined __USE_EXTERN_INLINES)");
__static_condition_renaming("__static_condition_default_262", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && (defined __USE_EXTERN_INLINES)");

};
typedef long int  __ptrdiff_t_0;// L143:L324
typedef long unsigned int  __size_t_1;// L177:L209
typedef int  __wchar_t_2;// L243:L321
struct ____anonymous_tag_3_4 {
int  __quot_5;// L99
int  __rem_6;// L100
};
typedef struct ____anonymous_tag_3_4  __div_t_7;// L97:L101
struct ____anonymous_tag_8_9 {
long int  __quot_10;// L107
long int  __rem_11;// L108
};
typedef struct ____anonymous_tag_8_9  __ldiv_t_12;// L105:L109
struct ____anonymous_tag_13_14 {
long long int  __quot_15;// L119
long long int  __rem_16;// L120
};
typedef struct ____anonymous_tag_13_14  __lldiv_t_17;// L117:L121
typedef int  (* (____compar_fn_t_100)) (const void  *, const void  *);// L741

// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
extern __size_t_1  (____ctype_get_mb_cur_max_18) (void  );// L139
extern __size_t_1  (____ctype_get_mb_cur_max_19) (void  );// L139
extern __size_t_1  (____ctype_get_mb_cur_max_20) (void  );// L139
extern __size_t_1  (____ctype_get_mb_cur_max_21) (void  );// L139
extern double  (__atof_23) (const char  * (____nptr_22));// L144:L145
extern double  (__atof_24) (const char  * (____nptr_22));// L144:L145
extern int  (__atoi_26) (const char  * (____nptr_25));// L147:L148
extern int  (__atoi_27) (const char  * (____nptr_25));// L147:L148
extern long int  (__atol_29) (const char  * (____nptr_28));// L150:L151
extern long int  (__atol_30) (const char  * (____nptr_28));// L150:L151
extern long long int  (__atoll_32) (const char  * (____nptr_31));// L157:L158
extern long long int  (__atoll_33) (const char  * (____nptr_31));// L157:L158
extern double  (__strtod_36) (const char  * __restrict  ____nptr_34, char  * (* __restrict  ____endptr_35));// L164:L166
extern float  (__strtof_39) (const char  * __restrict  ____nptr_37, char  * (* __restrict  ____endptr_38));// L172:L173
extern long double  (__strtold_42) (const char  * __restrict  ____nptr_40, char  * (* __restrict  ____endptr_41));// L175:L177
extern long int  (__strtol_46) (const char  * __restrict  ____nptr_43, char  * (* __restrict  ____endptr_44), int  ____base_45);// L183:L185
extern unsigned long int  (__strtoul_50) (const char  * __restrict  ____nptr_47, char  * (* __restrict  ____endptr_48), int  ____base_49);// L187:L189
extern long long int  (__strtoll_54) (const char  * __restrict  ____nptr_51, char  * (* __restrict  ____endptr_52), int  ____base_53);// L209:L211
extern unsigned long long int  (__strtoull_58) (const char  * __restrict  ____nptr_55, char  * (* __restrict  ____endptr_56), int  ____base_57);// L214:L216
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
__extension__/* no function due to type errors in the function prototype */
extern int  (__rand_62) (void  );// L374
extern int  (__rand_63) (void  );// L374
extern void  (__srand_65) (unsigned int  ____seed_64);// L376
extern void  * ((__malloc_67) (__size_t_1  ____size_66));// L466
extern void  * ((__malloc_68) (__size_t_1  ____size_66));// L466
extern void  * ((__calloc_71) (__size_t_1  ____nmemb_69, __size_t_1  ____size_70));// L468:L469
extern void  * ((__calloc_72) (__size_t_1  ____nmemb_69, __size_t_1  ____size_70));// L468:L469
extern void  * ((__realloc_75) (void  * (____ptr_73), __size_t_1  ____size_74));// L480:L481
extern void  * ((__realloc_76) (void  * (____ptr_73), __size_t_1  ____size_74));// L480:L481
extern void  (__free_78) (void  * (____ptr_77));// L483
extern void  * ((__aligned_alloc_81) (__size_t_1  ____alignment_79, __size_t_1  ____size_80));// L509:L510
extern void  * ((__aligned_alloc_82) (__size_t_1  ____alignment_79, __size_t_1  ____size_80));// L509:L510
extern void  (__abort_83) (void  );// L515
extern int  (__atexit_85) (void  (* (____func_84)) (void  ));// L519
extern int  (__at_quick_exit_87) (void  (* (____func_86)) (void  ));// L527
extern void  (__exit_89) (int  ____status_88);// L543
extern void  (__quick_exit_91) (int  ____status_90);// L549
extern void  (___Exit_93) (int  ____status_92);// L557
extern char  * ((__getenv_95) (const char  * (____name_94)));// L564
extern char  * ((__getenv_96) (const char  * (____name_94)));// L564
extern int  (__system_98) (const char  * (____command_97));// L716
extern int  (__system_99) (const char  * (____command_97));// L716
// typedef moved to top of scope
extern void  * ((__bsearch_108) (const void  * (____key_101), const void  * (____base_102), __size_t_1  ____nmemb_103, __size_t_1  ____size_104, ____compar_fn_t_100  ____compar_105));// L754:L756
extern void  * ((__bsearch_110) (const void  * (____key_101), const void  * (____base_102), __size_t_1  ____nmemb_103, __size_t_1  ____size_104, ____compar_fn_t_100  ____compar_105));// L754:L756
/* no function due to type errors in the function prototype */
extern void  (__qsort_129) (void  * (____base_124), __size_t_1  ____nmemb_125, __size_t_1  ____size_126, ____compar_fn_t_100  ____compar_127);// L764:L765
extern void  (__qsort_131) (void  * (____base_124), __size_t_1  ____nmemb_125, __size_t_1  ____size_126, ____compar_fn_t_100  ____compar_127);// L764:L765
extern int  (__abs_134) (int  ____x_133);// L774
extern int  (__abs_135) (int  ____x_133);// L774
extern long int  (__labs_137) (long int  ____x_136);// L775
extern long int  (__labs_138) (long int  ____x_136);// L775
extern long long int  (__llabs_140) (long long int  ____x_139);// L779:L780
extern long long int  (__llabs_141) (long long int  ____x_139);// L779:L780
extern __div_t_7  (__div_144) (int  ____numer_142, int  ____denom_143);// L788:L789
extern __div_t_7  (__div_145) (int  ____numer_142, int  ____denom_143);// L788:L789
extern __ldiv_t_12  (__ldiv_148) (long int  ____numer_146, long int  ____denom_147);// L790:L791
extern __ldiv_t_12  (__ldiv_150) (long int  ____numer_146, long int  ____denom_147);// L790:L791
extern __lldiv_t_17  (__lldiv_154) (long long int  ____numer_152, long long int  ____denom_153);// L796:L798
extern __lldiv_t_17  (__lldiv_156) (long long int  ____numer_152, long long int  ____denom_153);// L796:L798
extern int  (__mblen_160) (const char  * (____s_158), __size_t_1  ____n_159);// L862
extern int  (__mbtowc_164) (__wchar_t_2  * __restrict  ____pwc_161, const char  * __restrict  ____s_162, __size_t_1  ____n_163);// L865:L866
extern int  (__wctomb_167) (char  * (____s_165), __wchar_t_2  ____wchar_166);// L869
extern __size_t_1  (__mbstowcs_171) (__wchar_t_2  * __restrict  ____pwcs_168, const char  * __restrict  ____s_169, __size_t_1  ____n_170);// L873:L874
extern __size_t_1  (__wcstombs_175) (char  * __restrict  ____s_172, const __wchar_t_2  * __restrict  ____pwcs_173, __size_t_1  ____n_174);// L876:L878
/* no function due to type errors in the function prototype */
extern char  * ((____realpath_chk_180) (const char  * __restrict  ____name_177, char  * __restrict  ____resolved_178, __size_t_1  ____resolvedlen_179));// L23:L25
extern char  * ((____realpath_alias_183) (const char  * __restrict  ____name_181, char  * __restrict  ____resolved_182));// L26:L28
extern char  * ((____realpath_chk_warn_187) (const char  * __restrict  ____name_184, char  * __restrict  ____resolved_185, __size_t_1  ____resolvedlen_186));// L29:L34
/* no function due to type errors in the function prototype */
extern int  (____ptsname_r_chk_195) (int  ____fd_191, char  * (____buf_192), __size_t_1  ____buflen_193, __size_t_1  ____nreal_194);// L52:L53
extern int  (____ptsname_r_alias_199) (int  ____fd_196, char  * (____buf_197), __size_t_1  ____buflen_198);// L54:L56
extern int  (____ptsname_r_chk_warn_204) (int  ____fd_200, char  * (____buf_201), __size_t_1  ____buflen_202, __size_t_1  ____nreal_203);// L57:L61
/* no function due to type errors in the function prototype */
extern int  (____wctomb_chk_212) (char  * (____s_209), __wchar_t_2  ____wchar_210, __size_t_1  ____buflen_211);// L77:L78
extern int  (____wctomb_alias_215) (char  * (____s_213), __wchar_t_2  ____wchar_214);// L79:L80
/* no function due to type errors in the function prototype */
extern __size_t_1  (____mbstowcs_chk_222) (__wchar_t_2  * __restrict  ____dst_218, const char  * __restrict  ____src_219, __size_t_1  ____len_220, __size_t_1  ____dstlen_221);// L98:L100
extern __size_t_1  (____mbstowcs_alias_226) (__wchar_t_2  * __restrict  ____dst_223, const char  * __restrict  ____src_224, __size_t_1  ____len_225);// L101:L104
extern __size_t_1  (____mbstowcs_chk_warn_231) (__wchar_t_2  * __restrict  ____dst_227, const char  * __restrict  ____src_228, __size_t_1  ____len_229, __size_t_1  ____dstlen_230);// L105:L110
/* no function due to type errors in the function prototype */
extern __size_t_1  (____wcstombs_chk_239) (char  * __restrict  ____dst_235, const __wchar_t_2  * __restrict  ____src_236, __size_t_1  ____len_237, __size_t_1  ____dstlen_238);// L130:L132
extern __size_t_1  (____wcstombs_alias_243) (char  * __restrict  ____dst_240, const __wchar_t_2  * __restrict  ____src_241, __size_t_1  ____len_242);// L133:L136
extern __size_t_1  (____wcstombs_chk_warn_248) (char  * __restrict  ____dst_244, const __wchar_t_2  * __restrict  ____src_245, __size_t_1  ____len_246, __size_t_1  ____dstlen_247);// L137:L141
/* no function due to type errors in the function prototype */
static unsigned int  __all_fmt_252;// L9
static unsigned int  __all_fmt_253;// L9
int  (__main_256) (int  __argc_254, char  * (* (__argv_255))) {

{
{



__static_type_error("type error : no valid expression"); // L13
if (__static_condition_default_257) {
if ( rand( ) % 2 )// L15
{

{
{



if (__static_condition_default_258) {
 __all_fmt_252  &= ~ ( 3U << 23 ) ; // L4:L16
}
if (__static_condition_default_259) {
 __all_fmt_253  &= ~ ( 3U << 23 ) ; // L4:L16
}
}
}
}
}
if (__static_condition_default_260) {
if ( rand( ) % 2 )// L15
{

{
{



if (__static_condition_default_261) {
 __all_fmt_252  &= ~ ( 3U << 23 ) ; // L4:L16
}
if (__static_condition_default_262) {
 __all_fmt_253  &= ~ ( 3U << 23 ) ; // L4:L16
}
}
}
}
}
return 0 ;// L19
}
}


}

