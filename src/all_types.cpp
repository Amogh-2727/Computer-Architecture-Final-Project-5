#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "defs.cpp"

using namespace std;

void trap(uint32_t instruction)
{
    cout << "VOID Instruction. Exiting...." << endl;
    verbose_print(instruction, 1, 1);
    exit(0);
}

int R_type(uint32_t instruction, uint8_t *memory_r)
{
    unsigned int rd = 0;
    unsigned int funct3 = 0;
    unsigned int rs1 = 0;
    unsigned int rs2 = 0;
    unsigned int funct7 = 0;
    unsigned long long int result = 0;

    rd = (instruction >> 7) & 0x1F;
    funct3 = (instruction >> 12) & 0x07;
    rs1 = (instruction >> 15) & 0x1F;
    rs2 = (instruction >> 20) & 0x1F;
    funct7 = (instruction >> 25) & 0x3F;

    switch(funct3){
        case 0: 
            if(funct7 == 0) {
                Reg[rd] = (uint32_t)((int32_t)Reg[rs1] + (int32_t)Reg[rs2]);
            }

            else if (funct7 == 1)
            {
                Reg[rd] = (uint32_t)((int64_t)Reg[rs1] * (int64_t)Reg[rs2]);
            }

            else{
                Reg[rd] = (uint32_t)((int32_t)Reg[rs1] - (int32_t)Reg[rs2]);
            }
            break;

        case 1: 
            if (funct7 == 1)
            {
                result = (uint64_t)((int64_t)Reg[rs1] * (int64_t)Reg[rs2]);
                Reg[rd] = (uint32_t)(result >> 32);
            }     
            else
            {
                Reg[rd] = Reg[rs1] << Reg[rs2];
            }
            break;

        case 2: 
            if (funct7 == 1)
            {
                result = (uint64_t)((int64_t)Reg[rs1] * (uint64_t)Reg[rs2]);
                Reg[rd] = (uint32_t)(result >> 32);
            }
            else
            {
                if((int32_t)Reg[rs1] < (int32_t)Reg[rs2]){
                    Reg[rd] = 1;
                }
                else{
                    Reg[rd] = 0;
                }
            }    
            break;

        case 3: 
            if (funct7 == 1)
            {
                result = (uint64_t)((uint64_t)Reg[rs1] * (uint64_t)Reg[rs2]);
                Reg[rd] = (uint32_t)(result >> 32);
            }

            else
            {
                if(Reg[rs1] < Reg[rs2]){
                    Reg[rd] = 1;
                }
                else{
                    Reg[rd] = 0;
                }
            }    
            break;

        case 4: 
            if (funct7 == 1)
            {
                Reg[rd] = (uint32_t)((int32_t)Reg[rs1] / (int32_t)Reg[rs2]);
            }
            
            else
            {
                Reg[rd] = Reg[rs1] ^ Reg[rs2];
            }
            break;    

        case 5: 
            if(funct7 == 0) {
                Reg[rd] = Reg[rs1] >> Reg[rs2];
            }

            else if (funct7 == 1)
            {
                Reg[rd] = (uint32_t)((uint32_t)Reg[rs1] / (uint32_t)Reg[rs2]);
            }

            else{
                Reg[rd] = (int32_t)Reg[rs1] >> Reg[rs2];
            }
            break;
        
        case 6:

            if (funct7 == 1)
            {
                Reg[rd] = (uint32_t)((int32_t)Reg[rs1] % (int32_t)Reg[rs2]);
            }

            else
            {
                Reg[rd] = Reg[rs1] | Reg[rs2];
            }
            break;

        case 7: 

            if (funct7 == 1)
            {
                Reg[rd] = (uint32_t)((uint32_t)Reg[rs1] / (uint32_t)Reg[rs2]);
            }

            else
            {
                Reg[rd] = Reg[rs1] & Reg[rs2];
            }
            break;

        default:
            unknown_instr(instruction);
            break;    
    }
    verbose_print(instruction, Debug_mode, Debug_mode);
    
    PC = PC + 4;

    return 0;
}

void I_type(int32_t instruction, uint8_t *memory_r){

    unsigned int rd = 0;
    unsigned int funct3 = 0;
    unsigned int rs1 = 0;
    unsigned int imm = 0;
    unsigned int funct7 = 0;
    unsigned int shamt = 0;

    rd = (instruction >> 7) & 0x1F;
    funct3 = (instruction >> 12) & 0x07;
    rs1 = (instruction >> 15) & 0x1F;
    imm = (instruction >> 20) & 0xFFF;

    switch(funct3)
    {
        case 0:
            Reg[rd] = (uint32_t)((int32_t)Reg[rs1] + sign_ext(imm, 12));
            break;

        case 1:
            Reg[rd] = Reg[rs1] << sign_ext(imm, 12);
            break;

        case 2:
            if ((int32_t)Reg[rs1] < sign_ext(imm, 12))
                Reg[rd] = 1;
            else 
                Reg[rd] = 0;
            break;

        case 3: 
            if ((uint32_t)Reg[rs1] < (uint32_t)(sign_ext(imm, 12)))
                Reg[rd] = 1;
            else
                Reg[rd] = 0;
            break;

        case 4:
            Reg[rd]=Reg[rs1] ^ sign_ext(imm, 12);
            break;

        case 5:
            funct7 = (imm & 0xFE0) >> 5;
            shamt = (imm & 0x01F);
            if (funct7 == 0)
                Reg[rd] = Reg[rs1] >> shamt;
            else
                Reg[rd] = (uint32_t)((int32_t) Reg[rs1] >> shamt);
            break;

        case 6:
            Reg[rd] = Reg[rs1] | sign_ext(imm, 12);
            break;

        case 7: 
            Reg[rd] = Reg[rs1] & sign_ext(imm, 12);
            break;

        default:
            unknown_instr(instruction);
            break;    
    }
    verbose_print(instruction, Debug_mode, Debug_mode);
    PC = PC + 4;
    return;
}

void LUI_type(uint32_t instruction, uint8_t *memory_r)
{
    unsigned int rd = 0, imm = 0;

    rd = (instruction >> 7) & 0x1F;
    imm = (instruction >> 12) & 0xFFFFF;
    
    Reg[rd] = (imm << 12);
    
    verbose_print(instruction, Debug_mode, Debug_mode);
    PC = PC + 4;

    return;
}

void AUIPC_type(uint32_t instruction, uint8_t *memory_r)
{
    unsigned int rd = 0, imm = 0;

    rd = (instruction >> 7) & 0x1F;
    imm = (instruction >> 12) & 0xFFFFF;

    Reg[rd] = PC + (imm << 12);

    verbose_print(instruction, Debug_mode, Debug_mode);
    PC = PC + 4;

    return;
}


void JAL_type(uint32_t instruction, uint8_t *memory_r)
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

    verbose_print(instruction, Debug_mode, Debug_mode);
    PC = PC + sign_ext(imm,21);

    return;
}

void JALR_type(uint32_t instruction, uint8_t *memory_r)
{
    unsigned int rd = 0, rs1 = 0, imm = 0;

    rd = (instruction >> 7) & 0x1F;
    rs1 = (instruction >> 15) & 0x1F;
    imm = (instruction >> 20) & 0xFFF;

    if (rs1 == 1 && Reg[rs1] == 0 && rd == 0 && imm == 0)
    {
        Reg[rd] = 0;
        PC = PC;
        print_regs();
        exit(0);
    }

    else
    {
        Reg[rd] = PC + 4;
        verbose_print(instruction, Debug_mode, Debug_mode);
        PC = (uint32_t)((int32_t)Reg[rs1] + sign_ext(imm,12));
    }

    return;
}

void B_type(uint32_t instruction, uint8_t *memory_r)
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
            verbose_print(instruction, Debug_mode, Debug_mode);
            if (Reg[rs1] == Reg[rs2])
                PC = PC + sign_ext(imm,13);
            else
                PC = PC + 4;
            break;

        case 1: 
            verbose_print(instruction, Debug_mode, Debug_mode);
            if (Reg[rs1] != Reg[rs2])
                PC = PC + sign_ext(imm,13);
            else
                PC = PC + 4;
            break;

        case 4: 
            verbose_print(instruction, Debug_mode, Debug_mode);
            if ((int32_t)Reg[rs1] < (int32_t)Reg[rs2])
                PC = PC + sign_ext(imm,13);
            else
                PC = PC + 4;
            break;

        case 5: 
            verbose_print(instruction, Debug_mode, Debug_mode);
            if ((int32_t)Reg[rs1] >= (int32_t)Reg[rs2])
                PC = PC + sign_ext(imm,13);
            else
                PC = PC + 4;
            break;

        case 6: 
            verbose_print(instruction, Debug_mode, Debug_mode);
            if (Reg[rs1] < (uint32_t)Reg[rs2])
                PC = PC + sign_ext(imm,13);
            else
                PC = PC + 4;
            break;

        case 7: 
            verbose_print(instruction, Debug_mode, Debug_mode);
            if (Reg[rs1] >= (uint32_t)Reg[rs2])
                PC = PC + sign_ext(imm,13);
            else
                PC = PC + 4;
            break;                     

        default:
            unknown_instr(instruction);
            break;      

    }

    return;
}

uint32_t load_mem(uint32_t address, uint32_t type, uint8_t *memory_r)
{
    uint32_t data = 0;
    uint32_t temp1 = 0, temp2 = 0, temp3 =0;

    if (address >= 0 && address <= MEMSIZE)
    {
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
    }
    else
    {
        cout << "Load from memory failed. Address out of bounds " << endl << endl;
        exit(0);
    }
    return data;
}

void store_mem(uint32_t address, uint32_t type, uint8_t *memory_r, uint32_t data)
{
    if (address >= 0 && address <= MEMSIZE)
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
    }
    else
    {
        cout << "Store to memory failed. Address out of bounds " << endl << endl;
        exit(0);
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
            unknown_instr(instruction);
            break;      

    }
    verbose_print(instruction, Debug_mode, Debug_mode);
    PC += 4;

    return;
}

void STR_type(uint32_t instruction, uint8_t *memory_r)
{
    unsigned int rs2 = 0, funct3 = 0, rs1 = 0, imm_l = 0, imm_u = 0;
    unsigned int imm = 0x00000000;
    int32_t offset;
    uint32_t address, data;
    imm_l = (instruction >> 7) & 0x1F;
    funct3 = (instruction >> 12) & 0x07;
    rs1 = (instruction >> 15) & 0x1F;
    rs2 = (instruction >> 20) & 0x1F;
    imm_u = (instruction >> 25) & 0x7F;
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
            unknown_instr(instruction);
            break;      

    }
    verbose_print(instruction, Debug_mode, Debug_mode);
    PC += 4;

    return;
}

void ECALL_type(uint32_t instruction, uint8_t *memory_r)
{
    uint32_t cnt = 0;
    char ch;
    uint32_t address;

    address = Reg[11];
    
    if (Reg[17] == 63 && Reg[10] == 0)
    {
        for (uint32_t i = 0; i < Reg[12]; i++)
        {
            std::cin >> ch;
            store_mem(address,0,memory_r,uint32_t(ch));
            cnt++;
            address++;
        }

        Reg[10] = cnt;
    }

    else if (Reg[17] == 64 && Reg[10] == 1)
    {
        for (uint32_t i = 0; i < Reg[12]; i++)
        {
            ch = char(load_mem(address, 0, memory_r));
            std::cout << ch;
            cnt++;
            address++;
        }

        std::cout << endl;

        Reg[10] = cnt;
    }

    else if (Reg[17] == 94 && Reg[10] == 0)
    {
        cout << "ALL OK. " << endl;
        exit(0);
    }

    verbose_print(instruction, Debug_mode, Debug_mode);
    PC = PC + 4;
}