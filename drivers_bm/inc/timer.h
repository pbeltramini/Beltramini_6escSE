
#ifndef TIMER_H
#define TIMER_H

#include "chip.h" //cargo la libreria de PLCOPEN
#include "stdint.h"

//Declaro las funciones para el timer
void Inicializar_timer (void);

void Habilitar_interrup (void); //funcion que habilita las interrupciones

void Periodo_timer (uint32_t intervalo);

void Borrar_bandera (void); //funcion que limpia el flag




#endif /* #ifndef TIMER_H */




