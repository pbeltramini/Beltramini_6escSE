/* Diseñe e implemente un Firmware sobre la EDU-CIAA que permita adquirir una señal analogica de excursion
* entre 0 y 3.3V, presente en el pin CH1 del conector P1.
* El sistema debe encender el led rojo si la señal toma su valor maximo (>1020 d) y
* led verde si la señal toma su valor minimo (<5 d). Puede resolverlo por pooling.*/
/*2 parte: con una frecuencia de muestreo de 100 Hz (empleando el RIT por interrupciones).
 * El sistema debe analizar la excursión de la señal.
 * Encendiendo el led rojo se indica que la señal sobrepasa un umbral máximo.
 * Encendiendo el led verde se indica que el mínimo de la señal se encuentra por debajo de un umbral mínimo.
 * Los umbrlales podrán ajustarse empleando el teclado.
		Tec 1: Aumenta el valor del umbral.
		Tec 2: Disminuye el valor del umbral.*/

/*==================[inclusions]=============================================*/
#include "adquisicion_adc.h"       /* <= own header */
#include "stdint.h"


/*==================[macros and definitions]=================================*/

#define INTERVALO 10

/*==================[internal data declaration]==============================*/
uint16_t dato_convertido;
uint16_t valor_max=930;
uint16_t valor_min=5;
uint8_t tecla;
uint32_t amplitud1;
uint32_t amplitud2;
/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

int main(void)
{

	uint16_t umbral_max=1020; //amplitud maxima que puede tomar la señal
	uint16_t umbral_min=155; //corresponde a una tension minima de 0,5 V
	uint8_t retardo;

	/*Llamo las funciones de inicializacion de los drivers*/
	Inicializar_timer ();
	Inicializar_led ();
	Inicializar_tecla ();
	Inicializar_dac ();
	Inicializar_adc ();

	Periodo_timer (INTERVALO); // defino periodo de interrupcion a un periodo= intervalo
	Habilitar_interrup (); //funcion que habilita las interrupciones

	while (1)
		{
	   	tecla=Leer_tecla (); //leo la tecla apretada

	   	switch (tecla){	//Programo la acción segun la tecla apretada

	    		case TEC1:
	        	  	if (amplitud1<umbral_max){  //Tec 1: Aumenta el valor del umbral.
	        	  		amplitud1=amplitud1+10;
	        	  	}
	        	  	else{
	        	  		amplitud1=amplitud1;
	        	  	}
	        	  	valor_max=amplitud1;
	        	  	break;
	        	case TEC2:
	        		if (amplitud2>umbral_min){ //Tec 2: Disminuye el valor del umbral.
	        			amplitud2=amplitud2-10;
	        		}
	        		else{
	        			 amplitud2=amplitud2;
	        		}
	        		valor_min=amplitud2;
	        		break;
		}
		if (tecla!=0) //si hay tecla apretada, hago antirrebote  y apago todos los leds
	   	{
	       	Apagar_todos_led ();
	  		for(retardo=0; retardo<1000000;retardo++); //hago antirrebote
	   	}
		}
 }

void ISR_RIT (void)
{

	dato_convertido= Leer_adc ();  //Leo el valor convertido
	Escribir_dac (dato_convertido);  //paso el valor del contador para q se convierta en el dac

/*Implemento funcion que enciende led rojo si la señal toma su valor maximo y led verde
 * si la señal toma su valor minimo*/

	if (dato_convertido>valor_max)
	{
	  	Encender_led (LED2);
	}
	else
		Apagar_led (LED2);
	if (dato_convertido<valor_min)
	{
	  	Encender_led (LED3);
	}
	else
		Apagar_led (LED3);

	Borrar_bandera (); //funcion que limpia el flag
}


/*==================[end of file]============================================*/

