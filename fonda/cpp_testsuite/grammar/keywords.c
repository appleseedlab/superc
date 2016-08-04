_Bool bob; /* gnu89 and C99 */

_Complex c; /* gnu89 and C99 */

int restrict = 1; /* restrict is a C99 but not gnu89 keyword */

inline /* gnu89 and C99 */
int inc (int *a)
{
  (*a)++;

  return *a;
}
