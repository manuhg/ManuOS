#include <stdio.h>
#define internal 
#include "interrupts.h"

#define irq0_int 0x20
#define irq8_int 0x28
//#define enable_proceedings
#define idt_len 256
#define gdt_len 5
gdt_entry_t GDT[gdt_len];
gdt_ptr_t gdt_ptr;
idt_entry_t IDT[idt_len];
idt_ptr_t idt_ptr;

isr_t ihandlers[16+53];
//int gpfs=0;
/*
void init_idt_gdt()
{
	init_gdt();
	init_idt();
	set_irq_handler(1,irq1_keyb);
}
*/
static void init_gdt()
{
	
	
	gdt_ptr.limit=(sizeof(gdt_entry_t)*gdt_len)-1;
	gdt_ptr.base=(uint32)&GDT;
	#ifdef enable_proceedings
	mprintf(special_text_colour,"\n Initiating GDT");
	printf("\n\t setting 0-4 gates of GDT");
	#endif
	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment
	gdt_set_2((uint32)&gdt_ptr);
	
	#ifdef enable_proceedings
	printf("\n\t successfully set 0-4 gates of GDT");
	mprintf(_colour(_brt_yellow,_black),"\n GDT initialised : 5 entries");
	#endif
}

static void gdt_set_gate(int pos,uint32 base,uint32 limit,uint8 access,uint8 granularity)
{
	GDT[pos].base_low=(base&0xffff);  //first 16 bits
	GDT[pos].base_middle=(base>>16)&0xff; //next 8 bits
	GDT[pos].base_high=(base>>24)&0xff;//last 8 bits
	
	GDT[pos].limit_low=(limit&0xffff);
	GDT[pos].granularity=(limit>>16)&0x0f;
	GDT[pos].granularity|= granularity&0xf0;
	GDT[pos].access=access;		
}



static void init_idt()
{
	char a=0;
	#ifdef enable_proceedings
	printf("\n Initiating IDT");
	#endif
	idt_ptr.limit=(sizeof(idt_entry_t)*idt_len)-1;
	idt_ptr.base=(uint32)&IDT;
	
	memset(&IDT,0,sizeof(idt_entry_t)*idt_len);
	#ifdef enable_proceedings
	printf("\n\t setting 0-31 gates of IDT");
	#endif
	idt_set_gate( 0, (uint32)isr_0 , 0x08, 0x8E);
	idt_set_gate( 1, (uint32)isr_1 , 0x08, 0x8E);
	idt_set_gate( 2, (uint32)isr_2 , 0x08, 0x8E);
	idt_set_gate( 3, (uint32)isr_3 , 0x08, 0x8E);
	idt_set_gate( 4, (uint32)isr_4 , 0x08, 0x8E);
	idt_set_gate( 5, (uint32)isr_5 , 0x08, 0x8E);
	idt_set_gate( 6, (uint32)isr_6 , 0x08, 0x8E);
	idt_set_gate( 7, (uint32)isr_7 , 0x08, 0x8E);
	idt_set_gate( 8, (uint32)isr_8 , 0x08, 0x8E);
	idt_set_gate( 9, (uint32)isr_9 , 0x08, 0x8E);
	idt_set_gate( 10, (uint32)isr_10 , 0x08, 0x8E);
	idt_set_gate( 11, (uint32)isr_11 , 0x08, 0x8E);
	idt_set_gate( 12, (uint32)isr_12 , 0x08, 0x8E);
	idt_set_gate( 13, (uint32)isr_13 , 0x08, 0x8E);
	idt_set_gate( 14, (uint32)isr_14 , 0x08, 0x8E);
	idt_set_gate( 15, (uint32)isr_15 , 0x08, 0x8E);
	idt_set_gate( 16, (uint32)isr_16 , 0x08, 0x8E);
	idt_set_gate( 17, (uint32)isr_17 , 0x08, 0x8E);
	idt_set_gate( 18, (uint32)isr_18 , 0x08, 0x8E);
	idt_set_gate( 19, (uint32)isr_19 , 0x08, 0x8E);
	idt_set_gate( 20, (uint32)isr_20 , 0x08, 0x8E);
	idt_set_gate( 21, (uint32)isr_21 , 0x08, 0x8E);
	idt_set_gate( 22, (uint32)isr_22 , 0x08, 0x8E);
	idt_set_gate( 23, (uint32)isr_23 , 0x08, 0x8E);
	idt_set_gate( 24, (uint32)isr_24 , 0x08, 0x8E);
	idt_set_gate( 25, (uint32)isr_25 , 0x08, 0x8E);
	idt_set_gate( 26, (uint32)isr_26 , 0x08, 0x8E);
	idt_set_gate( 27, (uint32)isr_27 , 0x08, 0x8E);
	idt_set_gate( 28, (uint32)isr_28 , 0x08, 0x8E);
	idt_set_gate( 29, (uint32)isr_29 , 0x08, 0x8E);
	idt_set_gate( 30, (uint32)isr_30 , 0x08, 0x8E);
	idt_set_gate( 31, (uint32)isr_31 , 0x08, 0x8E);
	#ifdef enable_proceedings
    printf("\n\t successfull in setting 0-31 gates of IDT");
		
	printf("\n\t setting 32-47 gates of IDT");
	#endif
	idt_set_gate( 32, (uint32)irq_0 , 0x08, 0x8E);
	idt_set_gate( 33, (uint32)irq_1 , 0x08, 0x8E);
	idt_set_gate( 34, (uint32)irq_2 , 0x08, 0x8E);
	idt_set_gate( 35, (uint32)irq_3 , 0x08, 0x8E);
	idt_set_gate( 36, (uint32)irq_4 , 0x08, 0x8E);
	idt_set_gate( 37, (uint32)irq_5 , 0x08, 0x8E);
	idt_set_gate( 38, (uint32)irq_6 , 0x08, 0x8E);
	idt_set_gate( 39, (uint32)irq_7 , 0x08, 0x8E);
	idt_set_gate( 40, (uint32)irq_8 , 0x08, 0x8E);
	idt_set_gate( 41, (uint32)irq_9 , 0x08, 0x8E);
	idt_set_gate( 42, (uint32)irq_10, 0x08, 0x8E);
	idt_set_gate( 43, (uint32)irq_11, 0x08, 0x8E);
	idt_set_gate( 44, (uint32)irq_12, 0x08, 0x8E);
	idt_set_gate( 45, (uint32)irq_13, 0x08, 0x8E);
	idt_set_gate( 46, (uint32)irq_14, 0x08, 0x8E);
	idt_set_gate( 47, (uint32)irq_15, 0x08, 0x8E);
	
	idt_set_gate( 48, (uint32)irq_48, 0x08, 0x8E);
	idt_set_gate( 49, (uint32)irq_49, 0x08, 0x8E);
	idt_set_gate( 50, (uint32)irq_50, 0x08, 0x8E);	
	idt_set_gate( 51, (uint32)irq_51, 0x08, 0x8E);
	idt_set_gate( 52, (uint32)irq_52, 0x08, 0x8E);
	idt_set_gate( 53, (uint32)irq_53, 0x08, 0x8E);
	idt_set_gate( 54, (uint32)irq_54, 0x08, 0x8E);
	idt_set_gate( 55, (uint32)irq_55, 0x08, 0x8E);
	idt_set_gate( 56, (uint32)irq_56, 0x08, 0x8E);
	idt_set_gate( 57, (uint32)irq_57, 0x08, 0x8E);
	idt_set_gate( 58, (uint32)irq_58, 0x08, 0x8E);
	idt_set_gate( 59, (uint32)irq_59, 0x08, 0x8E);
	idt_set_gate( 60, (uint32)irq_60, 0x08, 0x8E);	
	idt_set_gate( 61, (uint32)irq_61, 0x08, 0x8E);
	idt_set_gate( 62, (uint32)irq_62, 0x08, 0x8E);
	idt_set_gate( 63, (uint32)irq_63, 0x08, 0x8E);
	idt_set_gate( 64, (uint32)irq_64, 0x08, 0x8E);
	idt_set_gate( 65, (uint32)irq_65, 0x08, 0x8E);
	idt_set_gate( 66, (uint32)irq_66, 0x08, 0x8E);
	idt_set_gate( 66, (uint32)irq_66, 0x08, 0x8E);
	idt_set_gate( 68, (uint32)irq_68, 0x08, 0x8E);
	idt_set_gate( 69, (uint32)irq_69, 0x08, 0x8E);
	idt_set_gate( 70, (uint32)irq_70, 0x08, 0x8E);
	idt_set_gate( 71, (uint32)irq_71, 0x08, 0x8E);
	idt_set_gate( 72, (uint32)irq_72, 0x08, 0x8E);
	idt_set_gate( 73, (uint32)irq_73, 0x08, 0x8E);
	idt_set_gate( 74, (uint32)irq_74, 0x08, 0x8E);
	idt_set_gate( 75, (uint32)irq_75, 0x08, 0x8E);
	idt_set_gate( 76, (uint32)irq_76, 0x08, 0x8E);
	idt_set_gate( 77, (uint32)irq_77, 0x08, 0x8E);
	idt_set_gate( 78, (uint32)irq_78, 0x08, 0x8E);
	idt_set_gate( 79, (uint32)irq_79, 0x08, 0x8E);
	idt_set_gate( 80, (uint32)irq_80, 0x08, 0x8E);
	idt_set_gate( 81, (uint32)irq_81, 0x08, 0x8E);
	idt_set_gate( 82, (uint32)irq_82, 0x08, 0x8E);
	idt_set_gate( 83, (uint32)irq_83, 0x08, 0x8E);
	idt_set_gate( 84, (uint32)irq_84, 0x08, 0x8E);
	idt_set_gate( 85, (uint32)irq_85, 0x08, 0x8E);
	idt_set_gate( 86, (uint32)irq_86, 0x08, 0x8E);
	idt_set_gate( 87, (uint32)irq_87, 0x08, 0x8E);
	idt_set_gate( 88, (uint32)irq_88, 0x08, 0x8E);
	idt_set_gate( 89, (uint32)irq_89, 0x08, 0x8E);
	idt_set_gate( 90, (uint32)irq_90, 0x08, 0x8E);
	idt_set_gate( 91, (uint32)irq_91, 0x08, 0x8E);
	idt_set_gate( 92, (uint32)irq_92, 0x08, 0x8E);
	idt_set_gate( 93, (uint32)irq_93, 0x08, 0x8E);
	idt_set_gate( 94, (uint32)irq_94, 0x08, 0x8E);
	idt_set_gate( 95, (uint32)irq_95, 0x08, 0x8E);
	idt_set_gate( 96, (uint32)irq_96, 0x08, 0x8E);
	idt_set_gate( 97, (uint32)irq_97, 0x08, 0x8E);
	idt_set_gate( 98, (uint32)irq_98, 0x08, 0x8E);
	idt_set_gate( 99, (uint32)irq_99, 0x08, 0x8E);
	idt_set_gate( 100, (uint32)irq_100, 0x08, 0x8E);
	
	idt_set_gate( 101, (uint32)irq_100above, 0x08, 0x8E);
	
	init_dummy_int(&IDT[101],101);
	v86_init();
	
	#ifdef enable_proceedings
	printf("\n\t successfull in setting 32-47 gates of IDT");
	printf("\n\t successfull in setting 48-101 gates of IDT");	
	printf("\n\t Remapping IRQ 0-15 from 0x0-0xF to 0x20-0x2F");
	#endif
	
	remap_irqs();
	idt_set_2((uint32)&idt_ptr);
	
	#ifdef enable_proceedings
	printf("\n\t IRQ remapping successful");	
	printf("\n\t 102 entries done");
	printf("\n\t 154 null entries done");
    mprintf( _colour(_brt_yellow,_black),"\n IDT initialised :256 entries done");
	#endif
	
	while(a<=15)
	unmask_irq(a++);
}

void init_dummy_int(idt_entry_t *dummy_int, int from)
{
	while(from<256)
	{
		IDT[from++]=*dummy_int;				
	}
}
static void idt_set_gate(uint8 pos,uint32 base,uint16 sel,uint8 flags)
{
	IDT[pos].base_low=base&0xffff;
	IDT[pos].base_high=(base>>16)&0xffff;
	
	IDT[pos].selector=sel;
	IDT[pos].zero=0;
	
	IDT[pos].flags=flags;
}

void mask_irq(char irq)
{
	if(irq>=8)
	{
		irq-=8;
		out(0xa1,in(0xa1)|(1<<irq));
	}
	else
	 outb(0x20,inb(0x20)|(1<<irq));
}
void unmask_irq(char irq)
{
	if(irq>=8)
	{
		irq-=8;
		out(0xa1,in(0xa1)&~(1<<irq));
	}
	else
	 outb(0x20,inb(0x20)&~(1<<irq));
}

void remap_irqs()
{
	outportb(0x20, 0x11);
	outportb(0xA0, 0x11);
	outportb(0x21, irq0_int);
	outportb(0xA1, irq8_int);
	outportb(0x21, 0x04);
	outportb(0xA1, 0x02);
	outportb(0x21, 0x01);
	outportb(0xA1, 0x01);
	outportb(0x21, ~0x03);
	outportb(0xA1, ~0x00);
}

/*
void interrupt_handler(regs_t regs)
{
	if(ihandlers[regs.int_no]!=0)
	{
		isr_t ihandler=ihandlers[regs.int_no];
		ihandler(regs);
		//print_regs(regs);
	}
	else
	{
		printf(" IRQ ");
		_print_long(regs.int_no); //printf(newline);
		//print_regs(regs);		
	}
	send_EOI(regs.int_no);	
}*/

 void interrupt_handler(regs_t *regs)
{
	send_EOI(regs->int_no);	
	if(ihandlers[regs->int_no])
	{
		isr_t ihandler=ihandlers[regs->int_no];
		ihandler(regs);
		//print_regs(regs);
	}
	else
	{
		printf(" IRQ ");
		if(regs->int_no==101)
		  printf("100above");
		else
		  printf("%d",regs->int_no);
		//outbyte('\n');
		//print_regs(regs);	
	}
	
}

void print_regs(regs_t *r)
{
	outbyte('\n');
	printf(" %d  ,",r->gs);
	printf(" %d  ,",r->fs);
	printf(" %d  ,",r->es);
	printf(" %d  ,",r->ds);
	printf(" %d  ,",r->edi);
	printf(" %d  ,",r->esi);
	printf(" %d  ,",r->ebp);
	printf(" %d  ,",r->esp);
	printf(" %d  ,",r->ebx);
	printf(" %d  ,",r->edx);
	printf(" %d  ,",r->ecx);
	printf(" %d  ,",r->eax);
	printf(" int_no= %d, ",r->int_no);
	printf(" %d  ,",r->err_code);
	printf(" %d  ,",r->eip);
	printf(" %d  ,",r->cs);
	printf(" %d  ,",r->eflags);
	printf(" %d  ,",r->useresp);
	printf(" %d  ,",r->ss);
}
char *isr_faults[]={" Division By Zero",
    " Debug",
    " Non Maskable Interrupt",
    " Breakpoint",
    " Into Detected Overflow",
    " Out of Bounds",
    " Invalid Opcode",
    " No Coprocessor",

    " Double Fault",
    " Coprocessor Segment Overrun",
    " Bad TSS",
    " Segment Not Present",
    " Stack Fault",
    " General Protection Fault",
    " Page Fault",
    " Unknown Interrupt",

    " Coprocessor Fault",
    " Alignment Check",
    " Machine Check",
    " Reserved",
    " Reserved",
    " Reserved",
    " Reserved",
    " Reserved",

    " Reserved",
    " Reserved",
    " Reserved",
    " Reserved",
    " Reserved",
    " Reserved",
    " Reserved",
    " Reserved"};
    
uint32 fault=0;
void isr_handler(regs_t *regs)
{
	while(1);
	printf("%d",regs->int_no);
	printf(isr_faults[regs->int_no]);
	if(regs->int_no){}
}

void set_irq_handler(int pos, isr_t handler)
{
	ihandlers[pos]=handler;
}
void set_isr_handler(int pos, isr_t handler)
{
	ihandlers[pos]=handler;
}

void send_EOI(int num)
{
	 if(num >= 8)
	  outb(0xA0, 0x20);
	 outb(0x20, 0x20);
}
