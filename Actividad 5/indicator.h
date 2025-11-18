#ifndef INDICATOR_H
#define INDICATOR_H

/* Inicializa LED indicador (PC13) */
void indicator_init(void);

/* Enciende LED (indicador) */
void indicator_on(void);

/* Apaga LED */
void indicator_off(void);

/* Alterna estado del LED */
void indicator_toggle(void);

#endif /* INDICATOR_H */
