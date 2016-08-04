/* {{ dg-checkwhat "c-parser" }} */
typedef enum
{
  a = (X) 0,	/*  {{ dg-error "expected" }} */
  b
} c;

typedef enum
{
  d = (X) 0	
} e;
