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
    
    if(((PC + 1) % 4) != 0)
    {
        cout << "Misaligned program counter. Resetting it to default value" << endl;
        PC = 0;
    }    
    
    Reg[2] = (uint32_t)atoi(argv[2]);
    
    memory_r = (uint8_t*)calloc(MEMSIZE, sizeof(uint8_t));
    //uint8_t *memory_r = new uint8_t[MEMSIZE];
    
    no_instr = load_code_to_mem(filename, PC);
    //print_mem(0, no_instr);
    print_regs();
    
    return 0;
}