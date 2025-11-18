#ifndef MODE_DMA_H
#define MODE_DMA_H

/* Ejecuta modo que inicia una transferencia DMA para enviar todo el buffer.
   - Envía un encabezado textual.
   - Inicia la transferencia DMA del buffer pool_values reinterpretado como bytes.
   - Espera a la finalización y luego envía un mensaje de fin.
   - Mientras DMA trabaja, el LED parpadea (demostración de CPU no bloqueado).
*/
void mode_dma_send(void);

#endif /* MODE_DMA_H */
