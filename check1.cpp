#include <iostream>
#include <fstream>
#include <string>
#include<stdint.h>
#include <bits/stdc++.h>
#include "defs.h"
//#include "instruction_Fetch.c"
//#include "R_Type.c"

uint8_t *memory_r = NULL;

using namespace std;

int function_R(int PC){

long int instr=0;
int rd =0;
int funct3;
int rs1=0;
int rs2=0;
int funct7;
long int temp1,temp2,temp3, temp4;

temp1 = memory_r[PC]& 0xFF;
temp2=memory_r[PC + 1]& 0xFF;
temp3=memory_r[PC + 2]& 0xFF;
temp4=memory_r[PC + 3]& 0xFF;

instr = ((temp4 << 24) | (temp3 << 16) | (temp2 << 8) | (temp1));
printf ("instr: %lx" , instr);

rd=(instr>>7)& 0x1F;
funct3=(instr>>12)& 0x07;
rs1=(instr>>15)& 0x1F;
rs2=(instr>>20)& 0x1F;
funct7=(instr>>25)& 0x3F;
printf(" rs1: %d , rs2: %d", rs1, rs2);
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

}

void instruction_Fetch(uint32_t no_instr)
{
int opcode;
uint32_t NPC;
uint32_t incr = 0;
int start_loc =0;
while(no_instr!=0)
{

opcode=memory_r[PC + incr] & 0x7F;

switch(opcode){
case 51:
function_R(PC);
break;
case (19|3|103):
//NPC=function_I(PC);
break;
case 35:
//function_S(PC);
break;
case 99:
//NPC=function_B(PC);
break;
case(55|23):
//NPC=function_U(PC);
break;
case 111:
//NPC=function_J(PC);
break;
}
no_instr -= 1;
incr += 4;
}
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
    
    no_instr = load_code_to_mem(filename);
    Reg[14] = 2;
    Reg[15] = 7;
    
    instruction_Fetch(no_instr);
    print_mem(0, no_instr);
    print_regs();
    
    return 0;
}