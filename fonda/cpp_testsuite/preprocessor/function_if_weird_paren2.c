#define F(x) x + 1
F(
#ifdef A 
abc )
F( def
#else
ghi
#endif
)
