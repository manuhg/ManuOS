#ifndef v86_h
#define v86_h

 #include <access.h>
 typedef void (*v86_task)(void); 	

struct DWORDREGS {
  unsigned long edi;
  unsigned long esi;
  unsigned long ebp;
  unsigned long cflag;
  unsigned long ebx;
  unsigned long edx;
  unsigned long ecx;
  unsigned long eax;
  unsigned short eflags;
};

struct DWORDREGS_W {
  unsigned long di;
  unsigned long si;
  unsigned long bp;
  unsigned long cflag;
  unsigned long bx;
  unsigned long dx;
  unsigned long cx;
  unsigned long ax;
  unsigned short flags;
};

struct WORDREGS {
  unsigned short di, _upper_di;
  unsigned short si, _upper_si;
  unsigned short bp, _upper_bp;
  unsigned short cflag, _upper_cflag;
  unsigned short bx, _upper_bx;
  unsigned short dx, _upper_dx;
  unsigned short cx, _upper_cx;
  unsigned short ax, _upper_ax;
  unsigned short flags;
};

struct BYTEREGS {
  unsigned short di, _upper_di;
  unsigned short si, _upper_si;
  unsigned short bp, _upper_bp;
  unsigned long cflag;
  unsigned char bl;
  unsigned char bh;
  unsigned short _upper_bx;
  unsigned char dl;
  unsigned char dh;
  unsigned short _upper_dx;
  unsigned char cl;
  unsigned char ch;
  unsigned short _upper_cx;
  unsigned char al;
  unsigned char ah;
  unsigned short _upper_ax;
  unsigned short flags;
};



union REGS {/*
  struct DWORDREGS d;
#ifdef _NAIVE_DOS_REGS
  struct WORDREGS x;
#else
#ifdef _BORLAND_DOS_REGS
  struct DWORDREGS x;
#else
  struct DWORDREGS_W x;
#endif
#endif*/
  struct WORDREGS w;
  struct BYTEREGS h;
};

 
 extern void uirq_50();
 extern void uirq_51();
 extern void uirq_48();
 extern short int86_asm( short int_no, const union REGS *in_regs, union REGS *out_regs );

 //extern void v86_set_vm_bit();
 Public short int86( short int_no, const union REGS *in_regs, union REGS *out_regs );
 Public void v86_set_vmbit(regs_t *r);
 Public void v86_switchv86(v86_task task);
 Public void v86_clear_vmbit(regs_t *r);
 Public void v86_init();
 Public void v86_test();
 
 Public void v86_set_vmbit_t(regs_t *r);

#endif
