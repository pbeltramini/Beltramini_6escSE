/* Diseñe e implemente un Firmware sobre la EDU-CIAA que genera una señal tipo diente de sierra de periodo
100 ms y excursion de 0 a 3V.
Incorpore al ejercicio anterior la funcionalidad de variar el periodo y la amplitud de la se~nal.
Tec 1: Aumenta la amplitud de la señal.
Tec 2: Disminuye la amplitud de la señal.
Tec 3: Aumenta el periodo de la señal.
Tec 4: Disminuye el periodo de la señal.*/


/*==================[inclusions]=============================================*/
#include "diente_sierra.h"       /* <= own header */
#include "stdint.h"


/*==================[macros and definitions]=================================*/

#define INTERVALO 1

/*==================[internal data declaration]==============================*/
uint32_t periodo=100;
uint32_t amplitud=930; //corresponde a una tension maxima de salida de 3 V
uint8_t tecla;
float paso;
uint8_t led=LED0G;
uint32_t contador=0;

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

int main(void)
{
	/* Llamo a las funciones de inicialización de los drivers  */
	Inicializar_timer ();
	Inicializar_led ();
	Inicializar_tecla ();
	Inicializar_dac ();

	Habilitar_interrup (); //funcion que habilita las interrupciones
	Periodo_timer (INTERVALO); //Hago parpadear leds cada intervalo=1ms


	paso=(float)(amplitud/periodo);

	for(;;);

 }

void ISR_RIT (void)
{

//	float contador_max=930;
	uint32_t valor;


//genero los escalones del diente de sierra. 10 muestras de ancho 9,3 ms c/u
	contador=contador + paso;  //incremento el contado de hasta el valor max amplitud
//	contador=contador + 9,3;

	if (contador>amplitud)
	{
		contador=0;
	  	Invertir_led (led);
	}

	valor= (uint32_t)contador;  //convierto el valor de contador que es float a enteo q recibe el dac

  	Escribir_dac (valor);  //paso el valor del contador para q se convierta en el dac

	Borrar_bandera (); //funcion que limpia el flag
}


/*==================[end of file]============================================*/

