typedef union {
  char__mbstate8[128];
  long long_mbstateL;/* for alignment */
} __mbstate_t;

typedef __mbstate_t__darwin_mbstate_t;/* mbstate_t */

#if defined(__GNUC__) && defined(__PTRDIFF_TYPE__)
typedef __PTRDIFF_TYPE____darwin_ptrdiff_t;/* ptr1 - ptr2 */
#else
typedef int__darwin_ptrdiff_t;/* ptr1 - ptr2 */
#endif /* __GNUC__ */

