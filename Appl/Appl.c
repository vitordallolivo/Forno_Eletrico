/*
 * Appl.c
 *
 * Created: 02/04/2019 21:29:10
 *  Author: Ana Watanabe
 */ 

//-------------------------------------- Include Files ----------------------------------------------------------------

#include "..\Header\C_Types.h"
#include "..\Header\Appl.h"
#include "..\Header\Display.h"
#include "..\Header\Gpio.h"
#include "..\Header\Adc.h"
#include "..\Header\Hal.h"
#include "..\Header\OvenTempControl.h"
//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------
KEY_EVENT_TYPE User_Action;

//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------
#define EXP_ADC                ENABLED
#define EXP_OVEN               ENABLED

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
			OvenTempControl__SetLevel(TEMP_LEVEL_OVEN_OFF);
			break;
			
			case KEY_MIN_EVENT:
			Display__SetState(OVEN_MIN);
			OvenTempControl__SetLevel(TEMP_LEVEL_MIN);
			break;
			
			case KEY_MED_EVENT:
			Display__SetState(OVEN_MED);
			OvenTempControl__SetLevel(TEMP_LEVEL_MED);
			break;
			
			case KEY_MAX_EVENT:
			Display__SetState(OVEN_MAX);
			OvenTempControl__SetLevel(TEMP_LEVEL_MAX);
			break;

			default:
			Display__SetState(OVEN_OFF);
			OvenTempControl__SetLevel(TEMP_LEVEL_OVEN_OFF);
			break;

		}
	}
	
} 