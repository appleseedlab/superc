#define F(x) (x)*func_def

#ifdef FUNCTION
#elif defined UNDEF
#undef F
#elif defined OBJECT
#define F object_def
#endif

F(argument)


