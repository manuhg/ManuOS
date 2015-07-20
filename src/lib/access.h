#ifndef _naccess

#ifdef Private
#undef Private
#endif
#define Private
#ifdef Public
#undef Public
#endif
#ifndef internal 
#define Public extern
#else
#define Public 
#endif

#endif
