//	Design a ​ non-pipelined​ MIPS processor which will take as input- the instruction
//	codes for an N factorial program and produces the necessary output. In how
//	many clock cycles does the output of the program appear?

/*
    Factorial code:
    
    addi $s0 $zero 5    //  001000  10000  00000  0000000000000101    //  i type
    addi $s1 $zero 5    //  001000  10001  00000  0000000000000101    //  i type
    addi $t0 $zero 1    //  001000  01000  00000  0000000000000001    //  i type
    addi $t1 $zero 1    //  001000  01001  00000  0000000000000001    //  i type

    loop:
    beq $s1 1 end       //  000100  10000  00001  0000000000000100    //  i type
    sub $s1 $s1 $t0     //  000000  10001  10001  01000  00000  100010  // r type
    mul $s0 $s0 $s1     //  000000  10000  10000  10001  00000  011000  // r type
    j loop              //  000010  11111111111111111111111101          //  j type

    end:

*/

/*
    Instructions:
    
    1) addi
    2) subtract
    3) mul
    4) jump
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

int twosComplement(string address)
{
    // 111101
    for(int i=0;i<address.length();i++)
    {
        if(address[i]=='1')
        {
            address[i]='0';
        }
        else address[i]='1';
    }

    int carry=1;
    for(int i=address.length()-1;i>=0;i--)
    {
        if(address[i]=='1' && carry==1){
            address[i]='0';
            carry=1;
        }

        else if(address[i]=='0' && carry==1)
        {
            address[i]='1';
            carry=0;
        }
    }
    return binToInt(address)*(-1);
}

// Tell whether the instruction set is R type or I type or J type
char tellType(string instruction)
{
	char type;

    if(instruction.substr(0,6)=="000000") type = 'r';
    else if(instruction.substr(0,6)=="000010") type = 'j';
    else type = 'i';
	return type; // this will determine further action on the instruction
}   // working fine

// Seperate different fields according to the type of instruction
vector<int> decodeInstruct(string instruction)
{
    // the course of this function will be determined by the return value of tellType function
	vector<int> fields;
    int opcode, rs, rt, rd, shamt, func, value, address;
    // value for addi, subi etc and address for jump

    char type = tellType(instruction);

    opcode = binToInt(instruction.substr(0,6));
   
    fields.push_back(opcode);

    if(type=='r')
    {
        rs = binToInt(instruction.substr(6, 5));
        fields.push_back(rs);
        rd = binToInt(instruction.substr(11, 5));
        fields.push_back(rd);
        rt = binToInt(instruction.substr(16, 5));
        fields.push_back(rt);
        shamt = binToInt(instruction.substr(21, 5));
        fields.push_back(shamt);
        func = binToInt(instruction.substr(26, 6));
        fields.push_back(func);
    }

    else if(type=='i')
    {
        rs = binToInt(instruction.substr(6, 5));
        fields.push_back(rs);
        rt = binToInt(instruction.substr(11, 5));
        fields.push_back(rt);
        value = binToInt(instruction.substr(16,16));
        fields.push_back(value);
    }

    else if(type=='j')
    {
        if(instruction.substr(6, 26)[0]=='0')
            address = binToInt(instruction.substr(6, 26));
        else
            address = twosComplement(instruction.substr(6, 26));

        fields.push_back(address);
    }

	return fields;
}   // working fine
 

int main()
{	
	vector<string> instructions;	          // instruction set
	vector<map<int, int>> registerFile;	      // register file
    vector<int> memory;                       // main memory


    return 0;
}


/*  Hurdles:                                                    Status:

    1) Write the code for factorial in mips.                    Done
    2) Write the instructions in instructions.txt               Done
    3) Decode Instructions                                      Done
    3) Start interpreting                                       Pending


*/
