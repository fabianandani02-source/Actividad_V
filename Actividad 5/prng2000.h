#ifndef PRNG2000_H
#define PRNG2000_H

#include <stdint.h>

/* Numero de elementos a generar */
#define POOL_SIZE 2000U

/* Inicializa el generador con una semilla */
void prng_init(uint32_t seed);

/* Devuelve el siguiente valor pseudoaleatorio de 32 bits */
uint32_t prng_next_u32(void);

#endif /* PRNG2000_H */
