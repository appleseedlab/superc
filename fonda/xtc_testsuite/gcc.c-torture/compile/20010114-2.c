/* Origin: <URL:http://gcc.gnu.org/ml/gcc-patches/2000-12/msg01384.html>
   from Fred Fish <fnf@geekgadgets.org>.  See also PR c/1625.  */
// {{ dg-preprocess "Need preprocessing" }}

#include <stdbool.h>

struct { int x; bool y; } foo = { 0, false };
