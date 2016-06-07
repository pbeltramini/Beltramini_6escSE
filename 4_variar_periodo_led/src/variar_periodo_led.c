/*Incorpore al ejercicio 3_control_led la funcionalidad de variar el periodo de parpadeo del led activo.
Tec 1: Selecciona el LED a la izquierda del actual.
Tec 2: Selecciona LED a la derecha del actual.
Tec 3: Disminuye el periodo de parpadeo.
Tec 4: Aumenta el periodo de parpadeo.*/


/*==================[inclusions]=============================================*/
#include "variar_periodo_led.h"       /* <= own header */
#include "stdint.h"


/*==================[macros and definitions]=================================*/
#define INTERVALO 10

/*==================[internal data declaration]==============================*/
 uint8_t tecla;
 uint8_t led_encendido;
 uint32_t retardo;
 uint32_t contador; //contador para variar la frecuenia
 uint32_t contador_max=25; //programo el tiempo máximo de la interrupcion a 250 ms

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

int main(void)
{
	Inicializar_timer (); //Llamo a la funcion
	Inicializar_led (); //Llamo a la funcion
	Inicializar_tecla (); //Llamo a la funcion

	Habilitar_interrup (); //funcion que habilita las interrupciones
	Periodo_timer (INTERVALO); //Hago parpadear leds cada 250 ms

	led_encendido=LED0R;

    for(;;)
    {
    	tecla=Leer_tecla (); //leo la tecla apretada

    	switch (tecla){	//Programo la acción segun la tecla apretada
    	    	case TEC1:
    	    	  	if (led_encendido>LED0R){  //Tec 1: Selecciona el LED a la izquierda del actual
//    	       			Apagar_led(led_encendido);
    	       			led_encendido--;
    	    	  	}
    	    		break;
    	    	case TEC2:
    	    		if (led_encendido<LED3){ //Tec 2: Selecciona LED a la derecha del actual
    	    			led_encendido++;
    	    		}
    	    		break;
    	    	case TEC3:    //Tec 3: Disminuye el periodo de parpadeo.
    	    		if (contador_max > 1)  //pongo tope minimo a 10 ms a contador
    	    		contador_max=contador_max-5;
    	    		contador=0;
    	    		break;
   	    		case TEC4:    //Tec 4: Aumenta el periodo de parpadeo.
   	    			if (contador_max < 200)  //pongo tope máximo de 2000 ms a contador
   	    			contador_max=contador_max+5;
   	    			contador=0;
   	    			break;
    	}

//    	Apagar_todos_led ();

      	if (tecla!=0) //si hay tecla apretada, hago antirrebote  y apago todos los leds
       	{
           	Apagar_todos_led ();
      		for(retardo=0; retardo<10000000;retardo++); //hago antirrebote
//           	Apagar_todos_led ();
      	}
    }
}

void ISR_RIT (void)
{
	contador++;
	if (contador==contador_max) //contador que me define el período de parpadeo
	{
		contador=0;
	  	Invertir_led (led_encendido);  //Hago titilar todos los leds
	}

	Borrar_bandera (); //funcion que limpia el flag
}


/*==================[end of file]============================================*/

