/*Diseñe e implemente un Firmware sobre la EDU-CIAA que haga parpadear un led con un periodo de 250 ms.
El sistema debe permitir seleccionar uno de entre 4 de los leds disponibles empleando una tecla para cada led.
Tec 1: Selecciona LED RGB (uno de los tres colores)
Tec 2: Selecciona LED 1.
Tec 3: Selecciona LED 2.
Tec 4: Selecciona LED 3.*/

/*==================[inclusions]=============================================*/
#include "control_led.h"       /* <= own header */
#include "stdint.h"


/*==================[macros and definitions]=================================*/
#define INTERVALO 250

/*==================[internal data declaration]==============================*/
 uint8_t tecla;
 uint8_t led_encendido=0;
 uint8_t retardo;
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

	Habilitar_interrup (); //funcion que habilita las interrupciones
	Periodo_timer (INTERVALO); //Hago parpadear leds cada intervalo= 250 ms

    for(;;)
    {
    	tecla=Leer_tecla (); //leo la tecla apretada

    //Programo la accion a ejercutarse segun la tecla apretada
    	switch (tecla){
    	    		case TEC1: led_encendido=LED0B; //Tec 1: Selecciona LED RGB (uno de los tres colores)
    	    			break;
    	    		case TEC2: led_encendido=LED1;   //Tec 2: Selecciona LED 1
    	    			break;
    	    		case TEC3: led_encendido=LED2;   //Tec 3: Selecciona LED 2
    	    			break;
    	    		case TEC4: led_encendido=LED3;   //Tec 4: Selecciona LED 3
    	    			break;
    	}
      	if (tecla!=0) //si hay tecla apretada y apago todos los leds
       	{
  //         for(retardo=0; retardo<100000;retardo++); //hago antiretardo

          Apagar_todos_led ();
     	}
 //   	led++;
    }
}

void ISR_RIT (void)
{

  	Invertir_led (led_encendido);  //Hago titilar todos los leds

	Borrar_bandera (); //funcion que limpia el flag
}


/*==================[end of file]============================================*/

