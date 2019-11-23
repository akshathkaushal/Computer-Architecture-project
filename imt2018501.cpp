/*  Design a cache simulator for a direct-mapped cache to hold 256 lines,
    16 words per line (word = 32 bits). Assume a 32 bit address. Implement a main
    memory. Implement an LRU scheme for replacement. Use the memory trace files
    at this ​location​ as input. The trace file will specify all the data memory accesses
    that occur in a certain program. Each line in the trace file will specify a new
    memory reference and has the following fields:
        a. Access Type: A single character indicating whether the access is a load
        ('l') or a store ('s').
        b. Address: A 32-bit integer (in unsigned hexadecimal format) specifying the
        memory address that is being accessed.
        c. Instructions since last memory access: Indicates the number of
        instructions of any type that executed between since the last memory
        access (i.e. the one on the previous line in the trace). For example, if the
        5th and 10th instructions in the program's execution are loads, and there
        are no memory operations between them, then the trace line for with the
        second load has "4" for this field.
    For different sizes of the block, for eg- 1 word per line, 2 words per line etc upto
    16, what are the hit/rates ? In other words, plot the miss/hit rates for varying
    word size per block. */

#include<bits/stdc++.h>
#include<fstream>
using namespace std;

int hexToInt(string memLocation)
{
    memLocation = memLocation.substr(2,memLocation.length());
    int len = memLocation.length(); 
    int base = 1; 
    int dec_val = 0; 
    for (int i=len-1; i>=0; i--) 
    {    
        if (memLocation[i]>='0' && memLocation[i]<='9') 
        { 
            dec_val += (memLocation[i] - 48)*base; 
            base = base * 16; 
        } 
        else if (memLocation[i]>='a' && memLocation[i]<='f') 
        { 
            dec_val += (memLocation[i] - 87)*base;
            base = base*16; 
        } 
    } 
      
    return dec_val; 
} // working correctly

int main()
{   
    vector<int> memory;                       // main memory
    stack<int> cache;                         // primary cache

    int hit, miss;

    return 0;
}