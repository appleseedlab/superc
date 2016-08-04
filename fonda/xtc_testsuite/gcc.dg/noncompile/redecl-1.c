/* Copyright 2000  Free Software Foundation */
/* by Alexandre Oliva  <aoliva@redhat.com> */
/* {{ dg-checkwhat "c-analyzer" }} */
int
foo ()
{
  int bar;          /* {{ dg-error "previous declaration" }} */ 
  volatile int bar; /* {{ dg-error "bar" }} */ 
}
