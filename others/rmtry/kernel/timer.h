#ifndef timer_h
#define timer_h
 #include <access.h>
 #include <typedefs.h>
 #define timer_secs(ticks) (ticks/timer_freq) 
 Public void timer_pic_handler(regs_t *regs);
 Public void timer_pic_init(uint32 frequency);
 
 Public int secDelay(unsigned int secs);
 Public void milliDelay(unsigned long millisecs);
  
#endif
