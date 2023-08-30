#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_209;
extern const bool __static_condition_default_263;
extern const bool __static_condition_default_229;
extern const bool __static_condition_default_237;
extern const bool __static_condition_default_247;
extern const bool __static_condition_default_255;
extern const bool __static_condition_default_189;
extern const bool __static_condition_default_27;
extern const bool __static_condition_default_236;
extern const bool __static_condition_default_248;
extern const bool __static_condition_default_244;
extern const bool __static_condition_default_250;
extern const bool __static_condition_default_238;
extern const bool __static_condition_default_196;
extern const bool __static_condition_default_264;
extern const bool __static_condition_default_230;
extern const bool __static_condition_default_243;
extern const bool __static_condition_default_265;
extern const bool __static_condition_default_251;
extern const bool __static_condition_default_222;
extern const bool __static_condition_default_261;
extern const bool __static_condition_default_204;
extern const bool __static_condition_default_239;
extern const bool __static_condition_default_254;
extern const bool __static_condition_default_256;
extern const bool __static_condition_default_262;
extern const bool __static_condition_default_259;
extern const bool __static_condition_default_260;
extern const bool __static_condition_default_249;
extern const bool __static_condition_default_225;
extern const bool __static_condition_default_205;
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
__static_renaming("__strrchr_97", "strrchr");
__static_renaming("__strcspn_100", "strcspn");
__static_renaming("__strspn_103", "strspn");
__static_renaming("__strpbrk_106", "strpbrk");
__static_renaming("__strstr_109", "strstr");
__static_renaming("__strtok_112", "strtok");
__static_renaming("____strtok_r_116", "__strtok_r");
__static_renaming("__strtok_r_120", "strtok_r");
__static_renaming("__strlen_122", "strlen");
__static_renaming("__strlen_123", "strlen");
__static_renaming("__strnlen_126", "strnlen");
__static_renaming("__strerror_128", "strerror");
__static_renaming("__strerror_129", "strerror");
__static_renaming("__strerror_r_133", "strerror_r");
__static_renaming("__strerror_l_136", "strerror_l");
__static_renaming("____bzero_139", "__bzero");
__static_renaming("____bzero_140", "__bzero");
__static_renaming("__bcopy_144", "bcopy");
__static_renaming("__bzero_147", "bzero");
__static_renaming("__bcmp_151", "bcmp");
__static_renaming("__index_154", "index");
__static_renaming("__rindex_157", "rindex");
__static_renaming("__ffs_159", "ffs");
__static_renaming("__strcasecmp_162", "strcasecmp");
__static_renaming("__strncasecmp_166", "strncasecmp");
__static_renaming("__strsep_169", "strsep");
__static_renaming("__strsignal_171", "strsignal");
__static_renaming("____stpcpy_174", "__stpcpy");
__static_renaming("__stpcpy_177", "stpcpy");
__static_renaming("____stpncpy_181", "__stpncpy");
__static_renaming("__stpncpy_185", "stpncpy");
__static_renaming("____stpncpy_chk_214", "__stpncpy_chk");
__static_renaming("____stpncpy_alias_218", "__stpncpy_alias");
__static_renaming("__node_data_231", "node_data");
__static_renaming("__pfnnid_map_232", "pfnnid_map");
__static_renaming("__max_pfn_233", "max_pfn");
__static_renaming("__pfn_to_nid_235", "pfn_to_nid");
__static_renaming("__nid_241", "nid");
__static_renaming("__pfn_valid_242", "pfn_valid");
__static_renaming("__setup_bootmem_245", "setup_bootmem");
__static_renaming("__setup_bootmem_246", "setup_bootmem");
__static_renaming("__pfn_252", "pfn");
__static_renaming("__kpageflags_read_253", "kpageflags_read");
__static_renaming("__main_257", "main");
__static_renaming("__main_258", "main");

__static_condition_renaming("__static_condition_default_27", "!(defined __STRICT_ANSI__)");
__static_condition_renaming("__static_condition_default_189", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_196", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_204", "(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_205", "!(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_209", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_222", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_225", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_229", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_230", "(defined CONFIG_NODES_SHIFT) && (defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_236", "(defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_237", "(defined NDEBUG) && (defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_238", "!(defined NDEBUG) && !(defined _ASSERT_H_DECLS) && (defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_239", "!(defined NDEBUG) && (defined _ASSERT_H_DECLS) && (defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_243", "!(defined CONFIG_NODES_SHIFT) && (defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_244", "(defined CONFIG_NODES_SHIFT) && (defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_247", "!(defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_248", "(defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_249", "(defined __STRICT_ANSI__) && !(defined _FORTIFY_SOURCE) && (defined CONFIG_DISCONTIGMEM) || (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && (defined CONFIG_DISCONTIGMEM) || (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && (defined CONFIG_DISCONTIGMEM) || (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && (defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_250", "!(defined __STRICT_ANSI__) && !(defined _FORTIFY_SOURCE) && (defined CONFIG_DISCONTIGMEM) || !(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && (defined CONFIG_DISCONTIGMEM) || !(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && (defined CONFIG_DISCONTIGMEM) || !(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && (defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_251", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && (defined CONFIG_DISCONTIGMEM)");
__static_condition_renaming("__static_condition_default_254", "(defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_255", "!(defined CONFIG_DISCONTIGMEM) && (defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_256", "(defined CONFIG_DISCONTIGMEM) && (defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_259", "!(defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_260", "!(defined CONFIG_DISCONTIGMEM) && !(defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_261", "(defined CONFIG_DISCONTIGMEM) && !(defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_262", "(defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_263", "!(defined CONFIG_DISCONTIGMEM) && (defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_264", "(defined CONFIG_DISCONTIGMEM) && (defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_265", "(defined __CORRECT_ISO_CPP_STRING_H_PROTO)");

if (__static_condition_default_265) {
__static_parse_error("Unable to parse");
}
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
extern char  * ((__strrchr_97) (const char  * (____s_95), int  ____c_96));// L258:L259
extern __size_t_15  (__strcspn_100) (const char  * (____s_98), const char  * (____reject_99));// L280:L281
extern __size_t_15  (__strspn_103) (const char  * (____s_101), const char  * (____accept_102));// L284:L285
extern char  * ((__strpbrk_106) (const char  * (____s_104), const char  * (____accept_105)));// L310:L311
extern char  * ((__strstr_109) (const char  * (____haystack_107), const char  * (____needle_108)));// L337:L338
extern char  * ((__strtok_112) (char  * __restrict  ____s_110, const char  * __restrict  ____delim_111));// L343:L344
extern char  * ((____strtok_r_116) (char  * __restrict  ____s_113, const char  * __restrict  ____delim_114, char  * (* __restrict  ____save_ptr_115)));// L349:L352
extern char  * ((__strtok_r_120) (char  * __restrict  ____s_117, const char  * __restrict  ____delim_118, char  * (* __restrict  ____save_ptr_119)));// L354:L356
extern __size_t_15  (__strlen_122) (const char  * (____s_121));// L394:L395
extern __size_t_15  (__strlen_123) (const char  * (____s_121));// L394:L395
extern __size_t_15  (__strnlen_126) (const char  * (____string_124), __size_t_15  ____maxlen_125);// L401:L402
extern char  * ((__strerror_128) (int  ____errnum_127));// L408
extern char  * ((__strerror_129) (int  ____errnum_127));// L408
extern int  (__strerror_r_133) (int  ____errnum_130, char  * (____buf_131), __size_t_15  ____buflen_132);// L422:L424
extern char  * ((__strerror_l_136) (int  ____errnum_134, ____locale_t_76  ____l_135));// L440
extern void  (____bzero_139) (void  * (____s_137), __size_t_15  ____n_138);// L446
extern void  (____bzero_140) (void  * (____s_137), __size_t_15  ____n_138);// L446
extern void  (__bcopy_144) (const void  * (____src_141), void  * (____dest_142), __size_t_15  ____n_143);// L450:L451
extern void  (__bzero_147) (void  * (____s_145), __size_t_15  ____n_146);// L454
extern int  (__bcmp_151) (const void  * (____s1_148), const void  * (____s2_149), __size_t_15  ____n_150);// L457:L458
extern char  * ((__index_154) (const char  * (____s_152), int  ____c_153));// L484:L485
extern char  * ((__rindex_157) (const char  * (____s_155), int  ____c_156));// L512:L513
extern int  (__ffs_159) (int  ____i_158);// L518
extern int  (__strcasecmp_162) (const char  * (____s1_160), const char  * (____s2_161));// L529:L530
extern int  (__strncasecmp_166) (const char  * (____s1_163), const char  * (____s2_164), __size_t_15  ____n_165);// L533:L534
extern char  * ((__strsep_169) (char  * (* __restrict  ____stringp_167), const char  * __restrict  ____delim_168));// L552:L554
extern char  * ((__strsignal_171) (int  ____sig_170));// L559
extern char  * ((____stpcpy_174) (char  * __restrict  ____dest_172, const char  * __restrict  ____src_173));// L562:L563
extern char  * ((__stpcpy_177) (char  * __restrict  ____dest_175, const char  * __restrict  ____src_176));// L564:L565
extern char  * ((____stpncpy_181) (char  * __restrict  ____dest_178, const char  * __restrict  ____src_179, __size_t_15  ____n_180));// L569:L571
extern char  * ((__stpncpy_185) (char  * __restrict  ____dest_182, const char  * __restrict  ____src_183, __size_t_15  ____n_184));// L572:L574
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
extern char  * ((____stpncpy_chk_214) (char  * (____dest_210), const char  * (____src_211), __size_t_15  ____n_212, __size_t_15  ____destlen_213));// L130:L131
extern char  * ((____stpncpy_alias_218) (char  * (____dest_215), const char  * (____src_216), __size_t_15  ____n_217));// L132:L133
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
int  __node_data_231[( 1 << 0 )];// L19
unsigned char  __pfnnid_map_232[512];// L24
unsigned long  __max_pfn_233= 512;// L25
int  (__pfn_to_nid_235) (unsigned int  __pfn_234) {

if (__static_condition_default_236) {

{// L28
{



if (__static_condition_default_237) {
( ( void   ) ( 0 ) ) ; // L29:L50
}
if (__static_condition_default_238) {
( (  __pfn_234  < 512 ) ? ( void   ) ( 0 ) :  ____assert_fail_4  ("pfn < PFNNID_MAP_MAX","/home/kisamefishfry/Documents/xtc-dev/fonda/cpp_testsuite/varBugs/LINUX/91ea8207168.c",29, __PRETTY_FUNCTION__ ) ) ; // L29:L91
}
if (__static_condition_default_239) {
__static_type_error("type error") ; // L29:L91
}
return ( int   )  __pfnnid_map_232  [  __pfn_234  ] ;// L30
}
}// L31


}
}
int  (__pfn_valid_242) (unsigned int  __pfn_240) {

if (__static_condition_default_236) {

{// L34
{



int  __nid_241=  __pfn_to_nid_235  ( __pfn_240 );// L35

if (  __nid_241  >= 0 )// L37
{
if (__static_condition_default_243) {
return (  __pfn_240  < (  __node_data_231  [  __nid_241  ] ) ) ;// L38
}
if (__static_condition_default_244) {
__static_type_error("invalid type found in return expression");
}
}
return 0 ;// L39
}
}// L40


}
}
void  (__setup_bootmem_245) (void  ) {

{
if (__static_condition_default_247) {

{// L50
{



}
}// L54


}

}}
void  (__setup_bootmem_246) (void  ) {

{
if (__static_condition_default_248) {

{// L50
{



if (__static_condition_default_249) {
 __memset_31  ( __pfnnid_map_232 ,0xff,sizeof((  __pfnnid_map_232  ))) ; // L52
}
if (__static_condition_default_250) {
 __memset_32  ( __pfnnid_map_232 ,0xff,sizeof((  __pfnnid_map_232  ))) ; // L52
}
if (__static_condition_default_251) {
__static_type_error("type error") ; // L52
}
}
}// L54


}

}}
int  (__kpageflags_read_253) () {

if (__static_condition_default_254) {

{// L58
{



unsigned int  __pfn_252= 0;// L59

if (__static_condition_default_255) {
for (  ;  __pfn_252  < 0 ;  __pfn_252  ++ )// L61
{

{// L61
{



if ( ( 1 ) )// L62
{
 ; // L63
}
}
}// L64
}
}
if (__static_condition_default_256) {
for (  ;  __pfn_252  <  __max_pfn_233  ;  __pfn_252  ++ )// L61
{

{// L61
{



if (  __pfn_valid_242  ( __pfn_252 ) )// L62
{
 ; // L63
}
}
}// L64
}
}
return 0 ;// L66
}
}// L67


}
}
int  (__main_257) () {

if (__static_condition_default_259) {

{// L71
{



if (__static_condition_default_260) {
 __setup_bootmem_245 ( ) ; // L72
}
if (__static_condition_default_261) {
 __setup_bootmem_246 ( ) ; // L72
}
return 0 ;// L76
}
}// L77


}
}
int  (__main_258) () {

if (__static_condition_default_262) {

{// L71
{



if (__static_condition_default_263) {
 __setup_bootmem_245 ( ) ; // L72
}
if (__static_condition_default_264) {
 __setup_bootmem_246 ( ) ; // L72
}
 __kpageflags_read_253 ( ) ; // L74
return 0 ;// L76
}
}// L77


}
}

