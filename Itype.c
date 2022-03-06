/*+I-Type | opcode = 19  | load opcode = 3 | JALR opcode = 103
Functions:                Load functions:   Jump and Link Register:
ADDI                      LB                JALR
SLTI                      LH
SLTIU                     LW
XORI                      LBU
ORI                       LHU
ANDI
SLLI
SRLI
SRAI
*/
#include<stdint.h>
//#include "defs.h"
#include <stdio.h>

int function_I(int PC, uint8_t *memory_r){

long int instr=0;
int rd =0;
int funct3;
int rs1=0;
int imm=0;
int shamt=0;
int funct_I =0;

long int temp1,temp2,temp3, temp4;

temp1 = memory_r[PC]& 0xFF;
temp2 = memory_r[PC + 1]& 0xFF;
temp3 = memory_r[PC + 2]& 0xFF;
temp4 = memory_r[PC + 3]& 0xFF;

instr = ((temp4 << 24) | (temp3 << 16) | (temp2 << 8) | (temp1));

rd=(instr>>7)& 0x1F;
funct3=(instr>>12)& 0x07;
rs1=(instr>>15)& 0x1F;
imm = (instr>>20)& 0xFFF;

switch(funct3){
    case 0: {

        Reg[rd]=(int32_t)Reg[rs1] + sign_ext(imm, 12);
        printf("ADDI");
    }

    break;

    case 1: {

        shamt = (instr>>20)& 0x1F
        funct_I=(instr>>25)& 0x3F;
        if(funct_I = 0){
        Reg[rd]=(int32_t)Reg[rs1] << sign_ext(shamt, 5);
        printf("SLLI");
        }
    }

    break;

    case 2:{
        if ((int32_t)Reg[rs1] < sign_ext(imm, 12)){

        Reg[rd]= 1;

        }
       else {
           Reg[rd]= 0;
       }
        printf("SLTI");

    }
    break;

    case 3: {
        if ((int32_t)Reg[rs1] < (int32_t)imm){

        Reg[rd]= 1;

        }
       else {
           Reg[rd]= 0;
       }
        printf("SLTIU");
    }
    break;

    case 4: {

        Reg[rd]=(((int32_t)Reg[rs1] & !(sign_ext(imm, 12))|(!((int32_t)Reg[rs1]) & sign_ext(imm, 12)));
        printf("XORI");
    }
    break;


    case 5: {

        shamt = (instr>>20)& 0x1F
        funct_I=(instr>>25)& 0x3F;

        if (funct_I = 0X00){
        Reg[rd]=(int32_t )Reg[rs1] >> (int32_t )(shamt);
        printf("SRLI");
        }

        else if (funct_I = 0X02){
        Reg[rd]=(int32_t )Reg[rs1] >> sign_ext(shamt, 5);
        printf("SRAI");
        }
    }

    break;



    case 6:{

        Reg[rd]=((int32_t)Reg[rs1] | sign_ext(imm, 12));
        printf("ORI");
    }
    break;

    case 7: {

        Reg[rd-1]=((int32_t)Reg[rs1]  & sign_ext(imm, 12));
        printf("ANDI ");
    }
    break;
}

return 0;

}



