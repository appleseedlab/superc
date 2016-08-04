// {{ dg-checkwhat "c-analyzer" }}

extern char *bar;

extern void foo (void)
{
   char str[]="abcdefghijklmnopqrstuvwxyz";
   bar = str;
}
