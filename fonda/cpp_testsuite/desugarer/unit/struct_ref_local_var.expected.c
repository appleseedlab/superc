struct evp_md_ctx_st;
struct evp_md_ctx_st *EVP_MD_CTX_new(void);

void test_function_1() {
	struct evp_md_ctx_st *mdctx;
	mdctx = EVP_MD_CTX_new();
}
