#include<stdint.h>
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
