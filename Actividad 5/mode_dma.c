#include <stdint.h>
#include "mode_dma.h"
#include "comms.h"
#include "sram_pool.h"
#include "indicator.h"
#include "stm32f10x.h"

/* delay_ms se define externamente en main.c */
extern void delay_ms(uint16_t ms);

void mode_dma_send(void)
{
    comms_send_text("\r\n-- MODO DMA INICIO --\r\n");

    /* Iniciar transferencia DMA: reinterpretamos pool_values como uint8_t* y longitud en bytes */
    uint8_t *byte_ptr = (uint8_t *)pool_values;
    uint32_t byte_len = POOL_SIZE * sizeof(pool_values[0]);

    /* Arrancamos DMA (no bloqueante) */
    comms_start_dma_transfer(byte_ptr, byte_len);

    /* Mientras la DMA hace la transferencia, CPU parpadea LED y puede ejecutar otras tareas */
    while (!(DMA1->ISR & (1 << 13))) {
        /* Parpadeo visual para evidenciar que CPU sigue ejecutando código */
        indicator_toggle();
        delay_ms(80);
    }

    /* Esperar y limpiar flag DMA (bloqueante breve) */
    comms_wait_dma_done();

    comms_send_text("\r\n-- MODO DMA FIN --\r\n");

    /* Apagar indicador al concluir */
    indicator_off();
}
