/**
 * @file		: isr.c
 * @brief		:Contiene todas las rutinas ISR
 * 	
 * @version	: 1.0
 * @date	: 24/11/2014
 * @author	: by_Ra!
===============================================================================
*/
#include "main.h"
#include "mdt.h"
#include "buffer.h"

/*---------------------Variables ------------------------*/
sfr16 T2 = 0xCC;
extern bit timer_1ms;
extern UNS_16 AUX[];
extern volatile UNS_16 msTicks;			 //definida en main.c
volatile bit Flag_Contando = OFF;			//indica si se esta realizando una cuenta
volatile UNS_16 Res1 = 0;
/*********************************************************************
 * @fn void isr_timer0()
 * @brief	rutina de interrupcion para el timer 0. Desborda cada 100us
 * @param[in] void
 * @return	void
 * Note: 
 **********************************************************************/
void isr_timer0 () interrupt 1 
{
	mdt();								// Maquina de Timer
	TH0 = T0_DESBORDE_H;
	TL0 = T0_DESBORDE_L + TL0;				// Recargamos el timer
	if(timer_1ms == OFF) //Cuenta de ms para el LCD que depende de msTicks
	{
		msTicks++;		
		timer_1ms_on; 	//recargamos
	}
}

/*********************************************************************
 * @fn void isr_ext1()
 * @brief	Indica el momento de guardar la cuenta
 * @param[in] void
 * @return	void
 * Note: -----
 **********************************************************************/
void isr_ext1 () interrupt 2 
{
	UNS_16 aux;
	if(Flag_Contando == OFF)	//!< En la primera IRQ no hay dato
	{                           
		Flag_Contando = ON;
		Res1 = 0; ;T2 = T2_RELOAD;
		TF2 = OFF; //Limpio el flag
		ET2 = ON; //Habilito la IRQ del T2
	}else                       
	{
		aux = T2;
		_BUFFER_Send( Res1, aux );//Guardo la cuenta
		Res1 = 0; T2 = T2_RELOAD;
	}
}

/*********************************************************************
 * @fn void isr_timer2()
 * @brief	
 * @param[in] void
 * @return	void
 * Note: 
 **********************************************************************/
void isr_timer2 () interrupt 5
{
	if(Res1 < 1200)
	{
		Res1++;
	}else 	//restauramos todo los valores. FUERA DE RANGO
	{
		ET2 = OFF;	// IRQ T2 OFF
		T2 = T2_RELOAD;		// Reload T2
		Flag_Contando = OFF;
	}
	TF2 = OFF;
}

/* --------------------------------- End Of File ------------------------------ */
