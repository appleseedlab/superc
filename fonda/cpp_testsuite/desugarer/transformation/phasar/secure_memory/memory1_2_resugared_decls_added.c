#define size_t unsigned int

void OPENSSL_cleanse(void *ptr, size_t len);

void CRYPTO_free(void *ptr, const char *file, int line);

# define OPENSSL_free(buffer) \
        CRYPTO_free(buffer, OPENSSL_FILE, OPENSSL_LINE)

void *CRYPTO_malloc(size_t num, const char *file, int line);

# define OPENSSL_malloc(BUFFER_SIZE) \
        CRYPTO_malloc(BUFFER_SIZE, OPENSSL_FILE, OPENSSL_LINE)

void error(const char *fmt, ...);

int main() {
  #ifdef CONFIG_B
    size_t BUFFER_SIZE = 256;
    unsigned char *buffer = OPENSSL_malloc(BUFFER_SIZE);
    for (size_t i = 0; i < BUFFER_SIZE; ++i) {
      buffer[i] = i;
    }
  #endif

  #ifdef CONFIG_B
   OPENSSL_cleanse(buffer, BUFFER_SIZE);
  #endif
  
   // buffer freed but maybe not cleared
   OPENSSL_free(buffer);
  return 0;
}
