#define _part_of_kernel
#include <kernel/kernel.h>
#include <kernel/timer.h>
#include <stdio.h>
#define internal
#include "acpi.h"

uint16 SLP_TYPa=0,SLP_TYPb=0;
uint16 SLP_EN=0;uint8 SCI_EN=0;
 char *ssd_tables[]=
 {
	 "APIC","BERT","FACP","DSDT",
	 "ECDT","EINJ","ERST","CPEP",
	 "FACS","HEST","MSCT","MPST",
	 "OEMx","PMTT","PSDT","RASF",
	 "SBST","SLIT","SRAT","SSDT",
	 "MCFG","MADT",
	 /*"RSDT","XSDT"*/
 };
 
void acpi_init()
{
	int i,j; sdt_header_t *tmp;
	rsdp=acpi_search_rsdp((phys_addr *)0xE0000,(phys_addr *)0xFFFFF);
	if(rsdp){}
	else 
	{
		printf("\n\t No ACPI RSDP signature found between %x -%x",0xE0000,0xFFFFF);
		rsdp=acpi_search_rsdp((phys_addr *)0x0,(phys_addr *)0xFFFFF);
		if(rsdp){}
	}
	printf("\n\t ACPI version: %d",rsdp->revision+1);
	printf(" OEMID : ");
	puts_sl(rsdp->OEMID,6);
	printf(" length : %d " ,rsdp->len);
	if(rsdp->revision==0)
	{
		mprintf(error_text_colour,"\n\t Usupported ACPI Version : Version 1");
		return;
	}
	xsdt=(xsdt_t *)(phys_addr *) _ptr_conv rsdp->xsdt_addr;
	if(bytesum((phys_addr *)_ptr_conv xsdt,xsdt->header.len)==0)
	{
		printf(" XSDT checksum validated\n\t ");
		tmp=acpi_findsdt(xsdt,"MCFG");
		if(tmp)
		{
			printf("MCFG, ");
			mcfg_pci=tmp;
		}
		tmp=acpi_findsdt(xsdt,"MADT");if(tmp)printf("MADT ,");
		for(i=0;i<20;i++)
		{
			tmp=acpi_findsdt(xsdt,ssd_tables[i]);
			if(tmp)
			{
				strncpy(sdtlst.sig[i],tmp->signature,4);
				memcpy(&sdtlst.header[i],tmp,sizeof(sdt_header_t));
				puts_sl(tmp->signature,4);puts(", ");
			}
			if(strncmp(tmp->signature,"FACP",4)==0) 
			 facp=(facp_t *)tmp;
		}
		tmp=acpi_findsdt(xsdt,"DSDT");
		if(!tmp && facp)
		{
			tmp=(sdt_header_t *)facp->DSDT;
			if(bytesum((phys_addr *)_ptr_conv tmp,tmp->len)==0 && strncmp(tmp->signature,"DSDT",4)==0)
			 {
				 for(j=0;j<22;j++)
				 {
					 if(strncmp(ssd_tables[j],"DSDT",4)==0)
					 {
						 strncpy(sdtlst.sig[j],tmp->signature,4);
						 memcpy(&sdtlst.header[j],tmp,sizeof(sdt_header_t));
						 puts_sl(sdtlst.header[j].signature,4);puts(", ");
					 }
				 }
			  }
		 }
		printf(". acpi tables found");
		if(facp)
		{
			if(acpi_parseDSDT())
			{
				puts("\n\t DSDT parsing successful ");
				if(acpi_enable()) puts(" ACPI Enabled");
			}
			else SCI_EN=0;
		}
	}
	return;
}
sdt_header_t *acpi_getsdt(char *sig)
{
	return acpi_findsdt(xsdt,sig);
}

sdt_header_t *acpi_findsdt(xsdt_t *_xsdt, char *signature)
{
	int i=0;sdt_header_t *tmp;
	for(i=0;i<22;i++)
	{
		tmp=(sdt_header_t *)_ptr_conv _xsdt->other_tables[i];
		if(strncmp(tmp->signature,signature,4)==0)
		  if(bytesum((phys_addr *)_ptr_conv tmp,tmp->len)==0)
		    return tmp;				
	}
	return (sdt_header_t *)0;
}
rsdp_desc_t *acpi_search_rsdp(phys_addr *base,phys_addr *end)
{
	rsdp_desc_t *_rsdp;
	if((uint32)base%16)
	 base=(phys_addr*)_aligned_addr((int)(int *)base,16);
	while(base<=end)
	{
		if(!((int)base%16))
		{
			if(strncmp((char *)base,_acpi_rsdp_sig,8)==0)
			{
				_rsdp=(rsdp_desc_t *)base;
			    if((bytesum(base,20)&0xff)==0)
			    {		
					if((bytesum(base+20,16)&0xff)==0)
					 printf("\n \tExtended structure checksum validated");
					return _rsdp;			
				}				
				
			}
		}++base;base=(phys_addr*)_aligned_addr((int)(int *)base,16);
	}
	return (rsdp_desc_t *)0;
}

uint8 acpi_parseDSDT()
{
	char *S5Addr = (char *) facp->DSDT +36; // skip header
	int dsdtlen = *(facp->DSDT+1) -36;
	while(dsdtlen-->0)
	{
		if(strncmp(S5Addr, "_S5_", 4)==0)
		 break;
		S5Addr++;
	}
	if (dsdtlen>0)
	{
		if ( ( *(S5Addr-1) == 0x08 || ( *(S5Addr-2) == 0x08 && *(S5Addr-1) == '\\') ) && *(S5Addr+4) == 0x12 )
		{
			S5Addr += 5;
			S5Addr += ((*S5Addr &0xC0)>>6) +2;   // calculate PkgLength size			
			if(*S5Addr == 0x0A)
			 S5Addr++;   // skip byteprefix
			SLP_TYPa = *(S5Addr)<<10;
			S5Addr++;			
			if (*S5Addr == 0x0A)
			 S5Addr++;   // skip byteprefix			 
			SLP_TYPb = *(S5Addr)<<10;
			SLP_EN=1<<13;
			SCI_EN=1;
			return 1;			
		 }
	 }
	 return 0;
}
uint32 bytesum(phys_addr *base, size_t size)
{
	char c=0,*ptr; uint32 i=0;
	ptr=(char *)base;
	for(i=0;i<size;i++)c+=*ptr++;
	return c;
}
extern void acpiPowerOff();
uint8 acpi_poweroff()
{
	//if(SCI_EN==0) return 0;
	acpi_enable();
	outw((uint32) *facp->PM1a_CNT_BLK,SLP_TYPa|SLP_EN);
    if(facp->PM1b_CNT_BLK)
      outw((uint32)*facp->PM1b_CNT_BLK,SLP_TYPb|SLP_EN);
    mprintf(error_text_colour,"\n\t ACPI Power Off Failed! ");
    return 0;
}

uint8 acpi_enable()
{
   // check if acpi is enabled
   if ((inw((unsigned int)facp->PM1a_CNT_BLK)&SCI_EN)== 0)
   {
      // check if acpi can be enabled
      if (facp->SMI_CMD!=0&&facp->ACPI_ENABLE!=0)
      {
         outb((unsigned int)facp->SMI_CMD,facp->ACPI_ENABLE); // send acpi enable command
         int i;
         for (i=0; i<300; i++ )
         {
            if((inw((unsigned int)facp->PM1a_CNT_BLK)&SCI_EN)==1)
              break;
            sleep(10);
         }
         if(facp->PM1b_CNT_BLK!=0)
            for(;i<300;i++ )
            {
               if((inw((unsigned int)facp->PM1b_CNT_BLK)&SCI_EN)==1)
                 break;
               sleep(10);
            }
         if (i<300)return 1;
         else return 0;         
      }
      else return 0;      
   }
   else return 1;
   
}
