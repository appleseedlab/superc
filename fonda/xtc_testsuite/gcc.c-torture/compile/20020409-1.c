/* PR c/5078 */
// {{ dg-preprocess "Need preprocessing" }}
#include <limits.h>

int f(int i)
{
  i -= 2 * (INT_MAX + 1);
  return i;
}
