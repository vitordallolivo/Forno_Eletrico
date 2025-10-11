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
	SOUND_PLAYING=1,
}SOUND_STATUS;
//-----------------------Globais -----------------

SOUNDS_TYPE PlaySound;
SOUNDS_TYPE WhichSound = PLAY_NO_SOUND;

unsigned char EndCycleSound_Counter = 0;

//-------------------------------------- PRIVATE (Function Prototypes) ---------------------------------------------------
SOUND_STATUS PowerOnSoundHandler(void);
SOUND_STATUS KeyPressSoundHandler(void);
SOUND_STATUS EndCycleSoundHandler(void);

void tone(unsigned short int frequency, unsigned short int duration, unsigned char duty_cycle);
void sound_delay(unsigned short int  duration);


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

//=====================================================================================================================
//-------------------------------------- Private Functions -------------------------------------------------------------
//=====================================================================================================================

//---------------------------------------------------------------------------------------------------------------------


SOUND_STATUS PowerOnSoundHandler(void)
{
	SOUND_STATUS status;

	//Hal__SetAllLeds(LED_ON);

	status = SOUND_PLAYING;
	
	tone(NOTE_DS8,2000,20);
	tone(NOTE_DS8,3000,20);

	status = SOUND_DONE;
	return status;
}

SOUND_STATUS KeyPressSoundHandler(void)
{
	SOUND_STATUS status;

	status = SOUND_PLAYING;
	
	switch(WhichSound){
		
		case PLAY_MIN:
			  tone(NOTE_B0,2000,20);
			  tone(NOTE_DS8,3000,20);
			  tone(NOTE_D5,1000,20);
			  tone(NOTE_AS7,3000,10);
		break;
		
		case PLAY_MED:
			tone(NOTE_B0,2000,20);
			tone(NOTE_FS7,3000,20);
			tone(NOTE_B0,2000,20);
			tone(NOTE_CS5,3000,20);
		break;
		
		case PLAY_MAX:
			tone(NOTE_D2,1000,20);
			tone(NOTE_CS5,3000,20);
			tone(NOTE_F2,1000,20);
			tone(NOTE_DS8,2500,20);
		break;
		
		case PLAY_OFF:
		
			for(unsigned char i=0; i<3; i++){
				tone(NOTE_DS8,1000,20);
				sound_delay(1000);
				tone(80000,500,20);
				sound_delay(500);
			}
		break;
		
		
		
	}



	status = SOUND_DONE;
	return status;
}

SOUND_STATUS EndCycleSoundHandler(void)
{
	SOUND_STATUS status;

	status = SOUND_PLAYING;
	Hal__SetBuzzer(OFF);

	status = SOUND_DONE;
	return status;
}


void sound_delay(unsigned short int duration) {
	for (unsigned short int i = 0; i < duration; i++) {
		_delay_ms(1);
	}
}

void tone(unsigned short int frequency, unsigned short int duration, unsigned char duty_cycle) {
	if (frequency == 0) {
		Hal__SetBuzzer(OFF);
		sound_delay(duration);
	} 
	else {
		Hal__SetBuzzerFreq(frequency);
		Hal_SetBuzzerDutyCycle(duty_cycle);
		sound_delay(duration);
		Hal__SetBuzzer(OFF);
	}
}