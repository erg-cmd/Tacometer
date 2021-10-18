 /**
 * @file		:buffer.h
 * @brief		: 
  * @version : 2.2
 * @date	: 24/11/2014
 * @author	: by_Ra!
===============================================================================
*/
#ifndef __BUFFER_H__
#define __BUFFER_H__

#include "main.h"

/*-------------------------Defines-----------------------------*/
/* buffer size definition */
#define BUFSIZE_N_MAX 100

/* Bufffer N-1 elementos */
#define __BUF_MASK(A) (A-1)
/* Check buf is full or not */
#define __BUF_IS_FULL(indice,length) (indice==length)
/* Check buf will be full in next receiving or not */
#define __BUF_WILL_FULL(head, tail) (tail==(head+2))
/* Check buf is empty */
#define __BUF_IS_EMPTY(head, tail) (head==tail)
/* Reset buf */
#define __BUF_RESET(bufidx)	(bufidx=0)
/* Increment buf */
#define __BUF_INCR(bufidx)	(bufidx=(bufidx+1))

#define __SEGtoRPM	600000000

#define _VALORES_RPM_N  20 //buffer de memoria para valores MAX,MIN,ETC
#define _CORRECCION_N	5 //puntos de interes para corregir

/*-------------------Estructuras de Datos----------------------*/
/** @brief Buffer */

typedef struct
{
	UNS_8	idx; 	//indice
	UNS_8 	BufferSize_N;
	UNS_32 cuenta[BUFSIZE_N_MAX];
} _BUFFER;

/*---------------------Prototipos de Funciones---------------------*/
UNS_32	_BUFFER_RPM(void);
bit		_BUFFER_Send(UNS_16, UNS_16);
UNS_8	_BUFFER_Nelements(void);
void 	_BUFFER_Init(void);
void 	_MEMORIA_Init(void);


#endif
