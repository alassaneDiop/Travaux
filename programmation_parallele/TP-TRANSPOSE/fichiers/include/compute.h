
#ifndef COMPUTE_IS_DEF
#define COMPUTE_IS_DEF

typedef void (*void_func_t) (void);
typedef int (*int_func_t) (void);

extern void_func_t first_touch [];
extern int_func_t compute [];
extern char *version_name [];
extern unsigned opencl_used [];

extern unsigned version;


#endif
