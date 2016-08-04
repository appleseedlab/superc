//M is free, define it as 1 or 0
#define F() M
#define RPAREN )
#define PART F(

#if PART )
true1
#else
false1
#endif

#if PART RPAREN
true2
#else
false2
#endif

//normal
F(     )

//try 1
PART )

//try 2
PART RPAREN )

//try 3
PART RPAREN

