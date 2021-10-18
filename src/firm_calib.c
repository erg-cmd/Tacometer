/**
 * @file	: firm_calib.c
 * @brief	: funciones para aproximar curvas a lineales
 * @version	: 2.0
 * @date	: 24/11/201405.12.2014 16:57:31
 * @author	: by_Ra!
===============================================================================
*/

#include "firm_calib.h"
#include "firm_lcd.h"
#include "barrido_teclado.h"

const int magnitud[] = {_CORRECCION_0_1,_CORRECCION_1_2,_CORRECCION_2_3,_CORRECCION_3_4,_CORRECCION_4_5,_CORRECCION_5_6,_CORRECCION_6_7,_CORRECCION_7_8,_CORRECCION_8_9,_CORRECCION_9_10,
						_CORRECCION_10_11,_CORRECCION_11_12,_CORRECCION_12_13,_CORRECCION_13_14,_CORRECCION_14_15,_CORRECCION_15_16,_CORRECCION_16_17,_CORRECCION_17_18,_CORRECCION_18_19,_CORRECCION_19_20,
						_CORRECCION_20_21,_CORRECCION_21_22,_CORRECCION_22_23,_CORRECCION_23_24,_CORRECCION_24_25,_CORRECCION_25_26,_CORRECCION_26_27,_CORRECCION_27_28,_CORRECCION_28_29};



/*********************************************************************
 * @fn void
 * @brief	entras con X y salis con Y en la recta de linealidad
 * @param[in]	void
 * @return		void
 * Note:		
 **********************************************************************/
 int Ajuste_RPM(UNS_16 rpm)
 {
	UNS_16 posicion = 0, aux = 0;
	posicion = rpm;
	if(posicion <_RANGO_RPM15)
	{
		if(posicion < _RANGO_RPM7)
		{
			if((posicion > _RANGO_RPM0) && (posicion < _RANGO_RPM1)) aux = magnitud[0];//EL VALOR a restar
			if((posicion > _RANGO_RPM1) && (posicion < _RANGO_RPM2)) aux = magnitud[1]; //EL VALOR a restar
			if((posicion > _RANGO_RPM2) && (posicion < _RANGO_RPM3)) aux = magnitud[2]; //EL VALOR a restar
			if((posicion > _RANGO_RPM3) && (posicion < _RANGO_RPM4)) aux = magnitud[3];//EL VALOR a restar
			if((posicion > _RANGO_RPM4) && (posicion < _RANGO_RPM5)) aux = magnitud[4];//EL VALOR a restar
			if((posicion > _RANGO_RPM5) && (posicion < _RANGO_RPM6)) aux = magnitud[5];//EL VALOR a restar
			if((posicion > _RANGO_RPM6) && (posicion < _RANGO_RPM7)) aux = magnitud[6];//EL VALOR a restar
		}else
		{
			if((posicion > _RANGO_RPM7) && (posicion < _RANGO_RPM8)) aux = magnitud[7];//EL VALOR a restar
			if((posicion > _RANGO_RPM8) && (posicion < _RANGO_RPM9)) aux = magnitud[8];//EL VALOR a restar
			if((posicion > _RANGO_RPM9) && (posicion < _RANGO_RPM10))  aux = magnitud[9];//EL VALOR a restar
			if((posicion > _RANGO_RPM10) && (posicion < _RANGO_RPM11)) aux = magnitud[10];//EL VALOR a restar
			if((posicion > _RANGO_RPM11) && (posicion < _RANGO_RPM12)) aux = magnitud[11];//EL VALOR a restar
			if((posicion > _RANGO_RPM12) && (posicion < _RANGO_RPM13)) aux = magnitud[12];//EL VALOR a restar
			if((posicion > _RANGO_RPM13) && (posicion < _RANGO_RPM14)) aux = magnitud[13];//EL VALOR a restar
			if((posicion > _RANGO_RPM14) && (posicion < _RANGO_RPM15)) aux = magnitud[14];//EL VALOR a restar
		}
	}else
	{
		if(posicion < _RANGO_RPM23)
		{
			if((posicion > _RANGO_RPM15) && (posicion < _RANGO_RPM16)) aux = magnitud[15];//EL VALOR a restar
			if((posicion > _RANGO_RPM16) && (posicion < _RANGO_RPM17)) aux = magnitud[16];
			if((posicion > _RANGO_RPM17) && (posicion < _RANGO_RPM18)) aux = magnitud[17];
			if((posicion > _RANGO_RPM18) && (posicion < _RANGO_RPM19)) aux = magnitud[18];
			if((posicion > _RANGO_RPM19) && (posicion < _RANGO_RPM20)) aux = magnitud[19];
			if((posicion > _RANGO_RPM20) && (posicion < _RANGO_RPM21)) aux = magnitud[20];
			if((posicion > _RANGO_RPM21) && (posicion < _RANGO_RPM22)) aux = magnitud[21];
			if((posicion > _RANGO_RPM22) && (posicion < _RANGO_RPM23)) aux = magnitud[22];
		}else
		{
			if((posicion > _RANGO_RPM23) && (posicion < _RANGO_RPM24)) aux = magnitud[23];//EL VALOR a restar
			if((posicion > _RANGO_RPM24) && (posicion < _RANGO_RPM25)) aux = magnitud[24];//EL VALOR a restar
			if((posicion > _RANGO_RPM25) && (posicion < _RANGO_RPM26)) aux = magnitud[25];//EL VALOR a restar
			if((posicion > _RANGO_RPM26) && (posicion < _RANGO_RPM27)) aux = magnitud[26];//EL VALOR a restar
			if((posicion > _RANGO_RPM27) && (posicion < _RANGO_RPM28)) aux = magnitud[27];//EL VALOR a restar
			if((posicion > _RANGO_RPM28) && (posicion < _RANGO_RPM29)) aux = magnitud[28];//EL VALOR a restar
		}
	}
	return aux;
 }
 
