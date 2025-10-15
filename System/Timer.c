/*
 * Timer.c
 *
 *  Created on: 08/10/2017
 *      Author: MAASDN
 */

//-------------------------------------- Include Files ----------------------------------------------------------------
#include <avr/interrupt.h>
#include "..\Header\C_Types.h"
#include "..\Header\Timer.h"
#include <util/delay.h>   //para incluir rotina _delay_ms()

//------------------------- Variáveis Globais---------------------
unsigned char flag_seg = 0;    // variável global para saber se passou 1seg.
//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------

//!Millisecond Timer structure
typedef struct
{
	TIMER_STATUS Status;
    unsigned short int Count;
}TYPE_MSTIMER;

TYPE_MSTIMER Ms_Timers[NUM_OF_MS_TIMERS];
 

//! HMS structure
typedef struct                                          
{
    unsigned char Hrs;
    unsigned char Min;
    unsigned char Sec;
}HMS;

//! HMS Timer structure
typedef struct
{
	TIMER_STATUS Status;
    HMS Time;
}TYPE_HMSTIMER;

TYPE_HMSTIMER Hms_Timers[NUM_OF_HMS_TIMERS];

#if (MS_TIMERS_RESOLUTION < 1)
    #error The MS_TIMERS_RESOLUTION parameter must be 1 or greater!!!.
#endif

#if (HMS_TIMERS_RESOLUTION < 1)
    #error The HMS_TIMERS_RESOLUTION parameter must be 1 or greater!!!.
#endif



unsigned short int Hms_1sec_Counter;      				//Counts ticks until 1 sec
const unsigned short int Hms_1sec_TimeBase = 1000 / HMS_TIMERS_RESOLUTION; //# of ticks in 1 sec

//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================

/**
 *  @brief      It Initializes the module Timers and its variables
 *
 *
 */
void Timer__Initialize(void)
{
	unsigned char i;

	for (i=0; i < NUM_OF_MS_TIMERS; i++)
	{
		Ms_Timers[i].Status = TIMER_EXPIRED;
		Ms_Timers[i].Count = 0;
	}

	for (i=0; i < NUM_OF_HMS_TIMERS; i++)
	{
		Hms_Timers[i].Status = TIMER_EXPIRED;
		Hms_Timers[i].Time.Hrs = 0;
		Hms_Timers[i].Time.Min = 0;
		Hms_Timers[i].Time.Sec = 0;
	}
}

//===================================== All Handlers ==========================+=====================
/**
 *  @brief      Services all compiled MillisecondTimers
 *              Roda a cada slot no ALL_SLOTS_TASKS()
 *
 */
void Timer__MsHandler(void)
{
	unsigned char i;                                	

	for(i=0; i < NUM_OF_MS_TIMERS; i++)                       
	{
		if(Ms_Timers[i].Status == TIMER_IS_RUNNING) 	//Is this timer running?
		{
			Ms_Timers[i].Count--;                   
			if(!(Ms_Timers[i].Count))               
			{
				Ms_Timers[i].Status = TIMER_EXPIRED;   //Set timer timeout
			}
		}
	}
}
//===================================== MillisecondTimers ==========================+=====================
/**
 *
 */
void Timer__MsSet(MS_TIMER_NAME id, unsigned short int ms_value)
{
	unsigned long time;                           

	if (id < NUM_OF_MS_TIMERS)
	{
		if (ms_value < MS_TIMERS_RESOLUTION)                     
		{
			Ms_Timers[id].Status = TIMER_EXPIRED;                   
		}
		else                                        
		{
			Ms_Timers[id].Status = TIMER_EXPIRED;      
			time = ms_value / MS_TIMERS_RESOLUTION;
			Ms_Timers[id].Count = (unsigned short int)time;  
			if (Ms_Timers[id].Count != 0)
			{
				Ms_Timers[id].Status = TIMER_IS_RUNNING;		
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------
/**
 * 
 */
void Timer__MsExpire(MS_TIMER_NAME id)
{
	if (id < NUM_OF_MS_TIMERS)
	{
		Ms_Timers[id].Count = 0;
		Ms_Timers[id].Status = TIMER_EXPIRED;
	}
}

//-----------------------------------------------------------------------------------------------------------------
/**
 * 
 */
TIMER_STATUS Timer__MsGetStatus (MS_TIMER_NAME id)
{
	return (Ms_Timers[id].Status);
}


//========================================== HMS TIMERS ===================================================
//-----------------------------------------------------------------------------------------------------------------
/**
 * Esta função roda a cada slot no ALL_SLOTS_TASKS() e decrementa uma
 * unidade  de .Sec e verifica se zerou.
 */
 
void Timer__HMSHandler(void)
{
	unsigned char i;                                
	
	if (flag_seg ==250)
	{
		for (i=0; i < NUM_OF_HMS_TIMERS; i++)             			// Loop through all  HMS timers
		{
			if (Hms_Timers[i].Status == TIMER_IS_RUNNING)           // Is this timer running?
			{
				if(Hms_Timers[i].Time.Sec)      					// Check seconds
				{
					Hms_Timers[i].Time.Sec--;
					if (!((Hms_Timers[i].Time.Sec) |
							(Hms_Timers[i].Time.Min) |
							(Hms_Timers[i].Time.Hrs)))  			//Is this timer finished?
					{
					Hms_Timers[i].Status = TIMER_EXPIRED;
					}
				}
				else if(Hms_Timers[i].Time.Min) 					// Check minutes
				{
					Hms_Timers[i].Time.Min--;
					Hms_Timers[i].Time.Sec = 59;
				}
				else if(Hms_Timers[i].Time.Hrs) 					// Check hours
				{
					Hms_Timers[i].Time.Hrs--;
					Hms_Timers[i].Time.Min = 59;
					Hms_Timers[i].Time.Sec = 59;
				}
			}
		}
    flag_seg = 0;    //reseta a variável para o próx. 250ms
	}

}


//-----------------------------------------------------------------------------------------------------------------
/**
 *   Atualiza HMS e checa o status de cada id se ainda TIMER_IS_RUNNING  ou TIMER_EXPIRED
 */
void Timer__HMSSet(HMS_TIMER_NAME id, unsigned char hrs, unsigned char min, unsigned char sec)
{
	if (id < NUM_OF_HMS_TIMERS)                              
	{
		Hms_Timers[id].Status = TIMER_EXPIRED;          
		Hms_Timers[id].Time.Hrs = hrs;              
		Hms_Timers[id].Time.Min = min;
		Hms_Timers[id].Time.Sec = sec;

		if (!(hrs | min | sec))  
		{
			Hms_Timers[id].Status = TIMER_EXPIRED;
		}
		else
		{
			Hms_Timers[id].Status = TIMER_IS_RUNNING;
			//clr_bit(PORTB,PB5);   // usado pra depuração
            //_delay_ms(2000);      // usado pra depuração
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------
/**
 * 
 */
void Timer__HMSExpire(HMS_TIMER_NAME id)
{
	if (id < NUM_OF_HMS_TIMERS)                               
	{
		Hms_Timers[id].Time.Hrs = 0;
		Hms_Timers[id].Time.Min = 0;
		Hms_Timers[id].Time.Sec = 0;
		Hms_Timers[id].Status = TIMER_EXPIRED;
	}
}

//-----------------------------------------------------------------------------------------------------------------
/**
 * Retorna o estado do timer solicitado
 */
TIMER_STATUS Timer__HMSGetStatus (HMS_TIMER_NAME id)
{
    return (Hms_Timers[id].Status);
}

//-----------------------------------------------------------------------------------------------------------------
/**
 * 
 */
unsigned char Timer__HMSGetTime (HMS_TIMER_NAME id)
{
    return (Hms_Timers[id].Time.Sec);
}


//=====================================================================================================================
//-------------------------------------- Interruption  Functions ------------------------------------------------------------
//=====================================================================================================================
ISR(TIMER1_OVF_vect)                              //interrupção do TIMER1 (pg.158)
{   
	TCNT1 = 65520;   //para contar a cada 1ms
	flag_seg ++;    //seta o flag indicando que passou 1ms
}


