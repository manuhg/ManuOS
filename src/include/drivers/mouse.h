#ifndef mouse_h
#define mouse_h
 #include <access.h>
 Public void mouse_handler(regs_t *r);
 Public void mouse_wait(byte a_type);
 Public byte mouse_read();
 Public void init_mouse();
#endif
