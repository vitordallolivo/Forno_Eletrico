/*
 * GPIO.h
 *
 * Created: 16-Aug-25 17:24:37
 *  Author: vitor
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#include "../Header/Micro.h"

#define set_bit(Y,bit_x) (Y|=(1<<bit_x)) /*ativa o bit x da variável Y (coloca em 1)*/
#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x)) /*limpa o bit x da variável Y (coloca em 0)*/
#define tst_bit(Y,bit_x) (Y&(1<<bit_x)) /*testa o bit x da variável Y  (retorna 0 ou 1)*/
#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x)) /*troca o estado do bit x da variável Y (complementa)*/

// --------------------------------Variáveis Globais--------------------------------
typedef enum{
		INPUT_DIGITAL_PULLUP = 0,
		INPUT_DIGITAL,
		OUTPUT_DIGITAL
}GPIO_PIN_TYPE;

typedef enum{
	PORT_B =0,
	PORT_C,
	PORT_D,
	NUM_OF_PORTS
}GPIO_PORT;

typedef enum{ 
	RESET = 0, 
	SET
}GPIO_PIN_STATE;


// --------------------------------DEFINIÇÕES DE PROJETO ------------------------------//

#define MAX_NUM_OF_PORT_PINS 8
#define MAX_NUM_OF_PORTS NUM_OF_PORTS

#ifdef __AVR_ATmega328P__

	// --------------------------------PINOS DO MODULO--------------------------------
	#define LED1 PB5 //LED1 é o substituto de PB5 na programação
	#define LED2 PB4 //LED2 é o substituto de PB4 na programação
	#define LED3 PB3 //LED3 é o substituto de PB3 na programação
	#define LED4 PB2 //LED4 é o substituto de PB2 na programação
	#define SW1  PC1 //SW1  é o substituto de PC1 na programação
	#define SW2  PC2 //SW1  é o substituto de PC2 na programação
	#define SW3  PC3 //SW1  é o substituto de PC3 na programação

	// Pinos RX e Tx do Atmega328P
	#define TX_pin PC0
	#define RX_pin PC1

	#define PORT_LED PORT_B
	#define PORT_SW PORT_C
	
	#define NUM_SEG 4
	#define LATCH_PIN     PD4   // pino 12 (shiftclk do 74HC595)
	#define CLK_PIN       PD7   // pino 11 (latchclk do 74HC595)
	#define DATA_PIN      PB0   // pino 14 (serial data input do 74HC595)
#endif

// --------------------------------Prototipos de funções--------------------------------//
void GPIO_CONFIG(GPIO_PORT port, unsigned char pin, GPIO_PIN_TYPE type);
void GPIO_PIN_WRITE(GPIO_PORT port, unsigned char pin, GPIO_PIN_STATE state);
void GPIO_PIN_TOGGLE(GPIO_PORT port, unsigned char pin);
unsigned char GPIO_PIN_READ(GPIO_PORT port, unsigned char pin);


#endif /* GPIO_H_ */