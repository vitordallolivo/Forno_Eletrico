/*
 * GPIO.h
 *
 * Created: 16-Aug-25 17:24:37
 *  Author: vitor
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#include "../Header/Micro.h"

#define set_bit(Y,bit_x) (Y|=(1<<bit_x)) /*ativa o bit x da vari�vel Y (coloca em 1)*/
#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x)) /*limpa o bit x da vari�vel Y (coloca em 0)*/
#define tst_bit(Y,bit_x) (Y&(1<<bit_x)) /*testa o bit x da vari�vel Y  (retorna 0 ou 1)*/
#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x)) /*troca o estado do bit x da vari�vel Y (complementa)*/

// --------------------------------Vari�veis Globais--------------------------------
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
	OFF = 0, 
	ON
}GPIO_PIN_STATE;


// --------------------------------DEFINI��ES DE PROJETO ------------------------------//

#define MAX_NUM_OF_PORT_PINS 8
#define MAX_NUM_OF_PORTS NUM_OF_PORTS

#ifdef __AVR_ATmega328P__
	#define SW_OFF 1  // � invertido por conta do pullup
	#define SW_ON  0
	// --------------------------------PINOS DO MODULO--------------------------------
	#define LED1 PB5 //LED1 � o substituto de PB5 na programa��o
	#define LED2 PB4 //LED2 � o substituto de PB4 na programa��o
	#define LED3 PB3 //LED3 � o substituto de PB3 na programa��o
	#define LED4 PB2 //LED4 � o substituto de PB2 na programa��o
	#define SW1  PC1 //SW1  � o substituto de PC1 na programa��o
	#define SW2  PC2 //SW1  � o substituto de PC2 na programa��o
	#define SW3  PC3 //SW1  � o substituto de PC3 na programa��o

	// Pinos RX e Tx do Atmega328P
	#define TX_pin PC0
	#define RX_pin PC1

	#define PORT_LED PORT_B
	#define PORT_SW PORT_C

#endif

// --------------------------------Prototipos de fun��es--------------------------------//
void GPIO_CONFIG(GPIO_PORT port, unsigned char pin, GPIO_PIN_TYPE type);
void GPIO_PIN_WRITE(GPIO_PORT port, unsigned char pin, GPIO_PIN_STATE state);
void GPIO_PIN_TOGGLE(GPIO_PORT port, unsigned char pin);
unsigned char GPIO_PIN_READ(GPIO_PORT port, unsigned char pin);

// ------------------------		MACROS ----------------------------------------------///

#define ENABLE_PULLUP(port,pin) GPIO_PIN_WRITE(port,pin,ON);]
#define DISABLE_PULLUP(port,pin) GPIO_PIN_WRITE(port,pin,OFF);
#define DEFINE_LED_STATE(pin,state) GPIO_PIN_WRITE(PORT_LED,pin,state)
#define READ_SW(pin) GPIO_PIN_READ(PORT_SW,pin)

#endif /* GPIO_H_ */