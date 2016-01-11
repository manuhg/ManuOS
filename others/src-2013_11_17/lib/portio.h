#ifndef ports_h
#define ports_h
 #include <defines.h>
 #include <types.h>

 #define out(port,data) outb(port,data)
 #define in(port) inb(port)
 
 #define inportb(port) inb(port) 
 #define inportw(port) inw(port)
 #define inportl(port) inl(port)

 #define outportb(port,data) outb(port,data)
 #define outportw(port,data) outw(port,data)
 #define outportl(port,data) outl(port,data) 
 
 #include <access.h>
 
 extern void insl_(uint16 port, void *buf, size_t count);
 Public uint8  inb(uint16 _port);
 Public uint16 inw(uint16 _port);
 Public uint32 inl(uint16 _port);
 
 Public void outb(uint16 _port, uchar _data);
 Public void outw(uint16 _port, uint16 _data);
 Public void outl(uint16 _port, uint32 _data);
#endif
