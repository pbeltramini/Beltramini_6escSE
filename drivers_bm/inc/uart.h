#ifndef UART_H
#define UART_H

#include "chip.h" //cargo la libreria de PLCOPEN


/*==================[macros and definitions]=================================*/
//Declaro las funciones

void Inicializar_uart (void);

uint8_t Leer_byte (void);

void Enviar_byte (uint8_t dato);

#endif /* #ifndef UART_H */
