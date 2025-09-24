/*
 * Hal.h
 *
 * Created: 26/08/2025 10:14:06
 *  Author: Vitor
 */ 


#ifndef HAL_H_
#define HAL_H_

//--------------------------- INCLUSAO DE ARQUIVOS ---------------------------//
 #include "..\Header\Hal_prm.h"
// -------------------------- Defines, Enumerações ---------------------------//

typedef enum
{
	LED_0 = 0,
	LED_1,
	LED_2,
	LED_3,
	NUM_OF_LEDS
}LED_OUTPUT_TYPE;

typedef enum
{
	KEY_0 = 0,
	KEY_1,
	KEY_2,
	KEY_3,
	NUM_OF_KEYS
}KEY_INPUT_TYPE;

typedef struct
{
	unsigned char key[NUM_OF_KEYS];
}KEYS_READ;


// define as entradas analógicas existentes POT_INT no canal 0 e POT_EXT no canal 5
typedef enum
{
	POT_INT = 0,
	ANALOG_INPUT_1,
	ANALOG_INPUT_2,
	ANALOG_INPUT_3,
	ANALOG_INPUT_4,
	POT_EXT,
	NUM_OF_ANALOG_INPUT,
}ANALOG_INPUT_TYPE;

//=====================================================================================================================
//--------------------------------------Funções Publicas (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
void Hal__Initialize(void);
void Hal__BackgroundHandler(void);
void Hal__FastHandler(void);

void Hal__SetLed(LED_OUTPUT_TYPE output,unsigned char value);
void Hal__SetAllLeds(unsigned char value);
unsigned char Hal__ReadKey(KEY_INPUT_TYPE key);
unsigned char Hal__ReadAllKey(void);            

void Hal__WriteValtoSegment(const char* ptr_display_values);


#endif /* HAL_H_ */