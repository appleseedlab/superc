/* Test for bad uses of 'void' in parameter lists.  */
/* Origin: Joseph Myers <jsm28@cam.ac.uk> */
/* {{ dg-checkwhat "c-analyzer" }} */
typedef const void cv;
typedef volatile void vv;

void foo0 (const void);       /* {{ dg-error "'void' as only parameter" }} */
void foo0a (cv);              /* {{ dg-error "'void' as only parameter" }} */ 
void foo1 (volatile void);    /* {{ dg-error "'void' as only parameter" }} */ 
void foo1a (vv);              /* {{ dg-error "'void' as only parameter" }} */ 
void foo2 (register void);    /* {{ dg-error "'void' as only parameter" }} */ 

void bar0 (const void) { }    /* {{ dg-error "'void' as only parameter" }} */
void bar0a (cv) { }           /* {{ dg-error "'void' as only parameter" }} */ 
void bar1 (volatile void) { } /* {{ dg-error "'void' as only parameter" }} */ 
void bar1a (vv) { }           /* {{ dg-error "'void' as only parameter" }} */ 
void bar2 (register void) { } /* {{ dg-error "'void' as only parameter" }} */ 
