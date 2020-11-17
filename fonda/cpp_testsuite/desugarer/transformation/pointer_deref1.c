struct bignum_st;
struct rsa_st {
  struct bignum_st *e;
};
extern struct rsa_st **RSA_new(void);
void _libssh2_rsa_new(struct rsa_st **rsa)
{
    struct bignum_st * e;
    rsa = RSA_new();
    (**rsa).e;
}
