/*
 * Hal.c
 *
 * Created: 26/08/2025 10:13:50
 *  Author: Vitor
 */ 
//--------------------------- INCLUSAO DE ARQUIVOS ---------------------------//

//#include "C_Types.h"
#include "..\Header\Gpio.h"
#include "..\Header\ADC.h"
#include "..\Header\Pwm.h"
#include "..\Header\Hal.h"
#include "..\Header\SevenSeg.h"
#include <util/delay.h>
//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------

const unsigned char Leds_Enable_Table[NUM_OF_LEDS]= {USE_LED_0, USE_LED_1, USE_LED_2, USE_LED_3};
const unsigned char Keys_Enable_Table[NUM_OF_KEYS]= {USE_KEY_0, USE_KEY_1, USE_KEY_2, USE_KEY_3};


const unsigned char AD_Enable_Table[NUM_OF_ANALOG_INPUT]= {DISABLED, DISABLED, DISABLED, DISABLED, DISABLED, ENABLED};
//const unsigned char AD_Enable_Table[NUM_OF_ANALOG_INPUT]= {USE_POT_IN, USE_POT_OUT};// {USE_POT_IN, USE_POT_OUT};
const unsigned char AD_Channel_Table[NUM_OF_ANALOG_INPUT] = {AD_CH0, AD_CH1, AD_CH2, AD_CH3, AD_CH4, AD_CH5};
// -------------------------- Defines, Enumerações ---------------------------//

#define LED_ON 			FALSE //LEDs use Inverse logic
#define LED_OFF 		TRUE  //LEDs use Inverse logic
#define KEY_PRESSED 	FALSE //Value read in the pin when key is pressed

#define  ON             1
#define  OFF            0

#define  TRUE           1
#define  FALSE          0
#define  ENABLED        1

#define ACENDE_LED 0 

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
	{PORT_D,SW4}     // SW4 (Pino D5)
};

HAL_GPIO_TYPE BUZZER_GPIO={
	.port = PORT_D,
	.pin  = 3
};


// Definições de steps para leitura do ADC
typedef enum
{
	MUX_INIT = 0,       //!< MUX_INIT
	MUX_AD_CONFIG,      //!< MUX_AD_CONFIG
	MUX_DUMMY_STATE_1,  //!< MUX_DUMMY_STATE_1
	MUX_AD_READ,        //!< MUX_AD_READ
	NUM_MUX_STEPS       //!< NUM_MUX_STEPS
} AD_MUX_STATES;

AD_MUX_STATES AD_Mux_State;

#define NUM_AD_SAMPLES        8

//-------------------------------------- Global Variables ----------------------------------------------------------------

unsigned char Hal_Leds_Buffer[NUM_OF_LEDS];
unsigned char Hal_Keys_Buffer;
KEYS_READ tab[3];
 
 
// Variáveis para ADC
ANALOG_INPUT_TYPE AD_Channel;
unsigned short int AD_Accumulator[NUM_OF_ANALOG_INPUT];
unsigned short int AD_Sample[NUM_OF_ANALOG_INPUT];
unsigned char AD_Counter[NUM_OF_ANALOG_INPUT];

unsigned short int Hal_Analog_Inputs[NUM_OF_ANALOG_INPUT];   // buffer da média do valor do ADC de cada canal


//-------------------------------------- PRIVATE (Function Prototypes) ---------------------------------------------------
void LEDsUpdate(void);
void KeysRead(void);
void ADProcess(void);
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
	ANALOG_INPUT_TYPE analog_index;
	
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
	
	// Buzzer GPIO Configuration
	GPIO_CONFIG(BUZZER_GPIO.port,BUZZER_GPIO.pin,OUTPUT_DIGITAL);
	GPIO_PIN_WRITE(BUZZER_GPIO.port,BUZZER_GPIO.pin, SET); // BUZZER DESLIGADO
	
	
	// Analog Inputs Configuration - modo de conversão e resolução e inicializa os buffers de várias leitura do ADC
	ADC__ConfigModes(HAL_ANALOG_MODE,HAL_CONVERSION_METHOD);
	AD_Mux_State = 	MUX_INIT;
	AD_Channel = POT_EXT;  // equivalente ao canal AD5 do arduino

	for(analog_index = 0; analog_index < NUM_OF_ANALOG_INPUT; analog_index++)
	{
		if(AD_Enable_Table[analog_index] == ENABLED)
		{
			Hal_Analog_Inputs[analog_index] = 0;   // zera o buffer de valor de cada canal
			AD_Accumulator[analog_index] = 0;
			AD_Counter[analog_index] = 0;
		}
	}
	
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *  This function shall run in background in the main loop 
 *  Call rate: 1ms, 5ms, 10ms, ...PARA ADC
 */

void Hal__BackgroundHandler(void)
{
	ADProcess();
}
//---------------------------------------------------------------------------------------------------------------------
/**
 *  This function shall run in background in the main loop 
 *  Call rate: 1ms, 5ms, 10ms, ...PARA ADC
 */
void Hal__FastHandler(void)
{
	LEDsUpdate();   // update the LEDs status
	KeysRead();     // reads the keys and update the Hal_Keys_Buffer
	
}


//---------------------------------------------------------------------------------------------------------------------
/**
 *  Use this function to turn a specific led ON or OFF
 *  output: Respective LED
 *  value: ON/OFF
 */
void Hal__SetLed(LED_OUTPUT_TYPE output,unsigned char value)
{
	Hal_Leds_Buffer[output] = LED_OFF;
	if (value == ACENDE_LED)
		Hal_Leds_Buffer[output] = LED_ON;
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
		Hal_Leds_Buffer[index] = LED_OFF;
		if (value == ACENDE_LED)
		Hal_Leds_Buffer[index] = LED_ON;
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
	if (key < NUM_OF_KEYS)
	{
		if (BIT_TEST(Hal_Keys_Buffer, key) > 0)
		return (TRUE);
	}
	return (FALSE);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *  Use this function to read the status of all keys
 *  *  return: retorno o ponteiro da estrutura com os vetores das chaves*/


unsigned char Hal__ReadAllKey(void)
{
	KEY_INPUT_TYPE index;
	for(index = 0; index < NUM_OF_KEYS; index++)
	{
		tab->key[index]=Hal__ReadKey(index);
		
		if (tab->key[index] == TRUE){ // A chave x foi apertada
			return index;
		}
	}
	return NUM_OF_KEYS; // Nenhuma chave apertada
	
}



void Hal__WriteValtoSegment(const char* ptr_display_values){	
	SevenSeg_WriteValueToSegment(ptr_display_values);
}


//---------------------------------------------------------------------------------------------------------------------
/**
 *  Use this function to read a value ADC in the selected channel
 *  
 */
unsigned short int Hal_GetAnalogInput(ANALOG_INPUT_TYPE input)
{
	if(input < NUM_OF_ANALOG_INPUT)
		return Hal_Analog_Inputs[input];  // retorna o valor no buffer HAL_AnalogInputs do canal solicitado
}


/**
 * 
 */
void Hal__SetBuzzer(unsigned char state)
{
	#if (USE_BUZZER == ENABLED)

	if(state > 0)
		{
		//BuzzerRequest = ON;
		Pwm__SetDutyCycle(PWM5,BUZZER_DEFAULT_ON_DUTY);
		}
	else
		{
		Pwm__SetDutyCycle(PWM5,BUZZER_OFF_DUTY);
		}
	
	#endif // (USE_BUZZER == ENABLED)
	
}



void Hal_SetBuzzerDutyCycle(unsigned char duty){
	Pwm__SetDutyCycle(PWM5,duty);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * 
 */
void Hal__SetBuzzerFreq(unsigned short int frequency)
{
	Pwm__SetTCFrequency(PWM_TC2, frequency);
}


//=====================================================================================================================
//-------------------------------------- PRIVATE Functions -------------------------------------------------------------
//=====================================================================================================================
//---------------------------------------------------------------------------------------------------------------------



/**
 *  This local function update the LEDs status
 */
void LEDsUpdate(void)
{
	unsigned char index;
	unsigned char value;
	
	//LEDs Update
	for(index = 0; index < NUM_OF_LEDS; index++){
		if(Leds_Enable_Table[index] == ENABLED){
			value = LED_ON;
			if(Hal_Leds_Buffer[index] > 0){  
					value = LED_OFF;
			}
			GPIO_PIN_WRITE(LED_GPIO[index].port, LED_GPIO[index].pin, value);
		}
	}
}
//---------------------------------------------------------------------------------------------------------------------
/**
 *  This local function reads the keys input and update the Hal_Keys_Buffer
 */

void KeysRead(void)
{
	//Keys read
	KEY_INPUT_TYPE key_index;
	unsigned char value;
	
	for(key_index = KEY_0; key_index < NUM_OF_KEYS; key_index++){
		if(Keys_Enable_Table[key_index] == ENABLED){
			value = GPIO_PIN_READ(KEYS_GPIO[key_index].port, KEYS_GPIO[key_index].pin);
			if(value == KEY_PRESSED){
				BIT_SET(Hal_Keys_Buffer,key_index);
			}
			else{
				BIT_CLR(Hal_Keys_Buffer,key_index);

			}
		}
	}
	

}

//---------------------------------------------------------------------------------------------------------------------
/**
 *  This local function reads the analog input and update the buffer Hal_Analog_inputs[]
    ROTINA ONDE SÃO FEITAS AS VÁRIAS LEITURAS DE AMOSTRAGEM (NUM_AD_SAMPLES) E DEPOIS TIRADO A MÉDIA DOS  VALORES
****/

void ADProcess(void)
{
	switch (AD_Mux_State)
	  {
	  case MUX_INIT:
		break;
	  case MUX_AD_CONFIG:
		ADC__ConfigModes(MODE_10BITS,AD_SINGLE_CONVERSION);
		break;
	  case MUX_DUMMY_STATE_1: //=> This state is placed in order to assure the raising time for ADC reading
		break;
	  case MUX_AD_READ:
		  if(AD_Enable_Table[AD_Channel] == ENABLED)
			 {
			 if(AD_Counter[AD_Channel] < NUM_AD_SAMPLES)
				 {
				 AD_Sample[AD_Channel] = ADC__GetValue(AD_Channel_Table[AD_Channel]);
				 AD_Accumulator[AD_Channel] += AD_Sample[AD_Channel];
				 AD_Counter[AD_Channel]++;
				 }
			 else
				{  // O Buffer Hal_Analog_Inputs[] é a média do valor de ADC e éAQUI atualizado!
				Hal_Analog_Inputs[AD_Channel] = (unsigned short int)(AD_Accumulator[AD_Channel]/NUM_AD_SAMPLES);
				AD_Accumulator[AD_Channel] = 0;
				AD_Counter[AD_Channel] = 0;
				}
			  } 
		   AD_Channel++;
		   if(AD_Channel >= NUM_OF_ANALOG_INPUT)
			 {
			 AD_Channel = 0;
			 }
		   break;
	  default:
		   break;
	  }

	AD_Mux_State++;                                // Ticking the state machine.

	if (AD_Mux_State >= NUM_MUX_STEPS){
	  AD_Mux_State = MUX_AD_CONFIG;
    }
}