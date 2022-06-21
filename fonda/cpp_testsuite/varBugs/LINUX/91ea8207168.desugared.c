#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_245;
extern const bool __static_condition_default_260;
extern const bool __static_condition_default_27;
extern const bool __static_condition_default_249;
extern const bool __static_condition_default_210;
extern const bool __static_condition_default_237;
extern const bool __static_condition_default_240;
extern const bool __static_condition_default_252;
extern const bool __static_condition_default_263;
extern const bool __static_condition_default_206;
extern const bool __static_condition_default_250;
extern const bool __static_condition_default_226;
extern const bool __static_condition_default_255;
extern const bool __static_condition_default_190;
extern const bool __static_condition_default_238;
extern const bool __static_condition_default_231;
extern const bool __static_condition_default_261;
extern const bool __static_condition_default_197;
extern const bool __static_condition_default_205;
extern const bool __static_condition_default_265;
extern const bool __static_condition_default_239;
extern const bool __static_condition_default_244;
extern const bool __static_condition_default_256;
extern const bool __static_condition_default_251;
extern const bool __static_condition_default_257;
extern const bool __static_condition_default_230;
extern const bool __static_condition_default_264;
extern const bool __static_condition_default_248;
extern const bool __static_condition_default_262;
extern const bool __static_condition_default_223;
void __static_initializer_default() {
__static_renaming("____assert_fail_4", "__assert_fail");
__static_renaming("____assert_perror_fail_9", "__assert_perror_fail");
__static_renaming("____assert_13", "__assert");
__static_renaming("__ptrdiff_t_14", "ptrdiff_t");
__static_renaming("__size_t_15", "size_t");
__static_renaming("__memmove_22", "memmove");
__static_renaming("__memset_31", "memset");
__static_renaming("__memset_32", "memset");
__static_renaming("__memcmp_36", "memcmp");
__static_renaming("__memchr_40", "memchr");
__static_renaming("__strcpy_43", "strcpy");
__static_renaming("__strncpy_47", "strncpy");
__static_renaming("__strcat_50", "strcat");
__static_renaming("__strncat_54", "strncat");
__static_renaming("__strcmp_57", "strcmp");
__static_renaming("__strncmp_61", "strncmp");
__static_renaming("__strcoll_64", "strcoll");
__static_renaming("__strxfrm_68", "strxfrm");
__static_renaming("____locale_t_76", "__locale_t");
__static_renaming("__locale_t_77", "locale_t");
__static_renaming("__strcoll_l_81", "strcoll_l");
__static_renaming("__strxfrm_l_86", "strxfrm_l");
__static_renaming("__strdup_88", "strdup");
__static_renaming("__strndup_91", "strndup");
__static_renaming("__strchr_94", "strchr");
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
__static_renaming("__node_data_232", "node_data");
__static_renaming("__pfnnid_map_233", "pfnnid_map");
__static_renaming("__max_pfn_234", "max_pfn");
__static_renaming("__pfn_to_nid_236", "pfn_to_nid");
__static_renaming("__nid_242", "nid");
__static_renaming("__pfn_valid_243", "pfn_valid");
__static_renaming("__setup_bootmem_246", "setup_bootmem");
__static_renaming("__setup_bootmem_247", "setup_bootmem");
__static_renaming("__pfn_253", "pfn");
__static_renaming("__kpageflags_read_254", "kpageflags_read");
__static_renaming("__main_258", "main");
__static_renaming("__main_259", "main");

__static_condition_renaming("__static_condition_default_27", "!(defined __STRICT_ANSI__)");
__static_condition_renaming("__static_condition_default_190", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_197", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_205", "(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_206", "!(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_210", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_223", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_226", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_230", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_231", "(defined CONFIG_NODES_SHIFT) && (defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_237", "(defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_238", "(defined NDEBUG) && (defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_239", "!(defined NDEBUG) && !(defined _ASSERT_H_DECLS) && (defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_240", "!(defined NDEBUG) && (defined _ASSERT_H_DECLS) && (defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_244", "!(defined CONFIG_NODES_SHIFT) && (defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_245", "(defined CONFIG_NODES_SHIFT) && (defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_248", "!(defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_249", "(defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_250", "(defined __STRICT_ANSI__) && !(defined _FORTIFY_SOURCE) && (defined CONFIG_DISCONTIGMEM) || (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && (defined CONFIG_DISCONTIGMEM) || (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && (defined CONFIG_DISCONTIGMEM) || (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && (defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_251", "!(defined __STRICT_ANSI__) && !(defined _FORTIFY_SOURCE) && (defined CONFIG_DISCONTIGMEM) || !(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && (defined CONFIG_DISCONTIGMEM) || !(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && (defined CONFIG_DISCONTIGMEM) || !(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && (defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_252", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && (defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_255", "(defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_256", "!(defined CONFIG_DISCONTIGMEM) && (defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_257", "(defined CONFIG_DISCONTIGMEM) && (defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_260", "!(defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_261", "!(defined CONFIG_DISCONTIGMEM) && !(defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_262", "(defined CONFIG_DISCONTIGMEM) && !(defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_263", "(defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_264", "!(defined CONFIG_DISCONTIGMEM) && (defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_265", "(defined CONFIG_DISCONTIGMEM) && (defined CONFIG_PROC_PAGE_MONITOR)");

};
typedef long int  __ptrdiff_t_14;// L143:L324
typedef long unsigned int  __size_t_15;// L177:L209
struct ____locale_struct_70 {
struct __forward_tag_reference_69  * (____locales_71[13]);// L0
const unsigned short int  * (____ctype_b_72);// L33
const int  * (____ctype_tolower_73);// L34
const int  * (____ctype_toupper_74);// L35
const char  * (____names_75[13]);// L38
};
typedef struct ____locale_struct_70  * (____locale_t_76);// L27:L39
typedef ____locale_t_76  __locale_t_77;// L42

struct __forward_tag_reference_69 { // generated union of struct variations
union {
};
};

extern void  (____assert_fail_4) (const char  * (____assertion_0), const char  * (____file_1), unsigned int  ____line_2, const char  * (____function_3));// L69:L71
extern void  (____assert_perror_fail_9) (int  ____errnum_5, const char  * (____file_6), unsigned int  ____line_7, const char  * (____function_8));// L74:L76
extern void  (____assert_13) (const char  * (____assertion_10), const char  * (____file_11), int  ____line_12);// L81:L82
// typedef moved to top of scope
// typedef moved to top of scope
extern void  * ((__memmove_22) (void  * (____dest_19), const void  * (____src_20), __size_t_15  ____n_21));// L46:L47
extern void  * ((__memset_31) (void  * (____s_28), int  ____c_29, __size_t_15  ____n_30));// L62
extern void  * ((__memset_32) (void  * (____s_28), int  ____c_29, __size_t_15  ____n_30));// L62
extern int  (__memcmp_36) (const void  * (____s1_33), const void  * (____s2_34), __size_t_15  ____n_35);// L65:L66
extern void  * ((__memchr_40) (const void  * (____s_37), int  ____c_38, __size_t_15  ____n_39));// L92:L93
extern char  * ((__strcpy_43) (char  * __restrict  ____dest_41, const char  * __restrict  ____src_42));// L125:L126
extern char  * ((__strncpy_47) (char  * __restrict  ____dest_44, const char  * __restrict  ____src_45, __size_t_15  ____n_46));// L128:L130
extern char  * ((__strcat_50) (char  * __restrict  ____dest_48, const char  * __restrict  ____src_49));// L133:L134
extern char  * ((__strncat_54) (char  * __restrict  ____dest_51, const char  * __restrict  ____src_52, __size_t_15  ____n_53));// L136:L137
extern int  (__strcmp_57) (const char  * (____s1_55), const char  * (____s2_56));// L140:L141
extern int  (__strncmp_61) (const char  * (____s1_58), const char  * (____s2_59), __size_t_15  ____n_60);// L143:L144
extern int  (__strcoll_64) (const char  * (____s1_62), const char  * (____s2_63));// L147:L148
extern __size_t_15  (__strxfrm_68) (char  * __restrict  ____dest_65, const char  * __restrict  ____src_66, __size_t_15  ____n_67);// L150:L152
// typedef moved to top of scope
// typedef moved to top of scope
extern int  (__strcoll_l_81) (const char  * (____s1_78), const char  * (____s2_79), ____locale_t_76  ____l_80);// L162:L163
extern __size_t_15  (__strxfrm_l_86) (char  * (____dest_82), const char  * (____src_83), __size_t_15  ____n_84, ____locale_t_76  ____l_85);// L165:L166
extern char  * ((__strdup_88) (const char  * (____s_87)));// L171:L172
extern char  * ((__strndup_91) (const char  * (____string_89), __size_t_15  ____n_90));// L179:L180
extern char  * ((__strchr_94) (const char  * (____s_92), int  ____c_93));// L231:L232
extern char  * ((__strchr_95) (const char  * (____s_92), int  ____c_93));// L231:L232
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
extern char  * ((__strerror_l_137) (int  ____errnum_135, ____locale_t_76  ____l_136));// L440
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
int  __node_data_232[( 1 << 0 )];// L19
unsigned char  __pfnnid_map_233[512];// L24
unsigned long  __max_pfn_234= 512;// L25
int  (__pfn_to_nid_236) (unsigned int  __pfn_235) {

if (__static_condition_default_237) {

{
{



if (__static_condition_default_238) {
( ( void   ) ( 0 ) ) ; // L29:L50
}
if (__static_condition_default_239) {
( (  __pfn_235  < 512 ) ? ( void   ) ( 0 ) :  ____assert_fail_4  ("pfn < PFNNID_MAP_MAX","/home/kisamefishfry/Documents/xtc-dev/fonda/cpp_testsuite/varBugs/LINUX/91ea8207168.c",29, __PRETTY_FUNCTION__ ) ) ; // L29:L91
}
if (__static_condition_default_240) {
__static_type_error("type error") ; // L29:L91
}
return ( int   )  __pfnnid_map_233  [  __pfn_235  ] ;// L30
}
}


}
}
int  (__pfn_valid_243) (unsigned int  __pfn_241) {

if (__static_condition_default_237) {

{
{



int  __nid_242=  __pfn_to_nid_236  ( __pfn_241 );// L35

if (  __nid_242  >= 0 )// L37
{
if (__static_condition_default_244) {
return (  __pfn_241  < (  __node_data_232  [  __nid_242  ] ) ) ;// L38
}
if (__static_condition_default_245) {
__static_type_error("invalid type found in return expression");
}
}
return 0 ;// L39
}
}


}
}
void  (__setup_bootmem_246) (void  ) {

{
if (__static_condition_default_248) {

{
{



}
}


}

}}
void  (__setup_bootmem_247) (void  ) {

{
if (__static_condition_default_249) {

{
{



if (__static_condition_default_250) {
 __memset_31  ( __pfnnid_map_233 ,0xff,sizeof((  __pfnnid_map_233  ))) ; // L52
}
if (__static_condition_default_251) {
 __memset_32  ( __pfnnid_map_233 ,0xff,sizeof((  __pfnnid_map_233  ))) ; // L52
}
if (__static_condition_default_252) {
__static_type_error("type error") ; // L52
}
}
}


}

}}
int  (__kpageflags_read_254) () {

if (__static_condition_default_255) {

{
{



unsigned int  __pfn_253= 0;// L59

if (__static_condition_default_256) {
for (  ;  __pfn_253  < 0 ;  __pfn_253  ++ )// L61
{

{
{



if ( ( 1 ) )// L62
{
 ; // L63
}
}
}
}
}
if (__static_condition_default_257) {
for (  ;  __pfn_253  <  __max_pfn_234  ;  __pfn_253  ++ )// L61
{

{
{



if (  __pfn_valid_243  ( __pfn_253 ) )// L62
{
 ; // L63
}
}
}
}
}
return 0 ;// L66
}
}


}
}
int  (__main_258) () {

if (__static_condition_default_260) {

{
{



if (__static_condition_default_261) {
 __setup_bootmem_246 ( ) ; // L72
}
if (__static_condition_default_262) {
 __setup_bootmem_247 ( ) ; // L72
}
return 0 ;// L76
}
}


}
}
int  (__main_259) () {

if (__static_condition_default_263) {

{
{



if (__static_condition_default_264) {
 __setup_bootmem_246 ( ) ; // L72
}
if (__static_condition_default_265) {
 __setup_bootmem_247 ( ) ; // L72
}
 __kpageflags_read_254 ( ) ; // L74
return 0 ;// L76
}
}


}
}

