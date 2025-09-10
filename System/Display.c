/*
 * Display.c
 *
 *  Created on: 10/09/2017
 *      Author: MAASDN
 */

#define F_CPU 16000000UL

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "..\Header\C_types.h"
#include "..\Header\Display.h"
#include "..\Header\Hal.h"
//#include "LcdMgr.h"
//#include "Timer.h"
#include <util/delay.h> /*biblioteca para o uso das rotinas de _delay_ms() e _delay_us()*/

//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------
#define NUM_EVENTS     		50
#define ACENDE_LED          0
#define APAGA_LED           1


//-------------------------------------- Global Variables ----------------------------------------------------------------

OVEN_DISPLAY_STATE_TYPE Oven_Display_State; // variável global de display
                                            // usado no  UpdateDisplayLeds(void)

KEY_EVENT_TYPE Display_Keys_Map;           // vari?vel global  de keys
                                           // usado no Display__GetEvent(void)
							   
const char ZERADO_DIGITO[4] = {0xC0,0xC0,0xC0,0xC0};   //# 0000
const char MINIMO_DIGITO[4] = {0xC0,0xF9,0x80,0xC0};   //# 0180
const char MEDIO_DIGITO[4] =  {0xC0,0xA4,0X90,0x92};   //# 0295
const char MAXIMO_DIGITO[4] = {0xC0,0x99,0X90,0xB0};   //# 0493
	
const char* ptr_last_display_write = MAXIMO_DIGITO;
//-------------------------------------- PRIVATE (Function Prototypes) ---------------------------------------------------

void UpdateDisplayLeds(void);
//void UpdateDisplayLCD(void);
void ReadDisplayKeys(void);
void UpdateDisplaySevenSeg(void);

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================
//---------------------------------------------------------------------------------------------------------------------
/**
 *  Inicializa vari?veis referente ao estado inicial do forno e das chaves
 */
void Display__Initialize(void)
	{
	Oven_Display_State = OVEN_INIT;
	Display_Keys_Map = KEY_OFF_EVENT;
	}

//---------------------------------------------------------------------------------------------------------------------
/**
 *   Atualiza o display(leds) do estado do forno em fun??o da leitura das chaves
 */
void Display__Handler(void)
{
	#if (LED_DISPLAY == ENABLED)	
	   UpdateDisplayLeds();        // atualiza??o dos leds
	#endif	                       // fun??o privada!
	#if (SEVEN_SEG_DISPLAY == ENABLED)
		UpdateDisplaySevenSeg();
	#endif
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *  A funcao atualiza a variavel global:
 *  Oven_Display_State que indica o estado do forno  
 */
void Display__SetState(OVEN_DISPLAY_STATE_TYPE state)
{
	if(state < NUM_OF_OVEN_STATES)
	{
		Oven_Display_State = state;
	}
	
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *      Lê as chaves e coloca valor na vari?vel global:
 *      Display_Keys_Map e retorna o  mesmo na fun??o

 */


KEY_EVENT_TYPE Display__GetEvent(void)
{
	KEY_EVENT_TYPE event;
	ReadDisplayKeys();    // L? as chaves e coloca valor na vari?vel global Display_Keys_Map
	event = Display_Keys_Map;  //atribui a event o global atualizada em ReadDisplayKeys()
	return (event);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *  
 */
//=====================================================================================================================
//-------------------------------------- PRIVATE Functions -------------------------------------------------------------
//=====================================================================================================================
//---------------------------------------------------------------------------------------------------------------------
/**
 *   Atualiza os estados dos leds chamando fun??es 
     tipo Hal__SetLed() 
 */
void UpdateDisplayLeds(void)
{
	
	switch(Oven_Display_State)
	{
	case OVEN_OFF:
	{
	       Hal__SetAllLeds(APAGA_LED);
		   break;
	}
	case OVEN_INIT:
	case OVEN_TIMEOUT:
	   		
		break;

	case OVEN_MIN:
	{
		Hal__SetLed(LED_0, ACENDE_LED);
		Hal__SetLed(LED_1, APAGA_LED);
		Hal__SetLed(LED_2, APAGA_LED);
		break;
	}
	case OVEN_MED:
	{
		Hal__SetLed(LED_0, ACENDE_LED);
		Hal__SetLed(LED_1, ACENDE_LED);
		Hal__SetLed(LED_2, APAGA_LED);
		break;
	}
	case OVEN_MAX:
	{
		Hal__SetLed(LED_0, ACENDE_LED);
		Hal__SetLed(LED_1, ACENDE_LED);
		Hal__SetLed(LED_2, ACENDE_LED);
		break;
	}
		
	default:
	{
	break;
	}
 }
}


//---------------------------------------------------------------------------------------------------------------------
/**
 *  Atualiza a variavel global (Display_Keys_Map) das chaves
 *  chamando Hal_ReadKey()
 */
void ReadDisplayKeys(void)
{	
	KEYS_READ* keys= Hal__ReadAllKey(); // Lê todas as chaves
	
	if (keys->key[KEY_0] == SW_ON &&  keys->key[KEY_2] == SW_ON){ // Forno desligado
		Display_Keys_Map = KEY_OFF_EVENT;
	}
	else{
		if (keys->key[KEY_0] == SW_ON ){ // Forno no minimo
			Display_Keys_Map = KEY_MIN_EVENT;	
		}
		if (keys->key[KEY_2] == SW_ON){ // Forno no máximo
			Display_Keys_Map  = KEY_MAX_EVENT;
		}
		if (keys->key[KEY_1] == SW_ON){ // Forno no médio
			Display_Keys_Map  = KEY_MED_EVENT;
		}
	}
}

/**
 *  Atualiza  7 Segmentos chamando Hal__WriteValtoSegment() para cada segmento
 *  DESAFIO: Mudar esta função enviando um ponteiro para ZERADO_DIGITO[], MINIMO_DIGITO[], 
 *  MEDIO_DIGITO[] e  MAXIMO_DIGITO[] na chamada de
 *  Hal__WriteValtoSegment(). Assim, ao invés de chamar 4 vezes,vai chamar apenas uma vez.
 *  Observe que as funções Hal__WriteValtoSegment() e
 *  SevenSeg_WriteValueToSegment() podem sofrer modificações!!!
 
 */




void UpdateDisplaySevenSeg(void)
{
	char* ptr_display_values = &ZERADO_DIGITO[0]; // Inicializa o ponteiro 
	switch(Oven_Display_State)
		{
		case OVEN_OFF:
			break;
		case OVEN_INIT:
		case OVEN_TIMEOUT:
			break;
		case OVEN_MIN:
			ptr_display_values = &MINIMO_DIGITO[0];
			break;
		case OVEN_MED:
			{
			ptr_display_values = &MEDIO_DIGITO[0];
			break;
			}
		case OVEN_MAX:
			{
			ptr_display_values = &MAXIMO_DIGITO[0];
			break;
			}
	
		default:
			{
			break;
			}
	   }
		Hal__WriteValtoSegment(ptr_display_values);
}
