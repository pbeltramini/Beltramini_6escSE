/* Diseñe e implemente un Firmware sobre la EDU-CIAA que genera una señal tipo diente de sierra de periodo 100 ms
 * y excursion de 0 a 3V. Incorpore al ejercicio anterior la funcionalidad de variar el periodo y la amplitud de la señal.
 * Tec 1: Aumenta la amplitud de la señal.
 * Tec 2: Disminuye la amplitud de la señal.
 * Tec 3: Aumenta el periodo de la señal.
 * Tec 4: Disminuye el periodo de la señal.*/


/*==================[inclusions]=============================================*/
#include "diente_sierra_variable.h"       /* <= own header */
#include "stdint.h"


/*==================[macros and definitions]=================================*/

#define INTERVALO 1

/*==================[internal data declaration]==============================*/
uint32_t periodo=10;  //corresponde a un periodo de la señal de 10 ms
uint32_t amplitud=465;  //corresponde a una amplitud de la señal de 1,5V
float paso;
uint8_t led;
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
	Periodo_timer (INTERVALO); //Llamo a la interrupcion con un período=intervalo


	uint8_t tecla;
	uint32_t amplitud_min=155; //corresponde a una tension minima de salida de 0,5 V
	uint32_t amplitud_max=1023;  //corresponde a una tension maxima de salida de 3,3 V
	uint32_t periodo_max=300; //corresponde a un periodo de 300 ms
	uint32_t periodo_min= 10; //corresponde a un periodo de 10 ms
	uint8_t retardo;

	for(;;)
    	{
	   	tecla=Leer_tecla (); //leo la tecla apretada

    	switch (tecla){	     //Programo la acción segun la tecla apretada
    	    	case TEC1:					//Tec 1: Aumenta la amplitud de la señal
    	    	  	if (amplitud<amplitud_max){
    	       			amplitud=amplitud+155; //incremento la amplitud de la señal en pasos de 0.5V
    	   	    	  	contador=0;/*reseteo para que no se tilde la tecla*/
    	       		  	led=LED0R;
    	    	  	}
    	       		break;
    	    	case TEC2:					//Tec 2: Disminuye la amplitud de la señal
    	    		if (amplitud>amplitud_min){
    	    			amplitud=amplitud-155; //decremento la amplitud de la señal en pasos de 0.5V
     	    			contador=0;/*reseteo para que no se tilde la tecla*/
    	    			led=LED1;
    	    		}
    	    		break;
    	    	case TEC3:   	 //Tec 3: Aumenta el periodo de la señal
   	    			if (periodo < periodo_max){  //pongo tope máximo de 300 ms al periodo
   	    				periodo=periodo+10;
   	    				contador=0;/*reseteo para que no se tilde la tecla*/
   	  	    			led=LED2;
   	    			}
   	    			break;
    	    	case TEC4:    //Tec 4: Disminuye el periodo de la señal..
    	    		if (periodo >periodo_min){  //pongo tope minimo de 10 ms al periodo
    	    			periodo=periodo-10;
    	    			contador=0;/*reseteo para que no se tilde la tecla*/
    	    			led=LED3;
    	    		}
    	    		break;
  	    	}
    	}

	if (tecla!=0) //si hay tecla apretada, hago antirrebote  y apago todos los leds
   	{
       	Apagar_todos_led ();
  		for(retardo=0; retardo<1000000;retardo++); //hago antirrebote
  	}
 }

void ISR_RIT (void)
{

//	float contador_max=930;
	uint32_t valor;
	paso=(float)(amplitud/periodo);

//genero los escalones del diente de sierra.
	contador=contador + paso;  //incremento el contado de hasta el valor max amplitud


	if (contador>amplitud)
	{
		contador=0;
	  	Invertir_led (led);
	}


	valor= (uint32_t)contador;  //convierto el valor de contador que es float a enteo q recibe el dac

  	Escribir_dac (valor);  //paso el valor del contador para que se convierta en el dac

	Borrar_bandera (); //funcion que limpia el flag
}


/*==================[end of file]============================================*/

