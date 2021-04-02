#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__size_t_0", "size_t");
__static_renaming("____u_char_1", "__u_char");
__static_renaming("____u_short_2", "__u_short");
__static_renaming("____u_int_3", "__u_int");
__static_renaming("____u_long_4", "__u_long");
__static_renaming("____int8_t_5", "__int8_t");
__static_renaming("____uint8_t_6", "__uint8_t");
__static_renaming("____int16_t_7", "__int16_t");
__static_renaming("____uint16_t_8", "__uint16_t");
__static_renaming("____int32_t_9", "__int32_t");
__static_renaming("____uint32_t_10", "__uint32_t");
__static_renaming("____int64_t_11", "__int64_t");
__static_renaming("____uint64_t_12", "__uint64_t");
__static_renaming("____quad_t_13", "__quad_t");
__static_renaming("____u_quad_t_14", "__u_quad_t");
__static_renaming("____intmax_t_15", "__intmax_t");
__static_renaming("____uintmax_t_16", "__uintmax_t");
__static_renaming("____dev_t_17", "__dev_t");
__static_renaming("____uid_t_18", "__uid_t");
__static_renaming("____gid_t_19", "__gid_t");
__static_renaming("____ino_t_20", "__ino_t");
__static_renaming("____ino64_t_21", "__ino64_t");
__static_renaming("____mode_t_22", "__mode_t");
__static_renaming("____nlink_t_23", "__nlink_t");
__static_renaming("____off_t_24", "__off_t");
__static_renaming("____off64_t_25", "__off64_t");
__static_renaming("____pid_t_26", "__pid_t");
__static_renaming("____fsid_t_29", "__fsid_t");
__static_renaming("____clock_t_30", "__clock_t");
__static_renaming("____rlim_t_31", "__rlim_t");
__static_renaming("____rlim64_t_32", "__rlim64_t");
__static_renaming("____id_t_33", "__id_t");
__static_renaming("____time_t_34", "__time_t");
__static_renaming("____useconds_t_35", "__useconds_t");
__static_renaming("____suseconds_t_36", "__suseconds_t");
__static_renaming("____daddr_t_37", "__daddr_t");
__static_renaming("____key_t_38", "__key_t");
__static_renaming("____clockid_t_39", "__clockid_t");
__static_renaming("____timer_t_40", "__timer_t");
__static_renaming("____blksize_t_41", "__blksize_t");
__static_renaming("____blkcnt_t_42", "__blkcnt_t");
__static_renaming("____blkcnt64_t_43", "__blkcnt64_t");
__static_renaming("____fsblkcnt_t_44", "__fsblkcnt_t");
__static_renaming("____fsblkcnt64_t_45", "__fsblkcnt64_t");
__static_renaming("____fsfilcnt_t_46", "__fsfilcnt_t");
__static_renaming("____fsfilcnt64_t_47", "__fsfilcnt64_t");
__static_renaming("____fsword_t_48", "__fsword_t");
__static_renaming("____ssize_t_49", "__ssize_t");
__static_renaming("____syscall_slong_t_50", "__syscall_slong_t");
__static_renaming("____syscall_ulong_t_51", "__syscall_ulong_t");
__static_renaming("____loff_t_52", "__loff_t");
__static_renaming("____caddr_t_53", "__caddr_t");
__static_renaming("____intptr_t_54", "__intptr_t");
__static_renaming("____socklen_t_55", "__socklen_t");
__static_renaming("____sig_atomic_t_56", "__sig_atomic_t");
__static_renaming("____FILE_58", "__FILE");
__static_renaming("__FILE_59", "FILE");
__static_renaming("____mbstate_t_66", "__mbstate_t");
__static_renaming("___G_fpos_t_70", "_G_fpos_t");
__static_renaming("___G_fpos64_t_74", "_G_fpos64_t");
__static_renaming("____gnuc_va_list_75", "__gnuc_va_list");
__static_renaming("___IO_lock_t_77", "_IO_lock_t");
__static_renaming("___IO_FILE_117", "_IO_FILE");
__static_renaming("___IO_2_1_stdin__119", "_IO_2_1_stdin_");
__static_renaming("___IO_2_1_stdout__120", "_IO_2_1_stdout_");
__static_renaming("___IO_2_1_stderr__121", "_IO_2_1_stderr_");
__static_renaming("____io_read_fn_125", "__io_read_fn");
__static_renaming("____io_write_fn_129", "__io_write_fn");
__static_renaming("____io_seek_fn_133", "__io_seek_fn");
__static_renaming("____io_close_fn_135", "__io_close_fn");
__static_renaming("____underflow_136", "__underflow");
__static_renaming("____uflow_137", "__uflow");
__static_renaming("____overflow_138", "__overflow");
__static_renaming("___IO_getc_140", "_IO_getc");
__static_renaming("___IO_putc_143", "_IO_putc");
__static_renaming("___IO_feof_145", "_IO_feof");
__static_renaming("___IO_ferror_147", "_IO_ferror");
__static_renaming("___IO_peekc_locked_149", "_IO_peekc_locked");
__static_renaming("___IO_flockfile_150", "_IO_flockfile");
__static_renaming("___IO_funlockfile_151", "_IO_funlockfile");
__static_renaming("___IO_ftrylockfile_152", "_IO_ftrylockfile");
__static_renaming("___IO_vfscanf_153", "_IO_vfscanf");
__static_renaming("___IO_vfprintf_154", "_IO_vfprintf");
__static_renaming("___IO_padn_155", "_IO_padn");
__static_renaming("___IO_sgetn_156", "_IO_sgetn");
__static_renaming("___IO_seekoff_157", "_IO_seekoff");
__static_renaming("___IO_seekpos_158", "_IO_seekpos");
__static_renaming("___IO_free_backup_area_159", "_IO_free_backup_area");
__static_renaming("__va_list_160", "va_list");
__static_renaming("__off_t_161", "off_t");
__static_renaming("__ssize_t_162", "ssize_t");
__static_renaming("__fpos_t_163", "fpos_t");
__static_renaming("__stdin_164", "stdin");
__static_renaming("__stdout_165", "stdout");
__static_renaming("__stderr_166", "stderr");
__static_renaming("__remove_168", "remove");
__static_renaming("__rename_171", "rename");
__static_renaming("__renameat_176", "renameat");
__static_renaming("__tmpfile_177", "tmpfile");
__static_renaming("__tmpnam_179", "tmpnam");
__static_renaming("__tmpnam_r_181", "tmpnam_r");
__static_renaming("__tempnam_184", "tempnam");
__static_renaming("__fclose_186", "fclose");
__static_renaming("__fflush_188", "fflush");
__static_renaming("__fflush_unlocked_190", "fflush_unlocked");
__static_renaming("__fopen_193", "fopen");
__static_renaming("__freopen_197", "freopen");
__static_renaming("__fdopen_200", "fdopen");
__static_renaming("__fmemopen_204", "fmemopen");
__static_renaming("__open_memstream_207", "open_memstream");
__static_renaming("__setbuf_210", "setbuf");
__static_renaming("__setvbuf_215", "setvbuf");
__static_renaming("__setbuffer_219", "setbuffer");
__static_renaming("__setlinebuf_221", "setlinebuf");
__static_renaming("__fprintf_224", "fprintf");
__static_renaming("__printf_226", "printf");
__static_renaming("__sprintf_229", "sprintf");
__static_renaming("__vfprintf_233", "vfprintf");
__static_renaming("__vprintf_236", "vprintf");
__static_renaming("__vsprintf_240", "vsprintf");
__static_renaming("__snprintf_244", "snprintf");
__static_renaming("__vsnprintf_249", "vsnprintf");
__static_renaming("__vdprintf_253", "vdprintf");
__static_renaming("__dprintf_256", "dprintf");
__static_renaming("__fscanf_259", "fscanf");
__static_renaming("__scanf_261", "scanf");
__static_renaming("__sscanf_264", "sscanf");
__static_renaming("__vfscanf_276", "vfscanf");
__static_renaming("__vscanf_279", "vscanf");
__static_renaming("__vsscanf_283", "vsscanf");
__static_renaming("__fgetc_296", "fgetc");
__static_renaming("__getc_298", "getc");
__static_renaming("__getchar_299", "getchar");
__static_renaming("__getc_unlocked_301", "getc_unlocked");
__static_renaming("__getchar_unlocked_302", "getchar_unlocked");
__static_renaming("__fgetc_unlocked_304", "fgetc_unlocked");
__static_renaming("__fputc_307", "fputc");
__static_renaming("__putc_310", "putc");
__static_renaming("__putchar_312", "putchar");
__static_renaming("__fputc_unlocked_315", "fputc_unlocked");
__static_renaming("__putc_unlocked_318", "putc_unlocked");
__static_renaming("__putchar_unlocked_320", "putchar_unlocked");
__static_renaming("__getw_322", "getw");
__static_renaming("__putw_325", "putw");
__static_renaming("__fgets_329", "fgets");
__static_renaming("____getdelim_334", "__getdelim");
__static_renaming("__getdelim_339", "getdelim");
__static_renaming("__getline_343", "getline");
__static_renaming("__fputs_346", "fputs");
__static_renaming("__puts_348", "puts");
__static_renaming("__ungetc_351", "ungetc");
__static_renaming("__fseek_371", "fseek");
__static_renaming("__ftell_373", "ftell");
__static_renaming("__rewind_375", "rewind");
__static_renaming("__fseeko_379", "fseeko");
__static_renaming("__ftello_381", "ftello");
__static_renaming("__fgetpos_384", "fgetpos");
__static_renaming("__fsetpos_387", "fsetpos");
__static_renaming("__clearerr_389", "clearerr");
__static_renaming("__feof_391", "feof");
__static_renaming("__ferror_393", "ferror");
__static_renaming("__clearerr_unlocked_395", "clearerr_unlocked");
__static_renaming("__feof_unlocked_397", "feof_unlocked");
__static_renaming("__ferror_unlocked_399", "ferror_unlocked");
__static_renaming("__perror_401", "perror");
__static_renaming("__sys_nerr_402", "sys_nerr");
__static_renaming("__sys_errlist_403", "sys_errlist");
__static_renaming("__fileno_405", "fileno");
__static_renaming("__fileno_unlocked_407", "fileno_unlocked");
__static_renaming("__popen_410", "popen");
__static_renaming("__pclose_412", "pclose");
__static_renaming("__ctermid_414", "ctermid");
__static_renaming("__flockfile_416", "flockfile");
__static_renaming("__ftrylockfile_418", "ftrylockfile");
__static_renaming("__funlockfile_420", "funlockfile");
__static_renaming("__decode_spi_frequency_426", "decode_spi_frequency");


};
enum __codecvt_result {
____codecvt_ok_83,
____codecvt_partial_84,
____codecvt_error_85,
____codecvt_noconv_86,
};
enum __anonymous_tag_424 {
__SPI_FREQUENCY_20MHZ_421,
__SPI_FREQUENCY_33MHZ_422,
__SPI_FREQUENCY_50MHZ_423,
};
typedef long unsigned int  __size_t_0;
typedef unsigned char  ____u_char_1;
typedef unsigned short int  ____u_short_2;
typedef unsigned int  ____u_int_3;
typedef unsigned long int  ____u_long_4;
typedef signed char  ____int8_t_5;
typedef unsigned char  ____uint8_t_6;
typedef signed short int  ____int16_t_7;
typedef unsigned short int  ____uint16_t_8;
typedef signed int  ____int32_t_9;
typedef unsigned int  ____uint32_t_10;
typedef signed long int  ____int64_t_11;
typedef unsigned long int  ____uint64_t_12;
typedef long int  ____quad_t_13;
typedef unsigned long int  ____u_quad_t_14;
typedef long int  ____intmax_t_15;
typedef unsigned long int  ____uintmax_t_16;
typedef unsigned long int  ____dev_t_17;
typedef unsigned int  ____uid_t_18;
typedef unsigned int  ____gid_t_19;
typedef unsigned long int  ____ino_t_20;
typedef unsigned long int  ____ino64_t_21;
typedef unsigned int  ____mode_t_22;
typedef unsigned long int  ____nlink_t_23;
typedef long int  ____off_t_24;
typedef long int  ____off64_t_25;
typedef int  ____pid_t_26;
struct __anonymous_tag_27 {
int  (____val_28[2]);
};
typedef struct __anonymous_tag_27  ____fsid_t_29;
typedef long int  ____clock_t_30;
typedef unsigned long int  ____rlim_t_31;
typedef unsigned long int  ____rlim64_t_32;
typedef unsigned int  ____id_t_33;
typedef long int  ____time_t_34;
typedef unsigned int  ____useconds_t_35;
typedef long int  ____suseconds_t_36;
typedef int  ____daddr_t_37;
typedef int  ____key_t_38;
typedef int  ____clockid_t_39;
typedef void  (* ____timer_t_40);
typedef long int  ____blksize_t_41;
typedef long int  ____blkcnt_t_42;
typedef long int  ____blkcnt64_t_43;
typedef unsigned long int  ____fsblkcnt_t_44;
typedef unsigned long int  ____fsblkcnt64_t_45;
typedef unsigned long int  ____fsfilcnt_t_46;
typedef unsigned long int  ____fsfilcnt64_t_47;
typedef long int  ____fsword_t_48;
typedef long int  ____ssize_t_49;
typedef long int  ____syscall_slong_t_50;
typedef unsigned long int  ____syscall_ulong_t_51;
typedef ____off64_t_25  ____loff_t_52;
typedef char  (* ____caddr_t_53);
typedef long int  ____intptr_t_54;
typedef unsigned int  ____socklen_t_55;
typedef int  ____sig_atomic_t_56;
typedef struct __forward_tag_reference_57  ____FILE_58;
typedef struct __forward_tag_reference_57  __FILE_59;
union __anonymous_tag_60 {
unsigned int  ____wch_61;
char  (____wchb_62[4]);
};
struct __anonymous_tag_63 {
int  ____count_64;
union __anonymous_tag_60  ____value_65;
};
typedef struct __anonymous_tag_63  ____mbstate_t_66;
struct __anonymous_tag_67 {
____off_t_24  ____pos_68;
____mbstate_t_66  ____state_69;
};
typedef struct __anonymous_tag_67  ___G_fpos_t_70;
struct __anonymous_tag_71 {
____off64_t_25  ____pos_72;
____mbstate_t_66  ____state_73;
};
typedef struct __anonymous_tag_71  ___G_fpos64_t_74;
typedef __builtin_va_list  ____gnuc_va_list_75;
typedef void  ___IO_lock_t_77;
struct ___IO_marker_79 {
struct __forward_tag_reference_78  (* ___next_80);
struct __forward_tag_reference_57  (* ___sbuf_81);
int  ___pos_82;
};
struct ___IO_FILE_87 {
int  ___flags_88;
char  (* ___IO_read_ptr_89);
char  (* ___IO_read_end_90);
char  (* ___IO_read_base_91);
char  (* ___IO_write_base_92);
char  (* ___IO_write_ptr_93);
char  (* ___IO_write_end_94);
char  (* ___IO_buf_base_95);
char  (* ___IO_buf_end_96);
char  (* ___IO_save_base_97);
char  (* ___IO_backup_base_98);
char  (* ___IO_save_end_99);
struct ___IO_marker_79  (* ___markers_100);
struct __forward_tag_reference_57  (* ___chain_101);
int  ___fileno_102;
int  ___flags2_103;
____off_t_24  ___old_offset_104;
unsigned short  ___cur_column_105;
signed char  ___vtable_offset_106;
char  (___shortbuf_107[1]);
___IO_lock_t_77  (* ___lock_108);
____off64_t_25  ___offset_109;
void  (* ____pad1_110);
void  (* ____pad2_111);
void  (* ____pad3_112);
void  (* ____pad4_113);
__size_t_0  ____pad5_114;
int  ___mode_115;
char  (___unused2_116[15 * sizeof ( int   ) - 4 * sizeof ( void  * ) - sizeof ( __size_t_0   )]);
};
typedef struct ___IO_FILE_87  ___IO_FILE_117;
typedef ____ssize_t_49  ____io_read_fn_125 (void  (* ____cookie_122), char  (* ____buf_123), __size_t_0  ____nbytes_124);
typedef ____ssize_t_49  ____io_write_fn_129 (void  (* ____cookie_126), const char  (* ____buf_127), __size_t_0  ____n_128);
typedef int  ____io_seek_fn_133 (void  (* ____cookie_130), ____off64_t_25  (* ____pos_131), int  ____w_132);
typedef int  ____io_close_fn_135 (void  (* ____cookie_134));
typedef ____gnuc_va_list_75  __va_list_160;
typedef ____off_t_24  __off_t_161;
typedef ____ssize_t_49  __ssize_t_162;
typedef ___G_fpos_t_70  __fpos_t_163;

struct __forward_tag_reference_78 { // generated union of struct variations
union {
struct ___IO_marker_79 ___IO_marker_79;
};
};

struct __forward_tag_reference_57 { // generated union of struct variations
union {
struct ___IO_FILE_87 ___IO_FILE_87;
};
};

struct __forward_tag_reference_76 { // generated union of struct variations
union {
};
};

struct __forward_tag_reference_118 { // generated union of struct variations
union {
};
};

// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
struct __forward_tag_reference_57 ;
// typedef moved to top of scope
struct __forward_tag_reference_57 ;
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
struct __forward_tag_reference_76 ;
struct __forward_tag_reference_57 ;
// typedef moved to top of scope
struct ___IO_marker_79 ;
enum __codecvt_result ;
struct ___IO_FILE_87 ;
// typedef moved to top of scope
struct __forward_tag_reference_118 ;
extern struct __forward_tag_reference_118  ___IO_2_1_stdin__119;
extern struct __forward_tag_reference_118  ___IO_2_1_stdout__120;
extern struct __forward_tag_reference_118  ___IO_2_1_stderr__121;
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
extern int  ____underflow_136 (___IO_FILE_117  *);
extern int  ____uflow_137 (___IO_FILE_117  *);
extern int  ____overflow_138 (___IO_FILE_117  *, int  );
extern int  ___IO_getc_140 (___IO_FILE_117  (* ____fp_139));
extern int  ___IO_putc_143 (int  ____c_141, ___IO_FILE_117  (* ____fp_142));
extern int  ___IO_feof_145 (___IO_FILE_117  (* ____fp_144));
extern int  ___IO_ferror_147 (___IO_FILE_117  (* ____fp_146));
extern int  ___IO_peekc_locked_149 (___IO_FILE_117  (* ____fp_148));
extern void  ___IO_flockfile_150 (___IO_FILE_117  *);
extern void  ___IO_funlockfile_151 (___IO_FILE_117  *);
extern int  ___IO_ftrylockfile_152 (___IO_FILE_117  *);
extern int  ___IO_vfscanf_153 (___IO_FILE_117  * __restrict , const char  * __restrict , ____gnuc_va_list_75  , int  * __restrict );
extern int  ___IO_vfprintf_154 (___IO_FILE_117  * __restrict , const char  * __restrict , ____gnuc_va_list_75  );
extern ____ssize_t_49  ___IO_padn_155 (___IO_FILE_117  *, int  , ____ssize_t_49  );
extern __size_t_0  ___IO_sgetn_156 (___IO_FILE_117  *, void  *, __size_t_0  );
extern ____off64_t_25  ___IO_seekoff_157 (___IO_FILE_117  *, ____off64_t_25  , int  , int  );
extern ____off64_t_25  ___IO_seekpos_158 (___IO_FILE_117  *, ____off64_t_25  , int  );
extern void  ___IO_free_backup_area_159 (___IO_FILE_117  *);
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
extern struct ___IO_FILE_87  (* __stdin_164);
extern struct ___IO_FILE_87  (* __stdout_165);
extern struct ___IO_FILE_87  (* __stderr_166);
extern int  __remove_168 (const char  (* ____filename_167));
extern int  __rename_171 (const char  (* ____old_169), const char  (* ____new_170));
extern int  __renameat_176 (int  ____oldfd_172, const char  (* ____old_173), int  ____newfd_174, const char  (* ____new_175));
extern __FILE_59  (* __tmpfile_177 (void  ));
extern char  (* __tmpnam_179 (char  (* ____s_178)));
extern char  (* __tmpnam_r_181 (char  (* ____s_180)));
extern char  (* __tempnam_184 (const char  (* ____dir_182), const char  (* ____pfx_183)));
extern int  __fclose_186 (__FILE_59  (* ____stream_185));
extern int  __fflush_188 (__FILE_59  (* ____stream_187));
extern int  __fflush_unlocked_190 (__FILE_59  (* ____stream_189));
extern __FILE_59  (* __fopen_193 (const char  (* __restrict  ____filename_191), const char  (* __restrict  ____modes_192)));
extern __FILE_59  (* __freopen_197 (const char  (* __restrict  ____filename_194), const char  (* __restrict  ____modes_195), __FILE_59  (* __restrict  ____stream_196)));
extern __FILE_59  (* __fdopen_200 (int  ____fd_198, const char  (* ____modes_199)));
extern __FILE_59  (* __fmemopen_204 (void  (* ____s_201), __size_t_0  ____len_202, const char  (* ____modes_203)));
extern __FILE_59  (* __open_memstream_207 (char  (* (* ____bufloc_205)), __size_t_0  (* ____sizeloc_206)));
extern void  __setbuf_210 (__FILE_59  (* __restrict  ____stream_208), char  (* __restrict  ____buf_209));
extern int  __setvbuf_215 (__FILE_59  (* __restrict  ____stream_211), char  (* __restrict  ____buf_212), int  ____modes_213, __size_t_0  ____n_214);
extern void  __setbuffer_219 (__FILE_59  (* __restrict  ____stream_216), char  (* __restrict  ____buf_217), __size_t_0  ____size_218);
extern void  __setlinebuf_221 (__FILE_59  (* ____stream_220));
extern int  __fprintf_224 (__FILE_59  (* __restrict  ____stream_222), const char  (* __restrict  ____format_223),  ... );
extern int  __printf_226 (const char  (* __restrict  ____format_225),  ... );
extern int  __sprintf_229 (char  (* __restrict  ____s_227), const char  (* __restrict  ____format_228),  ... );
extern int  __vfprintf_233 (__FILE_59  (* __restrict  ____s_230), const char  (* __restrict  ____format_231), ____gnuc_va_list_75  ____arg_232);
extern int  __vprintf_236 (const char  (* __restrict  ____format_234), ____gnuc_va_list_75  ____arg_235);
extern int  __vsprintf_240 (char  (* __restrict  ____s_237), const char  (* __restrict  ____format_238), ____gnuc_va_list_75  ____arg_239);
extern int  __snprintf_244 (char  (* __restrict  ____s_241), __size_t_0  ____maxlen_242, const char  (* __restrict  ____format_243),  ... );
extern int  __vsnprintf_249 (char  (* __restrict  ____s_245), __size_t_0  ____maxlen_246, const char  (* __restrict  ____format_247), ____gnuc_va_list_75  ____arg_248);
extern int  __vdprintf_253 (int  ____fd_250, const char  (* __restrict  ____fmt_251), ____gnuc_va_list_75  ____arg_252);
extern int  __dprintf_256 (int  ____fd_254, const char  (* __restrict  ____fmt_255),  ... );
extern int  __fscanf_259 (__FILE_59  (* __restrict  ____stream_257), const char  (* __restrict  ____format_258),  ... );
extern int  __scanf_261 (const char  (* __restrict  ____format_260),  ... );
extern int  __sscanf_264 (const char  (* __restrict  ____s_262), const char  (* __restrict  ____format_263),  ... );



extern int  __vfscanf_276 (__FILE_59  (* __restrict  ____s_273), const char  (* __restrict  ____format_274), ____gnuc_va_list_75  ____arg_275);
extern int  __vscanf_279 (const char  (* __restrict  ____format_277), ____gnuc_va_list_75  ____arg_278);
extern int  __vsscanf_283 (const char  (* __restrict  ____s_280), const char  (* __restrict  ____format_281), ____gnuc_va_list_75  ____arg_282);



extern int  __fgetc_296 (__FILE_59  (* ____stream_295));
extern int  __getc_298 (__FILE_59  (* ____stream_297));
extern int  __getchar_299 (void  );
extern int  __getc_unlocked_301 (__FILE_59  (* ____stream_300));
extern int  __getchar_unlocked_302 (void  );
extern int  __fgetc_unlocked_304 (__FILE_59  (* ____stream_303));
extern int  __fputc_307 (int  ____c_305, __FILE_59  (* ____stream_306));
extern int  __putc_310 (int  ____c_308, __FILE_59  (* ____stream_309));
extern int  __putchar_312 (int  ____c_311);
extern int  __fputc_unlocked_315 (int  ____c_313, __FILE_59  (* ____stream_314));
extern int  __putc_unlocked_318 (int  ____c_316, __FILE_59  (* ____stream_317));
extern int  __putchar_unlocked_320 (int  ____c_319);
extern int  __getw_322 (__FILE_59  (* ____stream_321));
extern int  __putw_325 (int  ____w_323, __FILE_59  (* ____stream_324));
extern char  (* __fgets_329 (char  (* __restrict  ____s_326), int  ____n_327, __FILE_59  (* __restrict  ____stream_328)));
extern ____ssize_t_49  ____getdelim_334 (char  (* (* __restrict  ____lineptr_330)), __size_t_0  (* __restrict  ____n_331), int  ____delimiter_332, __FILE_59  (* __restrict  ____stream_333));
extern ____ssize_t_49  __getdelim_339 (char  (* (* __restrict  ____lineptr_335)), __size_t_0  (* __restrict  ____n_336), int  ____delimiter_337, __FILE_59  (* __restrict  ____stream_338));
extern ____ssize_t_49  __getline_343 (char  (* (* __restrict  ____lineptr_340)), __size_t_0  (* __restrict  ____n_341), __FILE_59  (* __restrict  ____stream_342));
extern int  __fputs_346 (const char  (* __restrict  ____s_344), __FILE_59  (* __restrict  ____stream_345));
extern int  __puts_348 (const char  (* ____s_347));
extern int  __ungetc_351 (int  ____c_349, __FILE_59  (* ____stream_350));
extern int  __fseek_371 (__FILE_59  (* ____stream_368), long int  ____off_369, int  ____whence_370);
extern long int  __ftell_373 (__FILE_59  (* ____stream_372));
extern void  __rewind_375 (__FILE_59  (* ____stream_374));
extern int  __fseeko_379 (__FILE_59  (* ____stream_376), ____off_t_24  ____off_377, int  ____whence_378);
extern ____off_t_24  __ftello_381 (__FILE_59  (* ____stream_380));
extern int  __fgetpos_384 (__FILE_59  (* __restrict  ____stream_382), __fpos_t_163  (* __restrict  ____pos_383));
extern int  __fsetpos_387 (__FILE_59  (* ____stream_385), const __fpos_t_163  (* ____pos_386));
extern void  __clearerr_389 (__FILE_59  (* ____stream_388));
extern int  __feof_391 (__FILE_59  (* ____stream_390));
extern int  __ferror_393 (__FILE_59  (* ____stream_392));
extern void  __clearerr_unlocked_395 (__FILE_59  (* ____stream_394));
extern int  __feof_unlocked_397 (__FILE_59  (* ____stream_396));
extern int  __ferror_unlocked_399 (__FILE_59  (* ____stream_398));
extern void  __perror_401 (const char  (* ____s_400));
extern int  __sys_nerr_402;
extern const char  (* const  (__sys_errlist_403[]));
extern int  __fileno_405 (__FILE_59  (* ____stream_404));
extern int  __fileno_unlocked_407 (__FILE_59  (* ____stream_406));
extern __FILE_59  (* __popen_410 (const char  (* ____command_408), const char  (* ____modes_409)));
extern int  __pclose_412 (__FILE_59  (* ____stream_411));
extern char  (* __ctermid_414 (char  (* ____s_413)));
extern void  __flockfile_416 (__FILE_59  (* ____stream_415));
extern int  __ftrylockfile_418 (__FILE_59  (* ____stream_417));
extern void  __funlockfile_420 (__FILE_59  (* ____stream_419));
enum __anonymous_tag_424 ;
static void  __decode_spi_frequency_426 (unsigned int  __freq_425) {
{
switch (  __freq_425  ) { case  __SPI_FREQUENCY_20MHZ_421  : 
 __printf_226  ( "20MHz" ) ;

break ;


case  __SPI_FREQUENCY_33MHZ_422  : 
 __printf_226  ( "33MHz" ) ;

break ;


case  __SPI_FREQUENCY_50MHZ_423  : 
 __printf_226  ( "50MHz" ) ;

break ;


default : 
 __printf_226  ( "unknown<%x>MHz",  __freq_425  ) ;

 }

}


}

