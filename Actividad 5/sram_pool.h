#ifndef SRAM_POOL_H
#define SRAM_POOL_H

#include <stdint.h>
#include "prng2000.h"

/* Buffer global en SRAM para almacenar POOL_SIZE valores de 32 bits */
extern uint32_t pool_values[POOL_SIZE];

/* Rellena el buffer pool_values con POOL_SIZE valores usando prng */
void pool_fill_from_prng(void);

#endif /* SRAM_POOL_H */
