#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_273;
extern const bool __static_condition_default_259;
extern const bool __static_condition_default_271;
extern const bool __static_condition_default_210;
extern const bool __static_condition_default_269;
extern const bool __static_condition_default_241;
extern const bool __static_condition_default_265;
extern const bool __static_condition_default_190;
extern const bool __static_condition_default_258;
extern const bool __static_condition_default_264;
extern const bool __static_condition_default_197;
extern const bool __static_condition_default_238;
extern const bool __static_condition_default_272;
extern const bool __static_condition_default_205;
extern const bool __static_condition_default_243;
extern const bool __static_condition_default_206;
extern const bool __static_condition_default_242;
extern const bool __static_condition_default_240;
extern const bool __static_condition_default_246;
extern const bool __static_condition_default_255;
extern const bool __static_condition_default_262;
extern const bool __static_condition_default_263;
extern const bool __static_condition_default_244;
extern const bool __static_condition_default_28;
extern const bool __static_condition_default_253;
extern const bool __static_condition_default_250;
extern const bool __static_condition_default_19;
extern const bool __static_condition_default_245;
extern const bool __static_condition_default_266;
extern const bool __static_condition_default_223;
extern const bool __static_condition_default_260;
extern const bool __static_condition_default_226;
extern const bool __static_condition_default_261;
extern const bool __static_condition_default_270;
extern const bool __static_condition_default_239;
extern const bool __static_condition_default_254;
extern const bool __static_condition_default_230;
extern const bool __static_condition_default_267;
void __static_initializer_default() {
__static_renaming("____assert_fail_4", "__assert_fail");
__static_renaming("____assert_perror_fail_9", "__assert_perror_fail");
__static_renaming("____assert_13", "__assert");
__static_renaming("__ptrdiff_t_14", "ptrdiff_t");
__static_renaming("__size_t_15", "size_t");
__static_renaming("__memmove_23", "memmove");
__static_renaming("__memset_32", "memset");
__static_renaming("__memset_33", "memset");
__static_renaming("__memcmp_37", "memcmp");
__static_renaming("__memchr_41", "memchr");
__static_renaming("__strcpy_44", "strcpy");
__static_renaming("__strncpy_48", "strncpy");
__static_renaming("__strcat_51", "strcat");
__static_renaming("__strncat_55", "strncat");
__static_renaming("__strcmp_58", "strcmp");
__static_renaming("__strncmp_62", "strncmp");
__static_renaming("__strcoll_65", "strcoll");
__static_renaming("__strxfrm_69", "strxfrm");
__static_renaming("____locale_t_77", "__locale_t");
__static_renaming("__locale_t_78", "locale_t");
__static_renaming("__strcoll_l_82", "strcoll_l");
__static_renaming("__strxfrm_l_87", "strxfrm_l");
__static_renaming("__strdup_89", "strdup");
__static_renaming("__strndup_92", "strndup");
__static_renaming("__strchr_95", "strchr");
__static_renaming("__strrchr_98", "strrchr");
__static_renaming("__strcspn_101", "strcspn");
__static_renaming("__strspn_104", "strspn");
__static_renaming("__strpbrk_107", "strpbrk");
__static_renaming("__strstr_110", "strstr");
__static_renaming("__strtok_113", "strtok");
__static_renaming("____strtok_r_117", "__strtok_r");
__static_renaming("__strtok_r_121", "strtok_r");
__static_renaming("__strlen_123", "strlen");
__static_renaming("__strlen_124", "strlen");
__static_renaming("__strnlen_127", "strnlen");
__static_renaming("__strerror_129", "strerror");
__static_renaming("__strerror_130", "strerror");
__static_renaming("__strerror_r_134", "strerror_r");
__static_renaming("__strerror_l_137", "strerror_l");
__static_renaming("____bzero_140", "__bzero");
__static_renaming("____bzero_141", "__bzero");
__static_renaming("__bcopy_145", "bcopy");
__static_renaming("__bzero_148", "bzero");
__static_renaming("__bcmp_152", "bcmp");
__static_renaming("__index_155", "index");
__static_renaming("__rindex_158", "rindex");
__static_renaming("__ffs_160", "ffs");
__static_renaming("__strcasecmp_163", "strcasecmp");
__static_renaming("__strncasecmp_167", "strncasecmp");
__static_renaming("__strsep_170", "strsep");
__static_renaming("__strsignal_172", "strsignal");
__static_renaming("____stpcpy_175", "__stpcpy");
__static_renaming("__stpcpy_178", "stpcpy");
__static_renaming("____stpncpy_182", "__stpncpy");
__static_renaming("__stpncpy_186", "stpncpy");
__static_renaming("____stpncpy_chk_215", "__stpncpy_chk");
__static_renaming("____stpncpy_alias_219", "__stpncpy_alias");
__static_renaming("__pfnnid_map_231", "pfnnid_map");
__static_renaming("__pfnnid_map_232", "pfnnid_map");
__static_renaming("__pfnnid_map_233", "pfnnid_map");
__static_renaming("__max_pfn_234", "max_pfn");
__static_renaming("__r_236", "r");
__static_renaming("__pfn_to_nid_237", "pfn_to_nid");
__static_renaming("__nid_248", "nid");
__static_renaming("__pfn_valid_249", "pfn_valid");
__static_renaming("__pfn_251", "pfn");
__static_renaming("__kpageflags_read_252", "kpageflags_read");
__static_renaming("__setup_bootmem_256", "setup_bootmem");
__static_renaming("__setup_bootmem_257", "setup_bootmem");
__static_renaming("__main_268", "main");

__static_condition_renaming("__static_condition_default_19", "(defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_28", "(defined CONFIG_DISCONTIGMEM) && !(defined __STRICT_ANSI__)");
__static_condition_renaming("__static_condition_default_190", "(defined CONFIG_DISCONTIGMEM) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_197", "(defined CONFIG_DISCONTIGMEM) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_205", "(defined CONFIG_DISCONTIGMEM) && (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_206", "(defined CONFIG_DISCONTIGMEM) && !(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_210", "(defined CONFIG_DISCONTIGMEM) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_223", "(defined CONFIG_DISCONTIGMEM) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_226", "(defined CONFIG_DISCONTIGMEM) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_230", "(defined CONFIG_DISCONTIGMEM) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_238", "(defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_239", "(defined CONFIG_DISCONTIGMEM) && (defined NDEBUG)");
__static_condition_renaming("__static_condition_default_240", "(defined CONFIG_DISCONTIGMEM) && !(defined NDEBUG) && !(defined _ASSERT_H_DECLS)");
__static_condition_renaming("__static_condition_default_241", "(defined CONFIG_DISCONTIGMEM) && !(defined NDEBUG) && (defined _ASSERT_H_DECLS)");
__static_condition_renaming("__static_condition_default_242", "(defined CONFIG_DISCONTIGMEM) && !(defined _FORTIFY_SOURCE) || (defined CONFIG_DISCONTIGMEM) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) || (defined CONFIG_DISCONTIGMEM) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) || (defined CONFIG_DISCONTIGMEM) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_243", "(defined CONFIG_DISCONTIGMEM) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_244", "(defined CONFIG_DISCONTIGMEM) && (defined NDEBUG)");
__static_condition_renaming("__static_condition_default_245", "(defined CONFIG_DISCONTIGMEM) && !(defined NDEBUG) && !(defined _ASSERT_H_DECLS)");
__static_condition_renaming("__static_condition_default_246", "(defined CONFIG_DISCONTIGMEM) && !(defined NDEBUG) && (defined _ASSERT_H_DECLS)");
__static_condition_renaming("__static_condition_default_250", "(defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_253", "(defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_254", "!(defined CONFIG_DISCONTIGMEM) && (defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_255", "(defined CONFIG_DISCONTIGMEM) && (defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_258", "!(defined CONFIG_DISCONTIGMEM) && !(defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_259", "(defined CONFIG_DISCONTIGMEM) && !(defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_260", "(defined CONFIG_DISCONTIGMEM) && (defined __STRICT_ANSI__) && !(defined _FORTIFY_SOURCE) && !(defined CONFIG_PROC_PAGE_MONITOR) || (defined CONFIG_DISCONTIGMEM) && (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined CONFIG_PROC_PAGE_MONITOR) || (defined CONFIG_DISCONTIGMEM) && (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined CONFIG_PROC_PAGE_MONITOR) || (defined CONFIG_DISCONTIGMEM) && (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_261", "(defined CONFIG_DISCONTIGMEM) && !(defined __STRICT_ANSI__) && !(defined _FORTIFY_SOURCE) && !(defined CONFIG_PROC_PAGE_MONITOR) || (defined CONFIG_DISCONTIGMEM) && !(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined CONFIG_PROC_PAGE_MONITOR) || (defined CONFIG_DISCONTIGMEM) && !(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined CONFIG_PROC_PAGE_MONITOR) || (defined CONFIG_DISCONTIGMEM) && !(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_262", "(defined CONFIG_DISCONTIGMEM) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_263", "!(defined CONFIG_DISCONTIGMEM) && (defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_264", "(defined CONFIG_DISCONTIGMEM) && (defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_265", "(defined CONFIG_DISCONTIGMEM) && (defined __STRICT_ANSI__) && !(defined _FORTIFY_SOURCE) && (defined CONFIG_PROC_PAGE_MONITOR) || (defined CONFIG_DISCONTIGMEM) && (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && (defined CONFIG_PROC_PAGE_MONITOR) || (defined CONFIG_DISCONTIGMEM) && (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && (defined CONFIG_PROC_PAGE_MONITOR) || (defined CONFIG_DISCONTIGMEM) && (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && (defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_266", "(defined CONFIG_DISCONTIGMEM) && !(defined __STRICT_ANSI__) && !(defined _FORTIFY_SOURCE) && (defined CONFIG_PROC_PAGE_MONITOR) || (defined CONFIG_DISCONTIGMEM) && !(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && (defined CONFIG_PROC_PAGE_MONITOR) || (defined CONFIG_DISCONTIGMEM) && !(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && (defined CONFIG_PROC_PAGE_MONITOR) || (defined CONFIG_DISCONTIGMEM) && !(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && (defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_267", "(defined CONFIG_DISCONTIGMEM) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && (defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_269", "!(defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_270", "(defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_271", "!(defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_272", "(defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_273", "(defined CONFIG_DISCONTIGMEM) && (defined __CORRECT_ISO_CPP_STRING_H_PROTO)");

if (__static_condition_default_273) {
__static_parse_error("Unable to parse");
}
};
typedef long int  __ptrdiff_t_14;// L143:L324
typedef long unsigned int  __size_t_15;// L177:L209
struct ____locale_struct_71 {
struct __forward_tag_reference_70  * (____locales_72[13]);// L0
const unsigned short int  * (____ctype_b_73);// L33
const int  * (____ctype_tolower_74);// L34
const int  * (____ctype_toupper_75);// L35
const char  * (____names_76[13]);// L38
};
typedef struct ____locale_struct_71  * (____locale_t_77);// L27:L39
typedef ____locale_t_77  __locale_t_78;// L42

struct __forward_tag_reference_70 { // generated union of struct variations
union {
};
};

extern void  (____assert_fail_4) (const char  * (____assertion_0), const char  * (____file_1), unsigned int  ____line_2, const char  * (____function_3));// L69:L71
extern void  (____assert_perror_fail_9) (int  ____errnum_5, const char  * (____file_6), unsigned int  ____line_7, const char  * (____function_8));// L74:L76
extern void  (____assert_13) (const char  * (____assertion_10), const char  * (____file_11), int  ____line_12);// L81:L82
// typedef moved to top of scope
// typedef moved to top of scope
extern void  * ((__memmove_23) (void  * (____dest_20), const void  * (____src_21), __size_t_15  ____n_22));// L46:L47
extern void  * ((__memset_32) (void  * (____s_29), int  ____c_30, __size_t_15  ____n_31));// L62
extern void  * ((__memset_33) (void  * (____s_29), int  ____c_30, __size_t_15  ____n_31));// L62
extern int  (__memcmp_37) (const void  * (____s1_34), const void  * (____s2_35), __size_t_15  ____n_36);// L65:L66
extern void  * ((__memchr_41) (const void  * (____s_38), int  ____c_39, __size_t_15  ____n_40));// L92:L93
extern char  * ((__strcpy_44) (char  * __restrict  ____dest_42, const char  * __restrict  ____src_43));// L125:L126
extern char  * ((__strncpy_48) (char  * __restrict  ____dest_45, const char  * __restrict  ____src_46, __size_t_15  ____n_47));// L128:L130
extern char  * ((__strcat_51) (char  * __restrict  ____dest_49, const char  * __restrict  ____src_50));// L133:L134
extern char  * ((__strncat_55) (char  * __restrict  ____dest_52, const char  * __restrict  ____src_53, __size_t_15  ____n_54));// L136:L137
extern int  (__strcmp_58) (const char  * (____s1_56), const char  * (____s2_57));// L140:L141
extern int  (__strncmp_62) (const char  * (____s1_59), const char  * (____s2_60), __size_t_15  ____n_61);// L143:L144
extern int  (__strcoll_65) (const char  * (____s1_63), const char  * (____s2_64));// L147:L148
extern __size_t_15  (__strxfrm_69) (char  * __restrict  ____dest_66, const char  * __restrict  ____src_67, __size_t_15  ____n_68);// L150:L152
// typedef moved to top of scope
// typedef moved to top of scope
extern int  (__strcoll_l_82) (const char  * (____s1_79), const char  * (____s2_80), ____locale_t_77  ____l_81);// L162:L163
extern __size_t_15  (__strxfrm_l_87) (char  * (____dest_83), const char  * (____src_84), __size_t_15  ____n_85, ____locale_t_77  ____l_86);// L165:L166
extern char  * ((__strdup_89) (const char  * (____s_88)));// L171:L172
extern char  * ((__strndup_92) (const char  * (____string_90), __size_t_15  ____n_91));// L179:L180
extern char  * ((__strchr_95) (const char  * (____s_93), int  ____c_94));// L231:L232
extern char  * ((__strrchr_98) (const char  * (____s_96), int  ____c_97));// L258:L259
extern __size_t_15  (__strcspn_101) (const char  * (____s_99), const char  * (____reject_100));// L280:L281
extern __size_t_15  (__strspn_104) (const char  * (____s_102), const char  * (____accept_103));// L284:L285
extern char  * ((__strpbrk_107) (const char  * (____s_105), const char  * (____accept_106)));// L310:L311
extern char  * ((__strstr_110) (const char  * (____haystack_108), const char  * (____needle_109)));// L337:L338
extern char  * ((__strtok_113) (char  * __restrict  ____s_111, const char  * __restrict  ____delim_112));// L343:L344
extern char  * ((____strtok_r_117) (char  * __restrict  ____s_114, const char  * __restrict  ____delim_115, char  * (* __restrict  ____save_ptr_116)));// L349:L352
extern char  * ((__strtok_r_121) (char  * __restrict  ____s_118, const char  * __restrict  ____delim_119, char  * (* __restrict  ____save_ptr_120)));// L354:L356
extern __size_t_15  (__strlen_123) (const char  * (____s_122));// L394:L395
extern __size_t_15  (__strlen_124) (const char  * (____s_122));// L394:L395
extern __size_t_15  (__strnlen_127) (const char  * (____string_125), __size_t_15  ____maxlen_126);// L401:L402
extern char  * ((__strerror_129) (int  ____errnum_128));// L408
extern char  * ((__strerror_130) (int  ____errnum_128));// L408
extern int  (__strerror_r_134) (int  ____errnum_131, char  * (____buf_132), __size_t_15  ____buflen_133);// L422:L424
extern char  * ((__strerror_l_137) (int  ____errnum_135, ____locale_t_77  ____l_136));// L440
extern void  (____bzero_140) (void  * (____s_138), __size_t_15  ____n_139);// L446
extern void  (____bzero_141) (void  * (____s_138), __size_t_15  ____n_139);// L446
extern void  (__bcopy_145) (const void  * (____src_142), void  * (____dest_143), __size_t_15  ____n_144);// L450:L451
extern void  (__bzero_148) (void  * (____s_146), __size_t_15  ____n_147);// L454
extern int  (__bcmp_152) (const void  * (____s1_149), const void  * (____s2_150), __size_t_15  ____n_151);// L457:L458
extern char  * ((__index_155) (const char  * (____s_153), int  ____c_154));// L484:L485
extern char  * ((__rindex_158) (const char  * (____s_156), int  ____c_157));// L512:L513
extern int  (__ffs_160) (int  ____i_159);// L518
extern int  (__strcasecmp_163) (const char  * (____s1_161), const char  * (____s2_162));// L529:L530
extern int  (__strncasecmp_167) (const char  * (____s1_164), const char  * (____s2_165), __size_t_15  ____n_166);// L533:L534
extern char  * ((__strsep_170) (char  * (* __restrict  ____stringp_168), const char  * __restrict  ____delim_169));// L552:L554
extern char  * ((__strsignal_172) (int  ____sig_171));// L559
extern char  * ((____stpcpy_175) (char  * __restrict  ____dest_173, const char  * __restrict  ____src_174));// L562:L563
extern char  * ((__stpcpy_178) (char  * __restrict  ____dest_176, const char  * __restrict  ____src_177));// L564:L565
extern char  * ((____stpncpy_182) (char  * __restrict  ____dest_179, const char  * __restrict  ____src_180, __size_t_15  ____n_181));// L569:L571
extern char  * ((__stpncpy_186) (char  * __restrict  ____dest_183, const char  * __restrict  ____src_184, __size_t_15  ____n_185));// L572:L574
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
extern char  * ((____stpncpy_chk_215) (char  * (____dest_211), const char  * (____src_212), __size_t_15  ____n_213, __size_t_15  ____destlen_214));// L130:L131
extern char  * ((____stpncpy_alias_219) (char  * (____dest_216), const char  * (____src_217), __size_t_15  ____n_218));// L132:L133
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
unsigned char  __pfnnid_map_231[512];// L9
unsigned char  __pfnnid_map_232[512];// L9
unsigned char  __pfnnid_map_233[512];// L9
unsigned long  __max_pfn_234= 512;// L10
int  (__pfn_to_nid_237) (unsigned long  __pfn_235) {

if (__static_condition_default_238) {

{// L14
{



unsigned char  __r_236;// L15

if (__static_condition_default_239) {
( ( void   ) ( 0 ) ) ; // L17:L50
}
if (__static_condition_default_240) {
( (  __pfn_235  < 512 ) ? ( void   ) ( 0 ) :  ____assert_fail_4  ("pfn < PFNNID_MAP_MAX","/home/kisamefishfry/Documents/xtc-dev/fonda/cpp_testsuite/varBugs/LINUX/ae249b5fa27.c",17, __PRETTY_FUNCTION__ ) ) ; // L17:L91
}
if (__static_condition_default_241) {
__static_type_error("type error") ; // L17:L91
}
if (__static_condition_default_242) {
 __r_236  =  __pfnnid_map_231  [  __pfn_235  ] ; // L18
}
if (__static_condition_default_243) {
 __r_236  =  __pfnnid_map_233  [  __pfn_235  ] ; // L18
}
if (__static_condition_default_244) {
( ( void   ) ( 0 ) ) ; // L19:L50
}
if (__static_condition_default_245) {
( (  __r_236  != 0xff ) ? ( void   ) ( 0 ) :  ____assert_fail_4  ("r != 0xff","/home/kisamefishfry/Documents/xtc-dev/fonda/cpp_testsuite/varBugs/LINUX/ae249b5fa27.c",19, __PRETTY_FUNCTION__ ) ) ; // L19:L91
}
if (__static_condition_default_246) {
__static_type_error("type error") ; // L19:L91
}
return ( int   )  __r_236  ;// L21
}
}// L22


}
}
int  (__pfn_valid_249) (int  __pfn_247) {

if (__static_condition_default_250) {

{// L25
{



int  __nid_248=  __pfn_to_nid_237  ( __pfn_247 );// L26

return (  __nid_248  >= 0 ) ;// L28
}
}// L29


}
}
int  (__kpageflags_read_252) () {

if (__static_condition_default_253) {

{// L38
{



unsigned int  __pfn_251= 0;// L39

for (  ;  __pfn_251  <  __max_pfn_234  ;  __pfn_251  ++ )// L41
{

{// L41
{



if (__static_condition_default_254) {
if ( ( 1 ) )// L42
{
 ; // L43
}
}
if (__static_condition_default_255) {
if (  __pfn_valid_249  ( __pfn_251 ) )// L42
{
 ; // L43
}
}
}
}// L44
}
return 0 ;// L46
}
}// L47


}
}
void  (__setup_bootmem_256) (void  ) {

{
if (__static_condition_default_258) {

{// L51
{



}
}// L55


}

if (__static_condition_default_259) {

{// L51
{



if (__static_condition_default_260) {
 __memset_32  ( __pfnnid_map_231 ,0xff,sizeof((  __pfnnid_map_231  ))) ; // L53
}
if (__static_condition_default_261) {
 __memset_33  ( __pfnnid_map_231 ,0xff,sizeof((  __pfnnid_map_231  ))) ; // L53
}
if (__static_condition_default_262) {
__static_type_error("type error") ; // L53
}
}
}// L55


}

}}
void  (__setup_bootmem_257) (void  ) {

{
if (__static_condition_default_263) {

{// L51
{



}
}// L55


}

if (__static_condition_default_264) {

{// L51
{



if (__static_condition_default_265) {
 __memset_32  ( __pfnnid_map_231 ,0xff,sizeof((  __pfnnid_map_231  ))) ; // L53
}
if (__static_condition_default_266) {
 __memset_33  ( __pfnnid_map_231 ,0xff,sizeof((  __pfnnid_map_231  ))) ; // L53
}
if (__static_condition_default_267) {
__static_type_error("type error") ; // L53
}
}
}// L55


}

}}
int  (__main_268) () {

{// L58
{



if (__static_condition_default_269) {
 __setup_bootmem_256 ( ) ; // L59
}
if (__static_condition_default_270) {
 __setup_bootmem_257 ( ) ; // L59
}
if (__static_condition_default_253) {
 __kpageflags_read_252 ( ) ; // L61
}
if (__static_condition_default_271) {
return 0 ;// L63
}
if (__static_condition_default_272) {
return 0 ;// L63
}
}
}// L64


}

