/*
 * GPIO.c
 *
 * Created: 16-Aug-25 17:24:52
 *  Author: Vitor
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include "../Header/GPIO.h"

//-------------------------------------- Variáveis públicas -----------------------------------------------------------
const unsigned char GPIO_PIN_SET_MASK[] = {0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80};
const unsigned char GPIO_PIN_CLR_MASK[] = {0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};

volatile GPIO_DATA_TYPE *GPIO_DATA_LIST[NUM_OF_PORTS] = GPIO_DATA;   //está no Micro.h:  GPIO_DATA_TYPE  e #define GPIO_DATA {PORTA, PORTB, PORTC, PORTD, PORTE, PORTF, PORTG};
//------------------------------------ FUNCOES -----------------------------------------------------------
void GPIO_CONFIG(GPIO_PORT port, unsigned char pin, GPIO_PIN_TYPE type){
		
		
		// TODO : Implementar retorno para funções de configuração
		
		// Evita que ao usuário escolher um numero maior de portas ou pinos cause algum problema 
		// de memória grave
		if (port >= MAX_NUM_OF_PORTS || pin>= MAX_NUM_OF_PORT_PINS){
			return;
		}
		
		volatile GPIO_DATA_TYPE *pt_data;
		unsigned char set_bit_mask;
		unsigned char clr_bit_mask;
		
	
		set_bit_mask = GPIO_PIN_SET_MASK[pin];
		clr_bit_mask = GPIO_PIN_CLR_MASK[pin];
		
		// Aponta para o endereço do PORTx
		pt_data = GPIO_DATA_LIST[port];
			
		// O usuario pode escolher ter um input com pullup, input sem pullup ou uma saida
		switch(type){
			case INPUT_DIGITAL_PULLUP:
				pt_data->DIRECION_REG.byte &= clr_bit_mask;
				pt_data->DATA_OUT_PULL_REG.byte |= set_bit_mask;
				break;
			case INPUT_DIGITAL:
				pt_data->DIRECION_REG.byte &= clr_bit_mask; 
				pt_data->DATA_OUT_PULL_REG.byte &= clr_bit_mask;
				break;
			case OUTPUT_DIGITAL:
				pt_data->DIRECION_REG.byte |= set_bit_mask;
				break;
			default: // caso o usuário tenha configurado errado, para não dar problema
				break;
		}
}


void GPIO_PIN_WRITE(GPIO_PORT port, unsigned char pin, GPIO_PIN_STATE state){
	volatile GPIO_DATA_TYPE *pt_data;
	pt_data =  GPIO_DATA_LIST[port];
	
	if (state == ON){
		pt_data->DATA_OUT_PULL_REG.byte |= GPIO_PIN_SET_MASK[pin]; 
	}
	else{
		pt_data->DATA_OUT_PULL_REG.byte &= GPIO_PIN_CLR_MASK[pin]; 
	}
	
}
void GPIO_PIN_TOGGLE(GPIO_PORT port, unsigned char pin){
	volatile GPIO_DATA_TYPE *pt_data;
	pt_data = GPIO_DATA_LIST[port];
	
	// Se pegar o set_mask é fazer XOR com o pino que você quer, ex: 0b11111111 xor 0x1 = 0b11111110
	pt_data->DATA_OUT_PULL_REG.byte ^= GPIO_PIN_SET_MASK[pin];
}

unsigned char GPIO_PIN_READ(GPIO_PORT port, unsigned char pin){
	volatile GPIO_DATA_TYPE *pt_data;
	pt_data = GPIO_DATA_LIST[port];
	// AND dos dados de PINx com o pin_set_mask
	if(pt_data->DATA_IN_REG.byte & GPIO_PIN_SET_MASK[pin]){
		return ON;
	}
	return OFF;
}