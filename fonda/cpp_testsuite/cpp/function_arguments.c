//3.3 Macro arguments
//arguments are valid C identifiers separated by commas and whitespace
#define min(X, Y) ((X) < (Y) ? (X) : (Y))
x = min (a, b);
y = min(1 , 2 );
z = min(a + 28, *p);
//NOTE: cpp adds extra space before actual parameters in expansion, but gcc doesn't.
//leading and trailing whitespace in actual parameters in call is removed, which cpp does correctly

//parentheses in arguments must balance and they prevent commas separating arguments, but not brackets or braces mustn't and don't
uhoh = min(array[x = y, x + 1]);
whoa = min(array[(x = y, x + 1)], 99);

//arguments are first completely macro-expanded
//after substition, they complete text is scanned again for macros to expand including arguments
min (min (a, b), c)

//empty arguments to macros are valid
min(, b)
min(a, )
min(,)
min((,),)

//macro arguments inside string literals not replaced by actual arguments
#define foostr(x) x, "x"
foostr(bar)
