//Sample source code for demonstrating simple examples of bit-masking operations in C
// using the logical | and & operators.

//Written by Suneil Mohan for CSCE312.


#include<stdio.h>
int main() {

	unsigned int x;
	unsigned int y;
	unsigned int z;
	unsigned int a;
	unsigned int b;
	
	//set a 1 in x after 5 places (i.e. set a 1 in the 6th bit position)
	x=1<<5;
	//1 << 5 = 2^5 = 32: 00000000 00100000
	
	printf("x in decimal = %d\n",x);	
	printf("x in hex = %02x\n",x);	
	
	y=3;
	//y= 00000000 00000011
	
	
	//combine x and y logically using the OR operation
	z=x|y;
	// x|y => 00000000 00100000 OR 00000000 00000011
	// => z = 00000000 00100011
	
	printf("z in decmial = %d\n",z);	
	printf("z in hex = %x\n",z);	
	
	a= z & 0x11 ;
	// 00000000 00100011 AND 00000000 00010001
	//    00000000 00100011
	//AND 00000000 00010001
	//------------------------
	//    00000000 00000001
	
	printf("a in decmial = %d\n",a);	
	printf("a in hex = %x\n",a);	
	
	//set the 5th bit of 'a' and store it in 'b'
	b= a ^ 0x10 ; // ^ = XOR
	
	//    00000000 00000001 (a)
	//XOR 00000000 00010000 (5th bit position)
	//------------------------
	//    00000000 00010001 
	
	printf("b in decmial = %d\n",b);	
	printf("b in hex = %x\n",b);	
	
	
	
	
return 0;	
}