#include "sram_pool.h"
#include "prng2000.h"

/* Buffer en SRAM (global) */
uint32_t pool_values[POOL_SIZE];

void pool_fill_from_prng(void)
{
    for (uint32_t i = 0; i < POOL_SIZE; ++i) {
        pool_values[i] = prng_next_u32();
    }
}
