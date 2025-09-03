/*
 * Appl.c
 *
 * Created: 02/04/2019 21:29:10
 *  Author: Ana Watanabe
 */ 

//-------------------------------------- Include Files ----------------------------------------------------------------

//#include "C_Types.h"    ainda não...
#include <avr/io.h> //definições do componente especificado
#include <util/delay.h> /*biblioteca para o uso das rotinas de _delay_ms() e _delay_us()*/
#include "..\Header\Appl.h"
#include "..\Header\Gpio.h"
#include "..\Header\Display.h"
//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------
KEY_EVENT_TYPE User_Action;

//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------
#define ACESO       0
#define APAGADO     1
//-------------------------------------- Global Variables ----------------------------------------------------------------

unsigned char Timer_Counter;
unsigned char Toggle;
unsigned char Trigger;
//-------------------------------------- PRIVATE (Function Prototypes) ---------------------------------------------------


//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================


void Appl__Initialize(void){
	User_Action = EVENTS_NO_EVENT;
}


void Appl__Handler(void)
{
	User_Action = Display__GetEvent(); 
	if (User_Action != EVENTS_NO_EVENT)
	{
		switch(User_Action)
		{
			case KEY_OFF_EVENT:
			Display__SetState(OVEN_OFF);
			break;
			
			case KEY_MIN_EVENT:
			Display__SetState(OVEN_MIN);
			break;
			
			case KEY_MED_EVENT:
			Display__SetState(OVEN_MED);
			break;
			
			case KEY_MAX_EVENT:
			Display__SetState(OVEN_MAX);
			break;

			default:
			break;

		}
	}
	
} 