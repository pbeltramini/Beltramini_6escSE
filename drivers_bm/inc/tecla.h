#ifndef TECLA_H
#define TECLA_H

#include "chip.h" //cargo la libreria de PLCOPEN
#include "stdint.h"



/*==================[macros and definitions]=================================*/


//Declaro las funciones para las teclas

void Inicializar_tecla (void);

uint8_t Leer_tecla (void);



#endif /* #ifndef TECLA_H */
