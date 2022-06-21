#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_129;
extern const bool __static_condition_default_131;
extern const bool __static_condition_default_268;
extern const bool __static_condition_default_108;
extern const bool __static_condition_default_263;
extern const bool __static_condition_default_106;
extern const bool __static_condition_default_265;
extern const bool __static_condition_default_154;
extern const bool __static_condition_default_267;
extern const bool __static_condition_default_270;
extern const bool __static_condition_default_122;
extern const bool __static_condition_default_156;
extern const bool __static_condition_default_269;
extern const bool __static_condition_default_257;
extern const bool __static_condition_default_121;
extern const bool __static_condition_default_189;
extern const bool __static_condition_default_148;
extern const bool __static_condition_default_150;
extern const bool __static_condition_default_266;
extern const bool __static_condition_default_262;
extern const bool __static_condition_default_256;
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
__static_renaming("__free_77", "free");
__static_renaming("__aligned_alloc_80", "aligned_alloc");
__static_renaming("__aligned_alloc_81", "aligned_alloc");
__static_renaming("__abort_82", "abort");
__static_renaming("__atexit_84", "atexit");
__static_renaming("__at_quick_exit_86", "at_quick_exit");
__static_renaming("__exit_88", "exit");
__static_renaming("__quick_exit_90", "quick_exit");
__static_renaming("___Exit_92", "_Exit");
__static_renaming("__getenv_94", "getenv");
__static_renaming("__getenv_95", "getenv");
__static_renaming("__system_97", "system");
__static_renaming("__system_98", "system");
__static_renaming("____compar_fn_t_99", "__compar_fn_t");
__static_renaming("__bsearch_107", "bsearch");
__static_renaming("__bsearch_109", "bsearch");
__static_renaming("____l_116", "__l");
__static_renaming("____u_117", "__u");
__static_renaming("____idx_118", "__idx");
__static_renaming("____p_119", "__p");
__static_renaming("____comparison_120", "__comparison");
__static_renaming("__qsort_128", "qsort");
__static_renaming("__qsort_130", "qsort");
__static_renaming("__abs_133", "abs");
__static_renaming("__abs_134", "abs");
__static_renaming("__labs_136", "labs");
__static_renaming("__labs_137", "labs");
__static_renaming("__llabs_139", "llabs");
__static_renaming("__llabs_140", "llabs");
__static_renaming("__div_143", "div");
__static_renaming("__div_144", "div");
__static_renaming("__ldiv_147", "ldiv");
__static_renaming("__ldiv_149", "ldiv");
__static_renaming("__lldiv_153", "lldiv");
__static_renaming("__lldiv_155", "lldiv");
__static_renaming("__mblen_159", "mblen");
__static_renaming("__mbtowc_163", "mbtowc");
__static_renaming("__wctomb_166", "wctomb");
__static_renaming("__mbstowcs_170", "mbstowcs");
__static_renaming("__wcstombs_174", "wcstombs");
__static_renaming("____realpath_chk_179", "__realpath_chk");
__static_renaming("____realpath_alias_182", "__realpath_alias");
__static_renaming("____realpath_chk_warn_186", "__realpath_chk_warn");
__static_renaming("____ptsname_r_chk_194", "__ptsname_r_chk");
__static_renaming("____ptsname_r_alias_198", "__ptsname_r_alias");
__static_renaming("____ptsname_r_chk_warn_203", "__ptsname_r_chk_warn");
__static_renaming("____wctomb_chk_211", "__wctomb_chk");
__static_renaming("____wctomb_alias_214", "__wctomb_alias");
__static_renaming("____mbstowcs_chk_221", "__mbstowcs_chk");
__static_renaming("____mbstowcs_alias_225", "__mbstowcs_alias");
__static_renaming("____mbstowcs_chk_warn_230", "__mbstowcs_chk_warn");
__static_renaming("____wcstombs_chk_238", "__wcstombs_chk");
__static_renaming("____wcstombs_alias_242", "__wcstombs_alias");
__static_renaming("____wcstombs_chk_warn_247", "__wcstombs_chk_warn");
__static_renaming("__cache_251", "cache");
__static_renaming("__cache_252", "cache");
__static_renaming("__util_ldap_shm_253", "util_ldap_shm");
__static_renaming("__apr_shm_attach_255", "apr_shm_attach");
__static_renaming("__apr_shm_create_259", "apr_shm_create");
__static_renaming("__result_260", "result");
__static_renaming("__util_ldap_cache_init_261", "util_ldap_cache_init");
__static_renaming("__main_264", "main");

__static_condition_renaming("__static_condition_default_106", "!(defined _FORTIFY_SOURCE) && (defined __COMPAR_FN_T) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && (defined __COMPAR_FN_T) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && (defined __COMPAR_FN_T) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_108", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_121", "(defined __USE_EXTERN_INLINES) && !(defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_122", "(defined __USE_EXTERN_INLINES) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_129", "!(defined __USE_EXTERN_INLINES) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_131", "(defined __USE_EXTERN_INLINES) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_148", "!(defined _FORTIFY_SOURCE) && (defined __ldiv_t_defined) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && (defined __ldiv_t_defined) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && (defined __ldiv_t_defined) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && (defined __ldiv_t_defined)");
__static_condition_renaming("__static_condition_default_150", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && (defined __ldiv_t_defined)");
__static_condition_renaming("__static_condition_default_154", "!(defined _FORTIFY_SOURCE) && (defined __lldiv_t_defined) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && (defined __lldiv_t_defined) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && (defined __lldiv_t_defined) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && (defined __lldiv_t_defined)");
__static_condition_renaming("__static_condition_default_156", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && (defined __lldiv_t_defined)");
__static_condition_renaming("__static_condition_default_189", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_256", "!(defined _FORTIFY_SOURCE) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_257", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_262", "APR_HAS_SHARED_MEMORY");
__static_condition_renaming("__static_condition_default_263", "!APR_HAS_SHARED_MEMORY");
__static_condition_renaming("__static_condition_default_265", "!(defined __USE_EXTERN_INLINES)");
__static_condition_renaming("__static_condition_default_266", "!(defined _FORTIFY_SOURCE) && !(defined __USE_EXTERN_INLINES) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined __USE_EXTERN_INLINES) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined __USE_EXTERN_INLINES) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined __USE_EXTERN_INLINES)");
__static_condition_renaming("__static_condition_default_267", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined __USE_EXTERN_INLINES)");
__static_condition_renaming("__static_condition_default_268", "(defined __USE_EXTERN_INLINES)");
__static_condition_renaming("__static_condition_default_269", "!(defined _FORTIFY_SOURCE) && (defined __USE_EXTERN_INLINES) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && (defined __USE_EXTERN_INLINES) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && (defined __USE_EXTERN_INLINES) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && (defined __USE_EXTERN_INLINES)");
__static_condition_renaming("__static_condition_default_270", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && (defined __USE_EXTERN_INLINES)");

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
typedef int  (* (____compar_fn_t_99)) (const void  *, const void  *);// L741

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
extern void  (__free_77) (void  * (____ptr_76));// L483
extern void  * ((__aligned_alloc_80) (__size_t_1  ____alignment_78, __size_t_1  ____size_79));// L509:L510
extern void  * ((__aligned_alloc_81) (__size_t_1  ____alignment_78, __size_t_1  ____size_79));// L509:L510
extern void  (__abort_82) (void  );// L515
extern int  (__atexit_84) (void  (* (____func_83)) (void  ));// L519
extern int  (__at_quick_exit_86) (void  (* (____func_85)) (void  ));// L527
extern void  (__exit_88) (int  ____status_87);// L543
extern void  (__quick_exit_90) (int  ____status_89);// L549
extern void  (___Exit_92) (int  ____status_91);// L557
extern char  * ((__getenv_94) (const char  * (____name_93)));// L564
extern char  * ((__getenv_95) (const char  * (____name_93)));// L564
extern int  (__system_97) (const char  * (____command_96));// L716
extern int  (__system_98) (const char  * (____command_96));// L716
// typedef moved to top of scope
extern void  * ((__bsearch_107) (const void  * (____key_100), const void  * (____base_101), __size_t_1  ____nmemb_102, __size_t_1  ____size_103, ____compar_fn_t_99  ____compar_104));// L754:L756
extern void  * ((__bsearch_109) (const void  * (____key_100), const void  * (____base_101), __size_t_1  ____nmemb_102, __size_t_1  ____size_103, ____compar_fn_t_99  ____compar_104));// L754:L756
/* no function due to type errors in the function prototype */
extern void  (__qsort_128) (void  * (____base_123), __size_t_1  ____nmemb_124, __size_t_1  ____size_125, ____compar_fn_t_99  ____compar_126);// L764:L765
extern void  (__qsort_130) (void  * (____base_123), __size_t_1  ____nmemb_124, __size_t_1  ____size_125, ____compar_fn_t_99  ____compar_126);// L764:L765
extern int  (__abs_133) (int  ____x_132);// L774
extern int  (__abs_134) (int  ____x_132);// L774
extern long int  (__labs_136) (long int  ____x_135);// L775
extern long int  (__labs_137) (long int  ____x_135);// L775
extern long long int  (__llabs_139) (long long int  ____x_138);// L779:L780
extern long long int  (__llabs_140) (long long int  ____x_138);// L779:L780
extern __div_t_7  (__div_143) (int  ____numer_141, int  ____denom_142);// L788:L789
extern __div_t_7  (__div_144) (int  ____numer_141, int  ____denom_142);// L788:L789
extern __ldiv_t_12  (__ldiv_147) (long int  ____numer_145, long int  ____denom_146);// L790:L791
extern __ldiv_t_12  (__ldiv_149) (long int  ____numer_145, long int  ____denom_146);// L790:L791
extern __lldiv_t_17  (__lldiv_153) (long long int  ____numer_151, long long int  ____denom_152);// L796:L798
extern __lldiv_t_17  (__lldiv_155) (long long int  ____numer_151, long long int  ____denom_152);// L796:L798
extern int  (__mblen_159) (const char  * (____s_157), __size_t_1  ____n_158);// L862
extern int  (__mbtowc_163) (__wchar_t_2  * __restrict  ____pwc_160, const char  * __restrict  ____s_161, __size_t_1  ____n_162);// L865:L866
extern int  (__wctomb_166) (char  * (____s_164), __wchar_t_2  ____wchar_165);// L869
extern __size_t_1  (__mbstowcs_170) (__wchar_t_2  * __restrict  ____pwcs_167, const char  * __restrict  ____s_168, __size_t_1  ____n_169);// L873:L874
extern __size_t_1  (__wcstombs_174) (char  * __restrict  ____s_171, const __wchar_t_2  * __restrict  ____pwcs_172, __size_t_1  ____n_173);// L876:L878
/* no function due to type errors in the function prototype */
extern char  * ((____realpath_chk_179) (const char  * __restrict  ____name_176, char  * __restrict  ____resolved_177, __size_t_1  ____resolvedlen_178));// L23:L25
extern char  * ((____realpath_alias_182) (const char  * __restrict  ____name_180, char  * __restrict  ____resolved_181));// L26:L28
extern char  * ((____realpath_chk_warn_186) (const char  * __restrict  ____name_183, char  * __restrict  ____resolved_184, __size_t_1  ____resolvedlen_185));// L29:L34
/* no function due to type errors in the function prototype */
extern int  (____ptsname_r_chk_194) (int  ____fd_190, char  * (____buf_191), __size_t_1  ____buflen_192, __size_t_1  ____nreal_193);// L52:L53
extern int  (____ptsname_r_alias_198) (int  ____fd_195, char  * (____buf_196), __size_t_1  ____buflen_197);// L54:L56
extern int  (____ptsname_r_chk_warn_203) (int  ____fd_199, char  * (____buf_200), __size_t_1  ____buflen_201, __size_t_1  ____nreal_202);// L57:L61
/* no function due to type errors in the function prototype */
extern int  (____wctomb_chk_211) (char  * (____s_208), __wchar_t_2  ____wchar_209, __size_t_1  ____buflen_210);// L77:L78
extern int  (____wctomb_alias_214) (char  * (____s_212), __wchar_t_2  ____wchar_213);// L79:L80
/* no function due to type errors in the function prototype */
extern __size_t_1  (____mbstowcs_chk_221) (__wchar_t_2  * __restrict  ____dst_217, const char  * __restrict  ____src_218, __size_t_1  ____len_219, __size_t_1  ____dstlen_220);// L98:L100
extern __size_t_1  (____mbstowcs_alias_225) (__wchar_t_2  * __restrict  ____dst_222, const char  * __restrict  ____src_223, __size_t_1  ____len_224);// L101:L104
extern __size_t_1  (____mbstowcs_chk_warn_230) (__wchar_t_2  * __restrict  ____dst_226, const char  * __restrict  ____src_227, __size_t_1  ____len_228, __size_t_1  ____dstlen_229);// L105:L110
/* no function due to type errors in the function prototype */
extern __size_t_1  (____wcstombs_chk_238) (char  * __restrict  ____dst_234, const __wchar_t_2  * __restrict  ____src_235, __size_t_1  ____len_236, __size_t_1  ____dstlen_237);// L130:L132
extern __size_t_1  (____wcstombs_alias_242) (char  * __restrict  ____dst_239, const __wchar_t_2  * __restrict  ____src_240, __size_t_1  ____len_241);// L133:L136
extern __size_t_1  (____wcstombs_chk_warn_247) (char  * __restrict  ____dst_243, const __wchar_t_2  * __restrict  ____src_244, __size_t_1  ____len_245, __size_t_1  ____dstlen_246);// L137:L141
/* no function due to type errors in the function prototype */
int  * (__cache_251)= ( ( void  * ) 0 );// L6
int  * (__cache_252)= ( ( void  * ) 0 );// L6
int  * (__util_ldap_shm_253);// L7
int  (__apr_shm_attach_255) (int  * (* (__util_ldap_shm_254))) {

{
{



if (__static_condition_default_256) {
if (  __cache_251  )// L11
{

{
{



*  __util_ldap_shm_254  =  __cache_251  ; // L12
return 0 ;// L13
}
}
}
}
if (__static_condition_default_257) {
if (  __cache_252  )// L11
{

{
{



*  __util_ldap_shm_254  =  __cache_252  ; // L12
return 0 ;// L13
}
}
}
}
return - 1 ;// L15
}
}


}
int  (__apr_shm_create_259) (int  * (* (__util_ldap_shm_258))) {

{
{



if (__static_condition_default_256) {
if (  __cache_251  )// L20
{
return 2 ;// L21
}
}
if (__static_condition_default_257) {
if (  __cache_252  )// L20
{
return 2 ;// L21
}
}
if (__static_condition_default_256) {
 __cache_251  = malloc (sizeof(int)) ; // L22
}
if (__static_condition_default_257) {
 __cache_252  = malloc (sizeof(int)) ; // L22
}
if (__static_condition_default_256) {
*  __util_ldap_shm_258  =  __cache_251  ; // L23
}
if (__static_condition_default_257) {
*  __util_ldap_shm_258  =  __cache_252  ; // L23
}
return 0 ;// L24
}
}


}
int  (__util_ldap_cache_init_261) () {

{
{



int  __result_260=  __apr_shm_create_259  (&  __util_ldap_shm_253 );// L30

if (__static_condition_default_262) {
if (  __result_260  != 1 )// L31
{

{
{



return  __result_260  ;// L32
}
}
}
}
if (__static_condition_default_263) {
return 1 ;// L35
}
if (__static_condition_default_262) {
return 1 ;// L35
}
}
}


}
int  (__main_264) (void  ) {

{
{



if (__static_condition_default_265) {
if ( rand( ) % 2 )// L40
{

{
{



if (__static_condition_default_266) {
 __cache_251  = malloc (sizeof(int)) ; // L41
}
if (__static_condition_default_267) {
 __cache_252  = malloc (sizeof(int)) ; // L41
}
}
}
}
}
if (__static_condition_default_268) {
if ( rand( ) % 2 )// L40
{

{
{



if (__static_condition_default_269) {
 __cache_251  = malloc (sizeof(int)) ; // L41
}
if (__static_condition_default_270) {
 __cache_252  = malloc (sizeof(int)) ; // L41
}
}
}
}
}
 __util_ldap_cache_init_261 ( ) ; // L43
return 0 ;// L44
}
}


}

