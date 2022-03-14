//////////////////////////////////////////////////////////////////////////
// RISCV (RV32I) ISA Simulator
// Instruction Set Architecture (ISA) level simulator for RV32I Base 
// Integer with M extension, implemented using C++
// 
// Contributors: Amogh Morey, Arjun Preetham, Ritvik Tiwari, Viraj Lodhia
//////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <stdint.h>
#include "instruction_fetch.cpp"

int load_code_to_mem(const char *t);
void instruction_fetch(uint32_t no_instr, uint8_t *memory_r);

using namespace std;

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
        exit(0);
    }    
    
    Reg[2] = (uint32_t)atoi(argv[2]);
    Debug_mode = (uint32_t)atoi(argv[4]);    
    memory_r = (uint8_t*)calloc(MEMSIZE, sizeof(uint8_t));
    
    no_instr = load_code_to_mem(filename);
    instruction_fetch(no_instr, memory_r);

    return 0;
}