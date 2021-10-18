/**
 * @file	: mdt.c
 * @brief	: Funcion llamada desde una interrupcion de 100us la cual decrementa
 * un arrays donde cada elemento representa a un delay
 * @version	: 2.0 - C8051f020
 * @date	: 24/11/2014
 * @author	: by_Ra!
  * NOTE: 	ON = el timer esta encendido ( esta contando )
			OFF = el timer esta apagado	( no cuenta )
===============================================================================
*/

#include "main.h"
#include "mdt.h"
/*--------------------Variables Globales -----------------------------*/

UNS_16  AUX[8] = {0,0,0,0,0,0,0,0};

bit timer_2500us = OFF;
//bit timer_500us = OFF;
bit timer_1ms = OFF;
//bit timer_2ms = OFF;
//bit timer_5ms = OFF;
//bit timer_10ms = OFF;
bit timer_1s = OFF;
bit timer_2s = OFF; 
/*********************************************************************
 * @fn			: void mdt ( void )
 * @brief		: hace poolling a un array decrementando cada elemento en
 * caso de estar habilitado(por un define en otra parte del programa), al 
 * llegar a dicho elemento lo decrementa en caso de ser posible, de lo contrario
 * borra un flag informando la finalizacion del tiempo X
 * @param[in]	: void
 * @return		: void
 * Note: Comentar los timer que no se necesiten
 **********************************************************************/
void mdt ()
{
if (AUX[0]){AUX[0]--;}
	else {timer_2500us = OFF;}
/*
if (AUX[1]){AUX[1]--;}
	else {timer_500us = OFF;}
-*/
if (AUX[2]){AUX[2]--;}
	else {timer_1ms = OFF;}
/*-
if (AUX[3]){AUX[3]--;}
	else {timer_2ms = OFF;}
if (AUX[4]){AUX[4]--;}
	else {timer_5ms = OFF;}
/if (AUX[5]){AUX[5]--;}
	else {timer_10ms = OFF;}
-*/
if (AUX[6]){AUX[6]--;}
	else {timer_1s = OFF;}
if (AUX[7]){AUX[7]--;}
	else {timer_2s = OFF;}

}

/* --------------------------------- End Of File ------------------------------ */
