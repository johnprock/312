
#include <stdio.h> //For input/output


/*  --- the following are sample code segments to implement logical operations --- */ 
//To implement  a AND b
inline unsigned int aANDb_function(unsigned int passed_input) 
{
	unsigned int returned_output;
	
	//To implement  a AND b
	if ( (passed_input & 0x3) == 3) //To mask the bit position 1 and 0
			returned_output = 1; // output is 1, when both a =1, b =1
		else returned_output = 0; //output is 0, when for combination a= 0, b=0; a=0, b=1; a=1, b=0

	return returned_output;
}


//To implement a OR b
inline unsigned int aORb_function(unsigned int passed_input) 
{
	unsigned int returned_output;
	
	//To implement a OR b
	returned_output = ( (passed_input & 0x3) == 0) ?  0: 1 ; //This one implements the OR's truth table

	return returned_output;
}


//To implement c OR (a AND b)
inline unsigned int cOR_aNADb_function(unsigned int passed_input) 
{
	unsigned int returned_output;
	
	//To implement c OR (a AND b)
	return returned_output = ( (passed_input & 0x7) > 2) ?  1: 0 ; //This one implements the (c OR (a AND b)) 's truth table

}

//The main program only tests the logic designed in the above functions
int main()
{
	//To implement a AND b, a OR b

	unsigned int input; //bit 2 is c, bit 1 is a, bit 0 is b

	unsigned int output; //bit 1 is the output

	//Patterns to test the code, these are used as truth table inputs (also known as test vectors)
	enum {

			PATTERN_000 = 0, //c = 0, a = 0, b = 0 
			PATTERN_001 = 1, //c = 0, a = 0, b = 1
			PATTERN_010 = 2, //c = 0, a = 1, b = 0
			PATTERN_011 = 3, //c = 0, a = 1, b = 1
			PATTERN_100 = 4, //c = 1, a = 0, b = 0 
			PATTERN_101 = 5, //c = 1, a = 0, b = 1
			PATTERN_110 = 6, //c = 1, a = 1, b = 0
			PATTERN_111 = 7 //c = 1, a = 1, b = 1

	};


	//To test the above code
	printf("0 AND 0 -> %d \n", aANDb_function(PATTERN_000) );
	printf("0 AND 1 -> %d \n", aANDb_function(PATTERN_001) );
	printf("1 AND 0 -> %d \n", aANDb_function(PATTERN_010) );
	printf("1 AND 1 -> %d \n", aANDb_function(PATTERN_011) );

	printf("0 AND 0 -> %d \n", aORb_function(PATTERN_000) );
	printf("0 AND 1 -> %d \n", aORb_function(PATTERN_001) );
	printf("1 AND 0 -> %d \n", aORb_function(PATTERN_010) );
	printf("1 AND 1 -> %d \n", aORb_function(PATTERN_011) );

	printf("0 OR (0 AND 0) -> %d \n", cOR_aNADb_function(PATTERN_000) );
	printf("0 OR (0 AND 1) -> %d \n", cOR_aNADb_function(PATTERN_001) );
	printf("0 OR (1 AND 0) -> %d \n", cOR_aNADb_function(PATTERN_010) );
	printf("0 OR (1 AND 1) -> %d \n", cOR_aNADb_function(PATTERN_011) );
	printf("1 OR (0 AND 0) -> %d \n", cOR_aNADb_function(PATTERN_100) );
	printf("1 OR (0 AND 1) -> %d \n", cOR_aNADb_function(PATTERN_101) );
	printf("1 OR (1 AND 0) -> %d \n", cOR_aNADb_function(PATTERN_110) );
	printf("1 OR (1 AND 1) -> %d \n", cOR_aNADb_function(PATTERN_111) );

	return 0;
}
