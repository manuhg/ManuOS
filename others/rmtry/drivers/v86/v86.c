#include <typedefs.h>
#include <kernel/interrupts.h>
#include <stdio.h>
#define internal
#include "v86.h"


extern void set_vdio_mode();
short int86( short int_no, const union REGS *in_regs, union REGS *out_regs )
{
	short a;a=0;
	asm("int $50");
	//a= int86_asm(int_no,in_regs,out_regs);
	if(in_regs && out_regs && int_no){}
	set_vdio_mode();
	asm("int $51");	
	return a;
}

void v86_test()
{
	union REGS i,o;
	i.h.ah=0x00;
	i.h.al=0x13;
	int86(0x10,&i,&o);
}

void v86_set_vmbit(regs_t *r)
{
	int _eflags;
	if(r->int_no==50)
	{
		_eflags=r->eflags;
		_eflags|=2;//10b
		r->eflags=_eflags;
		_printf("eflags set");
    }
}

void v86_set_vmbit_t(regs_t *r)
{
	int _eflags;_printf("eflags setting..");
	if(r->int_no==48)
	{
		_eflags=r->eflags;
		_eflags|=2;//10b
		r->eflags=_eflags;
		_print_int(_eflags);
		_printf("eflags set_t");
    }
    else
     print_regs(r);
    
}

void v86_clear_vmbit(regs_t *r)
{
	int _eflags;
	if(r->int_no==51)
	{
		_eflags=r->eflags;
		_eflags|=0;
		r->eflags=_eflags;
		_printf("eflags clear");
    }
}

void v86_switchv86(v86_task task)
{
	asm("int $50");
	task();
	asm("int $51");	
	
}

void v86_init()
{
	set_irq_handler(48,v86_set_vmbit_t);
	set_irq_handler(50,v86_set_vmbit);
	set_irq_handler(51,v86_clear_vmbit);
	//idt_set_gate(51,(uint32)uirq_51,0x08,0x8E);
}
