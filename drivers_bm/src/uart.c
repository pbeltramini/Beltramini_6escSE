/*==================[inclusions]=============================================*/
#include "uart.h"
#include "stdint.h"

/*==================[macros and definitions]=================================*/
#define UART_PAQUETE 7
#define UART_PIN_TX 1
#define UART_PIN_RX 2

uint8_t dato;
/*==================[internal functions definition]==========================*/

void Inicializar_uart (void)
{
	/*UART2 (USB-UART) */
	Chip_UART_Init(LPC_USART2);
	Chip_UART_SetBaud(LPC_USART2, 115200);

	Chip_UART_SetupFIFOS(LPC_USART2, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0);

	Chip_UART_TXEnable(LPC_USART2);

	Chip_SCU_PinMux(UART_PAQUETE, UART_PIN_TX, MD_PDN, FUNC6); /* P7_1: UART2 TXD */
	Chip_SCU_PinMux(UART_PAQUETE,UART_PIN_RX, MD_PLN | MD_EZI  | MD_ZI, FUNC6); /* P7_2: UART2 RXD */
}

uint8_t Leer_byte (void)
{
	dato=Chip_UART_ReadByte(LPC_USART2);
	return dato;
}

void Enviar_byte (uint8_t dato)
{
	Chip_UART_SendByte(LPC_USART2, dato);
}
