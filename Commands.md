Description

x0 -> hard coded to zero
x1 - x31 -> General purpose registers
x1 - > ra(return address)
x2 -> stack pointer

R -Type  | opcode = 27
Functions:
ADD
SUM
SLL
SLT
SLTU
XOR
SRL
SRA
OR
AND

I-Type | opcode = 19  | load opcode = 3
Functions:                Load functions:
ADDI
SLTI
SLTIU
XORI
ORI
ANDI
SLLI
SRLI
SRAI

S-Type | opcode = 35
SB
SH 
SW

B-Type | opcode = 99
BEQ
BNE
BLT
BGE
BLTU
BGEU

U-type | opcode = 55 | Auipc opcode =23
LUI              AUIPC

J- Type | opcode = 111
JAL
