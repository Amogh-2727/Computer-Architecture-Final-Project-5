#include<stdio.h>

int func_R(int PC,, uint8_t *memory_r){

long int instruct=0;
int rd=0;
int funct3=0;
int rs1=0;
int rs2=0;
int funct7=0;
long int temp1,temp2,temp3,temp4;

temp1 = memory_r[PC]& 0xFF;
temp2 = memory_r[PC + 1]& 0xFF;
temp3 = memory_r[PC + 2]& 0xFF;
temp4 = memory_r[PC + 3]& 0xFF;

instr = ((temp4 << 24) | (temp3 << 16) | (temp2 << 8) | (temp1));

rd=(instruct>>7) & 0x1F;
funct3=(instruct>>5) & 0x07;
rs1=(instruct>>3) & 0x1F;
rs2=(instruct>>5) & 0x1F;
funct7=(instruct>>5) & 0x3F;

switch(funct3){
    case 0: {
        if(funct7=0) {

        Reg[rd]=Reg[rs1]+Reg[rs2];
        printf("ADD");
    }
    else{

        Reg[rd]=Reg[rs1]-Reg[rs2];
        printf("SUB");}
    }
    break;

    case 1:{
        
        Reg[rd]=Reg[rs1]<<Reg[rs2];
        printf("SLL");
    }
    break;

    case 2: {

        if(Reg[rs1]<Reg[rs2]){
            Reg[rd]=1;
        }
        else{
            Reg[rd]=0;
        }
        printf("SLT");
    }
    break;

    case 3: {
        if(Reg[rs1]<Reg[rs2]){
            Reg[rd]=1;
        }
        else{
            Reg[rd]=0;
        }
        printf("SLTU");
    }
    break;

    case 4: {

        Reg[rd]=((Reg[rs1]& !Reg[rs2])|(!Reg[rs1]& Reg[rs2]);
        printf("XOR");
         }
    break;

    case 5: {
        if(funct7=0) {
            Reg[rd]=Reg[rs1]>>Reg[rs2];
        printf("SRL");
        }
        else{
            Reg[rd]=Reg[rs1]>>Reg[rs2];
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
        
        Reg[rd]=(Reg[rs1] & Reg[rs2]);
        printf("AND ");
    }
    break;
}

}
