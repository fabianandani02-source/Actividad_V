/*
 * indicator.c
 * Control simple del LED de la placa (PC13).
 *
 * Notas:
 * - PC13 se configura como salida push-pull (o push-pull reducida) y se controla
 *   mediante BSRR para operaciones atómicas.
 */

#include <stm32f10x.h>
#include "indicator.h"

void indicator_init(void)
{
    /* Habilitar reloj GPIOC */
    RCC->APB2ENR |= (1 << 4); // IOPCEN

    /* PC13 salida 2 MHz push-pull (0x2) */
    GPIOC->CRH &= ~(0xF << 20);
    GPIOC->CRH |=  (0x2 << 20);

    /* Apagar por defecto */
    indicator_off();
}

void indicator_on(void)
{
    /* PC13 low -> LED ON (en placas Blue Pill) */
    GPIOC->BSRR = (1U << 29); /* reset bit 13 (BSRR upper bits) */
}

void indicator_off(void)
{
    /* PC13 high -> LED OFF */
    GPIOC->BSRR = (1U << 13); /* set bit 13 */
}

void indicator_toggle(void)
{
    if (GPIOC->ODR & (1U << 13)) {
        indicator_on();
    } else {
        indicator_off();
    }
}
