#ifndef DEFS_H
#define DEFS_H

#define MEMSIZE 65536

uint8_t *memory_r = NULL;
uint32_t Reg[32];
uint32_t PC;
uint32_t Debug_mode = 0;

char inp = '\0';

int32_t sign_ext(uint32_t data, uint32_t size);

int load_code_to_mem(const char *t);

void print_regs();

void unknown_instr(uint32_t instruction);

void verbose_print(uint32_t instruction, uint32_t mode1, uint32_t mode2);

void print_usage();

void debugger(uint32_t Debug_mode, uint8_t *memory_r, uint32_t instruction);

#endif