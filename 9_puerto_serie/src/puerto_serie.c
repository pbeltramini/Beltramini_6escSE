/* Diseñe e implemente un Firmware sobre la EDU-CIAA que permita adquirir una señal analogica de excursion
entre 0 y 3.3V, presente en el CH1. El sistema debe enviar por el puerto serie una cadena de caracteres
con el valor en decimal del dato convertido.*/

/*==================[inclusions]=============================================*/
#include "puerto_serie.h"       /* <= own header */
#include "stdint.h"

/*==================[macros and definitions]=================================*/

#define INTERVALO 300

/*==================[internal data declaration]==============================*/
uint8_t i;
uint8_t data;
uint16_t dato;
uint16_t dato_r;
uint16_t byte1;
uint16_t byte2;
uint16_t byte3;
uint16_t byte4;
uint16_t resto1;
uint16_t resto2;
uint16_t resto3;
/*==================[internal functions declaration]=========================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

int main(void)
{
//	Inicializar_timer (); //Llamo a la funcion
	Inicializar_led (); //Llamo a la funcion
	Inicializar_tecla (); //Llamo a la funcion
	Inicializar_uart ();
	Inicializar_adc (); //Llamo a la funcion adc

	Habilitar_interrup (); //funcion que habilita las interrupciones
	Periodo_timer (INTERVALO); // defino periodo de interrupcion a un periodo= intervalo


//	char mensaje[]= "Hola, soy Paola....\n\r";

	while (1){
		/*do nothing */
		data= i = 0;



//		data= Chip_UART_ReadByte(LPC_USART2);
		data= Leer_byte();

		switch (data){
			case 'r':
				/*Invertir led rojo*/
				Invertir_led (LED2);
				break;
			case 'v':
				/*Invertir led verde*/
				Invertir_led (LED3);
				break;
			case 'a':
				/*Invertir led amarillo*/
				Invertir_led (LED1);
				break;
			default:
				data=0;
			}
		}
		/*Envio cadena de caracteres mensaje*/
/*		while ((Chip_UART_ReadLineStatus(LPC_USART2) & USART_LSR_THRE)!=0)
		{
			Chip_UART_SendByte(LPC_USART2, mensaje[i]);
			i++;
		}*/
	}


void ISR_RIT (void)
{

	dato_r= Leer_adc ();  //Leo el valor convertido

/*convierto el dato leido del dac a 4 bytes separados, luego a char y lo envio por  la uart*/
	byte1= (dato_r/1000);
	Enviar_byte (byte1 +'0');  //convierto a char y envio

	resto1= (dato_r%1000);
	byte2= (resto1/100);
	Enviar_byte (byte2 + '0'); //convierto a char y envio

	resto2=(resto1 % 100);
	byte3= (resto2/10);
	Enviar_byte (byte3 +'0'); //convierto a char y envio

	resto3=(resto2 % 10);
	byte4= resto3;
	Enviar_byte (byte4 +'0'); //convierto a char y envio

	Enviar_byte ('\n\r');
	Borrar_bandera (); //funcion que limpia el flag
}


/*==================[end of file]============================================*/

