/*
 * firm_calib.h
 * 
 * Copyright 2014 EliasG <eliasg@eliasg-M6275>
 * 
 * ARG - BUENOS AIRES.
 * 
 * 
 */
 
 #ifndef __FIRM_CALIB_H__
#define __FIRM_CALIB_H__

#include "main.h"

/*------------------------------------------------------------------*/
#define N_AJUSTES 12
 
#define _RANGO_RPM0		400
#define _RANGO_RPM1		800
#define _RANGO_RPM2		1300
#define _RANGO_RPM3		1400
#define _RANGO_RPM4		1500
#define _RANGO_RPM5		1600
#define _RANGO_RPM6		1700
#define _RANGO_RPM7		1900
#define _RANGO_RPM8		2000
#define _RANGO_RPM9		2100
#define _RANGO_RPM10	2200
#define _RANGO_RPM11	2300
#define _RANGO_RPM12	2500
#define _RANGO_RPM13	2700
#define _RANGO_RPM14	2900
#define _RANGO_RPM15	3200
#define _RANGO_RPM16	4000
#define _RANGO_RPM17	5500
#define _RANGO_RPM18	8500
#define _RANGO_RPM19	9500
#define _RANGO_RPM20	10000
#define _RANGO_RPM21	10500
#define _RANGO_RPM22	11000
#define _RANGO_RPM23	13000
#define _RANGO_RPM24	13500
#define _RANGO_RPM25	13725
#define _RANGO_RPM26	14000
#define _RANGO_RPM27	14250
#define _RANGO_RPM28	14500
#define _RANGO_RPM29	15000

//valores por 10 porque consideramos el decimal
#define _CORRECCION_0_1		-150
#define _CORRECCION_1_2		-350
#define _CORRECCION_2_3		-250
#define _CORRECCION_3_4		-100
#define _CORRECCION_4_5		 100
#define _CORRECCION_5_6		 350
#define _CORRECCION_6_7		 600
#define _CORRECCION_7_8		 500
#define _CORRECCION_8_9		 300
#define _CORRECCION_9_10	 100
#define _CORRECCION_10_11	-100
#define _CORRECCION_11_12	-200
#define _CORRECCION_12_13	-100
#define _CORRECCION_13_14	 100
#define _CORRECCION_14_15	-60
#define _CORRECCION_15_16	 500
#define _CORRECCION_16_17	 2000
#define _CORRECCION_17_18	 3250
#define _CORRECCION_18_19	 5000
#define _CORRECCION_19_20	 6500
#define _CORRECCION_20_21	 9000
#define _CORRECCION_21_22	 10000
#define _CORRECCION_22_23	 12000
#define _CORRECCION_23_24	 13750
#define _CORRECCION_24_25	 16000
#define _CORRECCION_25_26	 18000
#define _CORRECCION_26_27	 20000
#define _CORRECCION_27_28	 21000
#define _CORRECCION_28_29	 22000


/*--------------Declaramos los protipos------------------------------*/
int Ajuste_RPM(UNS_16 );

#endif
