/**
 * @file		:main.h
 * @brief		:
 * @version	: 1.0
 * @date	: 24/11/2014
 * @author	: by_Ra!
===============================================================================
*/

#ifndef	__MAIN_H__
#define __MAIN_H__

/*-----------Includes--------------------*/
#include <C8051F020.H>

/*----------------	Tipos de Datos	--------------*/
typedef unsigned char UNS_8;
typedef unsigned int  UNS_16;
typedef unsigned long UNS_32;

/*----------------	defines	--------------*/
#define RESET 	0
#define SET		!RESET
#define FALSE	0
#define TRUE	!FALSE
#define OFF		0
#define ON		!OFF

#define PORT_LED P5
#define LED1 				0x10 // P5.5
#define LED2 				0x20 // P5.6
#define LED3 				0x40 // P5.7
#define LED4 				0x80 // P5.8

/*-------------------ESTADOS-------------------*/

#define __MEDIR 			0x01
#define __MOSTRAR 			0x02
#define __CORREGIR 			0x03

#define __MEDIR_READY		0x04
#define __MEDIR_RUNNING		0x05

/*------------------- MENU -------------------*/

#define _TECLA_SIG			'2'
#define _TECLA_OK			'3'
#define _TECLA_MUESTRAS_SIG	'5'
#define _TECLA_MUESTRAS_OK	'6'


#define _MENU_OFFSET  		0x00
#define _MENU_MUESTRA 		0x01
#define _MENU_MAX	  		0x02
#define _MENU_MIN	  		0x03
#define _MENU_PROM	  		0x04
#define _MENU_SALIR	  		0x05

#define _OPCIONdeMUESTREO 	5

/*------------------- MEDICION -------------------*/
//era 904 pero tenemos las rpm 5veces mas grandes, entonces X4.85
#define FACTORdeCORRECCION1 4384
#define FACTORdeCORRECCION2 100000

/*---------------------Defines---------------------
El timer0 va a desbordar cada 100us entonces el calculo
es: para un cristal de 11.0592Mhz ---> T/12 = 1.085us
 100us / 1.085us = 92 cuentas
 T0 desborde cada 100us
 T2 desborde cada 10us
----------------------------------------------------*/
//Timer 0
#define T0_DESBORDE_L	(0xFFFF-92)
#define T0_DESBORDE_H	(0xFFFF-92)>>8

//Timer 2
#define T2_RELOAD (0xFFFF-50000)

/*----Declaracion de Funciones--------------*/

void   firm_menu(UNS_8);
UNS_8  valor_maximo(void);
UNS_8  valor_minimo(void);
UNS_32 valor_promedio(void);
void   Separar_Digitos(UNS_32);

#endif
