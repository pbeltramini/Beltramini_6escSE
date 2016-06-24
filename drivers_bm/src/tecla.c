/*==================[inclusions]=============================================*/
#include "tecla.h"
#include "stdint.h"

/*==================[macros and definitions]=================================*/
#define TECLA_PAQUETE 1
#define TEC1_PIN 0
#define TEC2_PIN 1
#define TEC3_PIN 2
#define TEC4_PIN 6
#define PORT_NUM_TEC123 0
#define PORT_NUM_TEC4 1
#define TEC1_BIT 4
#define TEC2_BIT 8
#define TEC3_BIT 9
#define TEC4_BIT 9


#define IN 0

/*==================[internal functions definition]==========================*/

void Inicializar_tecla (void)  //defino la funcion para inicializar todos los leds
{

//	Chip_GPIO_Init (LPC_GPIO_PORT);

	 Chip_SCU_PinMux(TECLA_PAQUETE,TEC1_PIN,MD_PUP |MD_EZI|MD_ZI,FUNC0); /* mapea P1_0 en GPIO0[4], TEC_1 y habilita el pull up */
	 Chip_SCU_PinMux(TECLA_PAQUETE,TEC2_PIN,MD_PUP |MD_EZI|MD_ZI,FUNC0); /* mapea P1_1 en GPIO0[8], TEC_2 y habilita el pull up */
	 Chip_SCU_PinMux(TECLA_PAQUETE,TEC3_PIN,MD_PUP |MD_EZI|MD_ZI,FUNC0); /* mapea P1_2 en GPIO0[9], TEC_3 y habilita el pull up */
	 Chip_SCU_PinMux(TECLA_PAQUETE,TEC4_PIN,MD_PUP |MD_EZI|MD_ZI,FUNC0); /* mapea P1_6 en GPIO1[9], TEC_4 y habilita el pull up */

	 Chip_GPIO_SetDir(LPC_GPIO_PORT, PORT_NUM_TEC123, 1<<4 | 1<<8 | 1<<9, IN); /*selecciono las teclas 1,2 y3 como entrada*/
	 Chip_GPIO_SetDir(LPC_GPIO_PORT, PORT_NUM_TEC4, 1<<9, IN); /*selecciono la tecla 4 como entrada*/
}

uint8_t Leer_tecla (void)
{
	uint8_t tecla=0;

	if (Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, PORT_NUM_TEC123, TEC1_BIT)==0){ //veo si tecla 1 esta presionada
		tecla= 1;
		}
	if (Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, PORT_NUM_TEC123, TEC2_BIT)==0){ //veo si tecla 2 esta presionada
		tecla= 2;
		}
	if (Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, PORT_NUM_TEC123, TEC3_BIT)==0){ //veo si tecla 3 esta presionada
		tecla= 3;
		}
	if (Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, PORT_NUM_TEC4, TEC4_BIT)==0){ //veo si tecla 4 esta presionada
		tecla= 4;
		}
	return tecla;
}
