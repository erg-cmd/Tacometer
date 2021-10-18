/**
 * @file	: firm_lcd.h
 * @brief	: Defines & declaracion de funciones de firm_lcd.c
 * @version	: 2.0* 
 * @date	: 24/11/2014
 * @author	: by_Ra!
===============================================================================
*/
#ifndef __MDT_H__
#define __MDT_H__

/*-defines----------------------*/

#define timer_2500us_on;	{timer_2500us = ON;	AUX[0] = 25;} 
#define timer_500us_on;		{timer_500us = ON;	AUX[1] = 5;}
#define timer_1ms_on;		{timer_1ms = ON;	AUX[2] = 10;} 
#define timer_2ms_on;		{timer_2ms = ON;	AUX[3] = 20;}  
#define timer_5ms_on;		{timer_5ms = ON;	AUX[4] = 50;}
#define timer_10ms_on;		{timer_10ms = ON;	AUX[5] = 100;}
#define timer_1s_on;		{timer_1s = ON;		AUX[6] = 10000;}
#define timer_2s_on;		{timer_2s = ON;		AUX[7] = 20000;}

#define T2_INCR_		T2++
#define T2_RESET_		T2 = 0

#define MODULO(A,B)			(A>B) ? (A-B) : (B-A)

/*-Prototipos de funciones-------*/

void mdt();

#endif

/*-----Fin de texto-----*/
