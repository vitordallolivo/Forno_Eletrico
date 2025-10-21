/*
 * Sounds.c
 *
 * Created: 05/11/2019 22:42:42
 *  Author: Ana Watanabe
 */ 

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "..\Header\Micro.h"
#include "..\Header\Hal.h"
#include "..\Header\Sounds.h"
#include "..\Header\Timer.h"

//--------------------defines---------------------
#define POWER_ON_SOUND   0
#define KEY_PRESS        1
#define END_CYCLE        2


typedef enum
{
	SOUND_DONE =0,
	SOUND_PLAYING=1,
}SOUND_STATUS;


typedef enum
{
	POWER_ON_SOUND_STEP1 = 0,
	POWER_ON_SOUND_STEP2,
	POWER_ON_SOUND_STEP3,
	POWER_ON_SOUND_STEP4,
	POWER_ON_SOUND_STEP5,
	POWER_ON_SOUND_STEP6
}POWER_ON_SOUND_STEPS;

typedef enum
{
	KEY_PRESS_SOUND_STEP1 = 0,
	KEY_PRESS_SOUND_STEP2
}KEY_PRESS_SOUND_STEPS;

typedef enum
{
	END_CYCLE_SOUND_STEP_OFF = 0,
	END_CYCLE_SOUND_STEP_ON
}END_CYCLE_SOUND_STEPS;



//-----------------------Globais -----------------

SOUNDS_TYPE PlaySound;
SOUNDS_TYPE WhichSound = PLAY_NO_SOUND;

KEY_PRESS_SOUND_STEPS Key_Press_Sound_Step;
POWER_ON_SOUND_STEPS PowerON_Sound_Step;
END_CYCLE_SOUND_STEPS End_Cycle_Sound_Step;

unsigned char EndCycleSound_Counter = 0;

//-------------------------------------- PRIVATE (Function Prototypes) ---------------------------------------------------
SOUND_STATUS PowerOnSoundHandler(void);
SOUND_STATUS KeyPressSoundHandler(void);
SOUND_STATUS EndCycleSoundHandler(void);




//*********************************************************
//
//   Esta rotina inicializa a variável global Playsound
//   para sem som
//
//*********************************************************
 void Sounds__Initialize(void){
	PlaySound = PLAY_NO_SOUND;   // variável global => sem som no início	
	PowerON_Sound_Step = POWER_ON_SOUND_STEP1;
	Key_Press_Sound_Step = KEY_PRESS_SOUND_STEP1;
	End_Cycle_Sound_Step = END_CYCLE_SOUND_STEP_ON;
}

//*********************************************************
//
//   Esta rotina  roda no SLOT1 verifica se já finalizou o tempo do som
//   em função do tipo de som
//
//*********************************************************
 
void Sounds__Background(void)
{
	switch (PlaySound)
	{
		case SOUND_POWER_ON:
			if(PowerOnSoundHandler() == SOUND_DONE){
				PlaySound = PLAY_NO_SOUND;
				}
			break;

		case SOUND_KEY_PRESS:
			if(KeyPressSoundHandler() == SOUND_DONE){
				PlaySound = PLAY_NO_SOUND;    
			}
			break;

		case SOUND_END_CYCLE:
			if(EndCycleSoundHandler() == SOUND_DONE)
				{
				PlaySound = PLAY_NO_SOUND;  
				}
			break;
	
		case PLAY_NO_SOUND:
			Hal__SetBuzzer(OFF);
			break;
		default:
	    
			break;

	}
}

//*********************************************************
//
//   Esta rotina  atualiza a variável global PlaySound
//
//*********************************************************
 

void Sounds__PlaySounds( SOUNDS_TYPE sound_id)
{
	WhichSound = PLAY_NO_SOUND;
	
	if(sound_id < NUM_OF_SOUNDS){
   		WhichSound = sound_id;
		
		if(WhichSound >= PLAY_NO_SOUND){
			PlaySound = SOUND_KEY_PRESS;	   
		}
		else{
			PlaySound = sound_id;
		}
		
	}
}


//*********************************************************
//
//   Esta rotina  devolve o valor da variável global PlaySound
//
//*********************************************************
 SOUNDS_TYPE Sounds__GetSounds( void)
{
	return (PlaySound);
}


//=====================================================================================================================
//-------------------------------------- Private Functions -------------------------------------------------------------
//=====================================================================================================================

//---------------------------------------------------------------------------------------------------------------------


SOUND_STATUS PowerOnSoundHandler(void)
{
	SOUND_STATUS status;
	status = SOUND_PLAYING;
	Hal__SetBuzzerFreq(4000);

	switch (PowerON_Sound_Step)
	{
		case POWER_ON_SOUND_STEP1:
		Hal__SetBuzzer(ON);  // aqui entra
		//_delay_ms(2000);
		Timer__HMSSet(TIMER_HMS_POWER_ON_SOUND, 0,0,1);
		PowerON_Sound_Step = POWER_ON_SOUND_STEP2;
		break;

		case POWER_ON_SOUND_STEP2:
		if(Timer__HMSGetStatus(TIMER_HMS_POWER_ON_SOUND) == TIMER_EXPIRED)
		{
			Timer__HMSSet(TIMER_HMS_POWER_ON_SOUND, 0,0,1);
			//	Hal__SetBuzzer(ON);    // não entra aqui  !!!
			//_delay_ms(2000);
			PowerON_Sound_Step = POWER_ON_SOUND_STEP3;
			Hal__SetBuzzer(OFF);
		}
		break;

		case POWER_ON_SOUND_STEP3:
		if(Timer__HMSGetStatus(TIMER_HMS_POWER_ON_SOUND) == TIMER_EXPIRED)
		{
			Timer__HMSSet(TIMER_HMS_POWER_ON_SOUND, 0,0,1);
			PowerON_Sound_Step = POWER_ON_SOUND_STEP4;
			//Hal__SetBuzzerFreq(4000);   //mudar frequencia do PWM
			Hal__SetBuzzer(ON);
			//Hal__SetLed(LED_1, LED_ON);   //depuração
			//_delay_ms(2000);
		}
		break;
		
		case POWER_ON_SOUND_STEP4:
		if(Timer__HMSGetStatus(TIMER_HMS_POWER_ON_SOUND) == TIMER_EXPIRED)
		{
			Timer__HMSSet(TIMER_HMS_POWER_ON_SOUND, 0,0,1);
			PowerON_Sound_Step = POWER_ON_SOUND_STEP5;
			Hal__SetBuzzer(OFF);
			//Hal__SetLed(LED_1, LED_OFF);
			//_delay_ms(2000);
		}
		break;
		
		case POWER_ON_SOUND_STEP5:
		if(Timer__HMSGetStatus(TIMER_HMS_POWER_ON_SOUND) == TIMER_EXPIRED)
		{
			Timer__HMSSet(TIMER_HMS_POWER_ON_SOUND, 0,0,1);
			PowerON_Sound_Step = POWER_ON_SOUND_STEP6;
			//Hal__SetBuzzerFreq(4000);
			Hal__SetBuzzer(ON);
			//Hal__SetLed(LED_1, LED_ON);
			//_delay_ms(2000);
		}
		break;
		
		case POWER_ON_SOUND_STEP6:
		if(Timer__HMSGetStatus(TIMER_HMS_POWER_ON_SOUND) == TIMER_EXPIRED)
		{
			PowerON_Sound_Step = POWER_ON_SOUND_STEP1;
			Hal__SetBuzzer(OFF);
			//Hal__SetLed(LED_1, LED_OFF);
			status = SOUND_DONE;
		}
		break;

		default:
		PowerON_Sound_Step = POWER_ON_SOUND_STEP1;
		status = SOUND_DONE;
		break;
	}
	return status;
}

SOUND_STATUS KeyPressSoundHandler(void)
{
	SOUND_STATUS status;
	unsigned char time = 0;
	status = SOUND_PLAYING;
	switch(WhichSound){
		case PLAY_MIN:
			Hal__SetBuzzerFreq(NOTE_CS6);
			time = 1;
			break;
		
		case PLAY_MED:
			Hal__SetBuzzerFreq(NOTE_GS5);
			time   = 2;
			break;
		case PLAY_MAX:
			Hal__SetBuzzerFreq(NOTE_DS8);
			time   = 2;
			break;
		case PLAY_OFF:
			Hal__SetBuzzerFreq(NOTE_G4);
			time   = 1;
			break;
	}
	
	switch(Key_Press_Sound_Step)
	{
		case KEY_PRESS_SOUND_STEP1:
		Timer__HMSSet(TIMER_HMS_KEY_PRESS_SOUND, 0,0,time);
		Hal__SetBuzzer(ON);
		Key_Press_Sound_Step = KEY_PRESS_SOUND_STEP2;
		break;

		case KEY_PRESS_SOUND_STEP2:
		if(Timer__HMSGetStatus(TIMER_HMS_KEY_PRESS_SOUND) == TIMER_EXPIRED)
		{
			Hal__SetBuzzer(OFF);
			Key_Press_Sound_Step = KEY_PRESS_SOUND_STEP1;
			status = SOUND_DONE;
		}
		break;
		default:
		Key_Press_Sound_Step = KEY_PRESS_SOUND_STEP1;
		status = SOUND_DONE;
		break;
	}
	
	return status;
}

SOUND_STATUS EndCycleSoundHandler(void)
{
	SOUND_STATUS status;
	status = SOUND_PLAYING;
	Hal__SetBuzzerFreq(4000);

	switch(End_Cycle_Sound_Step)
	{
		case END_CYCLE_SOUND_STEP_ON:
		Timer__HMSSet(TIMER_HMS_END_CYCLE_SOUND, 0,0,3);
		Hal__SetBuzzer(ON);
		//_delay_ms(2000);
		End_Cycle_Sound_Step = END_CYCLE_SOUND_STEP_OFF;
		break;

		case END_CYCLE_SOUND_STEP_OFF:
		//Hal__SetBuzzer(ON);
		//_delay_ms(2000);
		if(Timer__HMSGetStatus(TIMER_HMS_END_CYCLE_SOUND) == TIMER_EXPIRED)
		{
			Hal__SetBuzzer(OFF);
			End_Cycle_Sound_Step = END_CYCLE_SOUND_STEP_ON;
			status = SOUND_DONE;
		}
		break;
		default:
		End_Cycle_Sound_Step = END_CYCLE_SOUND_STEP_ON;
		status = SOUND_DONE;
		break;
	}

	return status;
}

