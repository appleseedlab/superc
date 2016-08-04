/* Test for execution character set encoding errors.
   If we ever get a good way to test error recovery
   the string "foobar" should be translated.  */
/* check the first error */
/* {{ dg-checkwhat "c-parser" }} */
/* {{ dg-preprocess "Need preprocessing" }} */
asm (not_a_string); /* {{ dg-error "expected" }} */
char x[] = "foobar";

void foo (void)
{
  char *y;
  asm (not_a_string2); 

#define FOO "walrus"
  y = FOO;
}
