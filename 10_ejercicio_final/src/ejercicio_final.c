/* */

/*==================[inclusions]=============================================*/
#include "ejercicio_final.h"       /* <= own header */
#include "stdint.h"


/*==================[macros and definitions]=================================*/

#define INTERVALO 10
#define TEC1 1
#define TEC2 2
#define TEC3 3
#define TEC4 4
/*==================[internal data declaration]==============================*/
uint32_t amp_min=310;
uint32_t amp_max=620;
uint32_t a=0;
uint8_t per=5;
uint32_t amplitud;
uint8_t tecla;
float senal_leida, senal;
float ganancia=1;
float offset=465;
float g, a;
int i;
uint16_senal_f;
uint16_t byte1, byte2, byte3, byte4;
uint16_t resto1, resto2, resto3;

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

int main(void)
{


	/* Llamo a las funciones de inicialización de los drivers*/
	Inicializar_timer ();
	Inicializar_led ();
	Inicializar_tecla ();
	Inicializar_dac ();
	Inicializar_adc ();
	Inicializar_uart ();

	Periodo_timer (INTERVALO); // defino periodo de interrupcion a un periodo= intervalo
	Habilitar_interrup (); //funcion que habilita las interrupciones

	amplitud=amp_min;

	while (1)
		{
	   	tecla=Leer_tecla (); //leo la tecla apretada

		senal_leida= Leer_adc ();  //Leo señal del generado de funciones y lo convierto

		senal=(uint16_t)(senal_leida * ganancia + offset);

		/*A cada dato convertido lo multiplico por la ganacia y le sumo el offset*/
		g=ganancia;
		a=offset;
		switch (tecla){
    	    	case TEC1:	//Tec 1: Amplifica la señal x (0.8, 0.9, 1, 1.1 y 1.2)
    	    			if (g <1.2)
						{
							g= g + 0.10;
						}
						else
						{
						g=g;
						}
						ganancia= g;
						Invertir_led(LED0R);
					break;

    	    	case TEC2:    //Tec 2: Atenua la señal x (0.8, 0.9, 1, 1.1 y 1.2)
   	    				if (g > 0.8)
   	    				{
   	    					g= g-0.10;
   	    				}
   	    				else
   	    				{
   	    					g=g;
   	    				}
   	    				ganancia= g;
   	    				Invertir_led(LED1);
   	    				break;

    	    		//Tec 3 y 4: Modifica el offset de la senal sumandole: +200mV, +100mV, 0, -100mV y -200mV
    	    		case TEC3:
    	    			if (a < 62) //comparo con 62 que equivale a 220mV
    	    			{
    	    				a= a-31;
    	    			}
    	    			else
    	    			{
    	    				a=a;
    	    			}
    	    			offset= a;
    					Invertir_led(LED2);
    	    			break;

    	    		case TEC4:
    	    			if (a > 403) //offset_min= 465(==1,5V) - 62(==200mV)
    	    			{
    	    				a= a+31;
    	    			}
    	    			else
    	    			{
    	    				a=a;
    	    			}
    	    			offset= a;
    	    			Invertir_led(LED0B);
    	    			break;
			}
		/*convierto el dato leido del dac a 4 bytes separados, luego a char y lo envio por  la uart*/
			senal_f=(uint16)senal
			byte1= (senal_f/1000);
			Enviar_byte (byte1 +'0');  //convierto a char y envio

			resto1= (uint16_t)(senal_f%1000);
			byte2= (resto1/100);
			Enviar_byte (byte2 + '0'); //convierto a char y envio

			resto2=(resto1 % 100);
			byte3= (resto2/10);
			Enviar_byte (byte3 +'0'); //convierto a char y envio

			resto3=(resto2 % 10);
			byte4= resto3;
			Enviar_byte (byte4 +'0'); //convierto a char y envio

			Enviar_byte ('\n\r');


		}
 }

void ISR_RIT (void)
{
/* Genero señal cuadrada de calibración */
	a=a+1;
	if (amplitud<amp_max)
	{
		if (a>per)
		{
			a=0;
			amplitud=amp_max;
		}
	}
	else if (a>per)
		{
			a=0;
			amplitud=amp_min;
		}

  	Escribir_dac (amplitud);  //paso el valor del contador al dac para ver señal en el osciloscopio
  	if (i>10){ //Espero 1 seg

  		Enviar_byte (ganancia+'0');
  		Enviar_byte (offset+'0');
  		Invertir_led (LED3);
  	}
  	i++;
	Borrar_bandera (); //funcion que limpia el flag
}


/*==================[end of file]============================================*/

