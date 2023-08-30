#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_582;
extern const bool __static_condition_default_596;
extern const bool __static_condition_default_622;
extern const bool __static_condition_default_61;
extern const bool __static_condition_default_271;
extern const bool __static_condition_default_289;
extern const bool __static_condition_default_415;
extern const bool __static_condition_default_326;
extern const bool __static_condition_default_283;
extern const bool __static_condition_default_380;
extern const bool __static_condition_default_68;
extern const bool __static_condition_default_247;
extern const bool __static_condition_default_342;
extern const bool __static_condition_default_809;
extern const bool __static_condition_default_294;
extern const bool __static_condition_default_303;
extern const bool __static_condition_default_253;
extern const bool __static_condition_default_256;
extern const bool __static_condition_default_238;
extern const bool __static_condition_default_737;
extern const bool __static_condition_default_808;
extern const bool __static_condition_default_265;
extern const bool __static_condition_default_580;
extern const bool __static_condition_default_306;
extern const bool __static_condition_default_816;
extern const bool __static_condition_default_395;
extern const bool __static_condition_default_628;
extern const bool __static_condition_default_421;
extern const bool __static_condition_default_424;
extern const bool __static_condition_default_815;
extern const bool __static_condition_default_241;
extern const bool __static_condition_default_418;
extern const bool __static_condition_default_216;
extern const bool __static_condition_default_250;
extern const bool __static_condition_default_630;
extern const bool __static_condition_default_810;
extern const bool __static_condition_default_300;
extern const bool __static_condition_default_268;
extern const bool __static_condition_default_286;
extern const bool __static_condition_default_379;
extern const bool __static_condition_default_244;
extern const bool __static_condition_default_297;
extern const bool __static_condition_default_430;
extern const bool __static_condition_default_309;
extern const bool __static_condition_default_817;
extern const bool __static_condition_default_350;
extern const bool __static_condition_default_259;
extern const bool __static_condition_default_277;
extern const bool __static_condition_default_396;
extern const bool __static_condition_default_624;
extern const bool __static_condition_default_280;
extern const bool __static_condition_default_235;
extern const bool __static_condition_default_427;
extern const bool __static_condition_default_595;
extern const bool __static_condition_default_605;
extern const bool __static_condition_default_353;
extern const bool __static_condition_default_803;
extern const bool __static_condition_default_603;
extern const bool __static_condition_default_362;
extern const bool __static_condition_default_274;
extern const bool __static_condition_default_433;
extern const bool __static_condition_default_262;
void __static_initializer_default() {
__static_renaming("____errno_location_0", "__errno_location");
__static_renaming("__ptrdiff_t_1", "ptrdiff_t");
__static_renaming("__size_t_2", "size_t");
__static_renaming("__wchar_t_3", "wchar_t");
__static_renaming("__idtype_t_9", "idtype_t");
__static_renaming("____u_char_10", "__u_char");
__static_renaming("____u_short_11", "__u_short");
__static_renaming("____u_int_12", "__u_int");
__static_renaming("____u_long_13", "__u_long");
__static_renaming("____int8_t_14", "__int8_t");
__static_renaming("____uint8_t_15", "__uint8_t");
__static_renaming("____int16_t_16", "__int16_t");
__static_renaming("____uint16_t_17", "__uint16_t");
__static_renaming("____int32_t_18", "__int32_t");
__static_renaming("____uint32_t_19", "__uint32_t");
__static_renaming("____int64_t_20", "__int64_t");
__static_renaming("____uint64_t_21", "__uint64_t");
__static_renaming("____quad_t_22", "__quad_t");
__static_renaming("____u_quad_t_23", "__u_quad_t");
__static_renaming("____dev_t_24", "__dev_t");
__static_renaming("____uid_t_25", "__uid_t");
__static_renaming("____gid_t_26", "__gid_t");
__static_renaming("____ino_t_27", "__ino_t");
__static_renaming("____ino64_t_28", "__ino64_t");
__static_renaming("____mode_t_29", "__mode_t");
__static_renaming("____nlink_t_30", "__nlink_t");
__static_renaming("____off_t_31", "__off_t");
__static_renaming("____off64_t_32", "__off64_t");
__static_renaming("____pid_t_33", "__pid_t");
__static_renaming("____fsid_t_37", "__fsid_t");
__static_renaming("____clock_t_38", "__clock_t");
__static_renaming("____rlim_t_39", "__rlim_t");
__static_renaming("____rlim64_t_40", "__rlim64_t");
__static_renaming("____id_t_41", "__id_t");
__static_renaming("____time_t_42", "__time_t");
__static_renaming("____useconds_t_43", "__useconds_t");
__static_renaming("____suseconds_t_44", "__suseconds_t");
__static_renaming("____daddr_t_45", "__daddr_t");
__static_renaming("____key_t_46", "__key_t");
__static_renaming("____clockid_t_47", "__clockid_t");
__static_renaming("____timer_t_48", "__timer_t");
__static_renaming("____blksize_t_49", "__blksize_t");
__static_renaming("____blkcnt_t_50", "__blkcnt_t");
__static_renaming("____blkcnt64_t_51", "__blkcnt64_t");
__static_renaming("____fsblkcnt_t_52", "__fsblkcnt_t");
__static_renaming("____fsblkcnt64_t_53", "__fsblkcnt64_t");
__static_renaming("____fsfilcnt_t_54", "__fsfilcnt_t");
__static_renaming("____fsfilcnt64_t_55", "__fsfilcnt64_t");
__static_renaming("____fsword_t_56", "__fsword_t");
__static_renaming("____ssize_t_57", "__ssize_t");
__static_renaming("____syscall_slong_t_58", "__syscall_slong_t");
__static_renaming("____syscall_ulong_t_59", "__syscall_ulong_t");
__static_renaming("____loff_t_60", "__loff_t");
__static_renaming("____qaddr_t_62", "__qaddr_t");
__static_renaming("____caddr_t_63", "__caddr_t");
__static_renaming("____intptr_t_64", "__intptr_t");
__static_renaming("____socklen_t_65", "__socklen_t");
__static_renaming("____bswap_32_67", "__bswap_32");
__static_renaming("____bswap_64_70", "__bswap_64");
__static_renaming("____WAIT_STATUS_90", "__WAIT_STATUS");
__static_renaming("__div_t_95", "div_t");
__static_renaming("__ldiv_t_100", "ldiv_t");
__static_renaming("__lldiv_t_105", "lldiv_t");
__static_renaming("____ctype_get_mb_cur_max_106", "__ctype_get_mb_cur_max");
__static_renaming("____ctype_get_mb_cur_max_107", "__ctype_get_mb_cur_max");
__static_renaming("____ctype_get_mb_cur_max_108", "__ctype_get_mb_cur_max");
__static_renaming("____ctype_get_mb_cur_max_109", "__ctype_get_mb_cur_max");
__static_renaming("__atof_111", "atof");
__static_renaming("__atof_112", "atof");
__static_renaming("__atoi_114", "atoi");
__static_renaming("__atoi_115", "atoi");
__static_renaming("__atol_117", "atol");
__static_renaming("__atol_118", "atol");
__static_renaming("__atoll_120", "atoll");
__static_renaming("__atoll_121", "atoll");
__static_renaming("__strtod_124", "strtod");
__static_renaming("__strtof_127", "strtof");
__static_renaming("__strtold_130", "strtold");
__static_renaming("__strtol_134", "strtol");
__static_renaming("__strtoul_138", "strtoul");
__static_renaming("__strtoq_142", "strtoq");
__static_renaming("__strtouq_146", "strtouq");
__static_renaming("__strtoll_150", "strtoll");
__static_renaming("__strtoll_151", "strtoll");
__static_renaming("__strtoull_155", "strtoull");
__static_renaming("__l64a_160", "l64a");
__static_renaming("__l64a_161", "l64a");
__static_renaming("__a64l_163", "a64l");
__static_renaming("__a64l_164", "a64l");
__static_renaming("____u_char_165", "__u_char");
__static_renaming("____u_short_166", "__u_short");
__static_renaming("____u_int_167", "__u_int");
__static_renaming("____u_long_168", "__u_long");
__static_renaming("____int8_t_169", "__int8_t");
__static_renaming("____uint8_t_170", "__uint8_t");
__static_renaming("____int16_t_171", "__int16_t");
__static_renaming("____uint16_t_172", "__uint16_t");
__static_renaming("____int32_t_173", "__int32_t");
__static_renaming("____uint32_t_174", "__uint32_t");
__static_renaming("____int64_t_175", "__int64_t");
__static_renaming("____uint64_t_176", "__uint64_t");
__static_renaming("____quad_t_177", "__quad_t");
__static_renaming("____u_quad_t_178", "__u_quad_t");
__static_renaming("____dev_t_179", "__dev_t");
__static_renaming("____uid_t_180", "__uid_t");
__static_renaming("____gid_t_181", "__gid_t");
__static_renaming("____ino_t_182", "__ino_t");
__static_renaming("____ino64_t_183", "__ino64_t");
__static_renaming("____mode_t_184", "__mode_t");
__static_renaming("____nlink_t_185", "__nlink_t");
__static_renaming("____off_t_186", "__off_t");
__static_renaming("____off64_t_187", "__off64_t");
__static_renaming("____pid_t_188", "__pid_t");
__static_renaming("____fsid_t_192", "__fsid_t");
__static_renaming("____clock_t_193", "__clock_t");
__static_renaming("____rlim_t_194", "__rlim_t");
__static_renaming("____rlim64_t_195", "__rlim64_t");
__static_renaming("____id_t_196", "__id_t");
__static_renaming("____time_t_197", "__time_t");
__static_renaming("____useconds_t_198", "__useconds_t");
__static_renaming("____suseconds_t_199", "__suseconds_t");
__static_renaming("____daddr_t_200", "__daddr_t");
__static_renaming("____key_t_201", "__key_t");
__static_renaming("____clockid_t_202", "__clockid_t");
__static_renaming("____timer_t_203", "__timer_t");
__static_renaming("____blksize_t_204", "__blksize_t");
__static_renaming("____blkcnt_t_205", "__blkcnt_t");
__static_renaming("____blkcnt64_t_206", "__blkcnt64_t");
__static_renaming("____fsblkcnt_t_207", "__fsblkcnt_t");
__static_renaming("____fsblkcnt64_t_208", "__fsblkcnt64_t");
__static_renaming("____fsfilcnt_t_209", "__fsfilcnt_t");
__static_renaming("____fsfilcnt64_t_210", "__fsfilcnt64_t");
__static_renaming("____fsword_t_211", "__fsword_t");
__static_renaming("____ssize_t_212", "__ssize_t");
__static_renaming("____syscall_slong_t_213", "__syscall_slong_t");
__static_renaming("____syscall_ulong_t_214", "__syscall_ulong_t");
__static_renaming("____loff_t_215", "__loff_t");
__static_renaming("____qaddr_t_217", "__qaddr_t");
__static_renaming("____caddr_t_218", "__caddr_t");
__static_renaming("____intptr_t_219", "__intptr_t");
__static_renaming("____socklen_t_220", "__socklen_t");
__static_renaming("__u_char_221", "u_char");
__static_renaming("__u_char_222", "u_char");
__static_renaming("__u_short_223", "u_short");
__static_renaming("__u_short_224", "u_short");
__static_renaming("__u_int_225", "u_int");
__static_renaming("__u_int_226", "u_int");
__static_renaming("__u_long_227", "u_long");
__static_renaming("__u_long_228", "u_long");
__static_renaming("__quad_t_229", "quad_t");
__static_renaming("__quad_t_230", "quad_t");
__static_renaming("__u_quad_t_231", "u_quad_t");
__static_renaming("__u_quad_t_232", "u_quad_t");
__static_renaming("__fsid_t_233", "fsid_t");
__static_renaming("__fsid_t_234", "fsid_t");
__static_renaming("__loff_t_236", "loff_t");
__static_renaming("__loff_t_237", "loff_t");
__static_renaming("__loff_t_239", "loff_t");
__static_renaming("__loff_t_240", "loff_t");
__static_renaming("__ino_t_242", "ino_t");
__static_renaming("__ino_t_243", "ino_t");
__static_renaming("__ino_t_245", "ino_t");
__static_renaming("__ino_t_246", "ino_t");
__static_renaming("__dev_t_248", "dev_t");
__static_renaming("__dev_t_249", "dev_t");
__static_renaming("__gid_t_251", "gid_t");
__static_renaming("__gid_t_252", "gid_t");
__static_renaming("__gid_t_254", "gid_t");
__static_renaming("__gid_t_255", "gid_t");
__static_renaming("__mode_t_257", "mode_t");
__static_renaming("__mode_t_258", "mode_t");
__static_renaming("__nlink_t_260", "nlink_t");
__static_renaming("__nlink_t_261", "nlink_t");
__static_renaming("__uid_t_263", "uid_t");
__static_renaming("__uid_t_264", "uid_t");
__static_renaming("__uid_t_266", "uid_t");
__static_renaming("__uid_t_267", "uid_t");
__static_renaming("__off_t_269", "off_t");
__static_renaming("__off_t_270", "off_t");
__static_renaming("__off_t_272", "off_t");
__static_renaming("__off_t_273", "off_t");
__static_renaming("__pid_t_275", "pid_t");
__static_renaming("__pid_t_276", "pid_t");
__static_renaming("__pid_t_278", "pid_t");
__static_renaming("__pid_t_279", "pid_t");
__static_renaming("__id_t_281", "id_t");
__static_renaming("__id_t_282", "id_t");
__static_renaming("__ssize_t_284", "ssize_t");
__static_renaming("__ssize_t_285", "ssize_t");
__static_renaming("__daddr_t_287", "daddr_t");
__static_renaming("__daddr_t_288", "daddr_t");
__static_renaming("__caddr_t_290", "caddr_t");
__static_renaming("__caddr_t_291", "caddr_t");
__static_renaming("__key_t_292", "key_t");
__static_renaming("__key_t_293", "key_t");
__static_renaming("__key_t_295", "key_t");
__static_renaming("__key_t_296", "key_t");
__static_renaming("__clock_t_298", "clock_t");
__static_renaming("__clock_t_299", "clock_t");
__static_renaming("__time_t_301", "time_t");
__static_renaming("__time_t_302", "time_t");
__static_renaming("__clockid_t_304", "clockid_t");
__static_renaming("__clockid_t_305", "clockid_t");
__static_renaming("__timer_t_307", "timer_t");
__static_renaming("__timer_t_308", "timer_t");
__static_renaming("__ulong_310", "ulong");
__static_renaming("__ulong_311", "ulong");
__static_renaming("__ulong_312", "ulong");
__static_renaming("__ushort_313", "ushort");
__static_renaming("__uint_314", "uint");
__static_renaming("__int8_t_315", "int8_t");
__static_renaming("__int16_t_316", "int16_t");
__static_renaming("__int32_t_317", "int32_t");
__static_renaming("__int64_t_318", "int64_t");
__static_renaming("__u_int8_t_319", "u_int8_t");
__static_renaming("__u_int16_t_320", "u_int16_t");
__static_renaming("__u_int32_t_321", "u_int32_t");
__static_renaming("__u_int64_t_322", "u_int64_t");
__static_renaming("__register_t_323", "register_t");
__static_renaming("____bswap_32_325", "__bswap_32");
__static_renaming("____bswap_64_328", "__bswap_64");
__static_renaming("____sig_atomic_t_329", "__sig_atomic_t");
__static_renaming("____sigset_t_333", "__sigset_t");
__static_renaming("__sigset_t_334", "sigset_t");
__static_renaming("__suseconds_t_351", "suseconds_t");
__static_renaming("__suseconds_t_352", "suseconds_t");
__static_renaming("____fd_mask_354", "__fd_mask");
__static_renaming("____fd_mask_355", "__fd_mask");
__static_renaming("__fd_set_363", "fd_set");
__static_renaming("__fd_mask_364", "fd_mask");
__static_renaming("__fd_mask_365", "fd_mask");
__static_renaming("__select_377", "select");
__static_renaming("__select_378", "select");
__static_renaming("__pselect_393", "pselect");
__static_renaming("__pselect_394", "pselect");
__static_renaming("____fdelt_chk_398", "__fdelt_chk");
__static_renaming("____fdelt_warn_400", "__fdelt_warn");
__static_renaming("__gnu_dev_major_402", "gnu_dev_major");
__static_renaming("__gnu_dev_major_403", "gnu_dev_major");
__static_renaming("__gnu_dev_minor_405", "gnu_dev_minor");
__static_renaming("__gnu_dev_makedev_408", "gnu_dev_makedev");
__static_renaming("__blksize_t_413", "blksize_t");
__static_renaming("__blksize_t_414", "blksize_t");
__static_renaming("__blkcnt_t_416", "blkcnt_t");
__static_renaming("__blkcnt_t_417", "blkcnt_t");
__static_renaming("__fsblkcnt_t_419", "fsblkcnt_t");
__static_renaming("__fsblkcnt_t_420", "fsblkcnt_t");
__static_renaming("__blkcnt_t_422", "blkcnt_t");
__static_renaming("__blkcnt_t_423", "blkcnt_t");
__static_renaming("__fsblkcnt_t_425", "fsblkcnt_t");
__static_renaming("__fsblkcnt_t_426", "fsblkcnt_t");
__static_renaming("__fsfilcnt_t_428", "fsfilcnt_t");
__static_renaming("__fsfilcnt_t_429", "fsfilcnt_t");
__static_renaming("__fsfilcnt_t_431", "fsfilcnt_t");
__static_renaming("__fsfilcnt_t_432", "fsfilcnt_t");
__static_renaming("__pthread_t_434", "pthread_t");
__static_renaming("__pthread_attr_t_438", "pthread_attr_t");
__static_renaming("____pthread_list_t_443", "__pthread_list_t");
__static_renaming("____pthread_list_t_444", "__pthread_list_t");
__static_renaming("__pthread_mutex_t_460", "pthread_mutex_t");
__static_renaming("__pthread_mutexattr_t_465", "pthread_mutexattr_t");
__static_renaming("__rand_466", "rand");
__static_renaming("__srand_468", "srand");
__static_renaming("__rand_r_470", "rand_r");
__static_renaming("__drand48_471", "drand48");
__static_renaming("__erand48_473", "erand48");
__static_renaming("__lrand48_474", "lrand48");
__static_renaming("__nrand48_476", "nrand48");
__static_renaming("__mrand48_477", "mrand48");
__static_renaming("__jrand48_479", "jrand48");
__static_renaming("__srand48_481", "srand48");
__static_renaming("__seed48_483", "seed48");
__static_renaming("__lcong48_485", "lcong48");
__static_renaming("__malloc_487", "malloc");
__static_renaming("__malloc_488", "malloc");
__static_renaming("__calloc_491", "calloc");
__static_renaming("__calloc_492", "calloc");
__static_renaming("__realloc_495", "realloc");
__static_renaming("__free_497", "free");
__static_renaming("__cfree_499", "cfree");
__static_renaming("__alloca_501", "alloca");
__static_renaming("__valloc_503", "valloc");
__static_renaming("__valloc_504", "valloc");
__static_renaming("__posix_memalign_508", "posix_memalign");
__static_renaming("__posix_memalign_509", "posix_memalign");
__static_renaming("__aligned_alloc_512", "aligned_alloc");
__static_renaming("__aligned_alloc_513", "aligned_alloc");
__static_renaming("__aligned_alloc_514", "aligned_alloc");
__static_renaming("__aligned_alloc_515", "aligned_alloc");
__static_renaming("__abort_516", "abort");
__static_renaming("__atexit_518", "atexit");
__static_renaming("__at_quick_exit_520", "at_quick_exit");
__static_renaming("__on_exit_525", "on_exit");
__static_renaming("__exit_527", "exit");
__static_renaming("__exit_528", "exit");
__static_renaming("__quick_exit_530", "quick_exit");
__static_renaming("___Exit_532", "_Exit");
__static_renaming("__getenv_534", "getenv");
__static_renaming("__getenv_535", "getenv");
__static_renaming("__putenv_537", "putenv");
__static_renaming("__setenv_541", "setenv");
__static_renaming("__unsetenv_543", "unsetenv");
__static_renaming("__clearenv_544", "clearenv");
__static_renaming("__mktemp_546", "mktemp");
__static_renaming("__mkstemp_549", "mkstemp");
__static_renaming("__mkstemp_550", "mkstemp");
__static_renaming("__mkstemp_551", "mkstemp");
__static_renaming("__mkstemp_552", "mkstemp");
__static_renaming("__mkstemps_557", "mkstemps");
__static_renaming("__mkstemps_558", "mkstemps");
__static_renaming("__mkstemps_559", "mkstemps");
__static_renaming("__mkstemps_560", "mkstemps");
__static_renaming("__mkdtemp_562", "mkdtemp");
__static_renaming("__mkdtemp_563", "mkdtemp");
__static_renaming("__system_565", "system");
__static_renaming("__system_566", "system");
__static_renaming("__system_567", "system");
__static_renaming("__system_568", "system");
__static_renaming("__realpath_571", "realpath");
__static_renaming("__realpath_572", "realpath");
__static_renaming("____compar_fn_t_573", "__compar_fn_t");
__static_renaming("__bsearch_581", "bsearch");
__static_renaming("__bsearch_583", "bsearch");
__static_renaming("____l_590", "__l");
__static_renaming("____u_591", "__u");
__static_renaming("____idx_592", "__idx");
__static_renaming("____p_593", "__p");
__static_renaming("____comparison_594", "__comparison");
__static_renaming("__qsort_602", "qsort");
__static_renaming("__qsort_604", "qsort");
__static_renaming("__abs_607", "abs");
__static_renaming("__abs_608", "abs");
__static_renaming("__labs_610", "labs");
__static_renaming("__labs_611", "labs");
__static_renaming("__llabs_613", "llabs");
__static_renaming("__llabs_614", "llabs");
__static_renaming("__div_617", "div");
__static_renaming("__div_618", "div");
__static_renaming("__ldiv_621", "ldiv");
__static_renaming("__ldiv_623", "ldiv");
__static_renaming("__lldiv_627", "lldiv");
__static_renaming("__lldiv_629", "lldiv");
__static_renaming("__ecvt_635", "ecvt");
__static_renaming("__ecvt_636", "ecvt");
__static_renaming("__fcvt_641", "fcvt");
__static_renaming("__fcvt_642", "fcvt");
__static_renaming("__gcvt_646", "gcvt");
__static_renaming("__gcvt_647", "gcvt");
__static_renaming("__qecvt_652", "qecvt");
__static_renaming("__qecvt_653", "qecvt");
__static_renaming("__qfcvt_658", "qfcvt");
__static_renaming("__qfcvt_659", "qfcvt");
__static_renaming("__qgcvt_663", "qgcvt");
__static_renaming("__qgcvt_664", "qgcvt");
__static_renaming("__ecvt_r_671", "ecvt_r");
__static_renaming("__fcvt_r_678", "fcvt_r");
__static_renaming("__qecvt_r_685", "qecvt_r");
__static_renaming("__qfcvt_r_692", "qfcvt_r");
__static_renaming("__mblen_695", "mblen");
__static_renaming("__mblen_696", "mblen");
__static_renaming("__mbtowc_700", "mbtowc");
__static_renaming("__wctomb_703", "wctomb");
__static_renaming("__mbstowcs_707", "mbstowcs");
__static_renaming("__wcstombs_711", "wcstombs");
__static_renaming("__rpmatch_713", "rpmatch");
__static_renaming("__rpmatch_714", "rpmatch");
__static_renaming("__getsubopt_718", "getsubopt");
__static_renaming("__getsubopt_719", "getsubopt");
__static_renaming("__getloadavg_722", "getloadavg");
__static_renaming("____realpath_chk_727", "__realpath_chk");
__static_renaming("____realpath_alias_730", "__realpath_alias");
__static_renaming("____realpath_chk_warn_734", "__realpath_chk_warn");
__static_renaming("____ptsname_r_chk_742", "__ptsname_r_chk");
__static_renaming("____ptsname_r_alias_746", "__ptsname_r_alias");
__static_renaming("____ptsname_r_chk_warn_751", "__ptsname_r_chk_warn");
__static_renaming("____wctomb_chk_759", "__wctomb_chk");
__static_renaming("____wctomb_alias_762", "__wctomb_alias");
__static_renaming("____mbstowcs_chk_769", "__mbstowcs_chk");
__static_renaming("____mbstowcs_alias_773", "__mbstowcs_alias");
__static_renaming("____mbstowcs_chk_warn_778", "__mbstowcs_chk_warn");
__static_renaming("____wcstombs_chk_786", "__wcstombs_chk");
__static_renaming("____wcstombs_alias_790", "__wcstombs_alias");
__static_renaming("____wcstombs_chk_warn_795", "__wcstombs_chk_warn");
__static_renaming("__pm_buffer_799", "pm_buffer");
__static_renaming("__pm_pos_800", "pm_pos");
__static_renaming("__pm_len_801", "pm_len");
__static_renaming("__add_to_pagemap_802", "add_to_pagemap");
__static_renaming("__err_804", "err");
__static_renaming("__pagemap_pte_range_805", "pagemap_pte_range");
__static_renaming("__walk_page_range_806", "walk_page_range");
__static_renaming("__pagemap_read_807", "pagemap_read");
__static_renaming("__main_813", "main");
__static_renaming("__main_814", "main");

__static_condition_renaming("__static_condition_default_61", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && !(defined _SYS_WAIT_H) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_68", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && !(defined _SYS_WAIT_H)");
__static_condition_renaming("__static_condition_default_216", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _SYS_WAIT_H) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_235", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __u_char_defined)");
__static_condition_renaming("__static_condition_default_238", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined __u_char_defined)");
__static_condition_renaming("__static_condition_default_241", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __u_char_defined)");
__static_condition_renaming("__static_condition_default_244", "!(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && (_FILE_OFFSET_BITS == 64) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __ino_t_defined)");
__static_condition_renaming("__static_condition_default_247", "!(defined __STRICT_ANSI__) && !(defined _FILE_OFFSET_BITS) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __ino_t_defined) || !(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && !(_FILE_OFFSET_BITS == 64) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __ino_t_defined)");
__static_condition_renaming("__static_condition_default_250", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __dev_t_defined)");
__static_condition_renaming("__static_condition_default_253", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined __dev_t_defined)");
__static_condition_renaming("__static_condition_default_256", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __dev_t_defined)");
__static_condition_renaming("__static_condition_default_259", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_262", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __nlink_t_defined)");
__static_condition_renaming("__static_condition_default_265", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined __nlink_t_defined)");
__static_condition_renaming("__static_condition_default_268", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __nlink_t_defined)");
__static_condition_renaming("__static_condition_default_271", "!(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && (_FILE_OFFSET_BITS == 64) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __off_t_defined)");
__static_condition_renaming("__static_condition_default_274", "!(defined __STRICT_ANSI__) && !(defined _FILE_OFFSET_BITS) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __off_t_defined) || !(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && !(_FILE_OFFSET_BITS == 64) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __off_t_defined)");
__static_condition_renaming("__static_condition_default_277", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined __off_t_defined)");
__static_condition_renaming("__static_condition_default_280", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __off_t_defined)");
__static_condition_renaming("__static_condition_default_283", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __id_t_defined)");
__static_condition_renaming("__static_condition_default_286", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __ssize_t_defined)");
__static_condition_renaming("__static_condition_default_289", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __daddr_t_defined)");
__static_condition_renaming("__static_condition_default_294", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined __daddr_t_defined)");
__static_condition_renaming("__static_condition_default_297", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __daddr_t_defined)");
__static_condition_renaming("__static_condition_default_300", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __clock_t_defined)");
__static_condition_renaming("__static_condition_default_303", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __time_t_defined)");
__static_condition_renaming("__static_condition_default_306", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __clockid_t_defined)");
__static_condition_renaming("__static_condition_default_309", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __timer_t_defined)");
__static_condition_renaming("__static_condition_default_326", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _SYS_WAIT_H)");
__static_condition_renaming("__static_condition_default_342", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __timespec_defined)");
__static_condition_renaming("__static_condition_default_350", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined _STRUCT_TIMEVAL)");
__static_condition_renaming("__static_condition_default_353", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __suseconds_t_defined)");
__static_condition_renaming("__static_condition_default_362", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_379", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined _STRUCT_TIMEVAL)");
__static_condition_renaming("__static_condition_default_380", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined _STRUCT_TIMEVAL)");
__static_condition_renaming("__static_condition_default_395", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __timespec_defined)");
__static_condition_renaming("__static_condition_default_396", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined __timespec_defined)");
__static_condition_renaming("__static_condition_default_415", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __blksize_t_defined)");
__static_condition_renaming("__static_condition_default_418", "!(defined __STRICT_ANSI__) && !(defined _FILE_OFFSET_BITS) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __blkcnt_t_defined) || !(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && !(_FILE_OFFSET_BITS == 64) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __blkcnt_t_defined)");
__static_condition_renaming("__static_condition_default_421", "!(defined __STRICT_ANSI__) && !(defined _FILE_OFFSET_BITS) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) || !(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && !(_FILE_OFFSET_BITS == 64) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_424", "!(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && (_FILE_OFFSET_BITS == 64) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __blkcnt_t_defined)");
__static_condition_renaming("__static_condition_default_427", "!(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && (_FILE_OFFSET_BITS == 64) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_430", "!(defined __STRICT_ANSI__) && !(defined _FILE_OFFSET_BITS) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) || !(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && !(_FILE_OFFSET_BITS == 64) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_433", "!(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && (_FILE_OFFSET_BITS == 64) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_580", "!(defined _FORTIFY_SOURCE) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __COMPAR_FN_T) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __COMPAR_FN_T) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __COMPAR_FN_T) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_582", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_595", "!(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __USE_EXTERN_INLINES) && !(defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_596", "!(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __USE_EXTERN_INLINES) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_603", "!(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && !(defined __USE_EXTERN_INLINES) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_605", "!(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __USE_EXTERN_INLINES) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_622", "!(defined _FORTIFY_SOURCE) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __ldiv_t_defined) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __ldiv_t_defined) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __ldiv_t_defined) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __ldiv_t_defined)");
__static_condition_renaming("__static_condition_default_624", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __ldiv_t_defined)");
__static_condition_renaming("__static_condition_default_628", "!(defined _FORTIFY_SOURCE) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __lldiv_t_defined) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __lldiv_t_defined) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __lldiv_t_defined) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __lldiv_t_defined)");
__static_condition_renaming("__static_condition_default_630", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __lldiv_t_defined)");
__static_condition_renaming("__static_condition_default_737", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc)");
__static_condition_renaming("__static_condition_default_803", "(defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_808", "!(defined __STRICT_ANSI__) && !(defined _FORTIFY_SOURCE) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined CONFIG_PROC_PAGE_MONITOR) || !(defined __STRICT_ANSI__) && !(defined _FORTIFY_SOURCE) && !(defined _STDLIB_H) && (defined __need_malloc_and_calloc) && !(defined __malloc_and_calloc_defined) && (defined CONFIG_PROC_PAGE_MONITOR) || !(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined CONFIG_PROC_PAGE_MONITOR) || !(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined _STDLIB_H) && (defined __need_malloc_and_calloc) && !(defined __malloc_and_calloc_defined) && (defined CONFIG_PROC_PAGE_MONITOR) || !(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined CONFIG_PROC_PAGE_MONITOR) || !(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined _STDLIB_H) && (defined __need_malloc_and_calloc) && !(defined __malloc_and_calloc_defined) && (defined CONFIG_PROC_PAGE_MONITOR) || !(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined CONFIG_PROC_PAGE_MONITOR) || !(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined _STDLIB_H) && (defined __need_malloc_and_calloc) && !(defined __malloc_and_calloc_defined) && (defined CONFIG_PROC_PAGE_MONITOR) || (defined __STRICT_ANSI__) && !(defined _FORTIFY_SOURCE) && !(defined _STDLIB_H) && !(defined __malloc_and_calloc_defined) && (defined CONFIG_PROC_PAGE_MONITOR) || (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined _STDLIB_H) && !(defined __malloc_and_calloc_defined) && (defined CONFIG_PROC_PAGE_MONITOR) || (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined _STDLIB_H) && !(defined __malloc_and_calloc_defined) && (defined CONFIG_PROC_PAGE_MONITOR) || (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined _STDLIB_H) && !(defined __malloc_and_calloc_defined) && (defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_809", "!(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined CONFIG_PROC_PAGE_MONITOR) || !(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined _STDLIB_H) && (defined __need_malloc_and_calloc) && !(defined __malloc_and_calloc_defined) && (defined CONFIG_PROC_PAGE_MONITOR) || (defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined _STDLIB_H) && !(defined __malloc_and_calloc_defined) && (defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_810", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && (defined __need_malloc_and_calloc) && (defined __malloc_and_calloc_defined) && (defined CONFIG_PROC_PAGE_MONITOR) || !(defined __STRICT_ANSI__) && (defined _STDLIB_H) && (defined CONFIG_PROC_PAGE_MONITOR) || (defined __STRICT_ANSI__) && !(defined _STDLIB_H) && (defined __malloc_and_calloc_defined) && (defined CONFIG_PROC_PAGE_MONITOR) || (defined __STRICT_ANSI__) && (defined _STDLIB_H) && (defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_815", "!(defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_816", "(defined CONFIG_PROC_PAGE_MONITOR)");
__static_condition_renaming("__static_condition_default_817", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc)");

if (__static_condition_default_817) {
__static_parse_error("Unable to parse");
}
};
typedef long int  __ptrdiff_t_1;// L143:L324
typedef long unsigned int  __size_t_2;// L177:L209
typedef int  __wchar_t_3;// L243:L321
enum ____anonymous_tag_7_8 {
__P_ALL_4,
__P_PID_5,
__P_PGID_6,
};
typedef enum ____anonymous_tag_7_8  __idtype_t_9;// L50:L55
typedef unsigned char  ____u_char_10;// L30
typedef unsigned short int  ____u_short_11;// L31
typedef unsigned int  ____u_int_12;// L32
typedef unsigned long int  ____u_long_13;// L33
typedef signed char  ____int8_t_14;// L36
typedef unsigned char  ____uint8_t_15;// L37
typedef signed short int  ____int16_t_16;// L38
typedef unsigned short int  ____uint16_t_17;// L39
typedef signed int  ____int32_t_18;// L40
typedef unsigned int  ____uint32_t_19;// L41
typedef signed long int  ____int64_t_20;// L43
typedef unsigned long int  ____uint64_t_21;// L44
typedef long int  ____quad_t_22;// L52
typedef unsigned long int  ____u_quad_t_23;// L53
typedef unsigned long int  ____dev_t_24;// L109:L124
typedef unsigned int  ____uid_t_25;// L92:L125
typedef unsigned int  ____gid_t_26;// L92:L126
typedef unsigned long int  ____ino_t_27;// L94:L127
typedef unsigned long int  ____ino64_t_28;// L109:L128
typedef unsigned int  ____mode_t_29;// L92:L129
typedef unsigned long int  ____nlink_t_30;// L94:L130
typedef long int  ____off_t_31;// L93:L131
typedef long int  ____off64_t_32;// L108:L132
typedef int  ____pid_t_33;// L91:L133
struct ____anonymous_tag_34_35 {
int  ____val_36[2];// L72
};
typedef struct ____anonymous_tag_34_35  ____fsid_t_37;// L72:L134
typedef long int  ____clock_t_38;// L93:L135
typedef unsigned long int  ____rlim_t_39;// L94:L136
typedef unsigned long int  ____rlim64_t_40;// L109:L137
typedef unsigned int  ____id_t_41;// L92:L138
typedef long int  ____time_t_42;// L93:L139
typedef unsigned int  ____useconds_t_43;// L92:L140
typedef long int  ____suseconds_t_44;// L93:L141
typedef int  ____daddr_t_45;// L91:L143
typedef int  ____key_t_46;// L91:L144
typedef int  ____clockid_t_47;// L91:L147
typedef void  * (____timer_t_48);// L70:L150
typedef long int  ____blksize_t_49;// L93:L153
typedef long int  ____blkcnt_t_50;// L93:L158
typedef long int  ____blkcnt64_t_51;// L108:L159
typedef unsigned long int  ____fsblkcnt_t_52;// L94:L162
typedef unsigned long int  ____fsblkcnt64_t_53;// L109:L163
typedef unsigned long int  ____fsfilcnt_t_54;// L94:L166
typedef unsigned long int  ____fsfilcnt64_t_55;// L109:L167
typedef long int  ____fsword_t_56;// L93:L170
typedef long int  ____ssize_t_57;// L110:L172
typedef long int  ____syscall_slong_t_58;// L93:L175
typedef unsigned long int  ____syscall_ulong_t_59;// L94:L177
typedef ____off64_t_32  ____loff_t_60;// L181
typedef ____quad_t_22  * (____qaddr_t_62);// L182
typedef char  * (____caddr_t_63);// L183
typedef long int  ____intptr_t_64;// L110:L186
typedef unsigned int  ____socklen_t_65;// L92:L189
struct ____anonymous_tag_71_72 {
unsigned int  ____w_termsig_73 : 7;// L72
unsigned int  ____w_coredump_74 : 1;// L73
unsigned int  ____w_retcode_75 : 8;// L74
unsigned int  __anon_id_0_76 : 16;// L75
};
struct ____anonymous_tag_77_78 {
unsigned int  ____w_stopval_79 : 8;// L87
unsigned int  ____w_stopsig_80 : 8;// L88
unsigned int  __anon_id_1_81 : 16;// L89
};
union __wait_82 {
int  __w_status_83;// L68
struct ____anonymous_tag_71_72  ____wait_terminated_84;// L69
struct ____anonymous_tag_77_78  ____wait_stopped_85;// L84
};
union ____anonymous_tag_86_87 {
union __wait_82  * (____uptr_88);// L69
int  * (____iptr_89);// L70
};
typedef union ____anonymous_tag_86_87  ____WAIT_STATUS_90;// L67:L71
struct ____anonymous_tag_91_92 {
int  __quot_93;// L99
int  __rem_94;// L100
};
typedef struct ____anonymous_tag_91_92  __div_t_95;// L97:L101
struct ____anonymous_tag_96_97 {
long int  __quot_98;// L107
long int  __rem_99;// L108
};
typedef struct ____anonymous_tag_96_97  __ldiv_t_100;// L105:L109
struct ____anonymous_tag_101_102 {
long long int  __quot_103;// L119
long long int  __rem_104;// L120
};
typedef struct ____anonymous_tag_101_102  __lldiv_t_105;// L117:L121
typedef unsigned char  ____u_char_165;// L30
typedef unsigned short int  ____u_short_166;// L31
typedef unsigned int  ____u_int_167;// L32
typedef unsigned long int  ____u_long_168;// L33
typedef signed char  ____int8_t_169;// L36
typedef unsigned char  ____uint8_t_170;// L37
typedef signed short int  ____int16_t_171;// L38
typedef unsigned short int  ____uint16_t_172;// L39
typedef signed int  ____int32_t_173;// L40
typedef unsigned int  ____uint32_t_174;// L41
typedef signed long int  ____int64_t_175;// L43
typedef unsigned long int  ____uint64_t_176;// L44
typedef long int  ____quad_t_177;// L52
typedef unsigned long int  ____u_quad_t_178;// L53
typedef unsigned long int  ____dev_t_179;// L109:L124
typedef unsigned int  ____uid_t_180;// L92:L125
typedef unsigned int  ____gid_t_181;// L92:L126
typedef unsigned long int  ____ino_t_182;// L94:L127
typedef unsigned long int  ____ino64_t_183;// L109:L128
typedef unsigned int  ____mode_t_184;// L92:L129
typedef unsigned long int  ____nlink_t_185;// L94:L130
typedef long int  ____off_t_186;// L93:L131
typedef long int  ____off64_t_187;// L108:L132
typedef int  ____pid_t_188;// L91:L133
struct ____anonymous_tag_189_190 {
int  ____val_191[2];// L72
};
typedef struct ____anonymous_tag_189_190  ____fsid_t_192;// L72:L134
typedef long int  ____clock_t_193;// L93:L135
typedef unsigned long int  ____rlim_t_194;// L94:L136
typedef unsigned long int  ____rlim64_t_195;// L109:L137
typedef unsigned int  ____id_t_196;// L92:L138
typedef long int  ____time_t_197;// L93:L139
typedef unsigned int  ____useconds_t_198;// L92:L140
typedef long int  ____suseconds_t_199;// L93:L141
typedef int  ____daddr_t_200;// L91:L143
typedef int  ____key_t_201;// L91:L144
typedef int  ____clockid_t_202;// L91:L147
typedef void  * (____timer_t_203);// L70:L150
typedef long int  ____blksize_t_204;// L93:L153
typedef long int  ____blkcnt_t_205;// L93:L158
typedef long int  ____blkcnt64_t_206;// L108:L159
typedef unsigned long int  ____fsblkcnt_t_207;// L94:L162
typedef unsigned long int  ____fsblkcnt64_t_208;// L109:L163
typedef unsigned long int  ____fsfilcnt_t_209;// L94:L166
typedef unsigned long int  ____fsfilcnt64_t_210;// L109:L167
typedef long int  ____fsword_t_211;// L93:L170
typedef long int  ____ssize_t_212;// L110:L172
typedef long int  ____syscall_slong_t_213;// L93:L175
typedef unsigned long int  ____syscall_ulong_t_214;// L94:L177
typedef ____off64_t_187  ____loff_t_215;// L181
typedef ____quad_t_177  * (____qaddr_t_217);// L182
typedef char  * (____caddr_t_218);// L183
typedef long int  ____intptr_t_219;// L110:L186
typedef unsigned int  ____socklen_t_220;// L92:L189
typedef ____u_char_10  __u_char_221;// L33
typedef ____u_char_165  __u_char_222;// L33
typedef ____u_short_11  __u_short_223;// L34
typedef ____u_short_166  __u_short_224;// L34
typedef ____u_int_12  __u_int_225;// L35
typedef ____u_int_167  __u_int_226;// L35
typedef ____u_long_13  __u_long_227;// L36
typedef ____u_long_168  __u_long_228;// L36
typedef ____quad_t_22  __quad_t_229;// L37
typedef ____quad_t_177  __quad_t_230;// L37
typedef ____u_quad_t_23  __u_quad_t_231;// L38
typedef ____u_quad_t_178  __u_quad_t_232;// L38
typedef ____fsid_t_37  __fsid_t_233;// L39
typedef ____fsid_t_192  __fsid_t_234;// L39
typedef ____loff_t_60  __loff_t_236;// L44
typedef ____loff_t_215  __loff_t_237;// L44
typedef ____loff_t_60  __loff_t_239;// L44
typedef ____loff_t_215  __loff_t_240;// L44
typedef ____ino64_t_28  __ino_t_242;// L50
typedef ____ino64_t_183  __ino_t_243;// L50
typedef ____ino_t_27  __ino_t_245;// L48
typedef ____ino_t_182  __ino_t_246;// L48
typedef ____dev_t_24  __dev_t_248;// L60
typedef ____dev_t_179  __dev_t_249;// L60
typedef ____gid_t_26  __gid_t_251;// L65
typedef ____gid_t_181  __gid_t_252;// L65
typedef ____gid_t_26  __gid_t_254;// L65
typedef ____gid_t_181  __gid_t_255;// L65
typedef ____mode_t_29  __mode_t_257;// L70
typedef ____mode_t_184  __mode_t_258;// L70
typedef ____nlink_t_30  __nlink_t_260;// L75
typedef ____nlink_t_185  __nlink_t_261;// L75
typedef ____uid_t_25  __uid_t_263;// L80
typedef ____uid_t_180  __uid_t_264;// L80
typedef ____uid_t_25  __uid_t_266;// L80
typedef ____uid_t_180  __uid_t_267;// L80
typedef ____off64_t_32  __off_t_269;// L88
typedef ____off64_t_187  __off_t_270;// L88
typedef ____off_t_31  __off_t_272;// L86
typedef ____off_t_186  __off_t_273;// L86
typedef ____pid_t_33  __pid_t_275;// L98
typedef ____pid_t_188  __pid_t_276;// L98
typedef ____pid_t_33  __pid_t_278;// L98
typedef ____pid_t_188  __pid_t_279;// L98
typedef ____id_t_41  __id_t_281;// L104
typedef ____id_t_196  __id_t_282;// L104
typedef ____ssize_t_57  __ssize_t_284;// L109
typedef ____ssize_t_212  __ssize_t_285;// L109
typedef ____daddr_t_45  __daddr_t_287;// L115
typedef ____daddr_t_200  __daddr_t_288;// L115
typedef ____caddr_t_63  __caddr_t_290;// L116
typedef ____caddr_t_218  __caddr_t_291;// L116
typedef ____key_t_46  __key_t_292;// L122
typedef ____key_t_201  __key_t_293;// L122
typedef ____key_t_46  __key_t_295;// L122
typedef ____key_t_201  __key_t_296;// L122
typedef ____clock_t_38  __clock_t_298;// L59
typedef ____clock_t_193  __clock_t_299;// L59
typedef ____time_t_42  __time_t_301;// L75
typedef ____time_t_197  __time_t_302;// L75
typedef ____clockid_t_47  __clockid_t_304;// L91
typedef ____clockid_t_202  __clockid_t_305;// L91
typedef ____timer_t_48  __timer_t_307;// L103
typedef ____timer_t_203  __timer_t_308;// L103
typedef unsigned long int  __ulong_310;// L150
typedef unsigned long int  __ulong_311;// L150
typedef unsigned long int  __ulong_312;// L150
typedef unsigned short int  __ushort_313;// L151
typedef unsigned int  __uint_314;// L152
typedef int  __int8_t_315;// L188:L194
typedef int  __int16_t_316;// L188:L195
typedef int  __int32_t_317;// L188:L196
typedef int  __int64_t_318;// L188:L197
typedef unsigned int  __u_int8_t_319;// L190:L200
typedef unsigned int  __u_int16_t_320;// L190:L201
typedef unsigned int  __u_int32_t_321;// L190:L202
typedef unsigned int  __u_int64_t_322;// L190:L203
typedef int  __register_t_323;// L205
typedef int  ____sig_atomic_t_329;// L22
struct ____anonymous_tag_330_331 {
unsigned long int  ____val_332[( 1024 / ( 8 * sizeof(unsigned long) ) )];// L29
};
typedef struct ____anonymous_tag_330_331  ____sigset_t_333;// L27:L30
typedef ____sigset_t_333  __sigset_t_334;// L37
struct __timespec_335 {
____time_t_42  __tv_sec_336;// L0
____time_t_197  __tv_sec_337;// L0
____syscall_slong_t_58  __tv_nsec_339;// L0
____syscall_slong_t_213  __tv_nsec_340;// L0
};
struct __timeval_343 {
____time_t_42  __tv_sec_344;// L0
____time_t_197  __tv_sec_345;// L0
____suseconds_t_44  __tv_usec_347;// L0
____suseconds_t_199  __tv_usec_348;// L0
};
typedef ____suseconds_t_44  __suseconds_t_351;// L48
typedef ____suseconds_t_199  __suseconds_t_352;// L48
typedef long int  ____fd_mask_354;// L54
typedef long int  ____fd_mask_355;// L54
struct ____anonymous_tag_356_357 {
____fd_mask_354  ____fds_bits_358[1024 / ( 8 * ( int   ) sizeof(long) )];// L0
____fd_mask_355  ____fds_bits_360[1024 / ( 8 * ( int   ) sizeof(long) )];// L0
};
typedef struct ____anonymous_tag_356_357  __fd_set_363;// L64:L75
typedef ____fd_mask_354  __fd_mask_364;// L82
typedef ____fd_mask_355  __fd_mask_365;// L82
typedef ____blksize_t_49  __blksize_t_413;// L228
typedef ____blksize_t_204  __blksize_t_414;// L228
typedef ____blkcnt_t_50  __blkcnt_t_416;// L235
typedef ____blkcnt_t_205  __blkcnt_t_417;// L235
typedef ____fsblkcnt_t_52  __fsblkcnt_t_419;// L239
typedef ____fsblkcnt_t_207  __fsblkcnt_t_420;// L239
typedef ____blkcnt64_t_51  __blkcnt_t_422;// L248
typedef ____blkcnt64_t_206  __blkcnt_t_423;// L248
typedef ____fsblkcnt64_t_53  __fsblkcnt_t_425;// L252
typedef ____fsblkcnt64_t_208  __fsblkcnt_t_426;// L252
typedef ____fsfilcnt_t_54  __fsfilcnt_t_428;// L243
typedef ____fsfilcnt_t_209  __fsfilcnt_t_429;// L243
typedef ____fsfilcnt64_t_55  __fsfilcnt_t_431;// L256
typedef ____fsfilcnt64_t_210  __fsfilcnt_t_432;// L256
typedef unsigned long int  __pthread_t_434;// L60
union __pthread_attr_t_435 {
char  ____size_436[56];// L65
long int  ____align_437;// L66
};
typedef union __pthread_attr_t_435  __pthread_attr_t_438;// L69
struct ____pthread_internal_list_440 {
struct __forward_tag_reference_439  * (____prev_441);// L0
struct __forward_tag_reference_439  * (____next_442);// L0
};
typedef struct ____pthread_internal_list_440  ____pthread_list_t_443;// L75:L79
typedef struct ____pthread_internal_list_440  ____pthread_list_t_444;// L75:L79
struct ____pthread_mutex_s_445 {
int  ____lock_446;// L94
unsigned int  ____count_447;// L95
int  ____owner_448;// L96
unsigned int  ____nusers_449;// L98
int  ____kind_450;// L102
short  ____spins_451;// L104
short  ____elision_452;// L105
____pthread_list_t_443  ____list_453;// L0
____pthread_list_t_444  ____list_454;// L0
};
union ____anonymous_tag_455_456 {
struct ____pthread_mutex_s_445  ____data_457;// L92
char  ____size_458[40];// L126
long int  ____align_459;// L127
};
typedef union ____anonymous_tag_455_456  __pthread_mutex_t_460;// L90:L128
union ____anonymous_tag_461_462 {
char  ____size_463[4];// L132
int  ____align_464;// L133
};
typedef union ____anonymous_tag_461_462  __pthread_mutexattr_t_465;// L130:L134
typedef int  (* (____compar_fn_t_573)) (const void  *, const void  *);// L741

struct __forward_tag_reference_439 { // generated union of struct variations
union {
};
};

extern int  * ((____errno_location_0) (void  ));// L50
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
static __inline unsigned int  (____bswap_32_67) (unsigned int  ____bsx_66) {

if (__static_condition_default_68) {

{// L46
{



__static_type_error("invalid type found in return expression");
}
}// L48


}
}
static __inline ____uint64_t_21  (____bswap_64_70) (____uint64_t_21  ____bsx_69) {

if (__static_condition_default_68) {

{// L110
{



__static_type_error("invalid type found in return expression");
}
}// L112


}
}
union __wait_82 ;// L66
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
extern __size_t_2  (____ctype_get_mb_cur_max_106) (void  );// L139
extern __size_t_2  (____ctype_get_mb_cur_max_107) (void  );// L139
extern __size_t_2  (____ctype_get_mb_cur_max_108) (void  );// L139
extern __size_t_2  (____ctype_get_mb_cur_max_109) (void  );// L139
extern double  (__atof_111) (const char  * (____nptr_110));// L144:L145
extern double  (__atof_112) (const char  * (____nptr_110));// L144:L145
extern int  (__atoi_114) (const char  * (____nptr_113));// L147:L148
extern int  (__atoi_115) (const char  * (____nptr_113));// L147:L148
extern long int  (__atol_117) (const char  * (____nptr_116));// L150:L151
extern long int  (__atol_118) (const char  * (____nptr_116));// L150:L151
extern long long int  (__atoll_120) (const char  * (____nptr_119));// L157:L158
extern long long int  (__atoll_121) (const char  * (____nptr_119));// L157:L158
extern double  (__strtod_124) (const char  * __restrict  ____nptr_122, char  * (* __restrict  ____endptr_123));// L164:L166
extern float  (__strtof_127) (const char  * __restrict  ____nptr_125, char  * (* __restrict  ____endptr_126));// L172:L173
extern long double  (__strtold_130) (const char  * __restrict  ____nptr_128, char  * (* __restrict  ____endptr_129));// L175:L177
extern long int  (__strtol_134) (const char  * __restrict  ____nptr_131, char  * (* __restrict  ____endptr_132), int  ____base_133);// L183:L185
extern unsigned long int  (__strtoul_138) (const char  * __restrict  ____nptr_135, char  * (* __restrict  ____endptr_136), int  ____base_137);// L187:L189
extern long long int  (__strtoq_142) (const char  * __restrict  ____nptr_139, char  * (* __restrict  ____endptr_140), int  ____base_141);// L195:L197
extern unsigned long long int  (__strtouq_146) (const char  * __restrict  ____nptr_143, char  * (* __restrict  ____endptr_144), int  ____base_145);// L200:L202
extern long long int  (__strtoll_150) (const char  * __restrict  ____nptr_147, char  * (* __restrict  ____endptr_148), int  ____base_149);// L209:L211
extern long long int  (__strtoll_151) (const char  * __restrict  ____nptr_147, char  * (* __restrict  ____endptr_148), int  ____base_149);// L209:L211
extern unsigned long long int  (__strtoull_155) (const char  * __restrict  ____nptr_152, char  * (* __restrict  ____endptr_153), int  ____base_154);// L214:L216
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
__extension__/* no function due to type errors in the function prototype */
extern char  * ((__l64a_160) (long int  ____n_159));// L305
extern char  * ((__l64a_161) (long int  ____n_159));// L305
extern long int  (__a64l_163) (const char  * (____s_162));// L308:L309
extern long int  (__a64l_164) (const char  * (____s_162));// L308:L309
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
static __inline unsigned int  (____bswap_32_325) (unsigned int  ____bsx_324) {

if (__static_condition_default_326) {

{// L46
{



__static_type_error("invalid type found in return expression");
}
}// L48


}
}
static __inline ____uint64_t_176  (____bswap_64_328) (____uint64_t_176  ____bsx_327) {

if (__static_condition_default_326) {

{// L110
{



__static_type_error("invalid type found in return expression");
}
}// L112


}
}
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
struct __timespec_335 ;// L120

struct __timeval_343 ;// L30

// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
extern int  (__select_377) (int  ____nfds_366, __fd_set_363  * __restrict  ____readfds_367, __fd_set_363  * __restrict  ____writefds_369, __fd_set_363  * __restrict  ____exceptfds_371, struct __timeval_343  * __restrict  ____timeout_374);// L106:L109
extern int  (__select_378) (int  ____nfds_366, __fd_set_363  * __restrict  ____readfds_367, __fd_set_363  * __restrict  ____writefds_369, __fd_set_363  * __restrict  ____exceptfds_371, struct __forward_tag_reference_373  * __restrict  ____timeout_376);// L106:L109
extern int  (__pselect_393) (int  ____nfds_381, __fd_set_363  * __restrict  ____readfds_382, __fd_set_363  * __restrict  ____writefds_384, __fd_set_363  * __restrict  ____exceptfds_386, const struct __timespec_335  * __restrict  ____timeout_389, const ____sigset_t_333  * __restrict  ____sigmask_392);// L118:L122
extern int  (__pselect_394) (int  ____nfds_381, __fd_set_363  * __restrict  ____readfds_382, __fd_set_363  * __restrict  ____writefds_384, __fd_set_363  * __restrict  ____exceptfds_386, const struct __forward_tag_reference_388  * __restrict  ____timeout_391, const ____sigset_t_333  * __restrict  ____sigmask_392);// L118:L122
extern long int  (____fdelt_chk_398) (long int  ____d_397);// L24
extern long int  (____fdelt_warn_400) (long int  ____d_399);// L25:L26
extern unsigned int  (__gnu_dev_major_402) (unsigned long long int  ____dev_401);// L27:L28
extern unsigned int  (__gnu_dev_major_403) (unsigned long long int  ____dev_401);// L27:L28
extern unsigned int  (__gnu_dev_minor_405) (unsigned long long int  ____dev_404);// L30:L31
extern unsigned long long int  (__gnu_dev_makedev_408) (unsigned int  ____major_406, unsigned int  ____minor_407);// L33:L35
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
union __pthread_attr_t_435 ;// L63
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
extern int  (__rand_466) (void  );// L374
extern void  (__srand_468) (unsigned int  ____seed_467);// L376
extern int  (__rand_r_470) (unsigned int  * (____seed_469));// L381
extern double  (__drand48_471) (void  );// L389
extern double  (__erand48_473) (unsigned short int  ____xsubi_472[3]);// L390
extern long int  (__lrand48_474) (void  );// L393
extern long int  (__nrand48_476) (unsigned short int  ____xsubi_475[3]);// L394:L395
extern long int  (__mrand48_477) (void  );// L398
extern long int  (__jrand48_479) (unsigned short int  ____xsubi_478[3]);// L399:L400
extern void  (__srand48_481) (long int  ____seedval_480);// L403
extern unsigned short int  * ((__seed48_483) (unsigned short int  ____seed16v_482[3]));// L404:L405
extern void  (__lcong48_485) (unsigned short int  ____param_484[7]);// L406
extern void  * ((__malloc_487) (__size_t_2  ____size_486));// L466
extern void  * ((__malloc_488) (__size_t_2  ____size_486));// L466
extern void  * ((__calloc_491) (__size_t_2  ____nmemb_489, __size_t_2  ____size_490));// L468:L469
extern void  * ((__calloc_492) (__size_t_2  ____nmemb_489, __size_t_2  ____size_490));// L468:L469
extern void  * ((__realloc_495) (void  * (____ptr_493), __size_t_2  ____size_494));// L480:L481
extern void  (__free_497) (void  * (____ptr_496));// L483
extern void  (__cfree_499) (void  * (____ptr_498));// L488
extern void  * ((__alloca_501) (__size_t_2  ____size_500));// L32
extern void  * ((__valloc_503) (__size_t_2  ____size_502));// L498
extern void  * ((__valloc_504) (__size_t_2  ____size_502));// L498
extern int  (__posix_memalign_508) (void  * (* (____memptr_505)), __size_t_2  ____alignment_506, __size_t_2  ____size_507);// L503:L504
extern int  (__posix_memalign_509) (void  * (* (____memptr_505)), __size_t_2  ____alignment_506, __size_t_2  ____size_507);// L503:L504
extern void  * ((__aligned_alloc_512) (__size_t_2  ____alignment_510, __size_t_2  ____size_511));// L509:L510
extern void  * ((__aligned_alloc_513) (__size_t_2  ____alignment_510, __size_t_2  ____size_511));// L509:L510
extern void  * ((__aligned_alloc_514) (__size_t_2  ____alignment_510, __size_t_2  ____size_511));// L509:L510
extern void  * ((__aligned_alloc_515) (__size_t_2  ____alignment_510, __size_t_2  ____size_511));// L509:L510
extern void  (__abort_516) (void  );// L515
extern int  (__atexit_518) (void  (* (____func_517)) (void  ));// L519
extern int  (__at_quick_exit_520) (void  (* (____func_519)) (void  ));// L527
extern int  (__on_exit_525) (void  (* (____func_523)) (int  ____status_521, void  * (____arg_522)), void  * (____arg_524));// L535:L536
extern void  (__exit_527) (int  ____status_526);// L543
extern void  (__exit_528) (int  ____status_526);// L543
extern void  (__quick_exit_530) (int  ____status_529);// L549
extern void  (___Exit_532) (int  ____status_531);// L557
extern char  * ((__getenv_534) (const char  * (____name_533)));// L564
extern char  * ((__getenv_535) (const char  * (____name_533)));// L564
extern int  (__putenv_537) (char  * (____string_536));// L578
extern int  (__setenv_541) (const char  * (____name_538), const char  * (____value_539), int  ____replace_540);// L584:L585
extern int  (__unsetenv_543) (const char  * (____name_542));// L588
extern int  (__clearenv_544) (void  );// L595
extern char  * ((__mktemp_546) (char  * (____template_545)));// L606
extern int  (__mkstemp_549) (char  * (____template_547));// L619
extern int  (__mkstemp_551) (char  * (____template_547));// L619
extern int  (__mkstemp_550) (char  * (____template_548));// L622:L623
extern int  (__mkstemp_552) (char  * (____template_548));// L622:L623
extern int  (__mkstemps_557) (char  * (____template_553), int  ____suffixlen_554);// L641
extern int  (__mkstemps_558) (char  * (____template_555), int  ____suffixlen_556);// L644:L645
extern int  (__mkstemps_559) (char  * (____template_553), int  ____suffixlen_554);// L641
extern int  (__mkstemps_560) (char  * (____template_555), int  ____suffixlen_556);// L644:L645
extern char  * ((__mkdtemp_562) (char  * (____template_561)));// L662
extern char  * ((__mkdtemp_563) (char  * (____template_561)));// L662
extern int  (__system_565) (const char  * (____command_564));// L716
extern int  (__system_566) (const char  * (____command_564));// L716
extern int  (__system_567) (const char  * (____command_564));// L716
extern int  (__system_568) (const char  * (____command_564));// L716
extern char  * ((__realpath_571) (const char  * __restrict  ____name_569, char  * __restrict  ____resolved_570));// L733:L734
extern char  * ((__realpath_572) (const char  * __restrict  ____name_569, char  * __restrict  ____resolved_570));// L733:L734
// typedef moved to top of scope
extern void  * ((__bsearch_581) (const void  * (____key_574), const void  * (____base_575), __size_t_2  ____nmemb_576, __size_t_2  ____size_577, ____compar_fn_t_573  ____compar_578));// L754:L756
extern void  * ((__bsearch_583) (const void  * (____key_574), const void  * (____base_575), __size_t_2  ____nmemb_576, __size_t_2  ____size_577, ____compar_fn_t_573  ____compar_578));// L754:L756
/* no function due to type errors in the function prototype */
extern void  (__qsort_602) (void  * (____base_597), __size_t_2  ____nmemb_598, __size_t_2  ____size_599, ____compar_fn_t_573  ____compar_600);// L764:L765
extern void  (__qsort_604) (void  * (____base_597), __size_t_2  ____nmemb_598, __size_t_2  ____size_599, ____compar_fn_t_573  ____compar_600);// L764:L765
extern int  (__abs_607) (int  ____x_606);// L774
extern int  (__abs_608) (int  ____x_606);// L774
extern long int  (__labs_610) (long int  ____x_609);// L775
extern long int  (__labs_611) (long int  ____x_609);// L775
extern long long int  (__llabs_613) (long long int  ____x_612);// L779:L780
extern long long int  (__llabs_614) (long long int  ____x_612);// L779:L780
extern __div_t_95  (__div_617) (int  ____numer_615, int  ____denom_616);// L788:L789
extern __div_t_95  (__div_618) (int  ____numer_615, int  ____denom_616);// L788:L789
extern __ldiv_t_100  (__ldiv_621) (long int  ____numer_619, long int  ____denom_620);// L790:L791
extern __ldiv_t_100  (__ldiv_623) (long int  ____numer_619, long int  ____denom_620);// L790:L791
extern __lldiv_t_105  (__lldiv_627) (long long int  ____numer_625, long long int  ____denom_626);// L796:L798
extern __lldiv_t_105  (__lldiv_629) (long long int  ____numer_625, long long int  ____denom_626);// L796:L798
extern char  * ((__ecvt_635) (double  ____value_631, int  ____ndigit_632, int  * __restrict  ____decpt_633, int  * __restrict  ____sign_634));// L811:L812
extern char  * ((__ecvt_636) (double  ____value_631, int  ____ndigit_632, int  * __restrict  ____decpt_633, int  * __restrict  ____sign_634));// L811:L812
extern char  * ((__fcvt_641) (double  ____value_637, int  ____ndigit_638, int  * __restrict  ____decpt_639, int  * __restrict  ____sign_640));// L817:L818
extern char  * ((__fcvt_642) (double  ____value_637, int  ____ndigit_638, int  * __restrict  ____decpt_639, int  * __restrict  ____sign_640));// L817:L818
extern char  * ((__gcvt_646) (double  ____value_643, int  ____ndigit_644, char  * (____buf_645)));// L823:L824
extern char  * ((__gcvt_647) (double  ____value_643, int  ____ndigit_644, char  * (____buf_645)));// L823:L824
extern char  * ((__qecvt_652) (long double  ____value_648, int  ____ndigit_649, int  * __restrict  ____decpt_650, int  * __restrict  ____sign_651));// L829:L831
extern char  * ((__qecvt_653) (long double  ____value_648, int  ____ndigit_649, int  * __restrict  ____decpt_650, int  * __restrict  ____sign_651));// L829:L831
extern char  * ((__qfcvt_658) (long double  ____value_654, int  ____ndigit_655, int  * __restrict  ____decpt_656, int  * __restrict  ____sign_657));// L832:L834
extern char  * ((__qfcvt_659) (long double  ____value_654, int  ____ndigit_655, int  * __restrict  ____decpt_656, int  * __restrict  ____sign_657));// L832:L834
extern char  * ((__qgcvt_663) (long double  ____value_660, int  ____ndigit_661, char  * (____buf_662)));// L835:L836
extern char  * ((__qgcvt_664) (long double  ____value_660, int  ____ndigit_661, char  * (____buf_662)));// L835:L836
extern int  (__ecvt_r_671) (double  ____value_665, int  ____ndigit_666, int  * __restrict  ____decpt_667, int  * __restrict  ____sign_668, char  * __restrict  ____buf_669, __size_t_2  ____len_670);// L841:L843
extern int  (__fcvt_r_678) (double  ____value_672, int  ____ndigit_673, int  * __restrict  ____decpt_674, int  * __restrict  ____sign_675, char  * __restrict  ____buf_676, __size_t_2  ____len_677);// L844:L846
extern int  (__qecvt_r_685) (long double  ____value_679, int  ____ndigit_680, int  * __restrict  ____decpt_681, int  * __restrict  ____sign_682, char  * __restrict  ____buf_683, __size_t_2  ____len_684);// L848:L851
extern int  (__qfcvt_r_692) (long double  ____value_686, int  ____ndigit_687, int  * __restrict  ____decpt_688, int  * __restrict  ____sign_689, char  * __restrict  ____buf_690, __size_t_2  ____len_691);// L852:L855
extern int  (__mblen_695) (const char  * (____s_693), __size_t_2  ____n_694);// L862
extern int  (__mblen_696) (const char  * (____s_693), __size_t_2  ____n_694);// L862
extern int  (__mbtowc_700) (__wchar_t_3  * __restrict  ____pwc_697, const char  * __restrict  ____s_698, __size_t_2  ____n_699);// L865:L866
extern int  (__wctomb_703) (char  * (____s_701), __wchar_t_3  ____wchar_702);// L869
extern __size_t_2  (__mbstowcs_707) (__wchar_t_3  * __restrict  ____pwcs_704, const char  * __restrict  ____s_705, __size_t_2  ____n_706);// L873:L874
extern __size_t_2  (__wcstombs_711) (char  * __restrict  ____s_708, const __wchar_t_3  * __restrict  ____pwcs_709, __size_t_2  ____n_710);// L876:L878
extern int  (__rpmatch_714) (const char  * (____response_712));// L887
extern int  (__rpmatch_713) (const char  * (____response_712));// L887
extern int  (__getsubopt_719) (char  * (* __restrict  ____optionp_715), char  * const  * __restrict  ____tokens_716, char  * (* __restrict  ____valuep_717));// L898:L901
extern int  (__getsubopt_718) (char  * (* __restrict  ____optionp_715), char  * const  * __restrict  ____tokens_716, char  * (* __restrict  ____valuep_717));// L898:L901
extern int  (__getloadavg_722) (double  ____loadavg_720[], int  ____nelem_721);// L950:L951
/* no function due to type errors in the function prototype */
extern char  * ((____realpath_chk_727) (const char  * __restrict  ____name_724, char  * __restrict  ____resolved_725, __size_t_2  ____resolvedlen_726));// L23:L25
extern char  * ((____realpath_alias_730) (const char  * __restrict  ____name_728, char  * __restrict  ____resolved_729));// L26:L28
extern char  * ((____realpath_chk_warn_734) (const char  * __restrict  ____name_731, char  * __restrict  ____resolved_732, __size_t_2  ____resolvedlen_733));// L29:L34
/* no function due to type errors in the function prototype */
extern int  (____ptsname_r_chk_742) (int  ____fd_738, char  * (____buf_739), __size_t_2  ____buflen_740, __size_t_2  ____nreal_741);// L52:L53
extern int  (____ptsname_r_alias_746) (int  ____fd_743, char  * (____buf_744), __size_t_2  ____buflen_745);// L54:L56
extern int  (____ptsname_r_chk_warn_751) (int  ____fd_747, char  * (____buf_748), __size_t_2  ____buflen_749, __size_t_2  ____nreal_750);// L57:L61
/* no function due to type errors in the function prototype */
extern int  (____wctomb_chk_759) (char  * (____s_756), __wchar_t_3  ____wchar_757, __size_t_2  ____buflen_758);// L77:L78
extern int  (____wctomb_alias_762) (char  * (____s_760), __wchar_t_3  ____wchar_761);// L79:L80
/* no function due to type errors in the function prototype */
extern __size_t_2  (____mbstowcs_chk_769) (__wchar_t_3  * __restrict  ____dst_765, const char  * __restrict  ____src_766, __size_t_2  ____len_767, __size_t_2  ____dstlen_768);// L98:L100
extern __size_t_2  (____mbstowcs_alias_773) (__wchar_t_3  * __restrict  ____dst_770, const char  * __restrict  ____src_771, __size_t_2  ____len_772);// L101:L104
extern __size_t_2  (____mbstowcs_chk_warn_778) (__wchar_t_3  * __restrict  ____dst_774, const char  * __restrict  ____src_775, __size_t_2  ____len_776, __size_t_2  ____dstlen_777);// L105:L110
/* no function due to type errors in the function prototype */
extern __size_t_2  (____wcstombs_chk_786) (char  * __restrict  ____dst_782, const __wchar_t_3  * __restrict  ____src_783, __size_t_2  ____len_784, __size_t_2  ____dstlen_785);// L130:L132
extern __size_t_2  (____wcstombs_alias_790) (char  * __restrict  ____dst_787, const __wchar_t_3  * __restrict  ____src_788, __size_t_2  ____len_789);// L133:L136
extern __size_t_2  (____wcstombs_chk_warn_795) (char  * __restrict  ____dst_791, const __wchar_t_3  * __restrict  ____src_792, __size_t_2  ____len_793, __size_t_2  ____dstlen_794);// L137:L141
/* no function due to type errors in the function prototype */
long  * (__pm_buffer_799);// L10
unsigned long  __pm_pos_800;// L11
unsigned long  __pm_len_801;// L11
static int  (__add_to_pagemap_802) () {

if (__static_condition_default_803) {

{// L14
{



 __pm_buffer_799  [  __pm_pos_800  ++ ] = 0 ; // L15
if (  __pm_pos_800  >=  __pm_len_801  )// L16
{
return 1 ;// L17
}
return 0 ;// L18
}
}// L19


}
}
static int  (__pagemap_pte_range_805) () {

if (__static_condition_default_803) {

{// L22
{



int  __err_804= 0;// L23

while ( 1 )// L25
{

{// L25
{



 __err_804  =  __add_to_pagemap_802 ( ) ; // L26
if (  __err_804  )// L27
{
return  __err_804  ;// L28
}
}
}// L29
}
return  __err_804  ;// L31
}
}// L32


}
}
int  (__walk_page_range_806) () {

if (__static_condition_default_803) {

{// L35
{



return  __pagemap_pte_range_805 ( ) ;// L36
}
}// L37


}
}
static int  (__pagemap_read_807) () {

if (__static_condition_default_803) {

{// L39
{



 __pm_len_801  = sizeof(long) * 10 ; // L6:L40
if (__static_condition_default_808) {
 __pm_buffer_799  = malloc ( __pm_len_801 ) ; // L41
}
if (__static_condition_default_809) {
 __pm_buffer_799  = malloc ( __pm_len_801 ) ; // L41
}
if (__static_condition_default_810) {
__static_type_error("type error") ; // L41
}
if ( !  __pm_buffer_799  )// L43
{
return - 12 ;// L44
}
 __pm_pos_800  = 0 ; // L46
 __walk_page_range_806 ( ) ; // L47
return 0 ;// L49
}
}// L50


}
}
int  (__main_813) (int  __argc_811, char  * (* (__argv_812))) {

if (__static_condition_default_815) {

{// L54
{



return 0 ;// L58
}
}// L59


}
}
int  (__main_814) (int  __argc_811, char  * (* (__argv_812))) {

if (__static_condition_default_816) {

{// L54
{



 __pagemap_read_807 ( ) ; // L56
return 0 ;// L58
}
}// L59


}
}

