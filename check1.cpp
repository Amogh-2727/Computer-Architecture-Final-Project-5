#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <stdint.h>
#include "defs.h"
#include "instruction_Fetch.cpp"

uint8_t *memory_r = NULL;

using namespace std;

int load_code_to_mem(const char *t)
{    
    long int instruct;
    ifstream file(t);
    string instr_add = "";
    std::string instr = "";
    long int instr_cnt = 0;
    long int instr_add_t = 0;
    while(getline(file, instr_add,':'))
    {
        getline(file, instr);

        instruct = std::stol(instr, nullptr, 16);
        instr_add_t = std::stol(instr_add, nullptr, 16);

        //cout << std::hex << instruct << std::dec << endl;

        memory_r[instr_add_t] = instruct & 0xFF;
        memory_r[instr_add_t + 1] = (instruct >> 8) & 0xFF;
        memory_r[instr_add_t + 2] = (instruct >> 16) & 0xFF;
        memory_r[instr_add_t + 3] = (instruct >> 24) & 0xFF;
        

        ++instr_cnt;
    }
        file.close();
    return instr_cnt;
}

void print_mem(int l, int instr_cnt)
{
    for(int j = 65535; j > 65500 ; j--)
    {   
        //printf("memory[%x] = %x\n", l, memory_r[l]);
        std::cout << std::hex <<"Memory[" << j << "] = " <<  (int)memory_r[j] << std::dec << endl;
        l++;
    }
}

int main(int argc, char *argv[]) {

    const char *filename = argv[3];
    long int no_instr = 0;
    
    for(int i = 0; i < 32; i++){
        Reg[i] = 0;
    }
    
    PC = 0;
    Reg[1] = 0;
    Reg[2] = 65535;

    PC = (uint32_t)atoi(argv[1]);
    
    if((PC % 4) != 0)
    {
        cout << "Misaligned program counter. Resetting it to default value" << endl;
        PC = 0;
    }    
    
    Reg[2] = (uint32_t)atoi(argv[2]);
    
    memory_r = (uint8_t*)calloc(MEMSIZE, sizeof(uint8_t));
    
    no_instr = load_code_to_mem(filename);

    instruction_Fetch(no_instr, memory_r);
    
    print_mem(0, no_instr);
    
    return 0;
}