/**
 * @file		:barrido_teclado.c
 * @brief		: contiene Driver y Firm del Teclado 4x3
 * @version	: 1.2
 * @date	: 24/11/2014
 * @author	: by_Ra!
===============================================================================
*/
#include "barrido_teclado.h"
#include "main.h"
#include "mdt.h"

/*-------------------Variables Externas------------------------------*/

extern bit timer_2500us;
extern UNS_16	AUX[];
/*-------------------Variables Teclado------------------------------*/
static UNS_8 tecla = NO_KEY;	//!< buffer de teclado

// Filas del Teclado
sbit FILA_1 = TECLADO_PORT^TECLADO_FILA1;
sbit FILA_2 = TECLADO_PORT^TECLADO_FILA2;
sbit FILA_3 = TECLADO_PORT^TECLADO_FILA3;
sbit FILA_4 = TECLADO_PORT^TECLADO_FILA4;

// Columnas del Teclado
sbit COLUM_1 = TECLADO_PORT^TECLADO_COLUM1; 
sbit COLUM_2 = TECLADO_PORT^TECLADO_COLUM2; 
sbit COLUM_3 = TECLADO_PORT^TECLADO_COLUM3; 
/*********************************************************************
 * @fn void ReboteTecla()
 * @brief		Elimina el rebote de la tecla por soft
 * @param[in]	void 		 		
 * @return	void
 * Note: 
 **********************************************************************/
void ReboteTecla( void ) {
	
	static unsigned char CodigoAnterior = NO_KEY ;
	static unsigned char EstadosEstables = 0 ;
	unsigned char CodigoActual ;
      
	CodigoActual = LecturaTecla4x3( );				
	
	if( CodigoActual == NO_KEY ) {  //!< No se pulso tecla o rebote
		CodigoAnterior = NO_KEY ;
		EstadosEstables = 0 ;
		return ;
	}

	if( EstadosEstables == 0 )	{  //!< Primera vez
		CodigoAnterior = CodigoActual ;
		EstadosEstables = 1 ;
		return ;
	}

	if( EstadosEstables == CANTIDADdErEBOTES )	{  	//!< Acepto la tecla
		EstadosEstables = CANTIDADdErEBOTES + 1;	//!< Hará que no vuelva a entrar hasta que suelten la tecla
		tecla = CodigoAnterior ;	
		return ;
	}
	
	if( EstadosEstables > CANTIDADdErEBOTES )		//!< La tecla sigue pulsada
		return ;

	if( CodigoActual == CodigoAnterior )
		EstadosEstables ++ ;
	else
		EstadosEstables = 0 ;	
	return ;
}

/*********************************************************************
 * @fn unsigned char  LecturaTecla4x3 ( void )
 * @brief		Lectura del codigo de tecla con rebote de un teclado de 4 x 3
 * @param[in]	void 		 		
 * @return	unsigned char : Tecla ó NO_KEY si no se pulso tecla  
 * Note: 
 **********************************************************************/
unsigned char  LecturaTecla4x3( void ) 
{
 //Barro Fila 1
	 
	 FILA_1 = 0; FILA_2 = 1;FILA_3 = 1;FILA_4 = 1;

	  if(!COLUM_1) return  1;
	  if(!COLUM_2) return  2;
	  if(!COLUM_3) return  3;

//Barro Fila 2
	 FILA_1 = 1; FILA_2 = 0; FILA_3 = 1; FILA_4 = 1;

	  if(!COLUM_1) return  4;
	  if(!COLUM_2) return  5;
	  if(!COLUM_3) return  6;	


//Barro Fila 3
	 FILA_1 = 1; FILA_2 = 1; FILA_3 = 0; FILA_4 = 1;

	 if(!COLUM_1) return  7;
	 if(!COLUM_2) return  8;
	 if(!COLUM_3) return  9;

//Barro Fila 4
	 FILA_1 = 1; FILA_2 = 1; FILA_3 = 1; FILA_4 = 0;

	 if(!COLUM_1) return  10;
	 if(!COLUM_2) return  11;
	 if(!COLUM_3) return  12;

	  //Si no se presiono ninguna tecla.
	  return NO_KEY;
}
/*********************************************************************
 * @fn unsigned char  Teclado ( void )
 * @brief		Una vez que se lee la tecla limpia el buffer, es para aislar
 * el programa de esta variable impidiendo la modificacion directa
 * @param[in]	void 		 		
 * @return	unsigned char : Tecla ó NO_KEY si no se pulso tecla  
 * Note: 
 **********************************************************************/
unsigned char Teclado ()
{
   unsigned char Tecla;
   	 Tecla = tecla;
	 tecla = NO_KEY;
	 return Tecla;
}
/*********************************************************************
 * @fn unsigned char  LecturaTecla4x3 ( void )
 * @brief		Lee el teclado y vuelve a correr el timer del teclado
 * @param[in]	void 		 		
 * @return	void
 * Note: 
 **********************************************************************/
void actualizar_teclado ()
{
 if(timer_2500us == OFF){ReboteTecla();timer_2500us_on;}// actualiza el valor de tecla cada 2.5ms
}
/* --------------------------------- End Of File ------------------------------ */
