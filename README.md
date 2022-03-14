# Computer-Architecture-Final-Project-5
##### RISC-V ISA Simulator

The instruction set architecture (ISA) level simulator for RISC-V was implemented in C++.

The simulator accepts the following three input parameters:
*	Input memory image file (default to program.mem)
*	Starting address(default to 0)
*	Stack address (default to 65535)

The only registers the simulator should get initialized with (except as a result of simulating the loaded
code) are the sp, pc, and ra (which the user should initialize to 0).The simulation will continue until
it encounters a jr ra instruction with ra == 0.

##### Project Framework

   program.c ----> assembly_code.s ----> assembly.o ----> program.mem ====> RISC-V ISA Simulator

##### Prerequisites

C++ compiler
Some of them are listed below:
*	Microsoft Visual C++ compiler
*	The GNU compiler collection
	

#### Running the tests

Modify the following cmd accordingly:
*	make all DEBUG=0/1/2 MEM_FILE=file.mem R_PC=0

Markup: Multiple Test cases were verified,they are listed below:
*	Misaligned PC
*	Invalid instruction 
*	Unit testes for the complete RV32 Instruction set.
*	Unit testes for signed values of the complete RV32 Instruction set.
*	Nested loops : Nested if – else loops and Nested for loops.
*	Zero register test
*	Function call 
*	Debugger was implemented along with the following modes:
    *	Mode 0 :Silent mode
    *	Mode 1 :Verbose mode
    *	Mode 2 :Debugger mode

*   Ability to single step and print contents of register, memory, display current instruction was implemented through the debugger along with a Help cmd to display the different commands under the debugger and also an option for quit and direct verbose print.

*	RV32I M-Extension: MUL / DIV operations were verified.

*	Implemented the ecall instruction to provide the given three system calls (Read, Write, Exit)


##### Authors

*   **Arjun Preetham Murugesh Ekalaivan** 
*   **Ritvik Tiwari** 
*   **Viraj Lodhia** 
*   **Amogh M Morey** 

##### Acknowledgments

* https://riscv.org/wp-content/uploads/2019/12/riscv-spec-20191213.pdf  // RISC instruction set pdf
* https://github.com/scotws/RISC-V-tests/blob/master/docs/riscv_linux_system_calls.md
	//Linux System Calls for RISC-V with GNU GCC/Spike/pk
