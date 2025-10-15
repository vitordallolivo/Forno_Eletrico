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
#include "..\Header\Timer.h"
#include "..\Header\Hal.h"
#include "..\Header\OvenTempControl.h"

#include "../Header/Pwm.h"
#include "../Header/Sounds.h"

//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------
KEY_EVENT_TYPE User_Action;

//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------
#define EXP_ADC                ENABLED
#define EXP_OVEN               ENABLED

#define EXP_TIMER               DISABLED       // TEMPO em ms
#define EXP_TIMER1              DISABLED       // TEMPO em HMS
#define TIME_IN_50MS_BASE	20 //1s in 50ms time base (20*50ms = 1s)

//Oven Min time parameters
#define OVEN_MIN_ON_TIME_SEC	10
#define OVEN_MIN_ON_TIME_MIN	0
#define OVEN_MIN_ON_TIME_HRS	0

//Oven Med time parameters
#define OVEN_MED_ON_TIME_SEC	15
#define OVEN_MED_ON_TIME_MIN	0
#define OVEN_MED_ON_TIME_HRS	0

//Oven Max time parameters
#define OVEN_MAX_ON_TIME_SEC	20
#define OVEN_MAX_ON_TIME_MIN	0
#define OVEN_MAX_ON_TIME_HRS	0



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
	Sounds__PlaySounds(SOUND_POWER_ON);    //buzzer de power on
	Trigger = FALSE;
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
				Sounds__PlaySounds(PLAY_OFF);    //buzzer de key press
				Timer__HMSSet(TIMER_HMS_CYCLE_DURATION, 0,0,0);
				Trigger = FALSE;
			break;
			
			case KEY_MIN_EVENT:
				Display__SetState(OVEN_MIN);
				OvenTempControl__SetLevel(TEMP_LEVEL_MIN);
				Sounds__PlaySounds(PLAY_MIN);    //buzzer de key press
				Timer__HMSSet(TIMER_HMS_CYCLE_DURATION, OVEN_MIN_ON_TIME_HRS, OVEN_MIN_ON_TIME_MIN, OVEN_MIN_ON_TIME_SEC);
				Trigger = TRUE;
			break;
			
			case KEY_MED_EVENT:
				Display__SetState(OVEN_MED);
				OvenTempControl__SetLevel(TEMP_LEVEL_MED);
				Sounds__PlaySounds(PLAY_MED);    //buzzer de key press
				Timer__HMSSet(TIMER_HMS_CYCLE_DURATION, OVEN_MED_ON_TIME_HRS, OVEN_MED_ON_TIME_MIN, OVEN_MED_ON_TIME_SEC);
				Trigger = TRUE;
			break;
			
			case KEY_MAX_EVENT:
				Display__SetState(OVEN_MAX);
				OvenTempControl__SetLevel(TEMP_LEVEL_MAX);
				Sounds__PlaySounds(PLAY_MAX);    //buzzer de key press
				Timer__HMSSet(TIMER_HMS_CYCLE_DURATION, OVEN_MAX_ON_TIME_HRS, OVEN_MAX_ON_TIME_MIN, OVEN_MAX_ON_TIME_SEC);
				Trigger = TRUE;
			break;

			default:
				Display__SetState(OVEN_OFF);
				OvenTempControl__SetLevel(TEMP_LEVEL_OVEN_OFF);
				Sounds__PlaySounds(PLAY_NO_SOUND);
			break;

		}
		
		
	}
	
	if( Trigger == TRUE  && Timer__HMSGetStatus(TIMER_HMS_CYCLE_DURATION) == TIMER_EXPIRED )
	{
		Display__SetState(OVEN_TIMEOUT);
		OvenTempControl__SetLevel(TEMP_LEVEL_OVEN_OFF);
		Sounds__PlaySounds(SOUND_END_CYCLE);
		Trigger = FALSE;
	}
	
} 