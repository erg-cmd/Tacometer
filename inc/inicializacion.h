/**
 * @file		:inicializacion.h
 * @brief		:
 * @version	: 1.0
 * @date	: 24/11/2014
 * @author	: by_Ra!
===============================================================================
*/

#ifndef __INICIALIZACION_H__
#define __INICIALIZACION_H__


/*---------------------Defines---------------------
El timer0 va a desbordar cada 100us entonces el calculo
es: para un cristal de 11.0592Mhz ---> T/12 = 1.085us
 
100us / 1.085us = 92 cuentas
T0 desborde cada 100us
 
* El T2 en primera instancia contará hasta los 5.925ms. En caso de 
* desbordar se cargara el valor para que desborde cada 1us y sirva como
* base de tiempo para las demas
* 
* Timer2 

*Por la distribucion del Crossbar la /INT1 quedo dispuesta en el P0^4
*al estar ruteadas a los puertos la UART0 Y UART1 (P0^0-3 respectivamente)
*---------------------------------------------------------------------*/
//Timer 0
#define T0_DESBORDE_L	(0xFFFF-92)
#define T0_DESBORDE_H	(0xFFFF-92)>>8
					
//Timer 2
#define T2_RELOAD (0xFFFF-50000)

#define RESET 0
#define SET		!RESET
#define FALSE	0
#define TRUE	!FALSE


/*---------------------Prototipos de Funciones---------------------*/
void Inicializacion();

#endif
