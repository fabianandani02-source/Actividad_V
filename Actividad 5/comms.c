/*
 * comms.c
 * Control del USART1 y del DMA para transmision por Bluetooth (HC-05 por ejemplo).
 *
 * Notas:
 * - Inicializa GPIOA para PA9 (TX) y PA10 (RX).
 * - Configura USART1 a 9600 bps (asume PCLK2 = 72 MHz).
 * - Provee envío por polling y por DMA (DMA1 Channel4).
 * - Provee función para esperar a que la transferencia DMA termine.
 */

#include <stm32f10x.h>
#include "comms.h"

void comms_init(void)
{
    /* Habilitar relojes: GPIOA y USART1 */
    RCC->APB2ENR |= (1<<2) | (1<<14);   // IOPAEN + USART1EN

    /* PA9: TX (AF push-pull 50MHz) */
    GPIOA->CRH &= ~(0xF << 4);
    GPIOA->CRH |=  (0x0B << 4);  // 1011 = AF Push-Pull, 50MHz

    /* PA10: RX (input floating) */
    GPIOA->CRH &= ~(0xF << 8);
    GPIOA->CRH |=  (0x04 << 8);  // 0100 = floating input

    /* Baudrate 9600 (PCLK2 = 72MHz): BRR = 72000000/9600 = 7500 */
    USART1->BRR = 7500;

    /* Habilitar USART, TX y RX */
    USART1->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}

void comms_send_byte(uint8_t b)
{
    /* Escribe el dato y espera TC (Transmission Complete) */
    USART1->DR = (uint16_t)b;
    while (!(USART1->SR & USART_SR_TC));
    /* Limpieza: escribir 0 sobre TC no es necesario con periferico STM, 
       pero se deja la bandera para compatibilidad con algunas rutinas. */
}

void comms_send_text(const char *txt)
{
    while (*txt) {
        comms_send_byte((uint8_t)*txt++);
    }
}

void comms_start_dma_transfer(uint8_t *ptr, uint32_t length)
{
    /* Habilitar reloj del DMA1 */
    RCC->AHBENR |= (1 << 0); // DMA1EN

    /* Habilitar DMA para transmision USART1 */
    USART1->CR3 |= USART_CR3_DMAT;

    /* Reset Channel4 configuration */
    DMA1_Channel4->CCR = 0;

    /* Direcciones */
    DMA1_Channel4->CPAR = (uint32_t)&(USART1->DR);  // periférico
    DMA1_Channel4->CMAR = (uint32_t)ptr;           // memoria
    DMA1_Channel4->CNDTR = length;                 // longitud (bytes)

    /* Configurar CCR: memoria increment, 8-bit periph & mem, dir mem->periph */
    /* MEMINC = bit7, DIR = bit4, PSIZE/MSIZE = 00 (8-bit) */
    DMA1_Channel4->CCR |= (1<<7) | (1<<4);

    /* Habilitar canal */
    DMA1_Channel4->CCR |= 1;
}

void comms_wait_dma_done(void)
{
    /* Flag Transfer Complete channel4 = TCIF4 = bit 13 in ISR,
       se limpia escribiendo 1 en la correspondiente IFCR bit (13) */
    /* Espera a TC */
    while (!(DMA1->ISR & (1 << 13)));

    /* Limpiar flag TCIF4 y GIF4 y HTIF4 y TEIF4 si fueran necesarios:
       escribir 1 en IFCR limpia la bandera correspondiente */
    DMA1->IFCR = (1 << 13);  // CTCIF4
}
