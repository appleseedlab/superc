/* PR 16216 */
/* {{ dg-checkwhat "c-analyzer" }} */
void func()
{
        const char *pek; int i;
        pek=__builtin_va_arg(ap,const char*);	/* {{ dg-error "" }} */
}
