struct evp_md_ctx_st;
struct evp_md_ctx_st *EVP_MD_CTX_new(void);

#ifdef OQS_USE_SHA2_OPENSSL
void test_function() {
	struct evp_md_ctx_st *mdctx;
	mdctx = EVP_MD_CTX_new();
}
#endif
