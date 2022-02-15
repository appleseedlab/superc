#include <stdio.h>
#include <string.h>

#define T_ESCAPE_SHELL_CMD (0x01)

#ifdef CROSS_COMPILE
#define APR_HAVE_STDIO_H 1
#else
#include <stdlib.h> //apr-related headers
#if defined(WIN32) || defined(OS2)
#define NEED_ENHANCED_ESCAPES
#endif
#endif

int main(void)
{
  unsigned c = 0;
  unsigned char flags;

  for (c = 0; c < 256; ++c) {
    flags = 0;
    if (c % 20 == 0)
      printf("\n    ");

    /* escape_shell_cmd */
    #ifdef NEED_ENHANCED_ESCAPES
    /* Win32/OS2 have many of the same vulnerable characters
     * as Unix sh, plus the carriage return and percent char.
     * The proper escaping of these characters varies from unix
     * since Win32/OS2 use carets or doubled-double quotes,
     * and neither lf nor cr can be escaped.  We escape unix
     * specific as well, to assure that cross-compiled unix
     * applications behave similiarly when invoked on win32/os2.
     *
     * Rem please keep in-sync with apr's list in win32/filesys.c
     */
    if (c && strchr("&;`'\"|*?~<>^()[]{}$\\\n\r%", c)) {
      flags |= T_ESCAPE_SHELL_CMD;
    }
    #else
    if (c && strchr("&;`'\"|*?~<>^()[]{}$\\\n", c)) {
      flags |= T_ESCAPE_SHELL_CMD;
    }
    #endif
  }
  return 0;
}
