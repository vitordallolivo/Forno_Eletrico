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
#include <util/delay.h>   //para incluir rotina _delay_ms()

//--------------------defines---------------------
#define POWER_ON_SOUND   0
#define KEY_PRESS        1
#define END_CYCLE        2


typedef enum
{
	SOUND_DONE =0,
	SOUND_PLAYING=1 
}SOUND_STATUS;
//-----------------------Globais -----------------

SOUNDS_TYPE PlaySound;

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
	PlaySound = PLAY_NO_SOUND;

	if(sound_id < NUM_OF_SOUNDS)
   		PlaySound = sound_id;
}

//=====================================================================================================================
//-------------------------------------- Private Functions -------------------------------------------------------------
//=====================================================================================================================

//---------------------------------------------------------------------------------------------------------------------

SOUND_STATUS PowerOnSoundHandler(void)
{
	SOUND_STATUS status;

	//Hal__SetAllLeds(LED_ON);

	status = SOUND_PLAYING;
	Hal__SetBuzzerFreq(4000);
	Hal__SetBuzzer(ON);
	_delay_ms(2000);
	Hal__SetBuzzer(OFF);
	_delay_ms(1000);
	Hal__SetBuzzer(ON);
	_delay_ms(3000);
	Hal__SetBuzzer(OFF);

	status = SOUND_DONE;
	return status;
}

SOUND_STATUS KeyPressSoundHandler(void)
{
	SOUND_STATUS status;

	status = SOUND_PLAYING;
	Hal__SetBuzzerFreq(4000);
	Hal__SetBuzzer(ON);
	_delay_ms(1000);
	Hal__SetBuzzer(OFF);
	status = SOUND_DONE;
	return status;
}

SOUND_STATUS EndCycleSoundHandler(void)
{
	SOUND_STATUS status;

	status = SOUND_PLAYING;
	//Hal__SetBuzzerFreq(4000);
	//Hal__SetBuzzer(ON);
	//_delay_ms(1000);
	Hal__SetBuzzer(OFF);

	status = SOUND_DONE;
	return status;
}
