#include <stdint.h>
#include "mode_poll.h"
#include "comms.h"
#include "sram_pool.h"
#include "indicator.h"

/* Nota: delay_ms se asume definida en main (sujeto a la plataforma) */
extern void delay_ms(uint16_t ms);

void mode_poll_send(void)
{
    /* Encendido fijo del indicador durante el modo */
    indicator_on();

    /* Mensaje de inicio */
    comms_send_text("\r\n-- MODO POLLING INICIO --\r\n");

    /* Envio de todos los valores: cada valor 32-bit se transmite en 4 bytes (LSB primero)
       Esto permite que el receptor reciba datos binarios compactos */
    for (uint32_t i = 0; i < POOL_SIZE; ++i) {
        uint32_t v = pool_values[i];
        comms_send_byte((uint8_t)(v & 0xFFu));
        comms_send_byte((uint8_t)((v >> 8) & 0xFFu));
        comms_send_byte((uint8_t)((v >> 16) & 0xFFu));
        comms_send_byte((uint8_t)((v >> 24) & 0xFFu));
    }

    /* Mensaje de fin */
    comms_send_text("\r\n-- MODO POLLING FIN --\r\n");

    /* Indicador permanece encendido al terminar */
}
