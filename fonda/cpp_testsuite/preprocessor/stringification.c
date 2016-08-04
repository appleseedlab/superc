#define F(x) printf(#x)
#define G(x) F(x)

#ifdef A
#define M hello world
#else
#define M message
#endif

int main() {
  G(M);
}

