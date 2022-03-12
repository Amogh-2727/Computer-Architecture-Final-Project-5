#include<stdint.h>
#include "defs.h"
#include "all_types.cpp"
#include <stdio.h>

void instruction_Fetch(uint32_t no_instr, uint8_t *memory_r)
{
    int opcode;
    long int temp1,temp2,temp3, temp4;
    uint32_t instruction;

    while(1)
    {
        Reg[0] = 0;
        temp1 = memory_r[PC] & 0xFF;
        temp2 = memory_r[PC + 1] & 0xFF;
        temp3 = memory_r[PC + 2] & 0xFF;
        temp4 = memory_r[PC + 3] & 0xFF;

        instruction = ((temp4 << 24) | (temp3 << 16) | (temp2 << 8) | (temp1));

        opcode = memory_r[PC] & 0x7F;

        debugger(Debug_mode, memory_r, instruction);

        switch(opcode){
            case 51:
                R_type(instruction, memory_r);
                break;

            case 19:
                I_type(instruction, memory_r);
                break;

            case 3:
                LD_type(instruction, memory_r);
                break;
            
            case 35:
                STR_type(instruction, memory_r);
                break;

            case 99:
                B_type(instruction, memory_r);
                break;

            case 55:
                LUI_type(instruction, memory_r);
                break;

            case 23:
                AUIPC_type(instruction, memory_r);
                break;

            case 111:
                JAL_type(instruction, memory_r);
                break;

            case 103:
                JALR_type(instruction, memory_r);
                break;

            default: 
                unknown_instr(instruction);
                break;   
        }
        no_instr -= 1;
    }
}
