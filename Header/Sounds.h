/*
 * Sounds.h
 *
 * Created: 05/11/2019 22:49:44
 *  Author: Ana Watanabe
 */ 


#ifndef Sounds_H_
#define Sounds_H_


#include "../Header/Sounds_prm.h"

typedef enum {
	SOUND_POWER_ON = 0,
	SOUND_KEY_PRESS,
	SOUND_END_CYCLE,
	PLAY_NO_SOUND,   // NÃO RETIRE ESTA LINHA
	PLAY_MIN,
	PLAY_MED,
	PLAY_MAX,
	PLAY_OFF,
	NUM_OF_SOUNDS,
} SOUNDS_TYPE;

//Protótipos
void Sounds__Initialize(void);
void Sounds__Background(void);
void Sounds__PlaySounds( SOUNDS_TYPE sound_id);




#endif /* Sounds_H_ */