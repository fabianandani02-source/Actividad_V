#ifndef MODE_POLL_H
#define MODE_POLL_H

/* Ejecuta modo basado en envio por polling.
   - Enciende indicador de forma fija.
   - Envía un encabezado de texto.
   - Envía los POOL_SIZE valores (cada uint32_t como 4 bytes, LSB primero).
   - Envía mensaje de fin y deja LED encendido.
*/
void mode_poll_send(void);

#endif /* MODE_POLL_H */
