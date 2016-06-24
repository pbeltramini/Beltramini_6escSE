/*==================[inclusions]=============================================*/
#include "dac.h"
#include "stdint.h"

/*==================[macros and definitions]=================================*/

/*==================[internal functions definition]==========================*/


void Inicializar_dac (void)
{
	Chip_SCU_DAC_Analog_Config();
	Chip_DAC_Init(LPC_DAC);
	Chip_DAC_ConfigDAConverterControl(LPC_DAC, DAC_DMA_ENA);
}

void Escribir_dac (uint32_t valor) //paso el dato digital al dac
{
	Chip_DAC_UpdateValue(LPC_DAC, valor);
}

