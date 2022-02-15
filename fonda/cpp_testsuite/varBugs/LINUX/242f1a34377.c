#ifdef CONFIG_CRYPTO_BLKCIPHER
void *crypto_alloc_ablkcipher()
{
  return (void*)0;
}
#endif

#ifdef CONFIG_CRYPTO_TEST
static void test_cipher()
{
  crypto_alloc_ablkcipher();
}
#endif

int main(int argc, char** argv)
{
  #ifdef CONFIG_CRYPTO_TEST
  test_cipher();
  #endif
}
