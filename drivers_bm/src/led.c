/* Copyright 2016, XXXXXXXXX  
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief Blinking Bare Metal driver led
 **
 **
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal LED Driver
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif
#include "led.h"
#include <stdint.h>


/*==================[macros and definitions]=================================*/
#define LED_PAQUETE 2
#define LED0R_PIN 0
#define LED0G_PIN 1
#define LED0B_PIN 2
#define LED1_PIN 14
#define LED2_PIN 11
#define LED3_PIN 12
#define PORT_NUM_LED0 5
#define PORT_NUM_LED1 0
#define PORT_NUM_LED2y3 1
#define OUT 1

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
// uint8_t led;
/*==================[internal functions definition]==========================*/

void Inicializar_led (void)  //defino la funcion para inicializar todos los leds
{
	 Chip_GPIO_Init (LPC_GPIO_PORT);

	 Chip_SCU_PinMux(LED_PAQUETE,LED0R_PIN,MD_PUP,FUNC4); /* mapea P2 0 en GPIO5[0], LED0R y habilita el pull up */
	 Chip_SCU_PinMux(LED_PAQUETE,LED0G_PIN,MD_PUP,FUNC4); /* mapea P2 1 en GPIO5[1], LED0G y habilita el pull up */
	 Chip_SCU_PinMux(LED_PAQUETE,LED0B_PIN,MD_PUP,FUNC4); /* mapea P2 2 en GPIO5[2], LED0B y habilita el pull up */
	 Chip_SCU_PinMux(LED_PAQUETE,LED1_PIN,MD_PUP,FUNC0); /* remapea P2 10 en GPIO0[14], LED1 y habilita el pull up */
	 Chip_SCU_PinMux(LED_PAQUETE,LED2_PIN,MD_PUP,FUNC0); /* remapea P2 11 en GPIO1[11], LED2 y habilita el pull up */
	 Chip_SCU_PinMux(LED_PAQUETE,LED3_PIN,MD_PUP,FUNC0); /* remapea P2 12 en GPIO1[12], LED3 y habilita el pull up */

	 Chip_GPIO_SetDir(LPC_GPIO_PORT, PORT_NUM_LED0, 1<<0 | 1<<1 | 1<<2, OUT); /*selecciono los 3 LED0 como salida*/
	 Chip_GPIO_SetDir(LPC_GPIO_PORT, PORT_NUM_LED1, 1<<14, OUT); /*selecciono el LED1 como salida*/
	 Chip_GPIO_SetDir(LPC_GPIO_PORT, PORT_NUM_LED2y3, 1<<11 | 1<<12, OUT); /*selecciono los LED2 y LED3 como salida*/
}


void Encender_led (uint8_t led)
{
 /*paso como parametro la direccion base del periferico GPIO, el numero de puerto y el bit a modificar*/
	switch (led){
		case LED0R: Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, PORT_NUM_LED0, LED0R_PIN);
				break;
		case LED0G: Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, PORT_NUM_LED0, LED0G_PIN);
				break;
		case LED0B: Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, PORT_NUM_LED0, LED0B_PIN);
				break;
		case LED1: Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, PORT_NUM_LED1, LED1_PIN);
				break;
		case LED2: Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, PORT_NUM_LED2y3, LED2_PIN);
				break;
		case LED3: Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, PORT_NUM_LED2y3, LED3_PIN);
				break;
	}
}

void Invertir_led (uint8_t led)
{
	 /*paso como parametro la direccion base del periferico GPIO, el numero de puerto y el bit a modificar*/
	switch (led){
		case LED0R: Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, PORT_NUM_LED0, LED0R_PIN);
				break;
		case LED0G: Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, PORT_NUM_LED0, LED0G_PIN);
				break;
		case LED0B: Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, PORT_NUM_LED0, LED0B_PIN);
				break;
		case LED1: Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, PORT_NUM_LED1, LED1_PIN);
				break;
		case LED2: Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, PORT_NUM_LED2y3, LED2_PIN);
				break;
		case LED3: Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, PORT_NUM_LED2y3, LED3_PIN);
				break;
	}
}

void Apagar_led (uint8_t led)
{
	 /*paso como parametro la direccion base del periferico GPIO, el numero de puerto y el bit a modificar*/
	switch (led){
		case LED0R: Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, PORT_NUM_LED0, LED0R_PIN);
				break;
		case LED0G: Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, PORT_NUM_LED0, LED0G_PIN);
				break;
		case LED0B: Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, PORT_NUM_LED0, LED0B_PIN);
				break;
		case LED1: Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, PORT_NUM_LED1, LED1_PIN);
				break;
		case LED2: Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, PORT_NUM_LED2y3, LED2_PIN);
				break;
		case LED3: Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, PORT_NUM_LED2y3, LED3_PIN);
				break;
	}
}

void Apagar_todos_led (void)
{
	 /*paso como parametro la direccion base del periferico GPIO, el numero de puerto y el bit a modificar*/
	Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, PORT_NUM_LED0, LED0R_PIN);
	Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, PORT_NUM_LED0, LED0G_PIN);
	Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, PORT_NUM_LED0, LED0B_PIN);
	Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, PORT_NUM_LED1, LED1_PIN);
	Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, PORT_NUM_LED2y3, LED2_PIN);
	Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, PORT_NUM_LED2y3, LED3_PIN);
}


/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */




/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

