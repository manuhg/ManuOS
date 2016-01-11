#ifndef functions_h
#define functions_h


 #include <access.h>
#ifndef _lib_funcs_stdio
 #include <stdio.h>
#endif

 Public void _print_int(int a);
 Public void print_int(int a,int colour);
 Public void _print_hex(uint64_t a);
 Public void _print_long(long a);
 
 Public int leap(int yr);
 Public binary tobinary(sbinary val);
 Public sbinary frombinary(binary a);
 Public double power(double a,int t);
 Public int binlen(binary a);
 Public void thanks();
 Public void e_line();
 Public void iappend(int *a, int app);
 
struct ilst_node{
	int data;
	struct ilst_node *next;
	};
typedef struct ilst_node ilst_node;

struct dlist_node{
	double data;
	struct dlist_node *next;
	};
typedef struct dlist_node dlist_node;

struct ibinary_tree
{
	int data;
	struct ibinary_tree *right,*left;
};
typedef struct ibinary_tree ibinary_tree;


#define check_bit(var,pos) ((var) & (1<<(pos)))

#define max_int 10
// max int is the maximum number of digits an int variable can hold
#ifndef nint 

 Public int strtoint(char *str);// works correctly
 Public int strtoint_mov(char **ptr);// works correctly
 Public int sctoint(char *str);// works correctly
 Public int intat(int a, int pos);// works correctly
 Public char itochar(int a);// works correctly
 Public void itostring(int a,char *str);// works correctly till 7 digits
 Public int iReverse(int a);// works correctly
 Public void ireverse(int *a);// works correctly
 Public int intlen(int a);// works correctly
 Public void iappend(int *a, int app);// works correctly
 Public int ivalat(int a,int pos);// works correctly
 Public int inttill(int a,int pos);// works correctly  
#endif

 Public void gtkey();
 Public void gtkey_echo();

#ifndef ndouble 

 Public double todecimal(int a);// works correctly
 Public double todouble(char *str);// works correctly
 Public double todouble_mov(char **aa);
 Public double power(double a,int t);// works correctly

 Public int beforedecimal(double a);// works correctly 
 Public boolean hasdecimal(double a);// works correctly 



#endif

#ifndef ngeneral

 Public int tonum(char c);// works correctly
 Public boolean isnum(char c);// works correctly 
#endif

//extern void read_ata_disk(uint32 sectors,uint32 buffer,uint32 data_struct,uint32 lba);

#endif
