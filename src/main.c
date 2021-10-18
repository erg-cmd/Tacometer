/**
 * @file :main.c
 * @brief : 
 * @version	: 1.4
 * @date	: 24/11/2014
 * @author	: by_Ra!
 * @note	: Se cambio la manera de presentar los datos en pantalla, ahora 
 * hara el promedio de los datos que tenga y mostrara este promedio in/completo
 * cada 1s
========================================================================
*/

#include "main.h"
#include "inicializacion.h"
#include "mdt.h"
#include "buffer.h"
#include "firm_lcd.h"
#include "barrido_teclado.h"
#include "firm_calib.h"

/*-------------------Variables Externas------------------------------*/
extern bit timer_2500us;
extern bit timer_1s;
extern bit timer_2s;
extern UNS_16 AUX[]; //declarada en mdt.c
extern _BUFFER bm; //variable del buffer que hace el promedio
extern UNS_32 memoria[];
extern bit Flag_Contando; //declarada en isr.c
/*-----------------------Variables-----------------------------------*/
const UNS_8 CARACT[] = {'$','1','2','3','4','5','6','7','8','9','*','0','#'};
const UNS_8 BUFFER_SIZE_0[] = {" N =  2"};
const UNS_8 BUFFER_SIZE_1[] = {" N =  5"};
const UNS_8 BUFFER_SIZE_2[] = {" N = 10"};
const UNS_8 BUFFER_SIZE_3[] = {" N = 50"};
const UNS_8 BUFFER_SIZE_4[] = {" N =100"};
const UNS_8 BUFFER_SIZE_5[] = {2,5,10,50,100};
const UNS_8 *BUFFER_SIZE[] = {BUFFER_SIZE_0,BUFFER_SIZE_1,BUFFER_SIZE_2,BUFFER_SIZE_3,BUFFER_SIZE_4};


const UNS_8 Menu_0[] = {"Offset "};
const UNS_8 Menu_1[] = {"Muestra"};
const UNS_8 Menu_2[] = {" MAX    "};
const UNS_8 Menu_3[] = {" MIN    "};
const UNS_8 Menu_4[] = {" Prom   "};
const UNS_8 Menu_5[] = {" Salir  "};
const UNS_8 *Menu_[] = {Menu_0,Menu_1,Menu_2,Menu_3,Menu_4,Menu_5};

const UNS_8 Mens_0[] = {"TACO 14 | RPM"};
const UNS_8 Mens_1[] = {"  ME-I  |"};
const UNS_8 Mens_2[] = {"2:v 3:>"};
const UNS_8 Mens_3[] = {"5:v 6:>"};
const UNS_8 *Mens_[] = {Mens_0,Mens_1,Mens_2,Mens_3};

volatile UNS_16 msTicks; //Cuenta mili segundos. (firm_LCD)
volatile UNS_8 Digito[] = {0,0,0,0,0,'.',0,0};
volatile bit FLAG_MUESTRA = OFF;
volatile UNS_32 Offset = 1;
extern   UNS_16 Res1; //declarada en isr.c
/*********************************************************************
 * @fn void main()
 * @brief		
 * @param[in]	void 
 * @return	void
 * Note:
 **********************************************************************/
void main()
{
	volatile  UNS_32 periodo = 0; 	//var auxiliar para guardar el PROMEDIO
	UNS_8 tecla = NO_KEY, estado = __MEDIR, estado_medir = __MEDIR_READY;
	UNS_8 idx = 0;
	int delta = 0;	// para guardar la correccion a las rpm
	
	Inicializacion();	//Seteos de Perifericos
	TR0 = SET; 			//Habilito el Timer0
	LCD_Init();			//Incializo el LCD
	LCD_WrtCmd(LCD_DISPLAY_CLEAR);	//Borro el LCD, ahora se puede escribir!

	
	
	//Programa Principal---------------------------------------------
	LCD_WrtString(Mens_[0]); //Menu de Operacion
	LCD_GoToXY(0,1);
	LCD_WrtString(Mens_[1]);
	
	_BUFFER_Init(); 	//Limpia los elementos del buffer
	_MEMORIA_Init();	//Limpia el buffer de la memoria
	while(1) //Programa Principal
	{
		switch (estado)
		{
			case __MEDIR:
					switch(estado_medir)
					{
						case __MEDIR_READY:		//!< Seteo IRQ EXT1
								IE1 = RESET;	// Flag IRQ EXT1
								EX1 = SET;		//Habilito IRQ EXT1
								TR2 = ON; //Habilito el Timer 2
								estado_medir = __MEDIR_RUNNING;
						break;

						case __MEDIR_RUNNING: 	//!< Tacometro midiendo o en condiciones
							
							if(_BUFFER_Nelements() >= bm.BufferSize_N) //cuando se llena el buffer dejamos de tomar muestras
							{
								estado = __MOSTRAR;	//Saltamos a la siguiente posicion
								break;
							}
						
							actualizar_teclado(); //!< Sensado de Teclado
							tecla = Teclado();
							if(tecla != NO_KEY) //en caso de que haya una tecla apretada.
							{
								LCD_GoToXY(0,1); 		 //opciones abajo
								if(FLAG_MUESTRA == OFF)
								{
									LCD_WrtString(Mens_[2]); //opciones para moverse
								}else
								{
									LCD_WrtString(Mens_[3]); //opciones para moverse
								}
								firm_menu(CARACT[tecla]);//menu de opciones
							}
							
							if(!timer_1s) //!<Blink
							{
							 timer_1s_on;
							 P5 = ~P5;
							}
						break;
					}
			break;
			
			case __MOSTRAR: 			//!<  Muestra la medicion en LCD
				if(!timer_2s) 			//Cada 2 segundos muestra la medicion en pantalla
				{
					if(idx >= _VALORES_RPM_N)idx = 0;
					EA = OFF; 						//Deshabilito las IRQ Globales
					periodo = _BUFFER_RPM(); 		//Valor promedio
					EA = ON;  						// habilito las IRQ Globales
					delta = Ajuste_RPM(periodo/10);	// la correcion para el valor de rpm
					periodo += delta;				//corregimos
					periodo -= Offset; 				// afectamo por el offset
					memoria[idx++] = periodo; 		// Guardamos en memoria y postincrementamos 
					Separar_Digitos(periodo);
					LCD_GoToXY(9,1);				//
					LCD_WrtString(Digito);			//Escribimos las RPM por pantalla
					estado = __MEDIR;
					timer_2s_on; // reestablecemos la cuenta
				}
			break;
		}		
	}
}

/*********************************************************************
 * @fn void firm_menu()
 * @brief		A partir de una tecla ingresada se recorre un menu y muestra
 * por pantalla los datos.
 * @param[in]	UNS_8 
 * @return	void
 * Note: 
 **********************************************************************/
void firm_menu(UNS_8 tecla)
{
	static UNS_8 ESTADO_MENU = _MENU_SALIR,idx_buffer_size = 0;
	volatile UNS_8 aux = 0,indice = 0,Digito_OFFSET[]={0,0,0,0,0,'.',0};
		
	if(tecla ==_TECLA_SIG) //Imprime el menu desplazante
	{
		ESTADO_MENU++;
		if(ESTADO_MENU > _MENU_SALIR) ESTADO_MENU = 0; //loopeamos el mensaje
		LCD_GoToXY(0,0);
		LCD_WrtString(Menu_[ESTADO_MENU]); 
	}else
	{
		if(tecla == _TECLA_OK) // confirma la accion en pantalla
		{
			switch (ESTADO_MENU)
			{
			case _MENU_OFFSET: //Se toca valor por valor PROVISORIO
				LCD_GoToXY(0,1);
				while(indice < 7)
				{
					actualizar_teclado(); //!< Sensado de Teclado
					tecla = Teclado();
					if(tecla != NO_KEY) //en caso de que haya una tecla apretada.
					{
						Digito_OFFSET[indice] = CARACT[tecla]; //Levanto el caracter
						LCD_WrtData(Digito_OFFSET[indice++]); //Escribi el caracter
					}
					if(indice == 5) {LCD_WrtData(Digito_OFFSET[indice++]);} //Escribo el '.'
				}
				//Guardamos los valores en Offset
				Offset = (100000*(Digito_OFFSET[0] - 48));
				Offset = (10000*(Digito_OFFSET[1] - 48));
				Offset = (1000*(Digito_OFFSET[2] - 48));
				Offset = (100*(Digito_OFFSET[3] - 48));
				Offset = (10*(Digito_OFFSET[4] - 48));
				Offset = (Digito_OFFSET[6] - 48);
				
				LCD_GoToXY(0,0);
				LCD_WrtString(Mens_[0]);//Volvemos al menu de operacion
				LCD_GoToXY(0,1);
				LCD_WrtString(Mens_[1]);
				
			break;
			case _MENU_MUESTRA:		//Variamos las veces a muestrear
				FLAG_MUESTRA = ON;
				LCD_GoToXY(0,1); 		 //opciones abajo
				LCD_WrtString(Mens_[3]); //opciones para moverse
			break; 
			case _MENU_MAX: //buscamos el valor maximo en el array y lo mostramos
				aux = valor_maximo();
				Separar_Digitos(memoria[aux]);
				LCD_GoToXY(0,1);
				LCD_WrtString(Digito); // imprimimos el valor maximo
			break;
			case _MENU_MIN: //buscamos el valor minimo en el array y lo mostramos
				aux = valor_minimo();
				Separar_Digitos(memoria[aux]);
				LCD_GoToXY(0,1);
				LCD_WrtString(Digito); // imprimimos el valor minimo
			break;
			case _MENU_PROM: //promediamos el array y lo mostramos
				Separar_Digitos(valor_promedio()); //Decimal = 0
				LCD_GoToXY(0,1);
				LCD_WrtString(Digito); // imprimimos el valor promedio
			break;
			case _MENU_SALIR: //Restauramos el msj de bienvenida
				LCD_GoToXY(0,0);
				LCD_WrtString(Mens_[0]);
				LCD_GoToXY(0,1);
				LCD_WrtString(Mens_[1]);
			break;
			}
			ESTADO_MENU = _MENU_SALIR;
			
		}else
		{
			if(FLAG_MUESTRA)
			{
				//si es 5, cambia a la siguiente escala
				if(tecla == _TECLA_MUESTRAS_SIG) 
				{
					if(idx_buffer_size >= _OPCIONdeMUESTREO)idx_buffer_size = 0;
					LCD_GoToXY(0,0);
					LCD_WrtString(BUFFER_SIZE[idx_buffer_size++]);
				}else
				{
					if(tecla == _TECLA_MUESTRAS_OK)//si es 6, confirmamos el valor
					{
						bm.BufferSize_N = BUFFER_SIZE_5[idx_buffer_size-1];
						__BUF_RESET(bm.idx);	//reseteamos el indice
						LCD_GoToXY(0,0);
						LCD_WrtString(Mens_[0]);//Volvemos al menu de operacion
						LCD_GoToXY(0,1);
						LCD_WrtString(Mens_[1]);
						idx_buffer_size = 0;
						FLAG_MUESTRA = OFF;
					}
				}
			
			}
		}
	}
}

/*********************************************************************
 * @fn void valor_maximo()
 * @brief		del array memoria devuelve el valor maximo
 * por pantalla los datos.
 * @param[in]	void
 * @return	UNS_16 el maximo
 * Note: 
 **********************************************************************/
UNS_8 valor_maximo()
 {
	UNS_8 contador, max_posicion = 0;
	UNS_32 axu = 0;
	for(contador=_VALORES_RPM_N;contador>0;contador--) // Busqueda dentro del array
	{
		if(memoria[contador-1] > axu)
		{
			axu = memoria[contador-1];
			max_posicion = contador-1; // guardamos la posicion del valor buscado
		}
	}
	return max_posicion; // posicion de valor maximo
}

/*********************************************************************
 * @fn void valor_maximo()
 * @brief		del array memoria devuelve el valor maximo
 * por pantalla los datos.
 * @param[in]	void
 * @return	UNS_16 el minimo
 * Note: 
 **********************************************************************/
 UNS_8 valor_minimo()
 {
	UNS_8 contador, min_posicion = 0;
	UNS_32 axu = 20000; //porque es el peor caso siendo máximo
	for(contador=_VALORES_RPM_N;contador>0;contador--) // Busqueda dentro del array
	{
		if(memoria[contador-1] < axu) 
		{
			axu = memoria[contador-1];
			min_posicion = contador-1; // Guardamos la posicion del valor buscado
		}
	}
	return min_posicion; // posicion del valor mínimo
}

/*********************************************************************
 * @fn void valor_maximo()
 * @brief		del array memoria devuelve el valor maximo
 * por pantalla los datos.
 * @param[in]	void
 * @return	UNS_16 el promedio
 * Note: 
 **********************************************************************/
 UNS_32 valor_promedio()
 {
	UNS_8 contador = _VALORES_RPM_N;
	UNS_32 axu = 0;
	while(contador--)
	{
		axu += memoria[contador]; 
	}
	axu /= _VALORES_RPM_N;
	return axu;
}

/*********************************************************************
 * @fn void SepararDigitos()
 * @brief	
 * por pantalla los datos.
 * @param[in]	UNS_16 dato a separar
 * @return	
 * Note: Agregar
 **********************************************************************/ 
void Separar_Digitos(UNS_32 dato)
{
	UNS_8 indice = 4;
	UNS_32 periodo = dato;
	Digito[6] = (periodo%10)+48;
	periodo /= 10;
	while(indice) 				//Separamos el numero en digitos
	{
		Digito[indice--] = (periodo%10)+48;
		periodo /= 10;
	}
	Digito[indice] = periodo + 48;		//Guardamos el ultimo digito a mano
}
/* --------------------------------- End Of File ------------------------------ */
