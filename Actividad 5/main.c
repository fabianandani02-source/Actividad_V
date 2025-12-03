/*
 * main.c
 * Integración de módulos: genera 2000 números, guarda en SRAM, envía por polling y por DMA.
 *
 * Notas:
 * - Asegúrate de proporcionar la función delay_ms() para pausas simples.
 * - Debes incluir las cabeceras en tu proyecto y compilar con el CMSIS/startup apropiado.
 */

#include <stm32f10x.h>
#include <stdint.h>

#include "comms.h"
#include "prng2000.h"
#include "sram_pool.h"
#include "indicator.h"
#include "mode_poll.h"
#include "mode_dma.h"

/* Implementación simple de delay_ms para demostración (bloqueante).
   Ajustar conteo si tu compilador/velocidad difiere. */
void delay_ms(uint16_t ms)
{
    for (volatile uint32_t i = 0; i < (uint32_t)ms * 6000u; ++i) {
        __NOP();
    }
}

int main(void)
{
    /* Inicializaciones */
    indicator_init();
    comms_init();

    /* Inicializar PRNG y generar 2000 valores en SRAM */
    prng_init(0xBEEF1234u);
    pool_fill_from_prng();

    /* Demostración 1: envio por polling */
    mode_poll_send();

    /* Pequeña pausa antes de iniciar DMA */
    delay_ms(500);

    /* Demostración 2: envio por DMA (parpadeo de LED durante la transferencia) */
    mode_dma_send();

    /* Bucle infinito: parpadeo lento para indicar fin del flow */
    while (1) {
        indicator_toggle();
        delay_ms(300);
    }

    /* No llega aquí */
    return 0;
}
