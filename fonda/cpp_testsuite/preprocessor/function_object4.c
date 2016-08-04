//simplified example of
//http://lxr.linux.no/#linux+v2.6.38/include/asm-generic/memory_model.h#L72
//#define page_to_pfn __page_to_pfn
//used in
//http://lxr.linux.no/#linux+v2.6.38/include/linux/mm.h#L712


#ifdef A
#define cpu __cpu1
#elif B
#define cpu __cpu2
#endif

#define __cpu1(x) 1 * x
#define __cpu2(y) y + 1

int x = cpu(2);
