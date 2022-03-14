#ifndef DEFS_H
#define DEFS_H

#include<stdint.h>
#include <iomanip>
#include <iostream>

#define MEMSIZE 65536

using namespace std;

uint32_t Reg[32];
uint32_t PC;

int32_t sign_ext(uint32_t data, uint32_t size)
{
    int32_t val = data;
    val = ((val << (32 - size)) >> (32 - size));
    return val;
}

void print_regs()
{
    
    cout << "---------------------------------------------------------------------------------------------------------" << endl;
    cout << "|                                          Status of Registers                                          |" << endl;
    cout << "---------------------------------------------------------------------------------------------------------" << endl; 
    
    cout << "---------------------------------------------------------------------------------------------------------" << endl;
    cout << "| " << left << setw(10) << "R0" << " | " << left << setw(10) << "R1" << " | " << left << setw(10) << "R2" << " | " << left << setw(10) << "R3" << " | " << left << setw(10) << "R4" << " | " << left << setw(10) << "R5" << " | " << left << setw(10) << "R6" << " | " << left << setw(10) << "R7" << " | "  << endl;
    std::cout << std::hex << "| " << left << setw(10) << Reg[0] << " | " << left << setw(10) << Reg[1] << " | " << left << setw(10) << Reg[2] << " | " << left << setw(10) << Reg[3] << " | " << left << setw(10) << Reg[4] << " | " << left << setw(10) << Reg[5] << " | " << left << setw(10) << Reg[6] << " | " << left << setw(10) << Reg[7] << " | " << std::dec << endl;
    cout << "---------------------------------------------------------------------------------------------------------" << endl; 
    
    cout << "---------------------------------------------------------------------------------------------------------" << endl;
    cout << "| " << left << setw(10) << "R8" << " | " << left << setw(10) << "R9" << " | " << left << setw(10) << "R10" << " | " << left << setw(10) << "R11" << " | " << left << setw(10) << "R12" << " | " << left << setw(10) << "R13" << " | " << left << setw(10) << "R14" << " | " << left << setw(10) << "R15" << " | "  << endl;
    std::cout << std::hex << "| " << left << setw(10) << Reg[8] << " | " << left << setw(10) << Reg[9] << " | " << left << setw(10) << Reg[10] << " | " << left << setw(10) << Reg[11] << " | " << left << setw(10) << Reg[12] << " | " << left << setw(10) << Reg[13] << " | " << left << setw(10) << Reg[14] << " | " << left << setw(10) << Reg[15] << " | " << std::dec << endl;
    cout << "---------------------------------------------------------------------------------------------------------" << endl; 
    
    cout << "---------------------------------------------------------------------------------------------------------" << endl;
    cout << "| " << left << setw(10) << "R16" << " | " << left << setw(10) << "R17" << " | " << left << setw(10) << "R18" << " | " << left << setw(10) << "R19" << " | " << left << setw(10) << "R20" << " | " << left << setw(10) << "R21" << " | " << left << setw(10) << "R22" << " | " << left << setw(10) << "R23" << " | "  << endl;
    std::cout << std::hex << "| " << left << setw(10) << Reg[16] << " | " << left << setw(10) << Reg[17] << " | " << left << setw(10) << Reg[18] << " | " << left << setw(10) << Reg[19] << " | " << left << setw(10) << Reg[20] << " | " << left << setw(10) << Reg[21] << " | " << left << setw(10) << Reg[22] << " | " << left << setw(10) << Reg[23] << " | " << std::dec << endl;
    cout << "---------------------------------------------------------------------------------------------------------" << endl; 
    
    cout << "---------------------------------------------------------------------------------------------------------" << endl;
    cout << "| " << left << setw(10) << "R24" << " | " << left << setw(10) << "R25" << " | " << left << setw(10) << "R26" << " | " << left << setw(10) << "R27" << " | " << left << setw(10) << "R28" << " | " << left << setw(10) << "R29" << " | " << left << setw(10) << "R30" << " | " << left << setw(10) << "R31" << " | "  << endl;
    std::cout << std::hex << "| " << left << setw(10) << Reg[24] << " | " << left << setw(10) << Reg[25] << " | " << left << setw(10) << Reg[26] << " | " << left << setw(10) << Reg[27] << " | " << left << setw(10) << Reg[28] << " | " << left << setw(10) << Reg[29] << " | " << left << setw(10) << Reg[30] << " | " << left << setw(10) << Reg[31] << " | " << std::dec << endl;
    cout << "---------------------------------------------------------------------------------------------------------" << endl; 
    
    cout << "--------------" << endl;
    cout << "| " << left << setw(10) << "PC" << " | " << endl;
    std::cout << std::hex << "| " << left << setw(10) << PC << " | " << std::dec << endl;
    cout << "--------------" << endl; 
    
    
}

#endif
