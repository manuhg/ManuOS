#include "functions.h"
#include <string.h>
#include <types.h>

void print_int(int a, int colour)
{
	int i=1,len;
	if(a<0)
	{
		outbyte('-');
		a*=-1;
	}
	len=intlen(a);
	while(i<=len)
	{
		outbyte(intat(a,i)+48);
		_outc_bcg_pos(colour,get_cursor_pos());
		i++;
	}
}

void _print_int(int a)
{
	print_int(a,screen_bcg_colour);
}

void _print_long(long a)
{
	long tmp=0,aa=0;
	tmp=a;
	while(tmp)
	{
		aa=(aa*10)+(tmp%10);
		tmp=tmp/10;
	}
	while(aa)
	{
		outbyte((aa%10)+48);
		aa=aa/10;
	}
}
char hex[16]={"0123456789ABCDEF"};
void _print_hex(uint64_t a)
{
	uint8 rshift=64;
	_printf("0x");
	if(!a)
	{
		outbyte('0');
		return;
	}	
	while(rshift)
	{
		if(!((a>>(rshift-4))))
		  rshift-=4;
		else
		  break;
	}
	while(rshift)
	{
		rshift-=4;
		outbyte(hex[(a>>rshift)&0xf]);
	}
} 


void gtkey()
{
	if(getch()){}
}

void gtkey_echo()
{
	_printf("\nPress any key to continue\r");
	if(getch()){}
	_printf("                            \r");
	
}
int leap(int yr) 
{   
	int lpyr=0;//lpyr is leap year. if it is 0 it means it is not leap year if it is 1 or more than 0 then it is leap year 
	if(yr%4==0) 
	{ 
		if(yr%100==0) 
		{ 
			if(yr%400==0) 
			{ 
				lpyr=1; 
			} 
			else 
			{
				lpyr=0; 
			} 
		} 
		else 
		{ 
			lpyr=1; 
		} 
	} 
	else 
	{ 
		lpyr=0; 
	} 
	return lpyr; 
}

binary tobinary(sbinary val)
{
	binary a; sbinary temp;
	int i;
	a=0;
	temp=val;i=0;
	while(temp>0)
	{
		if(temp>1)
		{
			a=a+(binary)(power(10,i)*(temp%2)); //printf("\n\t%d\n",temp%2);
		    temp/=2;
		   
		}
		else if(temp==1)
		 {
			 a+=(binary)power(10,i)*1; //printf("\n\t%d\n",temp);
			 temp-=1;
		 }
		 i+=1;		
	}
	
	//printf("\n\n\t%u\n",a);
	return a;
}

sbinary frombinary(binary a) 
{
	sbinary aa;int i,len;
	aa=0;i=0;
	len=binlen(a);
	while(i<len)
	{
		aa+=(sbinary)power(2,i)*(a%10);//printf("\n\ta%%10=%d aa=sbin_fc i=%d",(a%10),aa,i);
		a/=10;
		i+=1;		
	}
	return aa;
}


	
int binlen(binary a) 
{ 
	int temp,num,len;boolean agn=true;//agn means again 
	num=a;len=0;
	while(agn) 
	{ 
		len+=1;
		temp=(int)(num/10);  
		num=temp;
		if(temp!=0) 
		 {agn=true;} 
		else
		 {agn=false;} 
	} 
	return len; 
}
	
void thanks() 
{ 
	_printf("\n\n================================================================================");
	_printf("\nThank you\nManu Hegde\nhegde1997@gmail.com\n\nPress any key to exit");
    if(getch()) 
	{
	}
}

void e_line()
{_printf("================================================================================");}




#ifndef nint 

int strtoint(char *str)// works correctly // scan and put into ineger only till a non integer occurs
{ 
	int num;int ic;num=0;
	ic=*str-48; 
    num=ic;
	str+=1;
	while(*str!='\0') 
	{		
		if(isnum(*str)) 
		{ 
			ic=*str-48; 
			iappend(&num,ic);			
		}
		else
			break;
		
		str+=1;
	} 
	
	return num; 
} 

int strtoint_mov(char **ptr)// works correctly // scan and put into ineger only till a non integer occurs
{ 
	int num;int ic;char *str;num=0;
	
	str=*ptr;
	ic=*str-48; 
    num=ic;
	str+=1;
	while(*str!='\0') 
	{		
		if(isnum(*str)) 
		{ 
			ic=*str-48; 
			iappend(&num,ic);			
		}
		else
			break;
		
		str+=1;
	} 
	*ptr=str;	
	return num; 
} 

int sctoint(char *str)// works correctly //scan for all numbers in the string
{ 
	int num;int ic;num=0;
	ic=*str-48; 
    num=ic;
	str+=1;
	while(*str!='\0') 
	{		
		if(isnum(*str)) 
		{ 
			ic=*str-48; 
			iappend(&num,ic);			
		}str+=1;
		
	} 
	
	return num; 
}  

int intat(int a, int pos) // works correctly
{
	
	int i,aa,len,num; 
	len=intlen(a); 
	i=len;
	aa=a;
	if(pos>len)
		return error;

	aa=(int)(aa/(power(10,len-pos)));
	num=aa%10;
	
	return num;

}

char itochar(int a) // works correctly
{ 
	int len;char c;
	len=intlen(a); 
	if(len!=1) 
	{ return error;} 
	c=a+48; 
	return c; 
}

void itostring(int a,char *str) // works correctly till 7 digits
{ 
	int len,i;
	len=intlen(a);
	for(i=1;i<=len;i++) 
	{ 
		*str=itochar(intat(a,i));
		str+=1;
	}
	/*while(*str!='\0')
	{
		if(*str<48 || *str>57)
			*str=0;
	}*/
}



int intlen(int a) // works correctly
{ 
	int num,len;
	num=a;len=0;
	do 
	{
		len+=1;
		num=(int)(num/10);
	} 
	while(num!=0);
	return len; 
}


void iappend(int *a, int app) // works correctly
{ 
	int len,j;
	len=intlen(app);

	for(j=1;j<=len;j++) 
		(*a)*=10;
	*a+=app;
} 


int iReverse(int a)// works correctly 
{ 
    int temp,len,i;
    temp=0;	
	len=intlen(a);
	for(i=len;i>=1;i--) 
	{ 
	    iappend(&temp,intat(a,i)); 
	} 
    return temp;	
}

void ireverse(int *a)// works correctly
	{ 
    int temp,len,i;
    temp=0;	
	len=intlen(*a);
	for(i=len;i>=1;i--) 
	{ 
	    iappend(&temp,intat(*a,i)); 
	} 
    *a=temp;	
}

int ivalat(int a,int pos)// works correctly 
{ 
	int aa;
	aa=intat(a,pos);
	aa*=(int)power(10,intlen(a)-pos);
	return aa;	
}

int inttill(int a,int pos)// works correctly 
  { 
	int aa;
	aa=(int)(a/power(10,intlen(a)-pos));
	return aa;
  }



#endif


#ifndef ndouble 



double todecimal(int a)// works correctly 
  {  
	  return a/power(10,intlen(a)); 
  }


double todouble(char *str) // works correctly
{ 
	double a;char *flp,*cpstr;
	a=0;
	cpstr=str;
	a=strtoint(str);
	str=cpstr;
	while(*str!='.')
		str+=1;
	if(*str=='.')
		flp=str;
	str+=1;
	a+=todecimal(strtoint(str));
	return a;
}

double todouble_mov(char **aa) // works correctly
{ 
	double a;char *flp,*cpstr,*str;
	a=0;str=*aa;
	cpstr=str;
	a=strtoint(str);
	str=cpstr;
	while(*str!='.')
		str+=1;
	if(*str=='.')
		flp=str;
	str+=1;
	a+=todecimal(strtoint_mov(&str));
	*aa=str;
	return a;
}


/*
double todouble(char *str) // works correctly
{ 
	char *fl,*cpstr;//point the place where there is floating point cpstr is copy of str
	double num;char c;int aflp,bflp;double decimals;//aflp is the numbers after the floating point 
	decimals=0;num=0;cpstr=str;

	if(isnum(*str)) //initialise bflp
	{
		c=*str;
		bflp=c-48; 
	}
	str+=1;
	iappend(&bflp,strtoint(str));//assign bflp till floating point or . occurs 
	while(1) //move str till floating point
	{ 
		if(*str=='.')
			break; 
		else
			str+=1; 
	}
	fl=str;
	cpstr=fl+1; 
	if(isnum(*cpstr)) //initialise aflp
	{
		c=*cpstr;
		aflp=c-48; 
	}	
	cpstr+=1;
	iappend(&aflp,strtoint(cpstr));//assign bflp till floating point or . occurs  
	decimals=todecimal(aflp);//decimal value of the integer that contains the numbers after floating point 
	
	num=bflp+decimals; 
	return num; 
}*/

//double sqrt(double a)

double power(double a,int t) // works correctly
{ 
	double sum;int i;
	sum=0;
	if(t==0) 
		return 1; 
	else if(t>0) 
	{ 
	    sum=a;
		for(i=1;i<t;i++)
		 sum*=a;  
		return sum;
	} 
	else if(t<0) 
	{ 
		int pt;//positive value of t;
		sum=0;pt=t*-1;
		sum=a; 
		for(i=1;i<pt;i++) 
		 sum*=a;//          -n       n
		sum=1/sum;// because a   = 1/a
		return sum;
	} 
	return 0; 
}




int beforedecimal(double a)// works correctly 
{ 
	int aa; 
	aa=(int)a; 
	return aa; 
}

boolean hasdecimal(double a)// works correctly  
  { 
	int temp;double aa;
	temp=(int)a; 
	aa=temp;
	if(aa==a)
	{ return false;}
	else
		return true; 
  }

#endif

#ifndef ngeneral
		
int tonum(char c)// works correctly 
{ 
	int a; 
	if(isnum(c)) 
	{
		a=c-48;
		return a;
	}
	else
		return error;	 
}

boolean isnum(char c)// works correctly 
{ 
	if(c>47 && c<58) 
		return true;
	else 
	    return false;
}
#endif

size_t strlen(char *str)
{
	size_t i=0;
	while(*str++)
	 i++;
	return i;
}
char *strcpy(char *dest,char *src)
{
	while(*src)
	 *dest++=*src++;
	return dest;
}
int strcmp(const char *str1,const char *str2)
{
  register const unsigned char *s1 = (const unsigned char *) str1;
  register const unsigned char *s2 = (const unsigned char *) str2;
  register unsigned c1, c2;

  do
    {
      c1 = (unsigned char) *s1++;
      c2 = (unsigned char) *s2++;
      if (c1 == '\0')
        return c1 - c2;
    }
  while (c1 == c2);

  return c1 - c2;
}

void strrev(char *str)
{
	char *temp,a;
	while(*temp++) ;
	while(str<temp)
	{
		a=*temp;
		*temp--=*str;
		*str++=a;
	}
}

int find(char *str,char *src,size_t len)
{
	size_t i=0,diff=0;
	char *st=str;
	char*sr=src;
	while(*src)
	{
		if(*src==*str)
		{
			st=str;sr=src;diff=0;
			i=0;
			do
			{
				diff=*st++-*sr++;
				i++;
			}while(!diff);
		}
		if(i==len)
		 return 1;
		 src++;
	}
	return 0;
}
