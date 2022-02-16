#include <iostream>
#include <fstream>
#include <string>
#include<stdint.h>
#include <bits/stdc++.h>
#include "defs.h"

uint8_t *memory_r = NULL;

using namespace std;

int load_code_to_mem(const char *t, uint32_t start_loc)
{    
    long int instruct;
    ifstream file(t);
    string data = "";
    std::string instr = "";
    uint32_t incr = 0;
    long int instr_cnt = 0;
    while(getline(file, data,':'))
    {
        getline(file, instr);

        instruct = std::stol(instr, nullptr, 16);

        //cout << std::hex << instruct << std::dec << endl;

        memory_r[start_loc + incr] = instruct & 0xFF;
        memory_r[start_loc + incr + 1] = (instruct >> 8) & 0xFF;
        memory_r[start_loc + incr + 2] = (instruct >> 16) & 0xFF;
        memory_r[start_loc + incr + 3] = (instruct >> 24) & 0xFF;
        
        incr += 4;
        ++instr_cnt;
    }
        file.close();
    return instr_cnt;
}

void print_mem(int l, int instr_cnt)
{
    for(int j = 0; j < instr_cnt * 4; j++)
    {   
        //printf("memory[%x] = %x\n", l, memory_r[l]);
        std::cout << std::hex <<"Memory[" << l << "] = " <<  (int)memory_r[l] << std::dec << endl;
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
    //uint8_t *memory_r = new uint8_t[MEMSIZE];
    
    no_instr = load_code_to_mem(filename, PC);
    print_mem(0, no_instr);
    
    return 0;
}
