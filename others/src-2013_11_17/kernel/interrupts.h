#ifndef interrupts_h
#define interrupts_h
#include <access.h>
/*
#define PIC1 0x20
#define PIC2 0xa1
#define PIC1_data 0x21
#define PIC1_data 0xa1*/

#include <typedefs.h>
#define _keyboard
#define idt_gdt_proto
#define _irqs
#define _isrs
#define _idt
#define _gdt

#define static 
#ifdef idt_gdt_proto

#define _idt
#ifdef _idt
 typedef void (*isr_t)(regs_t *);
 extern void idt_set_1();
 extern void idt_set_ptr(uint32);
   
 Public static void init_idt();
 Private static void idt_set_gate(uint8 pos,uint32 base,uint16 sel,uint8 flags);
 Private void interrupt_handler(regs_t *regs);
 Private void isr_handler(regs_t *regs);
 Public void remap_irqs();
 Public void send_EOI(int num);
 Public void set_irq_handler(int pos, isr_t handler);
 Public void set_isr_handler(int pos, isr_t handler);
 Public void init_dummy_int(idt_entry_t *dummy_int, int from);
 
 Public void print_regs(regs_t *r);
 
 Public void mask_irq(char irq);
 Public void unmask_irq(char irq);
 
 extern void int_cli();
 extern void int_sti(); 
 #ifdef internal
 extern void v86_init();
 #endif
#endif
#define _gdt
#ifdef _gdt
 extern void gdt_set_1();
 extern void gdt_set_ptr(uint32);
 
 Public void intit_idt_gdt();
 Public static void init_gdt();
 Private static void gdt_set_gate(int pos,uint32 base,uint32 limit,uint8 access,uint8 granularity);
#endif
#define _isrs
#ifdef _isrs

  extern void isr_0();
  extern void isr_1();
  extern void isr_2();
  extern void isr_3();
  extern void isr_4();
  extern void isr_5();
  extern void isr_6();
  extern void isr_7();
  extern void isr_8();
  extern void isr_9();
  extern void isr_10();
  extern void isr_11();
  extern void isr_12();
  extern void isr_13();
  extern void isr_14();
  extern void isr_15();
  extern void isr_16();
  extern void isr_17();
  extern void isr_18();
  extern void isr_19();
  extern void isr_20();
  extern void isr_21();
  extern void isr_22();
  extern void isr_23();
  extern void isr_24();
  extern void isr_25();
  extern void isr_26();
  extern void isr_27();
  extern void isr_28();
  extern void isr_29();
  extern void isr_30();
  extern void isr_31();

#endif
#define _irqs
#ifdef _irqs
  extern void irq_0();
  extern void irq_1();
  extern void irq_2();
  extern void irq_3();
  extern void irq_4();
  extern void irq_5();
  extern void irq_6();
  extern void irq_7();
  extern void irq_8();
  extern void irq_9();
  extern void irq_10();
  extern void irq_11();
  extern void irq_12();
  extern void irq_13();
  extern void irq_14();
  extern void irq_15();
  
  extern void irq_48();
  extern void irq_49();
  extern void irq_50();  
  extern void irq_51();
  extern void irq_52();
  extern void irq_53();
  extern void irq_54();
  extern void irq_55();
  extern void irq_56();
  extern void irq_57();
  extern void irq_58();
  extern void irq_59();
  extern void irq_60();  
  extern void irq_61();
  extern void irq_62();
  extern void irq_63();
  extern void irq_64();
  extern void irq_65();
  extern void irq_66();
  extern void irq_67();
  extern void irq_68();
  extern void irq_69();
  extern void irq_70();
  extern void irq_71();
  extern void irq_72();
  extern void irq_73();
  extern void irq_74();
  extern void irq_75();
  extern void irq_76();
  extern void irq_77();
  extern void irq_78();
  extern void irq_79();
  extern void irq_80();
  extern void irq_81();
  extern void irq_82();
  extern void irq_83();
  extern void irq_84();
  extern void irq_85();
  extern void irq_86();
  extern void irq_87();
  extern void irq_88();
  extern void irq_89();
  extern void irq_90();
  extern void irq_91();
  extern void irq_92();
  extern void irq_93();
  extern void irq_94();
  extern void irq_95();
  extern void irq_96();
  extern void irq_97();
  extern void irq_98();
  extern void irq_99();
  extern void irq_100();
  extern void irq_100above();

#endif
#endif

#endif
