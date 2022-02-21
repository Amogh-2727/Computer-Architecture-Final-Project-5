#include<stdio.h>

int func_R(int PC){

long int instruct=0;
int rd;
int funct3;
int rs1;
int rs2;
int funct7;
long int temp1,temp2,temp3;

instruct=memory_r[PC]& 0xFF;
temp1=(instruct<<8);
temp1=memory_r[PC + 1]& 0xFF;
temp2=(temp1<<16);
temp2=memory_r[PC + 2]& 0xFF;
temp3=(temp2<<24);
temp3=memory_r[PC + 3]& 0xFF;

instruct=temp3;

rd=(instruct>>7)&& 0x1F;
funct3=(instruct>>5)&& 0x07;
rs1=(instruct>>3)&& 0x1F;
rs2=(instruct>>5)&& 0x1F;
funct7=(instruct>>5)&& 0x3F;

switch(funct3){
    case 0: {
        if(funct7=0) {

        Reg[rd -1]=Reg[rs1 -1]+Reg[rs2 -1];
        printf("ADD");
    }
    else{

        Reg[rd -1]=Reg[rs1 -1]-Reg[rs2-1];
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

        Reg[rd-1]=((Reg[rs1-1]& !Reg[rs2-1])|(!Reg[rs1-1]& Reg[rs2-1]);
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

        Reg[rd-1]=(Reg[rs1-1] | Reg[rs2-1]);
        printf("OR");
    }
    break;

    case 7: {
        
        Reg[rd-1]=(Reg[rs1-1] & Reg[rs2-1]);
        printf("AND ");
    }
    break;
}

}
