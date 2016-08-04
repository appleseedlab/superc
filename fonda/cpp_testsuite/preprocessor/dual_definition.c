#ifdef FUNCTION
#define F(x) (x) * func_def
#elif defined OBJECT
#define F object_def
#endif

F(argument)

