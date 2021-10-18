/**
 * @file		:Inicializacion.c
 * @brief		:
 * 	
 * @version	: 1.0
 * @date	: 24/11/2014
 * @author	: by_Ra!
===============================================================================
*/
#include <C8051F020.H>
#include "inicializacion.h"

/*--------------------------Variables Especiales--------------------*/
sfr16 T0 = 0x8A;
sfr16 T2 = 0xCC;
sfr16 RCAP2 = 0xCA;

/*********************************************************************
 * @fn void Inicializacion ()
 * @brief	Seteo de WDT, OSCX, PUERTOS e INTERRUP
 * @param[in]	void	
 * @return	void
 * Note: Al timer0 lo utilizamos como base de tiempo de 1ms
 **********************************************************************/
void Inicializacion()
{
	unsigned int i;	//!< variable para retardo

	//-------SETEO WDT-----------------------
	WDTCN = 0xDE;   // Deshabilito el watchdog timer
	WDTCN = 0xAD;	// por ahora........
	//--------FIN WDT	------------------------

	//-------SETEO Oscilador Externo-----------------------
	OSCXCN = 0x67;					// Configuro el registro de control del oscilador 
									// 01100111
									// Habilito el oscilador para funcionar con cristal (22.1184MHz)
									// Configuro el rango de trabajo del oscilador
	for (i=0; i < 256; i++);		// Demora "Cuidado esta demora (bloqueante) se puede hacer porque 
									// estoy en la inicializacion y no bloqueo ningun otro proceso!!!!
									// Hay que hacer esta demora para que se estabilice el oscilador
	while (!(OSCXCN & 0x80));		// Espero hasta que se estabilice (Cuidado es bloqueante!!)
	OSCICN = 0x88;					// Configuro el oscilador interno
									// 10001000
									// Configuro el micro para utilizar el oscilador externo
	while (!(OSCXCN & 0x80));		// Espero hasta que se estabilice (Cuidado es bloqueante!!)
	OSCICN = 0x08;					// Configuro el oscilador interno
									// 00001000
									// Configuro el micro para utilizar el oscilador externo
	//-------FIN Oscilador Externo-----------------------	

	//-------SETEO PUERTOS-----------------------	
	//Seteo para pulsadores	(0 = Open-Drain \ 1 = Push-Pull)
	P74OUT = 0xFB;					// 1111 1011
//	P1MDOUT = 0x99;					//Para mi teclado Rustico
	P1MDOUT = 0xB8;					// 1011 1000 Configuro los Puertos del teclado
	P2MDOUT = 0xFF;					//Pueto LCD
	XBR0 = 0x04;					// Ruteo pins P0.0 y P0.1 a la uart0
	XBR1 = 0x10;					// ruteo /INT1 a un pin
	XBR2 = 0x44;					// Ruteo pins P0.2 y P0.3 a la uart1, 
									// Habilito la crossbar y habilito lo pull ups
	//-------FIN 	PUERTOS-----------------------	

	//-------SETEO TIMER-----------------------
		//El T2 se encuentra en modo recarga y 16 bits
	CKCON |= 0x20;					// T2 tiene la frec del sistema 
	TMOD = 0x91;  					//Timer 0 en modo 16 bits
	TL0 = T0_DESBORDE_L;				//desborda cada 100us
	TH0 = T0_DESBORDE_H;				//desborda cada 100us
	T2 = T2_RELOAD;
	RCAP2 = T2_RELOAD;				//idem
	//-------FIN 	TIMER-----------------------	
 
	//-------SETEO INTERRUP-----------------------	
	TF0 = RESET;					//borro el flag de desborde timer 0
	ET0 = SET;						//habilito la interrupcion por desborde timer 0
	IT1 = SET; 						//Seteo deteccion por flanco descendete /INT1
	EA  = SET;  					//habilito la interrupcion global
	//-------FIN 	INTERRUP-----------------------	
}

/* --------------------------------- End Of File ------------------------------ */
