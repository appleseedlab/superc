#ifdef CONFIG_FEATURE_VERBOSE
# define CONFIG_FEATURE_VERBOSE 1
# define ENABLE_FEATURE_VERBOSE 1
# ifdef MAKE_SUID
#  define IF_FEATURE_VERBOSE(...) __VA_ARGS__ "CONFIG_FEATURE_VERBOSE"
# else
#  define IF_FEATURE_VERBOSE(...) __VA_ARGS__
# endif
# define IF_NOT_FEATURE_VERBOSE(...)
#else
# undef CONFIG_FEATURE_VERBOSE
# define ENABLE_FEATURE_VERBOSE 0
# define IF_FEATURE_VERBOSE(...)
# define IF_NOT_FEATURE_VERBOSE(...) __VA_ARGS__
#endif

#ifdef CONFIG_SELINUX
# define CONFIG_SELINUX 1
# define ENABLE_SELINUX 1
# ifdef MAKE_SUID
#  define IF_SELINUX(...) __VA_ARGS__ "CONFIG_SELINUX"
# else
#  define IF_SELINUX(...) __VA_ARGS__
# endif
# define IF_NOT_SELINUX(...)
#else
# undef CONFIG_SELINUX
# define ENABLE_SELINUX 0
# define IF_SELINUX(...)
# define IF_NOT_SELINUX(...) __VA_ARGS__
#endif

enum {	/* cp.c, mv.c, install.c depend on these values. CAREFUL when changing them! */
	FILEUTILS_PRESERVE_STATUS = 1 << 0, /* -p */
	FILEUTILS_DEREFERENCE     = 1 << 1, /* !-d */
	FILEUTILS_RECUR           = 1 << 2, /* -R */
	FILEUTILS_FORCE           = 1 << 3, /* -f */
	FILEUTILS_INTERACTIVE     = 1 << 4, /* -i */
	FILEUTILS_MAKE_HARDLINK   = 1 << 5, /* -l */
	FILEUTILS_MAKE_SOFTLINK   = 1 << 6, /* -s */
	FILEUTILS_DEREF_SOFTLINK  = 1 << 7, /* -L */
	FILEUTILS_DEREFERENCE_L0  = 1 << 8, /* -H */
	/* -a = -pdR (mapped in cp.c) */
	/* -r = -dR  (mapped in cp.c) */
	/* -P = -d   (mapped in cp.c) */
	FILEUTILS_VERBOSE         = (1 << 12) * ENABLE_FEATURE_VERBOSE,	/* -v */
	FILEUTILS_UPDATE          = 1 << 13, /* -u */
#if ENABLE_SELINUX
	FILEUTILS_PRESERVE_SECURITY_CONTEXT = 1 << 14, /* -c */
#endif
	FILEUTILS_RMDEST          = 1 << (15 - !ENABLE_SELINUX), /* --remove-destination */
	/*
	 * Hole. cp may have some bits set here,
	 * they should not affect remove_file()/copy_file()
	 */
#if ENABLE_SELINUX
	FILEUTILS_SET_SECURITY_CONTEXT = 1 << 30,
#endif
	FILEUTILS_IGNORE_CHMOD_ERR = 1 << 31,
};
