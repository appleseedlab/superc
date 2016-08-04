#define F(x) 2*x

int main() {

  F(
#ifdef A
a
#else
b
#endif
    );

}
