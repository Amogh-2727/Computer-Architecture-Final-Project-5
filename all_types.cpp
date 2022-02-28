#include <stdint.h>
#include <stdlib.h>
#include "defs.h"
#include <stdio.h>

int function_R(int PC, uint8_t *memory_r){

long int instr=0;
int rd =0;
int funct3;
int rs1=0;
int rs2=0;
int funct7;
long int temp1,temp2,temp3, temp4;

temp1 = memory_r[PC]& 0xFF;
temp2 = memory_r[PC + 1]& 0xFF;
temp3 = memory_r[PC + 2]& 0xFF;
temp4 = memory_r[PC + 3]& 0xFF;

instr = ((temp4 << 24) | (temp3 << 16) | (temp2 << 8) | (temp1));

rd=(instr>>7)& 0x1F;
funct3=(instr>>12)& 0x07;
rs1=(instr>>15)& 0x1F;
rs2=(instr>>20)& 0x1F;
funct7=(instr>>25)& 0x3F;

switch(funct3){
    case 0: {
        if(funct7==0) {

        Reg[rd]=Reg[rs1] + Reg[rs2];
        printf("ADD");
    }
    else{

        Reg[rd]=Reg[rs1]-Reg[rs2];
        printf("SUB");}
    }
    break;

    case 1:{
         printf("SLL");
    }
    break;

    case 2: {
        printf("SLT");
    }
    break;

    case 3: {
        printf("SLTU");
    }
    break;

    case 4: {

        Reg[rd]=((Reg[rs1]& !Reg[rs2])|(!Reg[rs1]& Reg[rs2]));
        printf("XOR");
    }
    break;

    case 5: {
        if(funct7=0) {
        printf("SRL");
    }
    else{
        printf("SRA");
    }
    }
    break;
    
    case 6:{

        Reg[rd]=(Reg[rs1] | Reg[rs2]);
        printf("OR");
    }
    break;

    case 7: {
        
        Reg[rd-1]=(Reg[rs1] & Reg[rs2]);
        printf("AND ");
    }
    break;
}

return 0;
}

void LUI_type(uint32_t instruction)
{
    unsigned int rd = 0, imm = 0;

    rd = (instruction >> 7) & 0x1F;
    imm = (instruction >> 12) & 0xFFFFF;

    Reg[rd] = (imm << 12);
    PC = PC + 4;

    return;
}

void AUIPC_type(uint32_t instruction)
{
    unsigned int rd = 0, imm = 0;

    rd = (instruction >> 7) & 0x1F;
    imm = (instruction >> 12) & 0xFFFFF;

    Reg[rd] = PC + (imm << 12);
    PC = PC + 4;

    return;
}


void JAL_type(uint32_t instruction)
{
    unsigned int rd = 0, imm = 0, imm_19_12, imm_11, imm_10_1, imm_20;
    uint32_t zeromask = 0x00000000;

    rd = (instruction >> 7) & 0x1F;
    imm_19_12 = (instruction >> 12) & 0xFF;
    imm_11 = (instruction >> 20) & 0x01;
    imm_10_1 = (instruction >> 21) & 0x3FF;
    imm_20 = (instruction >> 31) & 0x01;
    imm = zeromask | (imm_10_1 << 1) | (imm_11 << 11) | (imm_19_12 << 12) | (imm_20 << 20);

    Reg[rd] = PC + 4;
    PC = PC + sign_ext(imm,21);

    return;
}

void JALR_type(uint32_t instruction)
{
    unsigned int rd = 0, funct3 = 0, rs1 = 0, imm = 0,;

    rd = (instruction >> 7) & 0x1F;
    funct3 = (instruction >> 12) & 0x07;
    rs1 = (instruction >> 15) & 0x1F;
    imm = (instruction >> 20) & 0xFFF;

    if (Reg[rs1] == 0 && rd == 0 && imm == 0 && funct3 == 0)
    {
        Reg[rd] = 0;
        PC = 0;
        exit(0);
    }

    else
    {
        Reg[rd] = PC + 4;
        PC = (uint32_t)((int32_t)Reg[rs1] + sign_ext(imm,12));
    }

    return;
}

void B_type(uint32_t instruction)
{
    
    unsigned int rs2 = 0, funct3 = 0, rs1 = 0, imm = 0, imm_12, imm_11, imm_10_5, imm_4_1;
    uint32_t zeromask = 0x00000000;

    imm_11 = (instruction >> 7) & 0x01;
    imm_4_1 = (instruction >> 8) & 0x0F;
    funct3 = (instruction >> 12) & 0x07;
    rs1 = (instruction >> 15) & 0x1F;
    rs2 = (instruction >> 20) & 0x1F;
    imm_10_5 = (instruction >> 25) & 0x3F;
    imm_12 = (instruction >> 31) & 0x01;
    imm = zeromask | (imm_4_1 << 1) | (imm_10_5 << 5) | (imm_11 << 11) | (imm_12 << 12);

    
    switch(funct3)
    {
        case 0: 
            if (Reg[rs1] == Reg[rs2])
                PC = PC + sign_ext(imm,13);
            else
                PC = PC + 4;
            break;

        case 1: 
            if (Reg[rs1] != Reg[rs2])
                PC = PC + sign_ext(imm,13);
            else
                PC = PC + 4;
            break;

        case 4: 
            if (Reg[rs1] < (int32_t)Reg[rs2])
                PC = PC + sign_ext(imm,13);
            else
                PC = PC + 4;
            break;

        case 5: 
            if (Reg[rs1] >= (int32_t)Reg[rs2])
                PC = PC + sign_ext(imm,13);
            else
                PC = PC + 4;
            break;

        case 6: 
            if (Reg[rs1] < (uint32_t)Reg[rs2])
                PC = PC + sign_ext(imm,13);
            else
                PC = PC + 4;
            break;

        case 7: 
            if (Reg[rs1] >= (uint32_t)Reg[rs2])
                PC = PC + sign_ext(imm,13);
            else
                PC = PC + 4;
            break;                     

        default:
            break;      

    }

    return;
}

void LD_type(uint32_t instruction, uint8_t *memory_r)
{
    unsigned int rd = 0, funct3 = 0, rs1 = 0, imm = 0;
    uint32_t zeromask = 0x00000000;
    uint32_t address;
    rd = (instruction >> 7) & 0x1F;
    funct3 = (instruction >> 12) & 0x07;
    rs1 = (instruction >> 15) & 0x1F;
    imm = (instruction >> 20) & 0xFFF;

    switch(funct3)
    {
        case 0: 
            address = (int32_t)Reg[rs1] + sign_ext(imm, 12);
            Reg[rd] = sign_ext(load_mem(address, 0, memory_r), 8);
            break;

        case 1: 
            address = (int32_t)Reg[rs1] + sign_ext(imm, 12);
            Reg[rd] = sign_ext(load_mem(address, 1, memory_r), 16);
            break;

        case 2: 
            address = (int32_t)Reg[rs1] + sign_ext(imm, 12);
            Reg[rd] = load_mem(address, 2, memory_r);
            break;

        case 4: 
            address = (int32_t)Reg[rs1] + sign_ext(imm, 12);
            Reg[rd] =  zeromask | (uint32_t)load_mem(address, 0, memory_r);
            break;

        case 5: 
            address = (int32_t)Reg[rs1] + sign_ext(imm, 12);
            Reg[rd] =  zeromask | (uint32_t)load_mem(address, 1, memory_r);
            break;      

        default:
            break;      

    }

    PC += 4;

    return;
}

void STR_type(uint32_t instruction, uint8_t *memory_r)
{
    unsigned int rs2 = 0, funct3 = 0, rs1 = 0, imm_l = 0, imm_u = 0;
    int32_t imm = 0x00000000;
    int32_t offset;
    uint32_t zeromask = 0x00000000;
    uint32_t address, data;
    imm_l = (instruction >> 7) & 0x1F;
    funct3 = (instruction >> 12) & 0x07;
    rs1 = (instruction >> 15) & 0x1F;
    rs2 = (instruction >> 20) & 0x1F;
    imm_u = (instruction >> 25) & 0x3F;

    imm = imm | (imm_u << 5) | (imm_l);
    offset = sign_ext(imm, 12);

    switch(funct3)
    {
        case 0: 
            address = (int32_t)Reg[rs1] + offset;
            data = Reg[rs2];
            store_mem(address, 0, memory_r, data);
            break;

        case 1: 
            address = (int32_t)Reg[rs1] + offset;
            data = Reg[rs2];
            store_mem(address, 1, memory_r, data);
            break;

        case 2: 
            address = (int32_t)Reg[rs1] + offset;
            data = Reg[rs2];
            store_mem(address, 2, memory_r, data);
            break;          

        default:
            break;      

    }

    PC += 4;

    return;
}

uint32_t load_mem(uint32_t address, uint32_t type, uint8_t *memory_r)
{
    uint32_t data = 0;
    uint32_t temp1 = 0, temp2 = 0, temp3 =0;


    switch(type)
    {
        case 0: //LB
            data = (uint32_t)memory_r[address];
            break;

        case 1: //LH
            temp1 = (uint32_t)memory_r[address + 1];
            data = (uint32_t)memory_r[address];
            data = (uint32_t)(data | (temp1 << 8)); 
            break;
            
        case 2: //LW
            temp3 = (uint32_t)memory_r[address + 3];
            temp2 = (uint32_t)memory_r[address + 2];
            temp1 = (uint32_t)memory_r[address + 1];
            data = (uint32_t)memory_r[address];
            data = (uint32_t)(data | (temp1 << 8) | (temp2 << 16) | (temp3 << 24)); 
            break;    

        default:
            break; 
    }

    return data;
}

void store_mem(uint32_t address, uint32_t type, uint8_t *memory_r, uint32_t data)
{

    switch(type)
    {
        case 0: //SB
            memory_r[address] = (uint8_t)(data & 0x000000ff);
            break;

        case 1: //SH
            memory_r[address] = (uint8_t)(data & 0x000000ff);
            memory_r[address + 1] = (uint8_t)((data & 0x0000ff00) >> 8);
            break;
            
        case 2: //SW
            memory_r[address] = (uint8_t)(data & 0x000000ff);
            memory_r[address + 1] = (uint8_t)((data & 0x0000ff00) >> 8);
            memory_r[address + 2] = (uint8_t)((data & 0x00ff0000) >> 16);
            memory_r[address + 3] = (uint8_t)((data & 0xff000000) >> 24);
            break;    

        default:
            break; 
    }

    return;
}
