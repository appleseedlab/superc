/* PR c/5503
   Test whether argument checking is done for fputs, bzero and bcmp.  */
// {{ dg-preprocess "Need preprocessing" }}
typedef struct { int i; } FILE;
typedef __SIZE_TYPE__ size_t;
int fputs (const char *, FILE *);
void bzero (void *, size_t);
int bcmp (const void *, const void *, size_t);

char buf[32];
FILE *f;
// {{ dg-checkwhat "c-analyzer" }}
int main ()
{
  fputs ("foo");		 // {{ dg-error "too few" }} 
  fputs ("foo", "bar", "baz");	 // {{ dg-error "too many" }} 
  fputs (21,                     // {{ dg-warning "passing argument 1" }} 
            43);                 // {{ dg-warning "makes pointer from integer" 17 }}
  bzero (buf);			 // {{ dg-error "too few" }}
  bzero (21);			 // {{ dg-error "too few" }}
  bcmp (buf, buf + 16);		 // {{ dg-error "too few" }} 
  bcmp (21);			 // {{ dg-error "too few" }}
  fputs ("foo", f);
  bzero (buf, 32);
  bcmp (buf, buf + 16, 16);
  return 0;
}

// {{ dg-warning "incompatible pointer types" 16 }}
// {{ dg-warning "makes pointer from integer" 20 }}
// {{ dg-warning "makes pointer from integer" 22 }}
