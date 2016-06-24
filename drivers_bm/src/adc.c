/*==================[inclusions]=============================================*/
#include "adc.h"
#include "stdint.h"

/*==================[macros and definitions]=================================*/
#define ADC_ID 0
uint16_t dato_convertido;

/*==================[internal functions definition]==========================*/

 //Configuro para usar ADC0 de los dos que posee, canal 1
void Inicializar_adc (void)
{
	LPC_ADC_T ADCSetup; //defino la variable ADCSetup con tipo estructura LPC_ADC_T
	Chip_SCU_ADC_Channel_Config(ADC_ID, ADC_CH1);
	Chip_ADC_Init(LPC_ADC0, &ADCSetup);
	/*Habilito el ADC*/
	Chip_ADC_EnableChannel(LPC_ADC0, ADC_CH1, ENABLE);
}

uint16_t Leer_adc (void)
{
	/*Start A/D conversion */
	Chip_ADC_SetStartMode(LPC_ADC0, ADC_START_NOW, ADC_TRIGGERMODE_RISING);
	/*Espera hasta que termine la conversion*/
	while (Chip_ADC_ReadStatus(LPC_ADC0, ADC_CH1, ADC_DR_DONE_STAT) != SET) {}
	/*Lee el valor del ADC y retorna la posicionde de memoria donde esta el dato convertido*/
	Chip_ADC_ReadValue(LPC_ADC0, ADC_CH1, &dato_convertido);

	return dato_convertido;
}
