#ifndef ADC_H
#define ADC_H

#include "chip.h" //cargo la libreria de PLCOPEN


/*==================[macros and definitions]=================================*/
//Declaro las funciones

void Inicializar_adc (void);

uint16_t Leer_adc (void);



#endif /* #ifndef ADC_H */
