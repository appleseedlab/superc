
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
	FILEUTILS_VERBOSE         = (1 << 12) * ENABLE_FEATURE_VERBOSE,	/* -v */
	FILEUTILS_UPDATE          = 1 << 13, /* -u */
	FILEUTILS_RMDEST          = 1 << (15 - 1), /* --remove-destination */
	FILEUTILS_IGNORE_CHMOD_ERR = 1 << 31,
};

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
	FILEUTILS_VERBOSE         = (1 << 12) * ENABLE_FEATURE_VERBOSE,	/* -v */
	FILEUTILS_UPDATE          = 1 << 13, /* -u */
	FILEUTILS_PRESERVE_SECURITY_CONTEXT = 1 << 14, /* -c */
	FILEUTILS_RMDEST          = 1 << (15 - 0), /* --remove-destination */
	FILEUTILS_SET_SECURITY_CONTEXT = 1 << 30,
	FILEUTILS_IGNORE_CHMOD_ERR = 1 << 31,
};
