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
#include "..\Header\Hal.h"
//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------


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
	Hal__Initialize();
	Hal__SetAllLeds(APAGADO);	
}


void Appl__Handler(void){
	
	KEYS_READ* keys = Hal__ReadAllKey(); 
	
	if (keys->key[KEY_0] == SW_ON &&  keys->key[KEY_2] == SW_ON){
		Hal__SetAllLeds(APAGADO);
	}
	else{
		if (keys->key[KEY_0] == SW_ON ){
			Hal__SetAllLeds(APAGADO);
			Hal__SetLed(LED_0,ACESO);
		}
		if (keys->key[KEY_2] == SW_ON){
			Hal__SetAllLeds(APAGADO);
			Hal__SetLed(LED_0,ACESO);
			Hal__SetLed(LED_1,ACESO);
			Hal__SetLed(LED_2,ACESO);
		}
		if (keys->key[KEY_1] == SW_ON){
			Hal__SetAllLeds(APAGADO);
			Hal__SetLed(LED_0,ACESO);
			Hal__SetLed(LED_1,ACESO);
		}
	}
}