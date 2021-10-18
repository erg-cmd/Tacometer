#ifndef __BARRIDO_TECLADO_H__
#define __BARRIDO_TECLADO_H__

#define		NO_KEY			0xFF

#define		CANTIDADdErEBOTES	30

/*-------------------------Defines-----------------------------*/


#define TECLADO_PORT  	P1			//Puerto a usar por el TECLADO

#define TECLADO_FILA1  	3		
#define TECLADO_FILA2 	4	  
#define TECLADO_FILA3  	7		
#define TECLADO_FILA4  	5		
#define TECLADO_COLUM1  2		
#define TECLADO_COLUM2  0		
#define TECLADO_COLUM3  1	

/*-
//	Para mi teclado rustico
#define TECLADO_FILA1  	4		
#define TECLADO_FILA2 	7	  
#define TECLADO_FILA3  	0		
#define TECLADO_FILA4  	3		
#define TECLADO_COLUM1  2		
#define TECLADO_COLUM2  5		
#define TECLADO_COLUM3  1	
-*/
/*---------------------Prototipos de Funciones---------------------*/

// Prototipos de barrido_teclado

void ReboteTecla(void);

unsigned char  LecturaTecla4x3 ( void );

unsigned char Teclado(void);

void actualizar_teclado (void);

/*------------------------------------------*/

#endif
