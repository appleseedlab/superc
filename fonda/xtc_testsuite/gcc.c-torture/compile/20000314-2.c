/* test analyzer, expected to pass */
// {{ dg-preprocess "Need preprocessing" }}
extern void malloc(__SIZE_TYPE__ size); 

toto()
{
    malloc(100);
}
