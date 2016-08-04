//simplified example of
//http://lxr.linux.no/#linux+v2.6.38/include/asm-generic/memory_model.h#L72
//#define page_to_pfn __page_to_pfn
//used in
//http://lxr.linux.no/#linux+v2.6.38/include/linux/mm.h#L712


#ifdef A
#define cpu __cpu
#endif

#define __cpu(x) 1 * x
//#define __cpu(y) y + 1

int x = cpu

#ifdef B
(2)
#else
(3)
#endif

;
