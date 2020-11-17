struct bignum_st;
struct rsa_st {
  struct bignum_st *e;
};
typedef struct rsa_st RSA;
extern RSA *RSA_new(void);
void _libssh2_rsa_new(RSA *rsa)
{
    struct bignum_st * e;
    rsa = RSA_new();
    (*rsa).e = e;
}
