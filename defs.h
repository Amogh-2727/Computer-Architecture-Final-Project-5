#ifndef DEFS_H
#define DEFS_H

#include<stdint.h>

#define MEMSIZE 65536
uint32_t Reg[32];
uint32_t PC;

int32_t sign_ext(uint32_t data, uint32_t size)
{
    int32_t val = data;
    val = ((data << (32 - size)) >> (32 - size));
    return val;
}

#endif