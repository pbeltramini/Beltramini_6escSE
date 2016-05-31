
/*==================[inclusions]=============================================*/
#include "Psicodelia.h"       /* <= own header */
#include "stdint.h"


/*==================[macros and definitions]=================================*/
#define INTERVALO 100

/*==================[internal data declaration]==============================*/
uint8_t led=0;
/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/


int main(void)
{
   /* perform the needed initialization here */

	Inicializar_timer ();
	Inicializar_led ();

	Periodo_timer (INTERVALO); //Hago parpadear leds cada 100 ms
	Habilitar_interrup (); //funcion que habilita las interrupciones
    for(;;);
}


void ISR_RIT (void)
{
	Invertir_led (led);
	if (led++>LED3)
	{
		led=1;   //Hago titilat todos los leds

	}
	Borrar_bandera (); //funcion que limpia el flag
}



/*==================[end of file]============================================*/

