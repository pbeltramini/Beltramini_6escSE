
/*==================[inclusions]=============================================*/
#include "timer.h"
#include "stdint.h"

/*==================[macros and definitions]=================================*/

/*==================[internal functions definition]==========================*/

void Inicializar_timer (void)
{
	Chip_RIT_Init(LPC_RITIMER); /*funcion de inicializacion del temporizador*/
}

void Habilitar_interrup (void)  //funcion que habilita las interrupciones
{
	NVIC_EnableIRQ(RITIMER_IRQn);
}

void Periodo_timer (uint32_t intervalo)
{
	Chip_RIT_SetTimerInterval(LPC_RITIMER, intervalo);  //configuro el intervalo (en ms.) de interrupcion
}

void Borrar_bandera () //Funcion que borra flag
{
	Chip_RIT_ClearInt(LPC_RITIMER);
}

