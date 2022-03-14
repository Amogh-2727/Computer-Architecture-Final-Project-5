#include<stdint.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string.h>
#include <bitset>
#include "defs.h"

using namespace std;

int32_t sign_ext(uint32_t data, uint32_t size)
{
    int32_t val = data;
    val = ((val << (32 - size)) >> (32 - size));
    return val;
}

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

void unknown_instr(uint32_t instruction)
{
    cout << "Instruction not recognised. Instruction Address: " << std::hex << instruction << std::dec << endl;
    exit(0);
}

void verbose_print(uint32_t instruction, uint32_t mode1, uint32_t mode2)
{
    if (mode1 == 1)
    {
        cout << "----------------------------------------------------------------------------------------------------------------" << endl;
        if (mode2 != 2)
        {    
            std::cout << std::hex << "Instruction Address: " << instruction << std::dec << endl << endl; 
        }
        std::cout << std::hex << "PC:  " << left << setw(10) << PC << std::dec << endl;
        std::cout << std::hex << "R0:  " << left << setw(10) << Reg[0] << "R1:  " << left << setw(10) << Reg[1] << "R2:  " << left << setw(10) << Reg[2] << "R3:  " << left << setw(10) << Reg[3] << "R4:  " << left << setw(10) << Reg[4] << "R5:  " << left << setw(10) << Reg[5] << "R6:  " << left << setw(10) << Reg[6] << "R7:  " << left << setw(10) << Reg[7]  << std::dec << endl;
        std::cout << std::hex << "R8:  " << left << setw(10) << Reg[8] << "R9:  " << left << setw(10) << Reg[9] << "R10: " << left << setw(10) << Reg[10] << "R11: " << left << setw(10) << Reg[11] << "R12: " << left << setw(10) << Reg[12] << "R13: " << left << setw(10) << Reg[13] << "R14: " << left << setw(10) << Reg[14] << "R15: " << left << setw(10) << Reg[15]  << std::dec << endl;
        std::cout << std::hex << "R16: " << left << setw(10) << Reg[16] << "R17: " << left << setw(10) << Reg[17] << "R18: " << left << setw(10) << Reg[18] << "R19: " << left << setw(10) << Reg[19] << "R20: " << left << setw(10) << Reg[20] << "R21: " << left << setw(10) << Reg[21] << "R22: " << left << setw(10) << Reg[22] << "R23: " << left << setw(10) << Reg[23]  << std::dec << endl;
        std::cout << std::hex << "R24: " << left << setw(10) << Reg[24] << "R25: " << left << setw(10) << Reg[25] << "R26: " << left << setw(10) << Reg[26] << "R27: " << left << setw(10) << Reg[27] << "R28: " << left << setw(10) << Reg[28] << "R29: " << left << setw(10) << Reg[29] << "R30: " << left << setw(10) << Reg[30] << "R31: " << left << setw(10) << Reg[31]  << std::dec << endl;
        cout << "----------------------------------------------------------------------------------------------------------------" << endl << endl;
    }
}

void print_usage()
{
    cout << "--------------------" << endl;
    cout << "       Usage:       " << endl; 
    cout << "--------------------" << endl; 
    cout << "Help:             h" << endl;  
    cout << "Quit:             q" << endl;  
    cout << "Step run:         n" << endl;
    cout << "Free run:         c" << endl;
    cout << "Registers:        r" << endl;
    cout << "Instruction:      i" << endl;
    cout << "Verbose Print:    p" << endl;
    cout << "Memory Access:    m" << endl;
    cout << "--------------------" << endl << endl;
}

void debugger(uint32_t mode, uint8_t *memory_r, uint32_t instruction)
{   
    uint32_t address, index;

    if (mode == 2)
    {   int flg = 1;
        while (inp != 'c')
        {   
            if (inp == 'n' || flg == 1)
            {
                std::cout << std::hex << "Instruction Address: " << instruction << " " << "PC: " << PC << std::dec << endl; 
            }
            cout << "(rdb) ";
            cin >> inp;
            switch(inp)
            {
                case 'c':
                    return;
                    break;
                
                case 'n': 
                    return;
                    break;
                
                case 'm':
                    flg = 0;
                    cout << "Address: ";
                    cin >> address;
                    cout << "Mem[" << address << "]: " << std::hex << (int)memory_r[address + 3] << (int)memory_r[address + 2] << (int)memory_r[address + 1] << (int)memory_r[address] << std::dec << endl;
                    break;
                
                case 'r':
                    flg = 0;
                    cout << "Register Index: ";
                    cin >> index;
                    cout << "Reg[" << index << "]: " << std::hex << Reg[index] << std::dec << endl;
                    break;

                case 'i':
                    flg = 0;
                    cout << "Instruction(hex): " << std::hex << instruction << std::dec << "  "<< "Instruction(bin): "<< std::bitset<32>(instruction) << endl;
                    break;

                case 'p':
                    flg = 0;
                    verbose_print(instruction, 1, Debug_mode);
                    break;

                case 'h':
                    flg = 0;
                    print_usage();
                    break;

                case 'q':
                    flg = 0;
                    exit(0);
                    break;    
                
                default:
                    flg = 0;
                    print_usage();
                    break;
            }
        }

    }
}