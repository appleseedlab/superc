#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_341;
extern const bool __static_condition_default_984;
extern const bool __static_condition_default_977;
extern const bool __static_condition_default_308;
extern const bool __static_condition_default_1013;
extern const bool __static_condition_default_429;
extern const bool __static_condition_default_1026;
extern const bool __static_condition_default_1027;
extern const bool __static_condition_default_240;
extern const bool __static_condition_default_349;
extern const bool __static_condition_default_597;
extern const bool __static_condition_default_993;
extern const bool __static_condition_default_255;
extern const bool __static_condition_default_804;
extern const bool __static_condition_default_420;
extern const bool __static_condition_default_1032;
extern const bool __static_condition_default_379;
extern const bool __static_condition_default_631;
extern const bool __static_condition_default_1038;
extern const bool __static_condition_default_623;
extern const bool __static_condition_default_267;
extern const bool __static_condition_default_738;
extern const bool __static_condition_default_293;
extern const bool __static_condition_default_581;
extern const bool __static_condition_default_361;
extern const bool __static_condition_default_352;
extern const bool __static_condition_default_325;
extern const bool __static_condition_default_296;
extern const bool __static_condition_default_1028;
extern const bool __static_condition_default_1031;
extern const bool __static_condition_default_237;
extern const bool __static_condition_default_60;
extern const bool __static_condition_default_629;
extern const bool __static_condition_default_302;
extern const bool __static_condition_default_1036;
extern const bool __static_condition_default_432;
extern const bool __static_condition_default_1010;
extern const bool __static_condition_default_276;
extern const bool __static_condition_default_1035;
extern const bool __static_condition_default_1034;
extern const bool __static_condition_default_288;
extern const bool __static_condition_default_258;
extern const bool __static_condition_default_279;
extern const bool __static_condition_default_583;
extern const bool __static_condition_default_243;
extern const bool __static_condition_default_803;
extern const bool __static_condition_default_1029;
extern const bool __static_condition_default_417;
extern const bool __static_condition_default_606;
extern const bool __static_condition_default_992;
extern const bool __static_condition_default_305;
extern const bool __static_condition_default_261;
extern const bool __static_condition_default_285;
extern const bool __static_condition_default_1017;
extern const bool __static_condition_default_282;
extern const bool __static_condition_default_246;
extern const bool __static_condition_default_1025;
extern const bool __static_condition_default_1022;
extern const bool __static_condition_default_395;
extern const bool __static_condition_default_234;
extern const bool __static_condition_default_67;
extern const bool __static_condition_default_596;
extern const bool __static_condition_default_625;
extern const bool __static_condition_default_264;
extern const bool __static_condition_default_378;
extern const bool __static_condition_default_423;
extern const bool __static_condition_default_394;
extern const bool __static_condition_default_215;
extern const bool __static_condition_default_997;
extern const bool __static_condition_default_252;
extern const bool __static_condition_default_1033;
extern const bool __static_condition_default_249;
extern const bool __static_condition_default_814;
extern const bool __static_condition_default_273;
extern const bool __static_condition_default_604;
extern const bool __static_condition_default_426;
extern const bool __static_condition_default_299;
extern const bool __static_condition_default_270;
extern const bool __static_condition_default_805;
extern const bool __static_condition_default_1030;
extern const bool __static_condition_default_414;
void __static_initializer_default() {
__static_renaming("__ptrdiff_t_0", "ptrdiff_t");
__static_renaming("__size_t_1", "size_t");
__static_renaming("__wchar_t_2", "wchar_t");
__static_renaming("__idtype_t_8", "idtype_t");
__static_renaming("____u_char_9", "__u_char");
__static_renaming("____u_short_10", "__u_short");
__static_renaming("____u_int_11", "__u_int");
__static_renaming("____u_long_12", "__u_long");
__static_renaming("____int8_t_13", "__int8_t");
__static_renaming("____uint8_t_14", "__uint8_t");
__static_renaming("____int16_t_15", "__int16_t");
__static_renaming("____uint16_t_16", "__uint16_t");
__static_renaming("____int32_t_17", "__int32_t");
__static_renaming("____uint32_t_18", "__uint32_t");
__static_renaming("____int64_t_19", "__int64_t");
__static_renaming("____uint64_t_20", "__uint64_t");
__static_renaming("____quad_t_21", "__quad_t");
__static_renaming("____u_quad_t_22", "__u_quad_t");
__static_renaming("____dev_t_23", "__dev_t");
__static_renaming("____uid_t_24", "__uid_t");
__static_renaming("____gid_t_25", "__gid_t");
__static_renaming("____ino_t_26", "__ino_t");
__static_renaming("____ino64_t_27", "__ino64_t");
__static_renaming("____mode_t_28", "__mode_t");
__static_renaming("____nlink_t_29", "__nlink_t");
__static_renaming("____off_t_30", "__off_t");
__static_renaming("____off64_t_31", "__off64_t");
__static_renaming("____pid_t_32", "__pid_t");
__static_renaming("____fsid_t_36", "__fsid_t");
__static_renaming("____clock_t_37", "__clock_t");
__static_renaming("____rlim_t_38", "__rlim_t");
__static_renaming("____rlim64_t_39", "__rlim64_t");
__static_renaming("____id_t_40", "__id_t");
__static_renaming("____time_t_41", "__time_t");
__static_renaming("____useconds_t_42", "__useconds_t");
__static_renaming("____suseconds_t_43", "__suseconds_t");
__static_renaming("____daddr_t_44", "__daddr_t");
__static_renaming("____key_t_45", "__key_t");
__static_renaming("____clockid_t_46", "__clockid_t");
__static_renaming("____timer_t_47", "__timer_t");
__static_renaming("____blksize_t_48", "__blksize_t");
__static_renaming("____blkcnt_t_49", "__blkcnt_t");
__static_renaming("____blkcnt64_t_50", "__blkcnt64_t");
__static_renaming("____fsblkcnt_t_51", "__fsblkcnt_t");
__static_renaming("____fsblkcnt64_t_52", "__fsblkcnt64_t");
__static_renaming("____fsfilcnt_t_53", "__fsfilcnt_t");
__static_renaming("____fsfilcnt64_t_54", "__fsfilcnt64_t");
__static_renaming("____fsword_t_55", "__fsword_t");
__static_renaming("____ssize_t_56", "__ssize_t");
__static_renaming("____syscall_slong_t_57", "__syscall_slong_t");
__static_renaming("____syscall_ulong_t_58", "__syscall_ulong_t");
__static_renaming("____loff_t_59", "__loff_t");
__static_renaming("____qaddr_t_61", "__qaddr_t");
__static_renaming("____caddr_t_62", "__caddr_t");
__static_renaming("____intptr_t_63", "__intptr_t");
__static_renaming("____socklen_t_64", "__socklen_t");
__static_renaming("____bswap_32_66", "__bswap_32");
__static_renaming("____bswap_64_69", "__bswap_64");
__static_renaming("____WAIT_STATUS_89", "__WAIT_STATUS");
__static_renaming("__div_t_94", "div_t");
__static_renaming("__ldiv_t_99", "ldiv_t");
__static_renaming("__lldiv_t_104", "lldiv_t");
__static_renaming("____ctype_get_mb_cur_max_105", "__ctype_get_mb_cur_max");
__static_renaming("____ctype_get_mb_cur_max_106", "__ctype_get_mb_cur_max");
__static_renaming("____ctype_get_mb_cur_max_107", "__ctype_get_mb_cur_max");
__static_renaming("____ctype_get_mb_cur_max_108", "__ctype_get_mb_cur_max");
__static_renaming("__atof_110", "atof");
__static_renaming("__atof_111", "atof");
__static_renaming("__atoi_113", "atoi");
__static_renaming("__atoi_114", "atoi");
__static_renaming("__atol_116", "atol");
__static_renaming("__atol_117", "atol");
__static_renaming("__atoll_119", "atoll");
__static_renaming("__atoll_120", "atoll");
__static_renaming("__strtod_123", "strtod");
__static_renaming("__strtof_126", "strtof");
__static_renaming("__strtold_129", "strtold");
__static_renaming("__strtol_133", "strtol");
__static_renaming("__strtoul_137", "strtoul");
__static_renaming("__strtoq_141", "strtoq");
__static_renaming("__strtouq_145", "strtouq");
__static_renaming("__strtoll_149", "strtoll");
__static_renaming("__strtoll_150", "strtoll");
__static_renaming("__strtoull_154", "strtoull");
__static_renaming("__l64a_159", "l64a");
__static_renaming("__l64a_160", "l64a");
__static_renaming("__a64l_162", "a64l");
__static_renaming("__a64l_163", "a64l");
__static_renaming("____u_char_164", "__u_char");
__static_renaming("____u_short_165", "__u_short");
__static_renaming("____u_int_166", "__u_int");
__static_renaming("____u_long_167", "__u_long");
__static_renaming("____int8_t_168", "__int8_t");
__static_renaming("____uint8_t_169", "__uint8_t");
__static_renaming("____int16_t_170", "__int16_t");
__static_renaming("____uint16_t_171", "__uint16_t");
__static_renaming("____int32_t_172", "__int32_t");
__static_renaming("____uint32_t_173", "__uint32_t");
__static_renaming("____int64_t_174", "__int64_t");
__static_renaming("____uint64_t_175", "__uint64_t");
__static_renaming("____quad_t_176", "__quad_t");
__static_renaming("____u_quad_t_177", "__u_quad_t");
__static_renaming("____dev_t_178", "__dev_t");
__static_renaming("____uid_t_179", "__uid_t");
__static_renaming("____gid_t_180", "__gid_t");
__static_renaming("____ino_t_181", "__ino_t");
__static_renaming("____ino64_t_182", "__ino64_t");
__static_renaming("____mode_t_183", "__mode_t");
__static_renaming("____nlink_t_184", "__nlink_t");
__static_renaming("____off_t_185", "__off_t");
__static_renaming("____off64_t_186", "__off64_t");
__static_renaming("____pid_t_187", "__pid_t");
__static_renaming("____fsid_t_191", "__fsid_t");
__static_renaming("____clock_t_192", "__clock_t");
__static_renaming("____rlim_t_193", "__rlim_t");
__static_renaming("____rlim64_t_194", "__rlim64_t");
__static_renaming("____id_t_195", "__id_t");
__static_renaming("____time_t_196", "__time_t");
__static_renaming("____useconds_t_197", "__useconds_t");
__static_renaming("____suseconds_t_198", "__suseconds_t");
__static_renaming("____daddr_t_199", "__daddr_t");
__static_renaming("____key_t_200", "__key_t");
__static_renaming("____clockid_t_201", "__clockid_t");
__static_renaming("____timer_t_202", "__timer_t");
__static_renaming("____blksize_t_203", "__blksize_t");
__static_renaming("____blkcnt_t_204", "__blkcnt_t");
__static_renaming("____blkcnt64_t_205", "__blkcnt64_t");
__static_renaming("____fsblkcnt_t_206", "__fsblkcnt_t");
__static_renaming("____fsblkcnt64_t_207", "__fsblkcnt64_t");
__static_renaming("____fsfilcnt_t_208", "__fsfilcnt_t");
__static_renaming("____fsfilcnt64_t_209", "__fsfilcnt64_t");
__static_renaming("____fsword_t_210", "__fsword_t");
__static_renaming("____ssize_t_211", "__ssize_t");
__static_renaming("____syscall_slong_t_212", "__syscall_slong_t");
__static_renaming("____syscall_ulong_t_213", "__syscall_ulong_t");
__static_renaming("____loff_t_214", "__loff_t");
__static_renaming("____qaddr_t_216", "__qaddr_t");
__static_renaming("____caddr_t_217", "__caddr_t");
__static_renaming("____intptr_t_218", "__intptr_t");
__static_renaming("____socklen_t_219", "__socklen_t");
__static_renaming("__u_char_220", "u_char");
__static_renaming("__u_char_221", "u_char");
__static_renaming("__u_short_222", "u_short");
__static_renaming("__u_short_223", "u_short");
__static_renaming("__u_int_224", "u_int");
__static_renaming("__u_int_225", "u_int");
__static_renaming("__u_long_226", "u_long");
__static_renaming("__u_long_227", "u_long");
__static_renaming("__quad_t_228", "quad_t");
__static_renaming("__quad_t_229", "quad_t");
__static_renaming("__u_quad_t_230", "u_quad_t");
__static_renaming("__u_quad_t_231", "u_quad_t");
__static_renaming("__fsid_t_232", "fsid_t");
__static_renaming("__fsid_t_233", "fsid_t");
__static_renaming("__loff_t_235", "loff_t");
__static_renaming("__loff_t_236", "loff_t");
__static_renaming("__loff_t_238", "loff_t");
__static_renaming("__loff_t_239", "loff_t");
__static_renaming("__ino_t_241", "ino_t");
__static_renaming("__ino_t_242", "ino_t");
__static_renaming("__ino_t_244", "ino_t");
__static_renaming("__ino_t_245", "ino_t");
__static_renaming("__dev_t_247", "dev_t");
__static_renaming("__dev_t_248", "dev_t");
__static_renaming("__gid_t_250", "gid_t");
__static_renaming("__gid_t_251", "gid_t");
__static_renaming("__gid_t_253", "gid_t");
__static_renaming("__gid_t_254", "gid_t");
__static_renaming("__mode_t_256", "mode_t");
__static_renaming("__mode_t_257", "mode_t");
__static_renaming("__nlink_t_259", "nlink_t");
__static_renaming("__nlink_t_260", "nlink_t");
__static_renaming("__uid_t_262", "uid_t");
__static_renaming("__uid_t_263", "uid_t");
__static_renaming("__uid_t_265", "uid_t");
__static_renaming("__uid_t_266", "uid_t");
__static_renaming("__off_t_268", "off_t");
__static_renaming("__off_t_269", "off_t");
__static_renaming("__off_t_271", "off_t");
__static_renaming("__off_t_272", "off_t");
__static_renaming("__pid_t_274", "pid_t");
__static_renaming("__pid_t_275", "pid_t");
__static_renaming("__pid_t_277", "pid_t");
__static_renaming("__pid_t_278", "pid_t");
__static_renaming("__id_t_280", "id_t");
__static_renaming("__id_t_281", "id_t");
__static_renaming("__ssize_t_283", "ssize_t");
__static_renaming("__ssize_t_284", "ssize_t");
__static_renaming("__daddr_t_286", "daddr_t");
__static_renaming("__daddr_t_287", "daddr_t");
__static_renaming("__caddr_t_289", "caddr_t");
__static_renaming("__caddr_t_290", "caddr_t");
__static_renaming("__key_t_291", "key_t");
__static_renaming("__key_t_292", "key_t");
__static_renaming("__key_t_294", "key_t");
__static_renaming("__key_t_295", "key_t");
__static_renaming("__clock_t_297", "clock_t");
__static_renaming("__clock_t_298", "clock_t");
__static_renaming("__time_t_300", "time_t");
__static_renaming("__time_t_301", "time_t");
__static_renaming("__clockid_t_303", "clockid_t");
__static_renaming("__clockid_t_304", "clockid_t");
__static_renaming("__timer_t_306", "timer_t");
__static_renaming("__timer_t_307", "timer_t");
__static_renaming("__ulong_309", "ulong");
__static_renaming("__ulong_310", "ulong");
__static_renaming("__ulong_311", "ulong");
__static_renaming("__ushort_312", "ushort");
__static_renaming("__uint_313", "uint");
__static_renaming("__int8_t_314", "int8_t");
__static_renaming("__int16_t_315", "int16_t");
__static_renaming("__int32_t_316", "int32_t");
__static_renaming("__int64_t_317", "int64_t");
__static_renaming("__u_int8_t_318", "u_int8_t");
__static_renaming("__u_int16_t_319", "u_int16_t");
__static_renaming("__u_int32_t_320", "u_int32_t");
__static_renaming("__u_int64_t_321", "u_int64_t");
__static_renaming("__register_t_322", "register_t");
__static_renaming("____bswap_32_324", "__bswap_32");
__static_renaming("____bswap_64_327", "__bswap_64");
__static_renaming("____sig_atomic_t_328", "__sig_atomic_t");
__static_renaming("____sigset_t_332", "__sigset_t");
__static_renaming("__sigset_t_333", "sigset_t");
__static_renaming("__suseconds_t_350", "suseconds_t");
__static_renaming("__suseconds_t_351", "suseconds_t");
__static_renaming("____fd_mask_353", "__fd_mask");
__static_renaming("____fd_mask_354", "__fd_mask");
__static_renaming("__fd_set_362", "fd_set");
__static_renaming("__fd_mask_363", "fd_mask");
__static_renaming("__fd_mask_364", "fd_mask");
__static_renaming("__select_376", "select");
__static_renaming("__select_377", "select");
__static_renaming("__pselect_392", "pselect");
__static_renaming("__pselect_393", "pselect");
__static_renaming("____fdelt_chk_397", "__fdelt_chk");
__static_renaming("____fdelt_warn_399", "__fdelt_warn");
__static_renaming("__gnu_dev_major_401", "gnu_dev_major");
__static_renaming("__gnu_dev_major_402", "gnu_dev_major");
__static_renaming("__gnu_dev_minor_404", "gnu_dev_minor");
__static_renaming("__gnu_dev_makedev_407", "gnu_dev_makedev");
__static_renaming("__blksize_t_412", "blksize_t");
__static_renaming("__blksize_t_413", "blksize_t");
__static_renaming("__blkcnt_t_415", "blkcnt_t");
__static_renaming("__blkcnt_t_416", "blkcnt_t");
__static_renaming("__fsblkcnt_t_418", "fsblkcnt_t");
__static_renaming("__fsblkcnt_t_419", "fsblkcnt_t");
__static_renaming("__blkcnt_t_421", "blkcnt_t");
__static_renaming("__blkcnt_t_422", "blkcnt_t");
__static_renaming("__fsblkcnt_t_424", "fsblkcnt_t");
__static_renaming("__fsblkcnt_t_425", "fsblkcnt_t");
__static_renaming("__fsfilcnt_t_427", "fsfilcnt_t");
__static_renaming("__fsfilcnt_t_428", "fsfilcnt_t");
__static_renaming("__fsfilcnt_t_430", "fsfilcnt_t");
__static_renaming("__fsfilcnt_t_431", "fsfilcnt_t");
__static_renaming("__pthread_t_433", "pthread_t");
__static_renaming("__pthread_attr_t_437", "pthread_attr_t");
__static_renaming("____pthread_list_t_442", "__pthread_list_t");
__static_renaming("____pthread_list_t_443", "__pthread_list_t");
__static_renaming("__pthread_mutex_t_459", "pthread_mutex_t");
__static_renaming("__pthread_mutexattr_t_464", "pthread_mutexattr_t");
__static_renaming("__rand_465", "rand");
__static_renaming("__srand_467", "srand");
__static_renaming("__rand_r_469", "rand_r");
__static_renaming("__drand48_470", "drand48");
__static_renaming("__erand48_472", "erand48");
__static_renaming("__lrand48_473", "lrand48");
__static_renaming("__nrand48_475", "nrand48");
__static_renaming("__mrand48_476", "mrand48");
__static_renaming("__jrand48_478", "jrand48");
__static_renaming("__srand48_480", "srand48");
__static_renaming("__seed48_482", "seed48");
__static_renaming("__lcong48_484", "lcong48");
__static_renaming("__malloc_486", "malloc");
__static_renaming("__malloc_487", "malloc");
__static_renaming("__malloc_488", "malloc");
__static_renaming("__malloc_489", "malloc");
__static_renaming("__calloc_492", "calloc");
__static_renaming("__calloc_493", "calloc");
__static_renaming("__realloc_496", "realloc");
__static_renaming("__free_498", "free");
__static_renaming("__cfree_500", "cfree");
__static_renaming("__alloca_502", "alloca");
__static_renaming("__valloc_504", "valloc");
__static_renaming("__valloc_505", "valloc");
__static_renaming("__posix_memalign_509", "posix_memalign");
__static_renaming("__posix_memalign_510", "posix_memalign");
__static_renaming("__aligned_alloc_513", "aligned_alloc");
__static_renaming("__aligned_alloc_514", "aligned_alloc");
__static_renaming("__aligned_alloc_515", "aligned_alloc");
__static_renaming("__aligned_alloc_516", "aligned_alloc");
__static_renaming("__abort_517", "abort");
__static_renaming("__atexit_519", "atexit");
__static_renaming("__at_quick_exit_521", "at_quick_exit");
__static_renaming("__on_exit_526", "on_exit");
__static_renaming("__exit_528", "exit");
__static_renaming("__exit_529", "exit");
__static_renaming("__quick_exit_531", "quick_exit");
__static_renaming("___Exit_533", "_Exit");
__static_renaming("__getenv_535", "getenv");
__static_renaming("__getenv_536", "getenv");
__static_renaming("__putenv_538", "putenv");
__static_renaming("__setenv_542", "setenv");
__static_renaming("__unsetenv_544", "unsetenv");
__static_renaming("__clearenv_545", "clearenv");
__static_renaming("__mktemp_547", "mktemp");
__static_renaming("__mkstemp_550", "mkstemp");
__static_renaming("__mkstemp_551", "mkstemp");
__static_renaming("__mkstemp_552", "mkstemp");
__static_renaming("__mkstemp_553", "mkstemp");
__static_renaming("__mkstemps_558", "mkstemps");
__static_renaming("__mkstemps_559", "mkstemps");
__static_renaming("__mkstemps_560", "mkstemps");
__static_renaming("__mkstemps_561", "mkstemps");
__static_renaming("__mkdtemp_563", "mkdtemp");
__static_renaming("__mkdtemp_564", "mkdtemp");
__static_renaming("__system_566", "system");
__static_renaming("__system_567", "system");
__static_renaming("__system_568", "system");
__static_renaming("__system_569", "system");
__static_renaming("__realpath_572", "realpath");
__static_renaming("__realpath_573", "realpath");
__static_renaming("____compar_fn_t_574", "__compar_fn_t");
__static_renaming("__bsearch_582", "bsearch");
__static_renaming("__bsearch_584", "bsearch");
__static_renaming("____l_591", "__l");
__static_renaming("____u_592", "__u");
__static_renaming("____idx_593", "__idx");
__static_renaming("____p_594", "__p");
__static_renaming("____comparison_595", "__comparison");
__static_renaming("__qsort_603", "qsort");
__static_renaming("__qsort_605", "qsort");
__static_renaming("__abs_608", "abs");
__static_renaming("__abs_609", "abs");
__static_renaming("__labs_611", "labs");
__static_renaming("__labs_612", "labs");
__static_renaming("__llabs_614", "llabs");
__static_renaming("__llabs_615", "llabs");
__static_renaming("__div_618", "div");
__static_renaming("__div_619", "div");
__static_renaming("__ldiv_622", "ldiv");
__static_renaming("__ldiv_624", "ldiv");
__static_renaming("__lldiv_628", "lldiv");
__static_renaming("__lldiv_630", "lldiv");
__static_renaming("__ecvt_636", "ecvt");
__static_renaming("__ecvt_637", "ecvt");
__static_renaming("__fcvt_642", "fcvt");
__static_renaming("__fcvt_643", "fcvt");
__static_renaming("__gcvt_647", "gcvt");
__static_renaming("__gcvt_648", "gcvt");
__static_renaming("__qecvt_653", "qecvt");
__static_renaming("__qecvt_654", "qecvt");
__static_renaming("__qfcvt_659", "qfcvt");
__static_renaming("__qfcvt_660", "qfcvt");
__static_renaming("__qgcvt_664", "qgcvt");
__static_renaming("__qgcvt_665", "qgcvt");
__static_renaming("__ecvt_r_672", "ecvt_r");
__static_renaming("__fcvt_r_679", "fcvt_r");
__static_renaming("__qecvt_r_686", "qecvt_r");
__static_renaming("__qfcvt_r_693", "qfcvt_r");
__static_renaming("__mblen_696", "mblen");
__static_renaming("__mblen_697", "mblen");
__static_renaming("__mbtowc_701", "mbtowc");
__static_renaming("__wctomb_704", "wctomb");
__static_renaming("__mbstowcs_708", "mbstowcs");
__static_renaming("__wcstombs_712", "wcstombs");
__static_renaming("__rpmatch_714", "rpmatch");
__static_renaming("__rpmatch_715", "rpmatch");
__static_renaming("__getsubopt_719", "getsubopt");
__static_renaming("__getsubopt_720", "getsubopt");
__static_renaming("__getloadavg_723", "getloadavg");
__static_renaming("____realpath_chk_728", "__realpath_chk");
__static_renaming("____realpath_alias_731", "__realpath_alias");
__static_renaming("____realpath_chk_warn_735", "__realpath_chk_warn");
__static_renaming("____ptsname_r_chk_743", "__ptsname_r_chk");
__static_renaming("____ptsname_r_alias_747", "__ptsname_r_alias");
__static_renaming("____ptsname_r_chk_warn_752", "__ptsname_r_chk_warn");
__static_renaming("____wctomb_chk_760", "__wctomb_chk");
__static_renaming("____wctomb_alias_763", "__wctomb_alias");
__static_renaming("____mbstowcs_chk_770", "__mbstowcs_chk");
__static_renaming("____mbstowcs_alias_774", "__mbstowcs_alias");
__static_renaming("____mbstowcs_chk_warn_779", "__mbstowcs_chk_warn");
__static_renaming("____wcstombs_chk_787", "__wcstombs_chk");
__static_renaming("____wcstombs_alias_791", "__wcstombs_alias");
__static_renaming("____wcstombs_chk_warn_796", "__wcstombs_chk_warn");
__static_renaming("__memmove_809", "memmove");
__static_renaming("__memset_818", "memset");
__static_renaming("__memset_819", "memset");
__static_renaming("__memcmp_823", "memcmp");
__static_renaming("__memchr_827", "memchr");
__static_renaming("__strcpy_830", "strcpy");
__static_renaming("__strncpy_834", "strncpy");
__static_renaming("__strcat_837", "strcat");
__static_renaming("__strncat_841", "strncat");
__static_renaming("__strcmp_844", "strcmp");
__static_renaming("__strncmp_848", "strncmp");
__static_renaming("__strcoll_851", "strcoll");
__static_renaming("__strxfrm_855", "strxfrm");
__static_renaming("____locale_t_863", "__locale_t");
__static_renaming("__locale_t_864", "locale_t");
__static_renaming("__strcoll_l_868", "strcoll_l");
__static_renaming("__strxfrm_l_873", "strxfrm_l");
__static_renaming("__strdup_875", "strdup");
__static_renaming("__strndup_878", "strndup");
__static_renaming("__strchr_881", "strchr");
__static_renaming("__strchr_882", "strchr");
__static_renaming("__strrchr_885", "strrchr");
__static_renaming("__strcspn_888", "strcspn");
__static_renaming("__strspn_891", "strspn");
__static_renaming("__strpbrk_894", "strpbrk");
__static_renaming("__strstr_897", "strstr");
__static_renaming("__strtok_900", "strtok");
__static_renaming("____strtok_r_904", "__strtok_r");
__static_renaming("__strtok_r_908", "strtok_r");
__static_renaming("__strlen_910", "strlen");
__static_renaming("__strlen_911", "strlen");
__static_renaming("__strnlen_914", "strnlen");
__static_renaming("__strerror_916", "strerror");
__static_renaming("__strerror_917", "strerror");
__static_renaming("__strerror_r_921", "strerror_r");
__static_renaming("__strerror_l_924", "strerror_l");
__static_renaming("____bzero_927", "__bzero");
__static_renaming("____bzero_928", "__bzero");
__static_renaming("__bcopy_932", "bcopy");
__static_renaming("__bzero_935", "bzero");
__static_renaming("__bcmp_939", "bcmp");
__static_renaming("__index_942", "index");
__static_renaming("__rindex_945", "rindex");
__static_renaming("__ffs_947", "ffs");
__static_renaming("__strcasecmp_950", "strcasecmp");
__static_renaming("__strncasecmp_954", "strncasecmp");
__static_renaming("__strsep_957", "strsep");
__static_renaming("__strsignal_959", "strsignal");
__static_renaming("____stpcpy_962", "__stpcpy");
__static_renaming("__stpcpy_965", "stpcpy");
__static_renaming("____stpncpy_969", "__stpncpy");
__static_renaming("__stpncpy_973", "stpncpy");
__static_renaming("____stpncpy_chk_1002", "__stpncpy_chk");
__static_renaming("____stpncpy_alias_1006", "__stpncpy_alias");
__static_renaming("__sc_1018", "sc");
__static_renaming("__sc_1019", "sc");
__static_renaming("__sc_1020", "sc");
__static_renaming("__sc_1021", "sc");
__static_renaming("__ssl_init_ModuleKill_1023", "ssl_init_ModuleKill");
__static_renaming("__ssl_init_ModuleKill_1024", "ssl_init_ModuleKill");
__static_renaming("__main_1037", "main");

__static_condition_renaming("__static_condition_default_60", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && !(defined _SYS_WAIT_H) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_67", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && !(defined _SYS_WAIT_H)");
__static_condition_renaming("__static_condition_default_215", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _SYS_WAIT_H) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_234", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __u_char_defined)");
__static_condition_renaming("__static_condition_default_237", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined __u_char_defined)");
__static_condition_renaming("__static_condition_default_240", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __u_char_defined)");
__static_condition_renaming("__static_condition_default_243", "!(defined __STRICT_ANSI__) && !(defined _FILE_OFFSET_BITS) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __ino_t_defined) || !(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && !(_FILE_OFFSET_BITS == 64) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __ino_t_defined)");
__static_condition_renaming("__static_condition_default_246", "!(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && (_FILE_OFFSET_BITS == 64) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __ino_t_defined)");
__static_condition_renaming("__static_condition_default_249", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __dev_t_defined)");
__static_condition_renaming("__static_condition_default_252", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined __dev_t_defined)");
__static_condition_renaming("__static_condition_default_255", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __dev_t_defined)");
__static_condition_renaming("__static_condition_default_258", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_261", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __nlink_t_defined)");
__static_condition_renaming("__static_condition_default_264", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined __nlink_t_defined)");
__static_condition_renaming("__static_condition_default_267", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __nlink_t_defined)");
__static_condition_renaming("__static_condition_default_270", "!(defined __STRICT_ANSI__) && !(defined _FILE_OFFSET_BITS) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __off_t_defined) || !(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && !(_FILE_OFFSET_BITS == 64) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __off_t_defined)");
__static_condition_renaming("__static_condition_default_273", "!(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && (_FILE_OFFSET_BITS == 64) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __off_t_defined)");
__static_condition_renaming("__static_condition_default_276", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined __off_t_defined)");
__static_condition_renaming("__static_condition_default_279", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __off_t_defined)");
__static_condition_renaming("__static_condition_default_282", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __id_t_defined)");
__static_condition_renaming("__static_condition_default_285", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __ssize_t_defined)");
__static_condition_renaming("__static_condition_default_288", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __daddr_t_defined)");
__static_condition_renaming("__static_condition_default_293", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined __daddr_t_defined)");
__static_condition_renaming("__static_condition_default_296", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __daddr_t_defined)");
__static_condition_renaming("__static_condition_default_299", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __clock_t_defined)");
__static_condition_renaming("__static_condition_default_302", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __time_t_defined)");
__static_condition_renaming("__static_condition_default_305", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __clockid_t_defined)");
__static_condition_renaming("__static_condition_default_308", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __timer_t_defined)");
__static_condition_renaming("__static_condition_default_325", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _SYS_WAIT_H)");
__static_condition_renaming("__static_condition_default_341", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __timespec_defined)");
__static_condition_renaming("__static_condition_default_349", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined _STRUCT_TIMEVAL)");
__static_condition_renaming("__static_condition_default_352", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __suseconds_t_defined)");
__static_condition_renaming("__static_condition_default_361", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_378", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined _STRUCT_TIMEVAL)");
__static_condition_renaming("__static_condition_default_379", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined _STRUCT_TIMEVAL)");
__static_condition_renaming("__static_condition_default_394", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __timespec_defined)");
__static_condition_renaming("__static_condition_default_395", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined __timespec_defined)");
__static_condition_renaming("__static_condition_default_414", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __blksize_t_defined)");
__static_condition_renaming("__static_condition_default_417", "!(defined __STRICT_ANSI__) && !(defined _FILE_OFFSET_BITS) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __blkcnt_t_defined) || !(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && !(_FILE_OFFSET_BITS == 64) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __blkcnt_t_defined)");
__static_condition_renaming("__static_condition_default_420", "!(defined __STRICT_ANSI__) && !(defined _FILE_OFFSET_BITS) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) || !(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && !(_FILE_OFFSET_BITS == 64) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_423", "!(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && (_FILE_OFFSET_BITS == 64) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __blkcnt_t_defined)");
__static_condition_renaming("__static_condition_default_426", "!(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && (_FILE_OFFSET_BITS == 64) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_429", "!(defined __STRICT_ANSI__) && !(defined _FILE_OFFSET_BITS) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) || !(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && !(_FILE_OFFSET_BITS == 64) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_432", "!(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && (_FILE_OFFSET_BITS == 64) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_581", "!(defined _FORTIFY_SOURCE) && !(defined __need_malloc_and_calloc) && (defined __COMPAR_FN_T) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined __need_malloc_and_calloc) && (defined __COMPAR_FN_T) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined __need_malloc_and_calloc) && (defined __COMPAR_FN_T) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_583", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_596", "!(defined __need_malloc_and_calloc) && (defined __USE_EXTERN_INLINES) && !(defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_597", "!(defined __need_malloc_and_calloc) && (defined __USE_EXTERN_INLINES) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_604", "!(defined __need_malloc_and_calloc) && !(defined __USE_EXTERN_INLINES) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_606", "!(defined __need_malloc_and_calloc) && (defined __USE_EXTERN_INLINES) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_623", "!(defined _FORTIFY_SOURCE) && !(defined __need_malloc_and_calloc) && (defined __ldiv_t_defined) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined __need_malloc_and_calloc) && (defined __ldiv_t_defined) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined __need_malloc_and_calloc) && (defined __ldiv_t_defined) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && (defined __ldiv_t_defined)");
__static_condition_renaming("__static_condition_default_625", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && (defined __ldiv_t_defined)");
__static_condition_renaming("__static_condition_default_629", "!(defined _FORTIFY_SOURCE) && !(defined __need_malloc_and_calloc) && (defined __lldiv_t_defined) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined __need_malloc_and_calloc) && (defined __lldiv_t_defined) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined __need_malloc_and_calloc) && (defined __lldiv_t_defined) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && (defined __lldiv_t_defined)");
__static_condition_renaming("__static_condition_default_631", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && (defined __lldiv_t_defined)");
__static_condition_renaming("__static_condition_default_738", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc)");
__static_condition_renaming("__static_condition_default_803", "!(defined _FORTIFY_SOURCE) && !(defined __need_malloc_and_calloc) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined __need_malloc_and_calloc) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined __need_malloc_and_calloc) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc)");
__static_condition_renaming("__static_condition_default_804", "(defined __need_malloc_and_calloc)");
__static_condition_renaming("__static_condition_default_805", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc)");
__static_condition_renaming("__static_condition_default_814", "!(defined __STRICT_ANSI__)");
__static_condition_renaming("__static_condition_default_977", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_984", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_992", "(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_993", "!(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_997", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_1010", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_1013", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_1017", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_1022", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc)");
__static_condition_renaming("__static_condition_default_1025", "!(defined _FORTIFY_SOURCE) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_1026", "(defined __STRICT_ANSI__) && !(defined _FORTIFY_SOURCE) && !(defined __need_malloc_and_calloc) || (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined __need_malloc_and_calloc) || (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined __need_malloc_and_calloc) || (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc)");
__static_condition_renaming("__static_condition_default_1027", "!(defined _FORTIFY_SOURCE) && (defined __need_malloc_and_calloc) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && (defined __need_malloc_and_calloc) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && (defined __need_malloc_and_calloc) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && (defined __need_malloc_and_calloc)");
__static_condition_renaming("__static_condition_default_1028", "(defined __STRICT_ANSI__) && !(defined _FORTIFY_SOURCE) && !(defined __need_malloc_and_calloc) && (defined SHARED_MODULE) || (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined __need_malloc_and_calloc) && (defined SHARED_MODULE) || (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined __need_malloc_and_calloc) && (defined SHARED_MODULE) || (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && (defined SHARED_MODULE)");
__static_condition_renaming("__static_condition_default_1029", "!(defined __STRICT_ANSI__) && !(defined _FORTIFY_SOURCE) && (defined SHARED_MODULE) || !(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && (defined SHARED_MODULE) || !(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && (defined SHARED_MODULE) || !(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && (defined SHARED_MODULE) || (defined __STRICT_ANSI__) && !(defined _FORTIFY_SOURCE) && (defined __need_malloc_and_calloc) && (defined SHARED_MODULE) || (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && (defined __need_malloc_and_calloc) && (defined SHARED_MODULE) || (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && (defined __need_malloc_and_calloc) && (defined SHARED_MODULE) || (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && (defined __need_malloc_and_calloc) && (defined SHARED_MODULE)");
__static_condition_renaming("__static_condition_default_1030", "!(defined _FORTIFY_SOURCE) && !(defined SHARED_MODULE) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined SHARED_MODULE) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined SHARED_MODULE) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined SHARED_MODULE)");
__static_condition_renaming("__static_condition_default_1031", "!(defined _FORTIFY_SOURCE) && (defined SHARED_MODULE) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && (defined SHARED_MODULE) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && (defined SHARED_MODULE) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && (defined SHARED_MODULE)");
__static_condition_renaming("__static_condition_default_1032", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_1033", "(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && (defined SHARED_MODULE)");
__static_condition_renaming("__static_condition_default_1034", "!(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && (defined SHARED_MODULE) || (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && (defined __need_malloc_and_calloc) && (defined SHARED_MODULE)");
__static_condition_renaming("__static_condition_default_1035", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined SHARED_MODULE)");
__static_condition_renaming("__static_condition_default_1036", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && (defined SHARED_MODULE)");
__static_condition_renaming("__static_condition_default_1038", "!(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc)");

if (__static_condition_default_1038) {
__static_parse_error("Unable to parse");
}
};
typedef long int  __ptrdiff_t_0;// L143:L324
typedef long unsigned int  __size_t_1;// L177:L209
typedef int  __wchar_t_2;// L243:L321
enum ____anonymous_tag_6_7 {
__P_ALL_3,
__P_PID_4,
__P_PGID_5,
};
typedef enum ____anonymous_tag_6_7  __idtype_t_8;// L50:L55
typedef unsigned char  ____u_char_9;// L30
typedef unsigned short int  ____u_short_10;// L31
typedef unsigned int  ____u_int_11;// L32
typedef unsigned long int  ____u_long_12;// L33
typedef signed char  ____int8_t_13;// L36
typedef unsigned char  ____uint8_t_14;// L37
typedef signed short int  ____int16_t_15;// L38
typedef unsigned short int  ____uint16_t_16;// L39
typedef signed int  ____int32_t_17;// L40
typedef unsigned int  ____uint32_t_18;// L41
typedef signed long int  ____int64_t_19;// L43
typedef unsigned long int  ____uint64_t_20;// L44
typedef long int  ____quad_t_21;// L52
typedef unsigned long int  ____u_quad_t_22;// L53
typedef unsigned long int  ____dev_t_23;// L109:L124
typedef unsigned int  ____uid_t_24;// L92:L125
typedef unsigned int  ____gid_t_25;// L92:L126
typedef unsigned long int  ____ino_t_26;// L94:L127
typedef unsigned long int  ____ino64_t_27;// L109:L128
typedef unsigned int  ____mode_t_28;// L92:L129
typedef unsigned long int  ____nlink_t_29;// L94:L130
typedef long int  ____off_t_30;// L93:L131
typedef long int  ____off64_t_31;// L108:L132
typedef int  ____pid_t_32;// L91:L133
struct ____anonymous_tag_33_34 {
int  ____val_35[2];// L72
};
typedef struct ____anonymous_tag_33_34  ____fsid_t_36;// L72:L134
typedef long int  ____clock_t_37;// L93:L135
typedef unsigned long int  ____rlim_t_38;// L94:L136
typedef unsigned long int  ____rlim64_t_39;// L109:L137
typedef unsigned int  ____id_t_40;// L92:L138
typedef long int  ____time_t_41;// L93:L139
typedef unsigned int  ____useconds_t_42;// L92:L140
typedef long int  ____suseconds_t_43;// L93:L141
typedef int  ____daddr_t_44;// L91:L143
typedef int  ____key_t_45;// L91:L144
typedef int  ____clockid_t_46;// L91:L147
typedef void  * (____timer_t_47);// L70:L150
typedef long int  ____blksize_t_48;// L93:L153
typedef long int  ____blkcnt_t_49;// L93:L158
typedef long int  ____blkcnt64_t_50;// L108:L159
typedef unsigned long int  ____fsblkcnt_t_51;// L94:L162
typedef unsigned long int  ____fsblkcnt64_t_52;// L109:L163
typedef unsigned long int  ____fsfilcnt_t_53;// L94:L166
typedef unsigned long int  ____fsfilcnt64_t_54;// L109:L167
typedef long int  ____fsword_t_55;// L93:L170
typedef long int  ____ssize_t_56;// L110:L172
typedef long int  ____syscall_slong_t_57;// L93:L175
typedef unsigned long int  ____syscall_ulong_t_58;// L94:L177
typedef ____off64_t_31  ____loff_t_59;// L181
typedef ____quad_t_21  * (____qaddr_t_61);// L182
typedef char  * (____caddr_t_62);// L183
typedef long int  ____intptr_t_63;// L110:L186
typedef unsigned int  ____socklen_t_64;// L92:L189
struct ____anonymous_tag_70_71 {
unsigned int  ____w_termsig_72 : 7;// L72
unsigned int  ____w_coredump_73 : 1;// L73
unsigned int  ____w_retcode_74 : 8;// L74
unsigned int  __anon_id_0_75 : 16;// L75
};
struct ____anonymous_tag_76_77 {
unsigned int  ____w_stopval_78 : 8;// L87
unsigned int  ____w_stopsig_79 : 8;// L88
unsigned int  __anon_id_1_80 : 16;// L89
};
union __wait_81 {
int  __w_status_82;// L68
struct ____anonymous_tag_70_71  ____wait_terminated_83;// L69
struct ____anonymous_tag_76_77  ____wait_stopped_84;// L84
};
union ____anonymous_tag_85_86 {
union __wait_81  * (____uptr_87);// L69
int  * (____iptr_88);// L70
};
typedef union ____anonymous_tag_85_86  ____WAIT_STATUS_89;// L67:L71
struct ____anonymous_tag_90_91 {
int  __quot_92;// L99
int  __rem_93;// L100
};
typedef struct ____anonymous_tag_90_91  __div_t_94;// L97:L101
struct ____anonymous_tag_95_96 {
long int  __quot_97;// L107
long int  __rem_98;// L108
};
typedef struct ____anonymous_tag_95_96  __ldiv_t_99;// L105:L109
struct ____anonymous_tag_100_101 {
long long int  __quot_102;// L119
long long int  __rem_103;// L120
};
typedef struct ____anonymous_tag_100_101  __lldiv_t_104;// L117:L121
typedef unsigned char  ____u_char_164;// L30
typedef unsigned short int  ____u_short_165;// L31
typedef unsigned int  ____u_int_166;// L32
typedef unsigned long int  ____u_long_167;// L33
typedef signed char  ____int8_t_168;// L36
typedef unsigned char  ____uint8_t_169;// L37
typedef signed short int  ____int16_t_170;// L38
typedef unsigned short int  ____uint16_t_171;// L39
typedef signed int  ____int32_t_172;// L40
typedef unsigned int  ____uint32_t_173;// L41
typedef signed long int  ____int64_t_174;// L43
typedef unsigned long int  ____uint64_t_175;// L44
typedef long int  ____quad_t_176;// L52
typedef unsigned long int  ____u_quad_t_177;// L53
typedef unsigned long int  ____dev_t_178;// L109:L124
typedef unsigned int  ____uid_t_179;// L92:L125
typedef unsigned int  ____gid_t_180;// L92:L126
typedef unsigned long int  ____ino_t_181;// L94:L127
typedef unsigned long int  ____ino64_t_182;// L109:L128
typedef unsigned int  ____mode_t_183;// L92:L129
typedef unsigned long int  ____nlink_t_184;// L94:L130
typedef long int  ____off_t_185;// L93:L131
typedef long int  ____off64_t_186;// L108:L132
typedef int  ____pid_t_187;// L91:L133
struct ____anonymous_tag_188_189 {
int  ____val_190[2];// L72
};
typedef struct ____anonymous_tag_188_189  ____fsid_t_191;// L72:L134
typedef long int  ____clock_t_192;// L93:L135
typedef unsigned long int  ____rlim_t_193;// L94:L136
typedef unsigned long int  ____rlim64_t_194;// L109:L137
typedef unsigned int  ____id_t_195;// L92:L138
typedef long int  ____time_t_196;// L93:L139
typedef unsigned int  ____useconds_t_197;// L92:L140
typedef long int  ____suseconds_t_198;// L93:L141
typedef int  ____daddr_t_199;// L91:L143
typedef int  ____key_t_200;// L91:L144
typedef int  ____clockid_t_201;// L91:L147
typedef void  * (____timer_t_202);// L70:L150
typedef long int  ____blksize_t_203;// L93:L153
typedef long int  ____blkcnt_t_204;// L93:L158
typedef long int  ____blkcnt64_t_205;// L108:L159
typedef unsigned long int  ____fsblkcnt_t_206;// L94:L162
typedef unsigned long int  ____fsblkcnt64_t_207;// L109:L163
typedef unsigned long int  ____fsfilcnt_t_208;// L94:L166
typedef unsigned long int  ____fsfilcnt64_t_209;// L109:L167
typedef long int  ____fsword_t_210;// L93:L170
typedef long int  ____ssize_t_211;// L110:L172
typedef long int  ____syscall_slong_t_212;// L93:L175
typedef unsigned long int  ____syscall_ulong_t_213;// L94:L177
typedef ____off64_t_186  ____loff_t_214;// L181
typedef ____quad_t_176  * (____qaddr_t_216);// L182
typedef char  * (____caddr_t_217);// L183
typedef long int  ____intptr_t_218;// L110:L186
typedef unsigned int  ____socklen_t_219;// L92:L189
typedef ____u_char_9  __u_char_220;// L33
typedef ____u_char_164  __u_char_221;// L33
typedef ____u_short_10  __u_short_222;// L34
typedef ____u_short_165  __u_short_223;// L34
typedef ____u_int_11  __u_int_224;// L35
typedef ____u_int_166  __u_int_225;// L35
typedef ____u_long_12  __u_long_226;// L36
typedef ____u_long_167  __u_long_227;// L36
typedef ____quad_t_21  __quad_t_228;// L37
typedef ____quad_t_176  __quad_t_229;// L37
typedef ____u_quad_t_22  __u_quad_t_230;// L38
typedef ____u_quad_t_177  __u_quad_t_231;// L38
typedef ____fsid_t_36  __fsid_t_232;// L39
typedef ____fsid_t_191  __fsid_t_233;// L39
typedef ____loff_t_59  __loff_t_235;// L44
typedef ____loff_t_214  __loff_t_236;// L44
typedef ____loff_t_59  __loff_t_238;// L44
typedef ____loff_t_214  __loff_t_239;// L44
typedef ____ino_t_26  __ino_t_241;// L48
typedef ____ino_t_181  __ino_t_242;// L48
typedef ____ino64_t_27  __ino_t_244;// L50
typedef ____ino64_t_182  __ino_t_245;// L50
typedef ____dev_t_23  __dev_t_247;// L60
typedef ____dev_t_178  __dev_t_248;// L60
typedef ____gid_t_25  __gid_t_250;// L65
typedef ____gid_t_180  __gid_t_251;// L65
typedef ____gid_t_25  __gid_t_253;// L65
typedef ____gid_t_180  __gid_t_254;// L65
typedef ____mode_t_28  __mode_t_256;// L70
typedef ____mode_t_183  __mode_t_257;// L70
typedef ____nlink_t_29  __nlink_t_259;// L75
typedef ____nlink_t_184  __nlink_t_260;// L75
typedef ____uid_t_24  __uid_t_262;// L80
typedef ____uid_t_179  __uid_t_263;// L80
typedef ____uid_t_24  __uid_t_265;// L80
typedef ____uid_t_179  __uid_t_266;// L80
typedef ____off_t_30  __off_t_268;// L86
typedef ____off_t_185  __off_t_269;// L86
typedef ____off64_t_31  __off_t_271;// L88
typedef ____off64_t_186  __off_t_272;// L88
typedef ____pid_t_32  __pid_t_274;// L98
typedef ____pid_t_187  __pid_t_275;// L98
typedef ____pid_t_32  __pid_t_277;// L98
typedef ____pid_t_187  __pid_t_278;// L98
typedef ____id_t_40  __id_t_280;// L104
typedef ____id_t_195  __id_t_281;// L104
typedef ____ssize_t_56  __ssize_t_283;// L109
typedef ____ssize_t_211  __ssize_t_284;// L109
typedef ____daddr_t_44  __daddr_t_286;// L115
typedef ____daddr_t_199  __daddr_t_287;// L115
typedef ____caddr_t_62  __caddr_t_289;// L116
typedef ____caddr_t_217  __caddr_t_290;// L116
typedef ____key_t_45  __key_t_291;// L122
typedef ____key_t_200  __key_t_292;// L122
typedef ____key_t_45  __key_t_294;// L122
typedef ____key_t_200  __key_t_295;// L122
typedef ____clock_t_37  __clock_t_297;// L59
typedef ____clock_t_192  __clock_t_298;// L59
typedef ____time_t_41  __time_t_300;// L75
typedef ____time_t_196  __time_t_301;// L75
typedef ____clockid_t_46  __clockid_t_303;// L91
typedef ____clockid_t_201  __clockid_t_304;// L91
typedef ____timer_t_47  __timer_t_306;// L103
typedef ____timer_t_202  __timer_t_307;// L103
typedef unsigned long int  __ulong_309;// L150
typedef unsigned long int  __ulong_310;// L150
typedef unsigned long int  __ulong_311;// L150
typedef unsigned short int  __ushort_312;// L151
typedef unsigned int  __uint_313;// L152
typedef int  __int8_t_314;// L188:L194
typedef int  __int16_t_315;// L188:L195
typedef int  __int32_t_316;// L188:L196
typedef int  __int64_t_317;// L188:L197
typedef unsigned int  __u_int8_t_318;// L190:L200
typedef unsigned int  __u_int16_t_319;// L190:L201
typedef unsigned int  __u_int32_t_320;// L190:L202
typedef unsigned int  __u_int64_t_321;// L190:L203
typedef int  __register_t_322;// L205
typedef int  ____sig_atomic_t_328;// L22
struct ____anonymous_tag_329_330 {
unsigned long int  ____val_331[( 1024 / ( 8 * sizeof(unsigned long) ) )];// L29
};
typedef struct ____anonymous_tag_329_330  ____sigset_t_332;// L27:L30
typedef ____sigset_t_332  __sigset_t_333;// L37
struct __timespec_334 {
____time_t_41  __tv_sec_335;// L0
____time_t_196  __tv_sec_336;// L0
____syscall_slong_t_57  __tv_nsec_338;// L0
____syscall_slong_t_212  __tv_nsec_339;// L0
};
struct __timeval_342 {
____time_t_41  __tv_sec_343;// L0
____time_t_196  __tv_sec_344;// L0
____suseconds_t_43  __tv_usec_346;// L0
____suseconds_t_198  __tv_usec_347;// L0
};
typedef ____suseconds_t_43  __suseconds_t_350;// L48
typedef ____suseconds_t_198  __suseconds_t_351;// L48
typedef long int  ____fd_mask_353;// L54
typedef long int  ____fd_mask_354;// L54
struct ____anonymous_tag_355_356 {
____fd_mask_353  ____fds_bits_357[1024 / ( 8 * ( int   ) sizeof(long) )];// L0
____fd_mask_354  ____fds_bits_359[1024 / ( 8 * ( int   ) sizeof(long) )];// L0
};
typedef struct ____anonymous_tag_355_356  __fd_set_362;// L64:L75
typedef ____fd_mask_353  __fd_mask_363;// L82
typedef ____fd_mask_354  __fd_mask_364;// L82
typedef ____blksize_t_48  __blksize_t_412;// L228
typedef ____blksize_t_203  __blksize_t_413;// L228
typedef ____blkcnt_t_49  __blkcnt_t_415;// L235
typedef ____blkcnt_t_204  __blkcnt_t_416;// L235
typedef ____fsblkcnt_t_51  __fsblkcnt_t_418;// L239
typedef ____fsblkcnt_t_206  __fsblkcnt_t_419;// L239
typedef ____blkcnt64_t_50  __blkcnt_t_421;// L248
typedef ____blkcnt64_t_205  __blkcnt_t_422;// L248
typedef ____fsblkcnt64_t_52  __fsblkcnt_t_424;// L252
typedef ____fsblkcnt64_t_207  __fsblkcnt_t_425;// L252
typedef ____fsfilcnt_t_53  __fsfilcnt_t_427;// L243
typedef ____fsfilcnt_t_208  __fsfilcnt_t_428;// L243
typedef ____fsfilcnt64_t_54  __fsfilcnt_t_430;// L256
typedef ____fsfilcnt64_t_209  __fsfilcnt_t_431;// L256
typedef unsigned long int  __pthread_t_433;// L60
union __pthread_attr_t_434 {
char  ____size_435[56];// L65
long int  ____align_436;// L66
};
typedef union __pthread_attr_t_434  __pthread_attr_t_437;// L69
struct ____pthread_internal_list_439 {
struct __forward_tag_reference_438  * (____prev_440);// L0
struct __forward_tag_reference_438  * (____next_441);// L0
};
typedef struct ____pthread_internal_list_439  ____pthread_list_t_442;// L75:L79
typedef struct ____pthread_internal_list_439  ____pthread_list_t_443;// L75:L79
struct ____pthread_mutex_s_444 {
int  ____lock_445;// L94
unsigned int  ____count_446;// L95
int  ____owner_447;// L96
unsigned int  ____nusers_448;// L98
int  ____kind_449;// L102
short  ____spins_450;// L104
short  ____elision_451;// L105
____pthread_list_t_442  ____list_452;// L0
____pthread_list_t_443  ____list_453;// L0
};
union ____anonymous_tag_454_455 {
struct ____pthread_mutex_s_444  ____data_456;// L92
char  ____size_457[40];// L126
long int  ____align_458;// L127
};
typedef union ____anonymous_tag_454_455  __pthread_mutex_t_459;// L90:L128
union ____anonymous_tag_460_461 {
char  ____size_462[4];// L132
int  ____align_463;// L133
};
typedef union ____anonymous_tag_460_461  __pthread_mutexattr_t_464;// L130:L134
typedef int  (* (____compar_fn_t_574)) (const void  *, const void  *);// L741
struct ____locale_struct_857 {
struct __forward_tag_reference_856  * (____locales_858[13]);// L0
const unsigned short int  * (____ctype_b_859);// L33
const int  * (____ctype_tolower_860);// L34
const int  * (____ctype_toupper_861);// L35
const char  * (____names_862[13]);// L38
};
typedef struct ____locale_struct_857  * (____locale_t_863);// L27:L39
typedef ____locale_t_863  __locale_t_864;// L42

struct __forward_tag_reference_438 { // generated union of struct variations
union {
};
};

struct __forward_tag_reference_856 { // generated union of struct variations
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
// typedef moved to top of scope
static __inline unsigned int  (____bswap_32_66) (unsigned int  ____bsx_65) {

if (__static_condition_default_67) {

{
{



__static_type_error("invalid type found in return expression");
}
}


}
}
static __inline ____uint64_t_20  (____bswap_64_69) (____uint64_t_20  ____bsx_68) {

if (__static_condition_default_67) {

{
{



__static_type_error("invalid type found in return expression");
}
}


}
}
union __wait_81 ;// L66
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
extern __size_t_1  (____ctype_get_mb_cur_max_105) (void  );// L139
extern __size_t_1  (____ctype_get_mb_cur_max_106) (void  );// L139
extern __size_t_1  (____ctype_get_mb_cur_max_107) (void  );// L139
extern __size_t_1  (____ctype_get_mb_cur_max_108) (void  );// L139
extern double  (__atof_110) (const char  * (____nptr_109));// L144:L145
extern double  (__atof_111) (const char  * (____nptr_109));// L144:L145
extern int  (__atoi_113) (const char  * (____nptr_112));// L147:L148
extern int  (__atoi_114) (const char  * (____nptr_112));// L147:L148
extern long int  (__atol_116) (const char  * (____nptr_115));// L150:L151
extern long int  (__atol_117) (const char  * (____nptr_115));// L150:L151
extern long long int  (__atoll_119) (const char  * (____nptr_118));// L157:L158
extern long long int  (__atoll_120) (const char  * (____nptr_118));// L157:L158
extern double  (__strtod_123) (const char  * __restrict  ____nptr_121, char  * (* __restrict  ____endptr_122));// L164:L166
extern float  (__strtof_126) (const char  * __restrict  ____nptr_124, char  * (* __restrict  ____endptr_125));// L172:L173
extern long double  (__strtold_129) (const char  * __restrict  ____nptr_127, char  * (* __restrict  ____endptr_128));// L175:L177
extern long int  (__strtol_133) (const char  * __restrict  ____nptr_130, char  * (* __restrict  ____endptr_131), int  ____base_132);// L183:L185
extern unsigned long int  (__strtoul_137) (const char  * __restrict  ____nptr_134, char  * (* __restrict  ____endptr_135), int  ____base_136);// L187:L189
extern long long int  (__strtoq_141) (const char  * __restrict  ____nptr_138, char  * (* __restrict  ____endptr_139), int  ____base_140);// L195:L197
extern unsigned long long int  (__strtouq_145) (const char  * __restrict  ____nptr_142, char  * (* __restrict  ____endptr_143), int  ____base_144);// L200:L202
extern long long int  (__strtoll_149) (const char  * __restrict  ____nptr_146, char  * (* __restrict  ____endptr_147), int  ____base_148);// L209:L211
extern long long int  (__strtoll_150) (const char  * __restrict  ____nptr_146, char  * (* __restrict  ____endptr_147), int  ____base_148);// L209:L211
extern unsigned long long int  (__strtoull_154) (const char  * __restrict  ____nptr_151, char  * (* __restrict  ____endptr_152), int  ____base_153);// L214:L216
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
__extension__/* no function due to type errors in the function prototype */
extern char  * ((__l64a_159) (long int  ____n_158));// L305
extern char  * ((__l64a_160) (long int  ____n_158));// L305
extern long int  (__a64l_162) (const char  * (____s_161));// L308:L309
extern long int  (__a64l_163) (const char  * (____s_161));// L308:L309
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
static __inline unsigned int  (____bswap_32_324) (unsigned int  ____bsx_323) {

if (__static_condition_default_325) {

{
{



__static_type_error("invalid type found in return expression");
}
}


}
}
static __inline ____uint64_t_175  (____bswap_64_327) (____uint64_t_175  ____bsx_326) {

if (__static_condition_default_325) {

{
{



__static_type_error("invalid type found in return expression");
}
}


}
}
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
struct __timespec_334 ;// L120

struct __timeval_342 ;// L30

// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
extern int  (__select_376) (int  ____nfds_365, __fd_set_362  * __restrict  ____readfds_366, __fd_set_362  * __restrict  ____writefds_368, __fd_set_362  * __restrict  ____exceptfds_370, struct __timeval_342  * __restrict  ____timeout_373);// L106:L109
extern int  (__select_377) (int  ____nfds_365, __fd_set_362  * __restrict  ____readfds_366, __fd_set_362  * __restrict  ____writefds_368, __fd_set_362  * __restrict  ____exceptfds_370, struct __forward_tag_reference_372  * __restrict  ____timeout_375);// L106:L109
extern int  (__pselect_392) (int  ____nfds_380, __fd_set_362  * __restrict  ____readfds_381, __fd_set_362  * __restrict  ____writefds_383, __fd_set_362  * __restrict  ____exceptfds_385, const struct __timespec_334  * __restrict  ____timeout_388, const ____sigset_t_332  * __restrict  ____sigmask_391);// L118:L122
extern int  (__pselect_393) (int  ____nfds_380, __fd_set_362  * __restrict  ____readfds_381, __fd_set_362  * __restrict  ____writefds_383, __fd_set_362  * __restrict  ____exceptfds_385, const struct __forward_tag_reference_387  * __restrict  ____timeout_390, const ____sigset_t_332  * __restrict  ____sigmask_391);// L118:L122
extern long int  (____fdelt_chk_397) (long int  ____d_396);// L24
extern long int  (____fdelt_warn_399) (long int  ____d_398);// L25:L26
extern unsigned int  (__gnu_dev_major_401) (unsigned long long int  ____dev_400);// L27:L28
extern unsigned int  (__gnu_dev_major_402) (unsigned long long int  ____dev_400);// L27:L28
extern unsigned int  (__gnu_dev_minor_404) (unsigned long long int  ____dev_403);// L30:L31
extern unsigned long long int  (__gnu_dev_makedev_407) (unsigned int  ____major_405, unsigned int  ____minor_406);// L33:L35
__extension__/* no function due to type errors in the function prototype */
__extension__/* no function due to type errors in the function prototype */
__extension__/* no function due to type errors in the function prototype */
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
union __pthread_attr_t_434 ;// L63
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
extern int  (__rand_465) (void  );// L374
extern void  (__srand_467) (unsigned int  ____seed_466);// L376
extern int  (__rand_r_469) (unsigned int  * (____seed_468));// L381
extern double  (__drand48_470) (void  );// L389
extern double  (__erand48_472) (unsigned short int  ____xsubi_471[3]);// L390
extern long int  (__lrand48_473) (void  );// L393
extern long int  (__nrand48_475) (unsigned short int  ____xsubi_474[3]);// L394:L395
extern long int  (__mrand48_476) (void  );// L398
extern long int  (__jrand48_478) (unsigned short int  ____xsubi_477[3]);// L399:L400
extern void  (__srand48_480) (long int  ____seedval_479);// L403
extern unsigned short int  * ((__seed48_482) (unsigned short int  ____seed16v_481[3]));// L404:L405
extern void  (__lcong48_484) (unsigned short int  ____param_483[7]);// L406
extern void  * ((__malloc_486) (__size_t_1  ____size_485));// L466
extern void  * ((__malloc_487) (__size_t_1  ____size_485));// L466
extern void  * ((__malloc_488) (__size_t_1  ____size_485));// L466
extern void  * ((__malloc_489) (__size_t_1  ____size_485));// L466
extern void  * ((__calloc_492) (__size_t_1  ____nmemb_490, __size_t_1  ____size_491));// L468:L469
extern void  * ((__calloc_493) (__size_t_1  ____nmemb_490, __size_t_1  ____size_491));// L468:L469
extern void  * ((__realloc_496) (void  * (____ptr_494), __size_t_1  ____size_495));// L480:L481
extern void  (__free_498) (void  * (____ptr_497));// L483
extern void  (__cfree_500) (void  * (____ptr_499));// L488
extern void  * ((__alloca_502) (__size_t_1  ____size_501));// L32
extern void  * ((__valloc_504) (__size_t_1  ____size_503));// L498
extern void  * ((__valloc_505) (__size_t_1  ____size_503));// L498
extern int  (__posix_memalign_509) (void  * (* (____memptr_506)), __size_t_1  ____alignment_507, __size_t_1  ____size_508);// L503:L504
extern int  (__posix_memalign_510) (void  * (* (____memptr_506)), __size_t_1  ____alignment_507, __size_t_1  ____size_508);// L503:L504
extern void  * ((__aligned_alloc_513) (__size_t_1  ____alignment_511, __size_t_1  ____size_512));// L509:L510
extern void  * ((__aligned_alloc_514) (__size_t_1  ____alignment_511, __size_t_1  ____size_512));// L509:L510
extern void  * ((__aligned_alloc_515) (__size_t_1  ____alignment_511, __size_t_1  ____size_512));// L509:L510
extern void  * ((__aligned_alloc_516) (__size_t_1  ____alignment_511, __size_t_1  ____size_512));// L509:L510
extern void  (__abort_517) (void  );// L515
extern int  (__atexit_519) (void  (* (____func_518)) (void  ));// L519
extern int  (__at_quick_exit_521) (void  (* (____func_520)) (void  ));// L527
extern int  (__on_exit_526) (void  (* (____func_524)) (int  ____status_522, void  * (____arg_523)), void  * (____arg_525));// L535:L536
extern void  (__exit_528) (int  ____status_527);// L543
extern void  (__exit_529) (int  ____status_527);// L543
extern void  (__quick_exit_531) (int  ____status_530);// L549
extern void  (___Exit_533) (int  ____status_532);// L557
extern char  * ((__getenv_535) (const char  * (____name_534)));// L564
extern char  * ((__getenv_536) (const char  * (____name_534)));// L564
extern int  (__putenv_538) (char  * (____string_537));// L578
extern int  (__setenv_542) (const char  * (____name_539), const char  * (____value_540), int  ____replace_541);// L584:L585
extern int  (__unsetenv_544) (const char  * (____name_543));// L588
extern int  (__clearenv_545) (void  );// L595
extern char  * ((__mktemp_547) (char  * (____template_546)));// L606
extern int  (__mkstemp_550) (char  * (____template_548));// L619
extern int  (__mkstemp_552) (char  * (____template_548));// L619
extern int  (__mkstemp_551) (char  * (____template_549));// L622:L623
extern int  (__mkstemp_553) (char  * (____template_549));// L622:L623
extern int  (__mkstemps_558) (char  * (____template_554), int  ____suffixlen_555);// L641
extern int  (__mkstemps_559) (char  * (____template_556), int  ____suffixlen_557);// L644:L645
extern int  (__mkstemps_560) (char  * (____template_554), int  ____suffixlen_555);// L641
extern int  (__mkstemps_561) (char  * (____template_556), int  ____suffixlen_557);// L644:L645
extern char  * ((__mkdtemp_563) (char  * (____template_562)));// L662
extern char  * ((__mkdtemp_564) (char  * (____template_562)));// L662
extern int  (__system_566) (const char  * (____command_565));// L716
extern int  (__system_567) (const char  * (____command_565));// L716
extern int  (__system_568) (const char  * (____command_565));// L716
extern int  (__system_569) (const char  * (____command_565));// L716
extern char  * ((__realpath_572) (const char  * __restrict  ____name_570, char  * __restrict  ____resolved_571));// L733:L734
extern char  * ((__realpath_573) (const char  * __restrict  ____name_570, char  * __restrict  ____resolved_571));// L733:L734
// typedef moved to top of scope
extern void  * ((__bsearch_582) (const void  * (____key_575), const void  * (____base_576), __size_t_1  ____nmemb_577, __size_t_1  ____size_578, ____compar_fn_t_574  ____compar_579));// L754:L756
extern void  * ((__bsearch_584) (const void  * (____key_575), const void  * (____base_576), __size_t_1  ____nmemb_577, __size_t_1  ____size_578, ____compar_fn_t_574  ____compar_579));// L754:L756
/* no function due to type errors in the function prototype */
extern void  (__qsort_603) (void  * (____base_598), __size_t_1  ____nmemb_599, __size_t_1  ____size_600, ____compar_fn_t_574  ____compar_601);// L764:L765
extern void  (__qsort_605) (void  * (____base_598), __size_t_1  ____nmemb_599, __size_t_1  ____size_600, ____compar_fn_t_574  ____compar_601);// L764:L765
extern int  (__abs_608) (int  ____x_607);// L774
extern int  (__abs_609) (int  ____x_607);// L774
extern long int  (__labs_611) (long int  ____x_610);// L775
extern long int  (__labs_612) (long int  ____x_610);// L775
extern long long int  (__llabs_614) (long long int  ____x_613);// L779:L780
extern long long int  (__llabs_615) (long long int  ____x_613);// L779:L780
extern __div_t_94  (__div_618) (int  ____numer_616, int  ____denom_617);// L788:L789
extern __div_t_94  (__div_619) (int  ____numer_616, int  ____denom_617);// L788:L789
extern __ldiv_t_99  (__ldiv_622) (long int  ____numer_620, long int  ____denom_621);// L790:L791
extern __ldiv_t_99  (__ldiv_624) (long int  ____numer_620, long int  ____denom_621);// L790:L791
extern __lldiv_t_104  (__lldiv_628) (long long int  ____numer_626, long long int  ____denom_627);// L796:L798
extern __lldiv_t_104  (__lldiv_630) (long long int  ____numer_626, long long int  ____denom_627);// L796:L798
extern char  * ((__ecvt_636) (double  ____value_632, int  ____ndigit_633, int  * __restrict  ____decpt_634, int  * __restrict  ____sign_635));// L811:L812
extern char  * ((__ecvt_637) (double  ____value_632, int  ____ndigit_633, int  * __restrict  ____decpt_634, int  * __restrict  ____sign_635));// L811:L812
extern char  * ((__fcvt_642) (double  ____value_638, int  ____ndigit_639, int  * __restrict  ____decpt_640, int  * __restrict  ____sign_641));// L817:L818
extern char  * ((__fcvt_643) (double  ____value_638, int  ____ndigit_639, int  * __restrict  ____decpt_640, int  * __restrict  ____sign_641));// L817:L818
extern char  * ((__gcvt_647) (double  ____value_644, int  ____ndigit_645, char  * (____buf_646)));// L823:L824
extern char  * ((__gcvt_648) (double  ____value_644, int  ____ndigit_645, char  * (____buf_646)));// L823:L824
extern char  * ((__qecvt_653) (long double  ____value_649, int  ____ndigit_650, int  * __restrict  ____decpt_651, int  * __restrict  ____sign_652));// L829:L831
extern char  * ((__qecvt_654) (long double  ____value_649, int  ____ndigit_650, int  * __restrict  ____decpt_651, int  * __restrict  ____sign_652));// L829:L831
extern char  * ((__qfcvt_659) (long double  ____value_655, int  ____ndigit_656, int  * __restrict  ____decpt_657, int  * __restrict  ____sign_658));// L832:L834
extern char  * ((__qfcvt_660) (long double  ____value_655, int  ____ndigit_656, int  * __restrict  ____decpt_657, int  * __restrict  ____sign_658));// L832:L834
extern char  * ((__qgcvt_664) (long double  ____value_661, int  ____ndigit_662, char  * (____buf_663)));// L835:L836
extern char  * ((__qgcvt_665) (long double  ____value_661, int  ____ndigit_662, char  * (____buf_663)));// L835:L836
extern int  (__ecvt_r_672) (double  ____value_666, int  ____ndigit_667, int  * __restrict  ____decpt_668, int  * __restrict  ____sign_669, char  * __restrict  ____buf_670, __size_t_1  ____len_671);// L841:L843
extern int  (__fcvt_r_679) (double  ____value_673, int  ____ndigit_674, int  * __restrict  ____decpt_675, int  * __restrict  ____sign_676, char  * __restrict  ____buf_677, __size_t_1  ____len_678);// L844:L846
extern int  (__qecvt_r_686) (long double  ____value_680, int  ____ndigit_681, int  * __restrict  ____decpt_682, int  * __restrict  ____sign_683, char  * __restrict  ____buf_684, __size_t_1  ____len_685);// L848:L851
extern int  (__qfcvt_r_693) (long double  ____value_687, int  ____ndigit_688, int  * __restrict  ____decpt_689, int  * __restrict  ____sign_690, char  * __restrict  ____buf_691, __size_t_1  ____len_692);// L852:L855
extern int  (__mblen_696) (const char  * (____s_694), __size_t_1  ____n_695);// L862
extern int  (__mblen_697) (const char  * (____s_694), __size_t_1  ____n_695);// L862
extern int  (__mbtowc_701) (__wchar_t_2  * __restrict  ____pwc_698, const char  * __restrict  ____s_699, __size_t_1  ____n_700);// L865:L866
extern int  (__wctomb_704) (char  * (____s_702), __wchar_t_2  ____wchar_703);// L869
extern __size_t_1  (__mbstowcs_708) (__wchar_t_2  * __restrict  ____pwcs_705, const char  * __restrict  ____s_706, __size_t_1  ____n_707);// L873:L874
extern __size_t_1  (__wcstombs_712) (char  * __restrict  ____s_709, const __wchar_t_2  * __restrict  ____pwcs_710, __size_t_1  ____n_711);// L876:L878
extern int  (__rpmatch_715) (const char  * (____response_713));// L887
extern int  (__rpmatch_714) (const char  * (____response_713));// L887
extern int  (__getsubopt_720) (char  * (* __restrict  ____optionp_716), char  * const  * __restrict  ____tokens_717, char  * (* __restrict  ____valuep_718));// L898:L901
extern int  (__getsubopt_719) (char  * (* __restrict  ____optionp_716), char  * const  * __restrict  ____tokens_717, char  * (* __restrict  ____valuep_718));// L898:L901
extern int  (__getloadavg_723) (double  ____loadavg_721[], int  ____nelem_722);// L950:L951
/* no function due to type errors in the function prototype */
extern char  * ((____realpath_chk_728) (const char  * __restrict  ____name_725, char  * __restrict  ____resolved_726, __size_t_1  ____resolvedlen_727));// L23:L25
extern char  * ((____realpath_alias_731) (const char  * __restrict  ____name_729, char  * __restrict  ____resolved_730));// L26:L28
extern char  * ((____realpath_chk_warn_735) (const char  * __restrict  ____name_732, char  * __restrict  ____resolved_733, __size_t_1  ____resolvedlen_734));// L29:L34
/* no function due to type errors in the function prototype */
extern int  (____ptsname_r_chk_743) (int  ____fd_739, char  * (____buf_740), __size_t_1  ____buflen_741, __size_t_1  ____nreal_742);// L52:L53
extern int  (____ptsname_r_alias_747) (int  ____fd_744, char  * (____buf_745), __size_t_1  ____buflen_746);// L54:L56
extern int  (____ptsname_r_chk_warn_752) (int  ____fd_748, char  * (____buf_749), __size_t_1  ____buflen_750, __size_t_1  ____nreal_751);// L57:L61
/* no function due to type errors in the function prototype */
extern int  (____wctomb_chk_760) (char  * (____s_757), __wchar_t_2  ____wchar_758, __size_t_1  ____buflen_759);// L77:L78
extern int  (____wctomb_alias_763) (char  * (____s_761), __wchar_t_2  ____wchar_762);// L79:L80
/* no function due to type errors in the function prototype */
extern __size_t_1  (____mbstowcs_chk_770) (__wchar_t_2  * __restrict  ____dst_766, const char  * __restrict  ____src_767, __size_t_1  ____len_768, __size_t_1  ____dstlen_769);// L98:L100
extern __size_t_1  (____mbstowcs_alias_774) (__wchar_t_2  * __restrict  ____dst_771, const char  * __restrict  ____src_772, __size_t_1  ____len_773);// L101:L104
extern __size_t_1  (____mbstowcs_chk_warn_779) (__wchar_t_2  * __restrict  ____dst_775, const char  * __restrict  ____src_776, __size_t_1  ____len_777, __size_t_1  ____dstlen_778);// L105:L110
/* no function due to type errors in the function prototype */
extern __size_t_1  (____wcstombs_chk_787) (char  * __restrict  ____dst_783, const __wchar_t_2  * __restrict  ____src_784, __size_t_1  ____len_785, __size_t_1  ____dstlen_786);// L130:L132
extern __size_t_1  (____wcstombs_alias_791) (char  * __restrict  ____dst_788, const __wchar_t_2  * __restrict  ____src_789, __size_t_1  ____len_790);// L133:L136
extern __size_t_1  (____wcstombs_chk_warn_796) (char  * __restrict  ____dst_792, const __wchar_t_2  * __restrict  ____src_793, __size_t_1  ____len_794, __size_t_1  ____dstlen_795);// L137:L141
/* no function due to type errors in the function prototype */
extern void  * ((__memmove_809) (void  * (____dest_806), const void  * (____src_807), __size_t_1  ____n_808));// L46:L47
extern void  * ((__memset_818) (void  * (____s_815), int  ____c_816, __size_t_1  ____n_817));// L62
extern void  * ((__memset_819) (void  * (____s_815), int  ____c_816, __size_t_1  ____n_817));// L62
extern int  (__memcmp_823) (const void  * (____s1_820), const void  * (____s2_821), __size_t_1  ____n_822);// L65:L66
extern void  * ((__memchr_827) (const void  * (____s_824), int  ____c_825, __size_t_1  ____n_826));// L92:L93
extern char  * ((__strcpy_830) (char  * __restrict  ____dest_828, const char  * __restrict  ____src_829));// L125:L126
extern char  * ((__strncpy_834) (char  * __restrict  ____dest_831, const char  * __restrict  ____src_832, __size_t_1  ____n_833));// L128:L130
extern char  * ((__strcat_837) (char  * __restrict  ____dest_835, const char  * __restrict  ____src_836));// L133:L134
extern char  * ((__strncat_841) (char  * __restrict  ____dest_838, const char  * __restrict  ____src_839, __size_t_1  ____n_840));// L136:L137
extern int  (__strcmp_844) (const char  * (____s1_842), const char  * (____s2_843));// L140:L141
extern int  (__strncmp_848) (const char  * (____s1_845), const char  * (____s2_846), __size_t_1  ____n_847);// L143:L144
extern int  (__strcoll_851) (const char  * (____s1_849), const char  * (____s2_850));// L147:L148
extern __size_t_1  (__strxfrm_855) (char  * __restrict  ____dest_852, const char  * __restrict  ____src_853, __size_t_1  ____n_854);// L150:L152
// typedef moved to top of scope
// typedef moved to top of scope
extern int  (__strcoll_l_868) (const char  * (____s1_865), const char  * (____s2_866), ____locale_t_863  ____l_867);// L162:L163
extern __size_t_1  (__strxfrm_l_873) (char  * (____dest_869), const char  * (____src_870), __size_t_1  ____n_871, ____locale_t_863  ____l_872);// L165:L166
extern char  * ((__strdup_875) (const char  * (____s_874)));// L171:L172
extern char  * ((__strndup_878) (const char  * (____string_876), __size_t_1  ____n_877));// L179:L180
extern char  * ((__strchr_881) (const char  * (____s_879), int  ____c_880));// L231:L232
extern char  * ((__strchr_882) (const char  * (____s_879), int  ____c_880));// L231:L232
extern char  * ((__strrchr_885) (const char  * (____s_883), int  ____c_884));// L258:L259
extern __size_t_1  (__strcspn_888) (const char  * (____s_886), const char  * (____reject_887));// L280:L281
extern __size_t_1  (__strspn_891) (const char  * (____s_889), const char  * (____accept_890));// L284:L285
extern char  * ((__strpbrk_894) (const char  * (____s_892), const char  * (____accept_893)));// L310:L311
extern char  * ((__strstr_897) (const char  * (____haystack_895), const char  * (____needle_896)));// L337:L338
extern char  * ((__strtok_900) (char  * __restrict  ____s_898, const char  * __restrict  ____delim_899));// L343:L344
extern char  * ((____strtok_r_904) (char  * __restrict  ____s_901, const char  * __restrict  ____delim_902, char  * (* __restrict  ____save_ptr_903)));// L349:L352
extern char  * ((__strtok_r_908) (char  * __restrict  ____s_905, const char  * __restrict  ____delim_906, char  * (* __restrict  ____save_ptr_907)));// L354:L356
extern __size_t_1  (__strlen_910) (const char  * (____s_909));// L394:L395
extern __size_t_1  (__strlen_911) (const char  * (____s_909));// L394:L395
extern __size_t_1  (__strnlen_914) (const char  * (____string_912), __size_t_1  ____maxlen_913);// L401:L402
extern char  * ((__strerror_916) (int  ____errnum_915));// L408
extern char  * ((__strerror_917) (int  ____errnum_915));// L408
extern int  (__strerror_r_921) (int  ____errnum_918, char  * (____buf_919), __size_t_1  ____buflen_920);// L422:L424
extern char  * ((__strerror_l_924) (int  ____errnum_922, ____locale_t_863  ____l_923));// L440
extern void  (____bzero_927) (void  * (____s_925), __size_t_1  ____n_926);// L446
extern void  (____bzero_928) (void  * (____s_925), __size_t_1  ____n_926);// L446
extern void  (__bcopy_932) (const void  * (____src_929), void  * (____dest_930), __size_t_1  ____n_931);// L450:L451
extern void  (__bzero_935) (void  * (____s_933), __size_t_1  ____n_934);// L454
extern int  (__bcmp_939) (const void  * (____s1_936), const void  * (____s2_937), __size_t_1  ____n_938);// L457:L458
extern char  * ((__index_942) (const char  * (____s_940), int  ____c_941));// L484:L485
extern char  * ((__rindex_945) (const char  * (____s_943), int  ____c_944));// L512:L513
extern int  (__ffs_947) (int  ____i_946);// L518
extern int  (__strcasecmp_950) (const char  * (____s1_948), const char  * (____s2_949));// L529:L530
extern int  (__strncasecmp_954) (const char  * (____s1_951), const char  * (____s2_952), __size_t_1  ____n_953);// L533:L534
extern char  * ((__strsep_957) (char  * (* __restrict  ____stringp_955), const char  * __restrict  ____delim_956));// L552:L554
extern char  * ((__strsignal_959) (int  ____sig_958));// L559
extern char  * ((____stpcpy_962) (char  * __restrict  ____dest_960, const char  * __restrict  ____src_961));// L562:L563
extern char  * ((__stpcpy_965) (char  * __restrict  ____dest_963, const char  * __restrict  ____src_964));// L564:L565
extern char  * ((____stpncpy_969) (char  * __restrict  ____dest_966, const char  * __restrict  ____src_967, __size_t_1  ____n_968));// L569:L571
extern char  * ((__stpncpy_973) (char  * __restrict  ____dest_970, const char  * __restrict  ____src_971, __size_t_1  ____n_972));// L572:L574
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
extern char  * ((____stpncpy_chk_1002) (char  * (____dest_998), const char  * (____src_999), __size_t_1  ____n_1000, __size_t_1  ____destlen_1001));// L130:L131
extern char  * ((____stpncpy_alias_1006) (char  * (____dest_1003), const char  * (____src_1004), __size_t_1  ____n_1005));// L132:L133
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
void  (__ssl_init_ModuleKill_1023) () {

if (__static_condition_default_1025) {

{
{



char  * (__sc_1018)= malloc (sizeof(char) * 45);// L6

char  * (__sc_1019)= malloc (sizeof(char) * 45);// L6

if (__static_condition_default_1026) {
 __strcpy_830  ( __sc_1018 ,"something") ; // L9
}
if (__static_condition_default_1027) {
 __strcpy_830  ( __sc_1019 ,"something") ; // L9
}
if (__static_condition_default_1028) {
free ( __sc_1018 ) ; // L12
}
if (__static_condition_default_1029) {
__static_type_error("type error") ; // L12
}
if (__static_condition_default_1030) {
return  ;// L16
}
if (__static_condition_default_1031) {
return  ;// L16
}
}
}


}
}
void  (__ssl_init_ModuleKill_1024) () {

if (__static_condition_default_1032) {

{
{



char  * (__sc_1020)= malloc (sizeof(char) * 45);// L6

char  * (__sc_1021)= malloc (sizeof(char) * 45);// L6

__static_type_error("type error") ; // L9
if (__static_condition_default_1033) {
free ( __sc_1020 ) ; // L12
}
if (__static_condition_default_1034) {
__static_type_error("type error") ; // L12
}
if (__static_condition_default_1035) {
return  ;// L16
}
if (__static_condition_default_1036) {
return  ;// L16
}
}
}


}
}
int  (__main_1037) (void  ) {

{
{



if (__static_condition_default_1025) {
 __ssl_init_ModuleKill_1023 ( ) ; // L21
}
if (__static_condition_default_1032) {
 __ssl_init_ModuleKill_1024 ( ) ; // L21
}
return 0 ;// L22
}
}


}

