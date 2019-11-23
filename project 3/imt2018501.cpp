//	Design a ​ non-pipelined​ MIPS processor which will take as input- the instruction
//	codes for an N factorial program and produces the necessary output. In how
//	many clock cycles does the output of the program appear?

/*
    Factorial code:
    
    li $s0 5 
    li $s1 5  
    
    loop:
    beq $s1 $1 end 
    subi $s1 $s1 1 
    mul $s0 $s0 $s1 
    j loop 

    end:

*/

/*
    Instructions:
    
    1) load immidiate
    2) add
    3) subtract
    4) subtract immidiate
    5) mul
    6) jump

*/



#include<bits/stdc++.h>
#include<fstream>
using namespace std;

int clock_cycles=0;

// Conversion from binary to integer
int binToInt(string binary)
{
    int dec_value = 0;  
    int base = 1;
  
    int temp = stoi(binary); 
    while (temp) { 
        int last_digit = temp % 10; 
        temp = temp / 10; 
  
        dec_value += last_digit * base; 
  
        base = base * 2; 
    } 
  
    return dec_value;   // working perfectly
}	

// Tell whether the instruction set is R type or I type or J type
char tellType(string instruction)
{
	char type;

	return type; // this will determine further action on the instruction
}

// Seperate different fields according to the type of instruction
vector<int> decodeInstruct(string instruction, char type)
{
    // the course of this function will be determined by the return value of tellType
	vector<int> fields;
    
	return fields;
}


int main()
{	
	vector<string> instructions;	          // instruction set
	vector<map<int, int>> registerFile;	      // register file
    vector<int> memory;                       // main memory

	return 0;
}


/*  Hurdles:                                                    Status:

    1) Write the code for factorial in mips.                    Done
    2) Write the instructions in instructions.txt               Pending
    3) Start interpreting                                       Pending


*/