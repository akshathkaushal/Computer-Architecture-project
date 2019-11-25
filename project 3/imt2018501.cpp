//	Design a ​ non-pipelined​ MIPS processor which will take as input- the instruction
//	codes for an N factorial program and produces the necessary output. In how
//	many clock cycles does the output of the program appear?

/*
    Factorial code:

    lw   $s0 0($zero)   //  100011  10000  00000  0000000000000000    //  i type
    lw   $s0 0($zero)   //  100011  10001  00000  0000000000000000    //  i type
    addi $t0 $zero 1    //  001000  01000  00000  0000000000000001    //  i type
    addi $t1 $zero 1    //  001000  01001  00000  0000000000000001    //  i type

    loop:
    beq $s1 1 end       //  000100  10001  00001  0000000000000100    //  i type
    sub $s1 $s1 $t0     //  000000  10001  10001  01000  00000  100010  // r type
    mul $s0 $s0 $s1     //  000000  10000  10000  10001  00000  011000  // r type
    j loop              //  000010  11111111111111111111111101          //  j type
    sw  $s0 0($zero)   //  101011  10000  00000  0000000000000001    //  i type

    end:

*/

/*
    Instructions:
    
    1) sw
    2) lw
    3) addi
    4) subtract
    5) mul
    6) jump
    7) beq
*/

/*
    Clocke cycles per instruction:

    1) Load (5 cycles)
    2) Store (4 cycles)
    3) R-type (4 cycles)
    4) Branch (3 cycles)
    5) Jump (3 cycles)
*/


#include<bits/stdc++.h>
#include<fstream>
using namespace std;
    
vector<int> registerFile;      // register file
vector<int> memory;            // main memory
int pc=0;

void initialize()
{
    // setting up register file
    for(int i=0;i<32;i++)
    {
        registerFile.push_back(0);
    }    

    // initializing memory
    for(int i=0;i<257;i++)
    {
        memory.push_back(0);
    }
}

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
}   

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
}   
 
// interpreting instructions
void sw(int rt, int rs, int offset)
{
    memory[rs+offset] = registerFile[rt];
}

void lw(int rt, int rs, int offset)
{
    registerFile[rt] = memory[rs+offset];
}

void addi(int rt, int rs, int val)
{
    registerFile[rt] = registerFile[rs]+val;
}

void sub(int rd, int rt, int rs)
{
    registerFile[rd] = registerFile[rt] - registerFile[rs];
}

void mul(int rd, int rt, int rs)
{
    registerFile[rd] = registerFile[rt] * registerFile[rs];
}

void beq(int rd, int rt, int offset)
{
    if(registerFile[rd]==rt)
    { 
        pc+=offset;
    }
    else{
        pc++;
    }
}

void j(int offset)
{
    pc+=offset;
}

int main()
{	
    // initializing memory and registers
    initialize();

    // take input 
    int input;
    string swCode="";
    cout<<"Enter a digit: ";
    cin>>input;
    memory[0]=input;

    int clock_cycles=0;

    vector<string> instructions;   // instruction set

    // reading instructions from file
    ifstream infile("instructions/factorial.txt");
    string inst;
    while(infile >> inst)
    {
        instructions.push_back(inst);
    }

    int inst_count = instructions.size();
    
    cout<<"PC"<<"\t"<<"INST"<<"\t"<<"$s0"<<"\t"<<"$s1"<<"\t"<<"$t0"<<"\t"<<"$t1"<<endl;
    cout<<"-------------------------------------------"<<endl;

    while(pc<inst_count)
    {
        // call instructions here
        vector<int> components = decodeInstruct(instructions[pc]);
        if(components[0]==binToInt("101011"))
        {
            cout<<"pc="<<pc<<"\tsw"<<"\t";
            sw(components[1], components[2], components[3]);
            pc++;
        }

        else if(components[0]==binToInt("100011"))
        {
            cout<<"pc="<<pc<<"\tlw"<<"\t";
            lw(components[1], components[2], components[3]);
            pc++;
        }

        else if(components[0]==binToInt("001000")){
            cout<<"pc="<<pc<<"\taddi"<<"\t";
            addi(components[1], components[2], components[3]);
            pc++;
        }

        else if(components[0]==binToInt("000100")){
            cout<<"pc="<<pc<<"\tbeq"<<"\t";
            beq(components[1], components[2], components[3]);
            //cout<<"beq pc = "<<pc<<endl;
        }

        else if(components[0]==binToInt("000000"))
        {
            if(components[5]==binToInt("100010")){
                cout<<"pc="<<pc<<"\tsub"<<"\t";
                sub(components[1], components[2], components[3]); 
                pc++;
            }
            else if(components[5]==binToInt("011000")){
                cout<<"pc="<<pc<<"\tmul"<<"\t";
                mul(components[1], components[2], components[3]);
                pc++;
            }
        }

        else if(components[0]==binToInt("000010")){
            cout<<"pc="<<pc<<"\tj"<<"\t";
            j(components[1]);    
        }

        cout<<registerFile[16]<<"\t"<<registerFile[17]<<"\t"<<registerFile[8]<<"\t"<<registerFile[9]<<endl;
    }

    cout<<"\nAnswer = "<<memory[1]<<endl;
    return 0;
}


/*  Hurdles:                                                    Status:

    1) Write the code for factorial in mips.                    Done
    2) Write the instructions in instructions.txt               Done
    3) Decode Instructions                                      Done
    4) Start interpreting                                       Done
    5) Call the instructions in order of Factorial code         Done
    6) count the number of clock cycles                         pending
*/
