/*
 * Hal.c
 *
 * Created: 26/08/2025 10:13:50
 *  Author: Vitor
 */ 
//--------------------------- INCLUSAO DE ARQUIVOS ---------------------------//

//#include "C_Types.h"
#include "..\Header\Gpio.h"
//#include "ADC.h"
//#include "PWM.h"
#include "..\Header\Hal.h"
#include "..\Header\SevenSeg.h"
#include <util/delay.h>

// -------------------------- Defines, Enumerações ---------------------------//

#define LED_ON 			FALSE //LEDs use Inverse logic
#define LED_OFF 		TRUE  //LEDs use Inverse logic
#define KEY_PRESSED 	FALSE //Value read in the pin when key is pressed

#define  ON             1
#define  OFF            0

#define  TRUE           1
#define  FALSE          0
#define  ENABLED        1

typedef struct
{
	GPIO_PORT port;
	unsigned char pin;
}HAL_GPIO_TYPE;

HAL_GPIO_TYPE LED_GPIO[NUM_OF_LEDS] =
{
	{PORT_B,LED1},    //! LED1
	{PORT_B,LED2},    //! LED2
	{PORT_B,LED3},    //! LED3
	{PORT_B,LED4},    //! LED4
};


HAL_GPIO_TYPE KEYS_GPIO[NUM_OF_KEYS] =
{
	{PORT_C,SW1},    //!SW1
	{PORT_C,SW2},    //!SW2
	{PORT_C,SW3},    //!SW3
};


//-------------------------------------- Global Variables ----------------------------------------------------------------

//unsigned char Hal_Leds_Buffer[NUM_OF_LEDS];
//unsigned char Hal_Keys_Buffer;
KEYS_READ tab;        // vari?vel tab ? do tipo estrutura com os vetores das chaves

//-------------------------------------- PRIVATE (Function Prototypes) ---------------------------------------------------

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================

/*
 * Call this function on initialize tasks before use any function of this module
 * This function will properly configure all pins before use it
 */
void Hal__Initialize(void)
{
	LED_OUTPUT_TYPE led_index;
	KEY_INPUT_TYPE key_index;
		
	
	// LEDs Configuration
	for(led_index = 0; led_index < NUM_OF_LEDS; led_index++)
	{
		GPIO_CONFIG(LED_GPIO[led_index].port, LED_GPIO[led_index].pin, OUTPUT_DIGITAL);
	}
	
	
	// Keys Configuration
	for(key_index = 0; key_index < NUM_OF_KEYS; key_index++)
	{
		GPIO_CONFIG(KEYS_GPIO[key_index].port, KEYS_GPIO[key_index].pin, INPUT_DIGITAL_PULLUP);
	}
	
	// Configuration of 7 segment's
	GPIO_CONFIG(PORT_D,4,OUTPUT_DIGITAL);
	GPIO_CONFIG(PORT_D,7,OUTPUT_DIGITAL);
	GPIO_CONFIG(PORT_B,0,OUTPUT_DIGITAL);
	
	
}


//---------------------------------------------------------------------------------------------------------------------
/**
 *  Use this function to turn a specific led ON or OFF
 *  output: Respective LED
 *  value: ON/OFF
 */
void Hal__SetLed(LED_OUTPUT_TYPE output,unsigned char value)
{
	GPIO_PIN_WRITE(LED_GPIO[output].port, LED_GPIO[output].pin, value);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *  Use this function to turn all LEDs ON or OFF
 *  value ON/OFF
 *  ON: To turn All LEDs ON 
 *  OFF: To turn All LEDs OFF
 */
void Hal__SetAllLeds(unsigned char value)
{
	LED_OUTPUT_TYPE index;
	
	for(index = 0; index < NUM_OF_LEDS; index++)
	{
		GPIO_PIN_WRITE(LED_GPIO[index].port, LED_GPIO[index].pin, value);
	}
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *  Use this function to read the status of a specific key
 *  key: desired key to be read
 *  return: TRUE if key is pressed otherwise FALSE
 */
unsigned char Hal__ReadKey(KEY_INPUT_TYPE key)
{
	unsigned char value;
	value = GPIO_PIN_READ(KEYS_GPIO[key].port, KEYS_GPIO[key].pin);
	return (value);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *  Use this function to read the status of all keys
 *  *  return: retorno o ponteiro da estrutura com os vetores das chaves*/


KEYS_READ* Hal__ReadAllKey(void)
{
	KEY_INPUT_TYPE index;
	for (index = 0; index < NUM_OF_KEYS; index++)
		tab.key[index] = 0xff;
		
	
	for (index = 0; index < NUM_OF_KEYS; index++){
			_delay_ms(100);
			tab.key[index] = GPIO_PIN_READ(KEYS_GPIO[index].port, KEYS_GPIO[index].pin);
	}
	return (&tab);
}

char last_display_status;

void Hal__WriteValtoSegment(const char* ptr_display_values){	
	SevenSeg_WriteValueToSegment(ptr_display_values);
}