#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_269;
extern const bool __static_condition_default_169;
extern const bool __static_condition_default_275;
extern const bool __static_condition_default_144;
extern const bool __static_condition_default_146;
extern const bool __static_condition_default_136;
extern const bool __static_condition_default_281;
extern const bool __static_condition_default_121;
extern const bool __static_condition_default_267;
extern const bool __static_condition_default_137;
extern const bool __static_condition_default_272;
extern const bool __static_condition_default_123;
extern const bool __static_condition_default_165;
extern const bool __static_condition_default_163;
extern const bool __static_condition_default_276;
extern const bool __static_condition_default_171;
extern const bool __static_condition_default_204;
extern const bool __static_condition_default_270;
extern const bool __static_condition_default_274;
extern const bool __static_condition_default_268;
extern const bool __static_condition_default_282;
void __static_initializer_default() {
__static_renaming("____assert_fail_4", "__assert_fail");
__static_renaming("____assert_perror_fail_9", "__assert_perror_fail");
__static_renaming("____assert_13", "__assert");
__static_renaming("__ptrdiff_t_14", "ptrdiff_t");
__static_renaming("__size_t_15", "size_t");
__static_renaming("__wchar_t_16", "wchar_t");
__static_renaming("__div_t_21", "div_t");
__static_renaming("__ldiv_t_26", "ldiv_t");
__static_renaming("__lldiv_t_31", "lldiv_t");
__static_renaming("____ctype_get_mb_cur_max_32", "__ctype_get_mb_cur_max");
__static_renaming("____ctype_get_mb_cur_max_33", "__ctype_get_mb_cur_max");
__static_renaming("____ctype_get_mb_cur_max_34", "__ctype_get_mb_cur_max");
__static_renaming("____ctype_get_mb_cur_max_35", "__ctype_get_mb_cur_max");
__static_renaming("__atof_37", "atof");
__static_renaming("__atof_38", "atof");
__static_renaming("__atoi_40", "atoi");
__static_renaming("__atoi_41", "atoi");
__static_renaming("__atol_43", "atol");
__static_renaming("__atol_44", "atol");
__static_renaming("__atoll_46", "atoll");
__static_renaming("__atoll_47", "atoll");
__static_renaming("__strtod_50", "strtod");
__static_renaming("__strtof_53", "strtof");
__static_renaming("__strtold_56", "strtold");
__static_renaming("__strtol_60", "strtol");
__static_renaming("__strtoul_64", "strtoul");
__static_renaming("__strtoll_68", "strtoll");
__static_renaming("__strtoull_72", "strtoull");
__static_renaming("__rand_76", "rand");
__static_renaming("__rand_77", "rand");
__static_renaming("__srand_79", "srand");
__static_renaming("__malloc_81", "malloc");
__static_renaming("__malloc_82", "malloc");
__static_renaming("__calloc_85", "calloc");
__static_renaming("__calloc_86", "calloc");
__static_renaming("__realloc_89", "realloc");
__static_renaming("__realloc_90", "realloc");
__static_renaming("__free_92", "free");
__static_renaming("__aligned_alloc_95", "aligned_alloc");
__static_renaming("__aligned_alloc_96", "aligned_alloc");
__static_renaming("__abort_97", "abort");
__static_renaming("__atexit_99", "atexit");
__static_renaming("__at_quick_exit_101", "at_quick_exit");
__static_renaming("__exit_103", "exit");
__static_renaming("__quick_exit_105", "quick_exit");
__static_renaming("___Exit_107", "_Exit");
__static_renaming("__getenv_109", "getenv");
__static_renaming("__getenv_110", "getenv");
__static_renaming("__system_112", "system");
__static_renaming("__system_113", "system");
__static_renaming("____compar_fn_t_114", "__compar_fn_t");
__static_renaming("__bsearch_122", "bsearch");
__static_renaming("__bsearch_124", "bsearch");
__static_renaming("____l_131", "__l");
__static_renaming("____u_132", "__u");
__static_renaming("____idx_133", "__idx");
__static_renaming("____p_134", "__p");
__static_renaming("____comparison_135", "__comparison");
__static_renaming("__qsort_143", "qsort");
__static_renaming("__qsort_145", "qsort");
__static_renaming("__abs_148", "abs");
__static_renaming("__abs_149", "abs");
__static_renaming("__labs_151", "labs");
__static_renaming("__labs_152", "labs");
__static_renaming("__llabs_154", "llabs");
__static_renaming("__llabs_155", "llabs");
__static_renaming("__div_158", "div");
__static_renaming("__div_159", "div");
__static_renaming("__ldiv_162", "ldiv");
__static_renaming("__ldiv_164", "ldiv");
__static_renaming("__lldiv_168", "lldiv");
__static_renaming("__lldiv_170", "lldiv");
__static_renaming("__mblen_174", "mblen");
__static_renaming("__mbtowc_178", "mbtowc");
__static_renaming("__wctomb_181", "wctomb");
__static_renaming("__mbstowcs_185", "mbstowcs");
__static_renaming("__wcstombs_189", "wcstombs");
__static_renaming("____realpath_chk_194", "__realpath_chk");
__static_renaming("____realpath_alias_197", "__realpath_alias");
__static_renaming("____realpath_chk_warn_201", "__realpath_chk_warn");
__static_renaming("____ptsname_r_chk_209", "__ptsname_r_chk");
__static_renaming("____ptsname_r_alias_213", "__ptsname_r_alias");
__static_renaming("____ptsname_r_chk_warn_218", "__ptsname_r_chk_warn");
__static_renaming("____wctomb_chk_226", "__wctomb_chk");
__static_renaming("____wctomb_alias_229", "__wctomb_alias");
__static_renaming("____mbstowcs_chk_236", "__mbstowcs_chk");
__static_renaming("____mbstowcs_alias_240", "__mbstowcs_alias");
__static_renaming("____mbstowcs_chk_warn_245", "__mbstowcs_chk_warn");
__static_renaming("____wcstombs_chk_253", "__wcstombs_chk");
__static_renaming("____wcstombs_alias_257", "__wcstombs_alias");
__static_renaming("____wcstombs_chk_warn_262", "__wcstombs_chk_warn");
__static_renaming("__vlan_dev_real_dev_266", "vlan_dev_real_dev");
__static_renaming("__vlan_dev_real_dev_271", "vlan_dev_real_dev");
__static_renaming("__ocrdma_inet6addr_event_273", "ocrdma_inet6addr_event");
__static_renaming("__main_279", "main");
__static_renaming("__main_280", "main");

__static_condition_renaming("__static_condition_default_121", "!(defined _FORTIFY_SOURCE) && (defined __COMPAR_FN_T) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && (defined __COMPAR_FN_T) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && (defined __COMPAR_FN_T) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_123", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_136", "(defined __USE_EXTERN_INLINES) && !(defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_137", "(defined __USE_EXTERN_INLINES) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_144", "!(defined __USE_EXTERN_INLINES) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_146", "(defined __USE_EXTERN_INLINES) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_163", "!(defined _FORTIFY_SOURCE) && (defined __ldiv_t_defined) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && (defined __ldiv_t_defined) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && (defined __ldiv_t_defined) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && (defined __ldiv_t_defined)");
__static_condition_renaming("__static_condition_default_165", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && (defined __ldiv_t_defined)");
__static_condition_renaming("__static_condition_default_169", "!(defined _FORTIFY_SOURCE) && (defined __lldiv_t_defined) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && (defined __lldiv_t_defined) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && (defined __lldiv_t_defined) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && (defined __lldiv_t_defined)");
__static_condition_renaming("__static_condition_default_171", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && (defined __lldiv_t_defined)");
__static_condition_renaming("__static_condition_default_204", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_267", "!(defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_268", "(defined NDEBUG) && !(defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_269", "!(defined NDEBUG) && !(defined _ASSERT_H_DECLS) && !(defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_270", "!(defined NDEBUG) && (defined _ASSERT_H_DECLS) && !(defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_272", "(defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_274", "!(defined CONFIG_VLAN_8021Q) && (defined CONFIG_IPV6) || (defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_275", "!(defined CONFIG_VLAN_8021Q) && (defined CONFIG_IPV6)");
__static_condition_renaming("__static_condition_default_276", "(defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_281", "!(defined CONFIG_VLAN_8021Q) && !(defined CONFIG_IPV6)");
__static_condition_renaming("__static_condition_default_282", "!(defined CONFIG_VLAN_8021Q) && (defined CONFIG_IPV6) || (defined CONFIG_VLAN_8021Q)");

};
typedef long int  __ptrdiff_t_14;// L143:L324
typedef long unsigned int  __size_t_15;// L177:L209
typedef int  __wchar_t_16;// L243:L321
struct ____anonymous_tag_17_18 {
int  __quot_19;// L99
int  __rem_20;// L100
};
typedef struct ____anonymous_tag_17_18  __div_t_21;// L97:L101
struct ____anonymous_tag_22_23 {
long int  __quot_24;// L107
long int  __rem_25;// L108
};
typedef struct ____anonymous_tag_22_23  __ldiv_t_26;// L105:L109
struct ____anonymous_tag_27_28 {
long long int  __quot_29;// L119
long long int  __rem_30;// L120
};
typedef struct ____anonymous_tag_27_28  __lldiv_t_31;// L117:L121
typedef int  (* (____compar_fn_t_114)) (const void  *, const void  *);// L741

extern void  (____assert_fail_4) (const char  * (____assertion_0), const char  * (____file_1), unsigned int  ____line_2, const char  * (____function_3));// L69:L71
extern void  (____assert_perror_fail_9) (int  ____errnum_5, const char  * (____file_6), unsigned int  ____line_7, const char  * (____function_8));// L74:L76
extern void  (____assert_13) (const char  * (____assertion_10), const char  * (____file_11), int  ____line_12);// L81:L82
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
extern __size_t_15  (____ctype_get_mb_cur_max_32) (void  );// L139
extern __size_t_15  (____ctype_get_mb_cur_max_33) (void  );// L139
extern __size_t_15  (____ctype_get_mb_cur_max_34) (void  );// L139
extern __size_t_15  (____ctype_get_mb_cur_max_35) (void  );// L139
extern double  (__atof_37) (const char  * (____nptr_36));// L144:L145
extern double  (__atof_38) (const char  * (____nptr_36));// L144:L145
extern int  (__atoi_40) (const char  * (____nptr_39));// L147:L148
extern int  (__atoi_41) (const char  * (____nptr_39));// L147:L148
extern long int  (__atol_43) (const char  * (____nptr_42));// L150:L151
extern long int  (__atol_44) (const char  * (____nptr_42));// L150:L151
extern long long int  (__atoll_46) (const char  * (____nptr_45));// L157:L158
extern long long int  (__atoll_47) (const char  * (____nptr_45));// L157:L158
extern double  (__strtod_50) (const char  * __restrict  ____nptr_48, char  * (* __restrict  ____endptr_49));// L164:L166
extern float  (__strtof_53) (const char  * __restrict  ____nptr_51, char  * (* __restrict  ____endptr_52));// L172:L173
extern long double  (__strtold_56) (const char  * __restrict  ____nptr_54, char  * (* __restrict  ____endptr_55));// L175:L177
extern long int  (__strtol_60) (const char  * __restrict  ____nptr_57, char  * (* __restrict  ____endptr_58), int  ____base_59);// L183:L185
extern unsigned long int  (__strtoul_64) (const char  * __restrict  ____nptr_61, char  * (* __restrict  ____endptr_62), int  ____base_63);// L187:L189
extern long long int  (__strtoll_68) (const char  * __restrict  ____nptr_65, char  * (* __restrict  ____endptr_66), int  ____base_67);// L209:L211
extern unsigned long long int  (__strtoull_72) (const char  * __restrict  ____nptr_69, char  * (* __restrict  ____endptr_70), int  ____base_71);// L214:L216
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
__extension__/* no function due to type errors in the function prototype */
extern int  (__rand_76) (void  );// L374
extern int  (__rand_77) (void  );// L374
extern void  (__srand_79) (unsigned int  ____seed_78);// L376
extern void  * ((__malloc_81) (__size_t_15  ____size_80));// L466
extern void  * ((__malloc_82) (__size_t_15  ____size_80));// L466
extern void  * ((__calloc_85) (__size_t_15  ____nmemb_83, __size_t_15  ____size_84));// L468:L469
extern void  * ((__calloc_86) (__size_t_15  ____nmemb_83, __size_t_15  ____size_84));// L468:L469
extern void  * ((__realloc_89) (void  * (____ptr_87), __size_t_15  ____size_88));// L480:L481
extern void  * ((__realloc_90) (void  * (____ptr_87), __size_t_15  ____size_88));// L480:L481
extern void  (__free_92) (void  * (____ptr_91));// L483
extern void  * ((__aligned_alloc_95) (__size_t_15  ____alignment_93, __size_t_15  ____size_94));// L509:L510
extern void  * ((__aligned_alloc_96) (__size_t_15  ____alignment_93, __size_t_15  ____size_94));// L509:L510
extern void  (__abort_97) (void  );// L515
extern int  (__atexit_99) (void  (* (____func_98)) (void  ));// L519
extern int  (__at_quick_exit_101) (void  (* (____func_100)) (void  ));// L527
extern void  (__exit_103) (int  ____status_102);// L543
extern void  (__quick_exit_105) (int  ____status_104);// L549
extern void  (___Exit_107) (int  ____status_106);// L557
extern char  * ((__getenv_109) (const char  * (____name_108)));// L564
extern char  * ((__getenv_110) (const char  * (____name_108)));// L564
extern int  (__system_112) (const char  * (____command_111));// L716
extern int  (__system_113) (const char  * (____command_111));// L716
// typedef moved to top of scope
extern void  * ((__bsearch_122) (const void  * (____key_115), const void  * (____base_116), __size_t_15  ____nmemb_117, __size_t_15  ____size_118, ____compar_fn_t_114  ____compar_119));// L754:L756
extern void  * ((__bsearch_124) (const void  * (____key_115), const void  * (____base_116), __size_t_15  ____nmemb_117, __size_t_15  ____size_118, ____compar_fn_t_114  ____compar_119));// L754:L756
/* no function due to type errors in the function prototype */
extern void  (__qsort_143) (void  * (____base_138), __size_t_15  ____nmemb_139, __size_t_15  ____size_140, ____compar_fn_t_114  ____compar_141);// L764:L765
extern void  (__qsort_145) (void  * (____base_138), __size_t_15  ____nmemb_139, __size_t_15  ____size_140, ____compar_fn_t_114  ____compar_141);// L764:L765
extern int  (__abs_148) (int  ____x_147);// L774
extern int  (__abs_149) (int  ____x_147);// L774
extern long int  (__labs_151) (long int  ____x_150);// L775
extern long int  (__labs_152) (long int  ____x_150);// L775
extern long long int  (__llabs_154) (long long int  ____x_153);// L779:L780
extern long long int  (__llabs_155) (long long int  ____x_153);// L779:L780
extern __div_t_21  (__div_158) (int  ____numer_156, int  ____denom_157);// L788:L789
extern __div_t_21  (__div_159) (int  ____numer_156, int  ____denom_157);// L788:L789
extern __ldiv_t_26  (__ldiv_162) (long int  ____numer_160, long int  ____denom_161);// L790:L791
extern __ldiv_t_26  (__ldiv_164) (long int  ____numer_160, long int  ____denom_161);// L790:L791
extern __lldiv_t_31  (__lldiv_168) (long long int  ____numer_166, long long int  ____denom_167);// L796:L798
extern __lldiv_t_31  (__lldiv_170) (long long int  ____numer_166, long long int  ____denom_167);// L796:L798
extern int  (__mblen_174) (const char  * (____s_172), __size_t_15  ____n_173);// L862
extern int  (__mbtowc_178) (__wchar_t_16  * __restrict  ____pwc_175, const char  * __restrict  ____s_176, __size_t_15  ____n_177);// L865:L866
extern int  (__wctomb_181) (char  * (____s_179), __wchar_t_16  ____wchar_180);// L869
extern __size_t_15  (__mbstowcs_185) (__wchar_t_16  * __restrict  ____pwcs_182, const char  * __restrict  ____s_183, __size_t_15  ____n_184);// L873:L874
extern __size_t_15  (__wcstombs_189) (char  * __restrict  ____s_186, const __wchar_t_16  * __restrict  ____pwcs_187, __size_t_15  ____n_188);// L876:L878
/* no function due to type errors in the function prototype */
extern char  * ((____realpath_chk_194) (const char  * __restrict  ____name_191, char  * __restrict  ____resolved_192, __size_t_15  ____resolvedlen_193));// L23:L25
extern char  * ((____realpath_alias_197) (const char  * __restrict  ____name_195, char  * __restrict  ____resolved_196));// L26:L28
extern char  * ((____realpath_chk_warn_201) (const char  * __restrict  ____name_198, char  * __restrict  ____resolved_199, __size_t_15  ____resolvedlen_200));// L29:L34
/* no function due to type errors in the function prototype */
extern int  (____ptsname_r_chk_209) (int  ____fd_205, char  * (____buf_206), __size_t_15  ____buflen_207, __size_t_15  ____nreal_208);// L52:L53
extern int  (____ptsname_r_alias_213) (int  ____fd_210, char  * (____buf_211), __size_t_15  ____buflen_212);// L54:L56
extern int  (____ptsname_r_chk_warn_218) (int  ____fd_214, char  * (____buf_215), __size_t_15  ____buflen_216, __size_t_15  ____nreal_217);// L57:L61
/* no function due to type errors in the function prototype */
extern int  (____wctomb_chk_226) (char  * (____s_223), __wchar_t_16  ____wchar_224, __size_t_15  ____buflen_225);// L77:L78
extern int  (____wctomb_alias_229) (char  * (____s_227), __wchar_t_16  ____wchar_228);// L79:L80
/* no function due to type errors in the function prototype */
extern __size_t_15  (____mbstowcs_chk_236) (__wchar_t_16  * __restrict  ____dst_232, const char  * __restrict  ____src_233, __size_t_15  ____len_234, __size_t_15  ____dstlen_235);// L98:L100
extern __size_t_15  (____mbstowcs_alias_240) (__wchar_t_16  * __restrict  ____dst_237, const char  * __restrict  ____src_238, __size_t_15  ____len_239);// L101:L104
extern __size_t_15  (____mbstowcs_chk_warn_245) (__wchar_t_16  * __restrict  ____dst_241, const char  * __restrict  ____src_242, __size_t_15  ____len_243, __size_t_15  ____dstlen_244);// L105:L110
/* no function due to type errors in the function prototype */
extern __size_t_15  (____wcstombs_chk_253) (char  * __restrict  ____dst_249, const __wchar_t_16  * __restrict  ____src_250, __size_t_15  ____len_251, __size_t_15  ____dstlen_252);// L130:L132
extern __size_t_15  (____wcstombs_alias_257) (char  * __restrict  ____dst_254, const __wchar_t_16  * __restrict  ____src_255, __size_t_15  ____len_256);// L133:L136
extern __size_t_15  (____wcstombs_chk_warn_262) (char  * __restrict  ____dst_258, const __wchar_t_16  * __restrict  ____src_259, __size_t_15  ____len_260, __size_t_15  ____dstlen_261);// L137:L141
/* no function due to type errors in the function prototype */
void  * ((__vlan_dev_real_dev_266) ()) {

if (__static_condition_default_267) {

{
{



if (__static_condition_default_268) {
( ( void   ) ( 0 ) ) ; // L13:L50
}
if (__static_condition_default_269) {
( ( 0 ) ? ( void   ) ( 0 ) :  ____assert_fail_4  ("false","/home/kisamefishfry/Documents/xtc-dev/fonda/cpp_testsuite/varBugs/LINUX/d549f55f2e1.c",13, __PRETTY_FUNCTION__ ) ) ; // L13:L91
}
if (__static_condition_default_270) {
__static_type_error("type error") ; // L13:L91
}
return ( ( void  * ) 0 ) ;// L14
}
}


}
}
void  * ((__vlan_dev_real_dev_271) ()) {

if (__static_condition_default_272) {

{
{



return ( ( void  * ) 0 ) ;// L8
}
}


}
}
static int  (__ocrdma_inet6addr_event_273) () {

if (__static_condition_default_274) {

{
{



if (__static_condition_default_275) {
 __vlan_dev_real_dev_266 ( ) ; // L21
}
if (__static_condition_default_276) {
 __vlan_dev_real_dev_271 ( ) ; // L21
}
return 0 ;// L23
}
}


}
}
int  (__main_279) (int  __argc_277, char  * (* (__argv_278))) {

if (__static_condition_default_281) {

{
{



return 0 ;// L32
}
}


}
}
int  (__main_280) (int  __argc_277, char  * (* (__argv_278))) {

if (__static_condition_default_282) {

{
{



 __ocrdma_inet6addr_event_273 ( ) ; // L30
return 0 ;// L32
}
}


}
}

