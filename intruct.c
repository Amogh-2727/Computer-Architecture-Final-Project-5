nclude<stdint.h>
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

					            temp1 = memory_r[PC] & 0xFF;
						            temp2 = memory_r[PC + 1] & 0xFF;
							            temp3 = memory_r[PC + 2] & 0xFF;
								            temp4 = memory_r[PC + 3] & 0xFF;

									            instruction = ((temp4 << 24) | (temp3 << 16) | (temp2 << 8) | (temp1));

										            opcode = memory_r[PC] & 0x7F;

											            switch(opcode){
													                case 51:
																                R_type(instruction);
																		                break;

																				            case 19:
																				                I_type(instruction);
																						                break;

																								            case 3:
																								                LD_type(instruction, memory_r);
																										                break;
																												            
																												            case 35:
																												                STR_type(instruction, memory_r);
																														                break;

																																            case 99:
																																                B_type(instruction);
																																		                break;

																																				            case 55:
																																				                LUI_type(instruction);
																																						                break;

																																								            case 23:
																																								                AUIPC_type(instruction);
																																										                break;

																																												            case 111:
																																												                JAL_type(instruction);
																																														                break;

																																																            case 103:
																																																                JALR_type(instruction);
																																																		                break;
																																																				        }
												            no_instr -= 1;
													            print_regs();
														        }
}
