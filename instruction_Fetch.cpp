#include<stdint.h>
#include "defs.h"
#include "all_types.cpp"
#include <stdio.h>

void instruction_Fetch(uint32_t no_instr, uint8_t *memory_r)
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
function_R(PC, memory_r);
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
