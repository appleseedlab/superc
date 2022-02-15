typedef long unsigned int size_t;
void *malloc(size_t n);
struct evp_cipher_ctx_st;
typedef struct evp_cipher_ctx_st EVP_CIPHER_CTX;
char *DoEncryption(EVP_CIPHER_CTX *CTX, const char *Msg, size_t MsgLen) {
  malloc((size_t) 1);
  char *Buffer = malloc((MsgLen + 16) % -16);
  return Buffer;
}
