#ifndef COMMS_H
#define COMMS_H

#include <stdint.h>

/* Inicializa USART1 a 9600 bps (PA9 TX, PA10 RX) */
void comms_init(void);

/* Envia un byte (polling): bloqueante hasta que la transmisión termine */
void comms_send_byte(uint8_t b);

/* Envia una cadena ASCII terminada en '\\0' usando comms_send_byte */
void comms_send_text(const char *txt);

/* Envia un bloque de bytes usando DMA (memoria -> USART1->DR)
   ptr: puntero al buffer de memoria
   length: número de bytes a transferir
   La función inicia la transferencia y retorna; para esperar la finalización
   llamar a comms_wait_dma_done() o usar la comprobación por flags.
*/
void comms_start_dma_transfer(uint8_t *ptr, uint32_t length);

/* Espera y limpia la bandera DMA de transferencia completa (bloqueante) */
void comms_wait_dma_done(void);

#endif /* COMMS_H */
