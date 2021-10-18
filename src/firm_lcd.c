/**
 * @file	: firm_lcd.c
 * @brief	: Inicializacion en 4 bits y funciones de manejo del LCD WH1602B
 * @version	: 2.0 - C8051f020
 * @date	: 24/11/2014 
 * @author	: by_Ra!
  * NOTE: faltaria la implementacion de una funcion que interprete un dato y me 
	lo imprima en su representacion decimal, hexa, etc.
===============================================================================
*/
#include <C8051F020.H>
#include "firm_lcd.h"

//debe definirse en el main
extern volatile UNS16 msTicks;

/*********************************************************************
 * @fn			: void LCD_Delay ( UNS16 msec )
 * @brief		: Genera un retraso de 0.x milisegundos
 * @param[in]	: UNS16 msec
 * @return		: void
 * Note: Simulando en Keil, tiene una latencia de 4ms - Funciona con 2ms
 **********************************************************************/

void LCD_Delay(UNS16 msec) 
{
	volatile UNS16 done = msTicks + msec;
	while (msTicks < done);
}

/*********************************************************************
 * @fn			: void LCD_WrtNibble ( UNS8 val )
 * @brief		: coloca el nibble bajo en LCD_PIN0, previo de un retardo 3-4ms
 * @param[in]	: UNS8 val
 * @return		: void
 * Note:  ----
 **********************************************************************/
 
void LCD_WrtNibble(UNS8 nibble) 
{
	UNS8 mask=0;
	LCD_Delay(4);//3
	mask=(LCD_PORT & ~(0x0F << LCD_PIN0));
	LCD_PORT = mask | ((nibble & 0x0F) << LCD_PIN0);
}
	
/*********************************************************************
 * @fn			: void LCD_WrtCmd ( UNS8 val )
 * @brief		: Manda comandos al LCD
 * @param[in]	: UNS8 val
 * @return		: void
 * Note:  Primero la parte Alta y despues la Baja del Nibble
 **********************************************************************/

void LCD_WrtCmd(UNS8 val)
{
	//Para comandos RS = 0
	LCD_WrtNibble(val>>4);
	CLEAR_PIN(LCD_PORT,LCD_PINRS);//RS = 0
	SET_PIN(LCD_PORT,LCD_PINE);  	// E = 1
//	LCD_Delay_40ns(5);//retardo 280ns
	 CLEAR_PIN(LCD_PORT,LCD_PINE);// E = 0
	LCD_WrtNibble(val);
	
	CLEAR_PIN(LCD_PORT,LCD_PINRS);//RS = 0
	SET_PIN(LCD_PORT,LCD_PINE);  	// E = 1
//	LCD_Delay_40ns(5);//retardo 280ns
	 CLEAR_PIN(LCD_PORT,LCD_PINE);// E = 0
	
}

/*********************************************************************
 * @fn			: void LCD_WrtData ( UNS8 caracter )
 * @brief		: Escribe un caracter en el display
 * @param[in]	: UNS8 caracter
 * @return		: void
 * Note:  Primero la parte Alta y despues la Baja del Nibble
 **********************************************************************/

void LCD_WrtData(UNS8 caracter)
{
	//Para escribir caracteres en display RS = 1
	LCD_WrtNibble(caracter>>4);
	SET_PIN(LCD_PORT,LCD_PINRS);//RS = 1
	SET_PIN(LCD_PORT,LCD_PINE);  	// E = 1
//	LCD_Delay_40ns(5);//retardo 280ns
	CLEAR_PIN(LCD_PORT,LCD_PINE);// E = 0
	LCD_WrtNibble(caracter);
	SET_PIN(LCD_PORT,LCD_PINRS);//RS = 1
	SET_PIN(LCD_PORT,LCD_PINE);  	// E = 1
//	LCD_Delay_40ns(5);//retardo 280ns
	CLEAR_PIN(LCD_PORT,LCD_PINE);// E = 0
}

/*********************************************************************
 * @fn			: void LCD_WrtString ( char* string )
 * @brief		: Imprime un string de UNS8, fin de cadena NULL
 * @param[in]	: UNS8* string
 * @return		: void
 * Note:  ----
 **********************************************************************/

void LCD_WrtString(char* string)
{
	LCD_Delay(4);//5
	while(*string)
	{
		LCD_WrtData(*string++);
	}
}

/*********************************************************************
 * @fn			: void LDC_GoToXY ( UNS8 x, UNS8 y )
 * @brief		: setea el cursor en la posicion x,y del LCD; X(0,1); Y(0,15)
 * @param[in]	: x posicion de fila(0,1) ; y posicion de columna (0,15)
 * @return		: void
 * Note: 
 **********************************************************************/

void LCD_GoToXY ( UNS8 x, UNS8 y ) 
{
    if ( y==0 )
    //	LCD_WrtCmd((1<<LCD_DDRAM)+LCD_START_LINE1+x);
		LCD_WrtCmd(0x80 + x);
    else /* y==1 */
    	//LCD_WrtCmd((1<<LCD_DDRAM)+LCD_START_LINE2+x);
		LCD_WrtCmd(0xC0 + x);
}

/*********************************************************************
 * @fn			: void LCD_Init ( void )
 * @brief		: Inicializacion y config-
 * -guracion particular
 * @param[in]	: void	 		
 * @return		: void
 * Note: CONFIGURAR SALIDA EN LA INICIALIZACION DE LOS PUERTOS
 **********************************************************************/

void LCD_Init(void) 
{
	// set all pins to output
	CLEAR_PIN(LCD_PORT,(LCD_PINRS|LCD_PINE)); // E = 0 y RS = 0
	LCD_Delay(2);
	LCD_WrtCmd(LCD_FUNCTION_SET_4BIT);//0x38 para 8bits y 28 para 4bits
	SET_PIN(LCD_PORT,LCD_PINE);  	// E = 1
//	LCD_Delay_40ns(5);//retardo 280ns
	CLEAR_PIN(LCD_PORT,LCD_PINE);// E = 0
	LCD_Delay(2);
	LCD_WrtCmd(LCD_DISP_ON_CUR_OFF);
	SET_PIN(LCD_PORT,LCD_PINE);  	// E = 1
//	LCD_Delay_40ns(5);//retardo 280ns
	CLEAR_PIN(LCD_PORT,LCD_PINE);// E = 0
	LCD_Delay(2);
	LCD_WrtCmd(LCD_DISPLAY_CLEAR);
	SET_PIN(LCD_PORT,LCD_PINE);  	// E = 1
//	LCD_Delay_40ns(5);//retardo 280ns
	CLEAR_PIN(LCD_PORT,LCD_PINE);// E = 0
	LCD_Delay(2);
	LCD_WrtCmd(LCD_INC_CURSOR);
	SET_PIN(LCD_PORT,LCD_PINE);  	// E = 1
//	LCD_Delay_40ns(5);//retardo 280ns
	CLEAR_PIN(LCD_PORT,LCD_PINE);// E = 0
	LCD_Delay(2);
	//LCD_WrtCmd(LCD_DISPLAY_ON);	// Hace visible el cursor y parpadea	
}

/* --------------------------------- End Of File ------------------------------ */
