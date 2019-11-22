//	Design a ​ non-pipelined​ MIPS processor which will take as input- the instruction
//	codes for an N factorial program and produces the necessary output. In how
//	many clock cycles does the output of the program appear?

#include<bits/stdc++.h>
#include<fstream>
using namespace std;


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

	return type;
}

// Seperate different fields according to the type of instruction
vector<int> decodeInstruct(string instruction, char type)
{
	vector<int> fields;

	return fields;
}


int main()
{	
	vector<string> instructions;	          // instruction set
	vector<map<int, int>> registerFile;	      // register file
    vector<int> memory;                       // main memory
    stack<int> cache;                         // primary cache

    
    
	return 0;
}