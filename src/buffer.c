/**
 * @file		:buffer.c
 * @brief		:Se crea una cola para el manejo de datos y se realiza
 * el promedio, agregar a cola y sacar de cola
 * @version	: 1.3
 * @date	: 24/11/2014
 * @author	: by_Ra!
===============================================================================
*/

#include "buffer.h"

/*--------------Declaracion de variables locales---------------*/

 _BUFFER bm; //ver si hace falta agregar volatile 
 UNS_32 memoria[_VALORES_RPM_N]; //ultimos valores medidos
// _CORRECCION correc; //puntos de interes para correciones
 /**********************************************************************
 * @brief 	
 * @param[in]	none
 * @return 	UNS_16 las rpm para mostrar en display
 * Note : 
 *********************************************************************/
UNS_32 _BUFFER_RPM()
{
	UNS_32 promedio = 0, rpm;
	UNS_8 contador;
	bit ajuste = OFF;
	
	//Es necesario afectar las cuentas?
	for(contador=0;contador<bm.BufferSize_N;contador++)
	{
		if(bm.cuenta[contador] > 1000000)
		{ 
			ajuste = ON;
			break;
		}
	}
	
	//Afectamos de ser necesario
	if(ajuste)
	{
		contador = bm.BufferSize_N;
		while(contador)
		{
			bm.cuenta[contador-1] /= 100; //Dividimos sobre 100
			contador--;
		}
	}
	
	//Realizamos el promedio
	contador = __BUF_MASK(bm.BufferSize_N);
	while(contador)			
	{
		promedio += bm.cuenta[contador--];
	}
	promedio += bm.cuenta[0]; //El ultimo lo cargamos a mano
	promedio /= bm.BufferSize_N;	  //Divido sobre la cantidad N
	promedio *= FACTORdeCORRECCION1; //904
	promedio /= FACTORdeCORRECCION2; //10000 (una decada mas para cortar el decimal)
	if(ajuste){promedio*= 100;} 	 //Lo devolvemos al valor original
	rpm = (__SEGtoRPM/promedio);
	__BUF_RESET(bm.idx);	//reseteamos el indice
	return (UNS_32) rpm;
}

/********************************************************************//**
 * @brief 	
 * @param[in]	none
 * @return 	TRUE:cargo dato; FALSE: No cargo dato
 * Note : Primero chequeamos que le buffer no esta lleno
 *********************************************************************/
bit _BUFFER_Send(UNS_16 veces, UNS_16 cuenta)
{
	UNS_32 aux = 0;
	if (!__BUF_IS_FULL(bm.idx,bm.BufferSize_N)) 	//si NO esta lleno el buffer
	{ 
		aux = veces;
		aux *= 50000;
		bm.cuenta[bm.idx++] = aux + cuenta;	//Guardamos y post incrementamos
	}else
	{
		return  FALSE;
	}
	return TRUE;
}

/********************************************************************//**
 * @brief 	Devuelve la cantidad de elementos en el array
 * @param[in]	none
 * @return 		UNS_8 cantidad de elementos
 * Note : -
 *********************************************************************/
UNS_8 _BUFFER_Nelements()
{
	return (bm.idx);
}

/********************************************************************
 * @brief Inicializa el buffer y su indice, los carga con 0
 * @param[in]	none
 * @return 		none
 * Note: -
 *********************************************************************/
void _BUFFER_Init(void)
{
	for(bm.idx = 0; bm.idx < BUFSIZE_N_MAX;bm.idx++)  
	{
		bm.cuenta[bm.idx] = 0;
	}
	bm.idx = 0; // Limpia indice
	bm.BufferSize_N = BUFSIZE_N_MAX; //Valor por defecto, pueden ser menos cuentas
}

/********************************************************************
 * @brief Inicializa el buffer y su indice, los carga con 0
 * @param[in]	none
 * @return 		none
 * Note: -
 *********************************************************************/
void _MEMORIA_Init(void)
{
	UNS_8 contador = 0;
	for(contador = 0; contador<_VALORES_RPM_N;contador++)  
	{
		memoria[contador] = 0;
	}
}
/* --------------------------------- End Of File ------------------------------ */
