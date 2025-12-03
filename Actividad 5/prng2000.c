/*
 * prng2000.c
 * Generador pseudoaleatorio eficiente para microcontrolador.
 *
 * Notas:
 * - Implementa un LCG de 32 bits (uso de overflow natural para mod 2^32).
 * - Provee prng_init() y prng_next_u32() para consumo por otros módulos.
 */

#include "prng2000.h"

/* Estado interno */
static uint32_t prng_state_local = 0xC0FFEEu;

/* Constantes (diseñadas para buen periodo en 32-bit LCG) */
static const uint32_t PRNG_A = 1664525u;
static const uint32_t PRNG_C = 1013904223u;

void prng_init(uint32_t seed)
{
    if (seed == 0) seed = 0xC0FFEEu;
    prng_state_local = seed;
}

uint32_t prng_next_u32(void)
{
    prng_state_local = (PRNG_A * prng_state_local) + PRNG_C;
    return prng_state_local;
}
