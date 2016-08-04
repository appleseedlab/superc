/* {{ dg-checkwhat "c-analyzer" }} */
struct a
{ double a, b, c; };

struct b
{
  struct a arr[6];
};

static struct b a_b =
{
  {0,0,0},
  {0,0,0},	/* {{ dg-error "extra brace group" }} */
  {0,0,0},	/* {{ dg-error "extra brace group" }} */
  {0,0,0},	/* {{ dg-error "extra brace group" }} */
  {0,0,0},	/* {{ dg-error "extra brace group" }} */
  {0,0,0},	/* {{ dg-error "extra brace group" }} */
};

/* {{ dg-warning "excess elements" 13 }} */
