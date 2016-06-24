#ifndef DAC_H
#define DAC_H

#include "chip.h" //cargo la libreria de PLCOPEN


/*==================[macros and definitions]=================================*/

//Declaro las funciones

void Inicializar_dac (void);

void Escribir_dac (uint32_t valor);



#endif /* #ifndef DAC_H */
