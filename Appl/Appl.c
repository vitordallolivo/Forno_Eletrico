/*
 * Appl.c
 *
 * Created: 02/04/2019 21:29:10
 *  Author: Ana Watanabe
 */ 

//-------------------------------------- Include Files ----------------------------------------------------------------

#include <avr/io.h> //definições do componente especificado
#include <util/delay.h> /*biblioteca para o uso das rotinas de
//_delay_ms() e _delay_us()*/
#include "..\Header\Appl.h"
#include "..\Header\Gpio.h"
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
	
	// Configurando pinos de saida dos leds
	GPIO_CONFIG(PORT_LED,LED1,OUTPUT_DIGITAL);
	GPIO_CONFIG(PORT_LED,LED2,OUTPUT_DIGITAL);
	GPIO_CONFIG(PORT_LED,LED3,OUTPUT_DIGITAL);
	GPIO_CONFIG(PORT_LED,LED4,OUTPUT_DIGITAL);
	// Apaga os LEDs
	DEFINE_LED_STATE(LED1,APAGADO);
	DEFINE_LED_STATE(LED2,APAGADO);
	DEFINE_LED_STATE(LED3,APAGADO);
	DEFINE_LED_STATE(LED4,APAGADO);
	
	// Configura os botões como entrada digital com pullup 
	GPIO_CONFIG(PORT_SW,SW1,INPUT_DIGITAL_PULLUP);
	GPIO_CONFIG(PORT_SW,SW2,INPUT_DIGITAL_PULLUP);
	GPIO_CONFIG(PORT_SW,SW3,INPUT_DIGITAL_PULLUP);
	
}


void Appl__Handler(void){
	unsigned char value1, value2, value3;
	
	value1  = READ_SW(SW1);
	_delay_ms(500);
	value2  = READ_SW(SW2);
	_delay_ms(500);
	value3  = READ_SW(SW3);
	
	
	// SE a chave 1 e 3 são pressionadas desativa os leds
	if (value1 == SW_ON && value3 == SW_ON)	{
		DEFINE_LED_STATE(LED1,APAGADO);
		DEFINE_LED_STATE(LED2,APAGADO);
		DEFINE_LED_STATE(LED3,APAGADO);
		DEFINE_LED_STATE(LED4,APAGADO);		
	}
	else{ // SE os dois não estão sendo pressionados, pode ser que ou eu esteja pressionando o SW1 ou SW3 (ou nenhum)
		if (value1 == SW_ON){
			DEFINE_LED_STATE(LED1,ACESO);
		}
		if (value3 == SW_ON){ // aciona D1,D2 e D3
			DEFINE_LED_STATE(LED1,ACESO);
			DEFINE_LED_STATE(LED2,ACESO);
			DEFINE_LED_STATE(LED3,ACESO);
		}
	}
	if (value2 == SW_ON){
		DEFINE_LED_STATE(LED1,ACESO);
		DEFINE_LED_STATE(LED2,ACESO);
	}

}