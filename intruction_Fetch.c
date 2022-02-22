void intruction_Fetch(uint32_t no_instr)
{
int opcode;
uint32_t NPC;
uint32_t incr = 0;
int start_loc =0;
while(no_instr!=0)
{

opcode=memory_r[start_loc + incr] & 0x7F;

switch(opcode){
case 27:
function_R(PC);
break;
case (19|3|103):
NPC=function_I(PC);
break;
case 35:
function_S(PC);
break;
case 99:
NPC=function_B(PC);
break;
case(55|23):
NPC=function_U(PC);
break;
case 111:
NPC=function_J(PC);
break;
}
no_instr -= 1;
incr += 4;
}
}
