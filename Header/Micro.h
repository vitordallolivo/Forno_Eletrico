/*
 * Micro.h
 *  Author: Ana Watanabe
 */ 


#ifndef MICRO_H_
#define MICRO_H_

#include <avr/io.h>

// MACROS

#define DISABLE_INTERRUPT() __asm SEI;
#define ENABLE_INTERRUPT()  __asm CLI;

//***********************************************************************************************************
// ************************************  MACROS *************************************************************
//***********************************************************************************************************
#define DISABLE_INTERRUPT() __asm SEI;
#define ENABLE_INTERRUPT()  __asm CLI;


//***********************************************************************************************************
// ************************************  Enums, Structs *****************************************************
//***********************************************************************************************************
//union Low Byte bit definitions Bits 0 - 7
typedef union
{
	unsigned char byte;
	struct
	{
		unsigned char bit0 :1;
		unsigned char bit1 :1;
		unsigned char bit2 :1;
		unsigned char bit3 :1;
		unsigned char bit4 :1;
		unsigned char bit5 :1;
		unsigned char bit6 :1;
		unsigned char bit7 :1;
	} bit;
} DEF_LOWBYTE;

//union High Byte bit definitions Bits 8 - 15
typedef union
{
	unsigned char byte;
	struct
	{
		unsigned char bit8 :1;
		unsigned char bit9 :1;
		unsigned char bit10 :1;
		unsigned char bit11 :1;
		unsigned char bit12 :1;
		unsigned char bit13 :1;
		unsigned char bit14 :1;
		unsigned char bit15 :1;
	} bit;
} DEF_HIBYTE;

// *********  GPIO Ports Registers  ******

// Port Data and Direction Registers
typedef struct
{
	volatile DEF_LOWBYTE DATA_IN_REG;
	volatile DEF_LOWBYTE DIRECION_REG;
	volatile DEF_LOWBYTE DATA_OUT_PULL_REG;
} GPIO_DATA_TYPE;


#ifdef __AVR_ATmega328P__

	// Port Data and Direction Registers Address
	#define GPIOB_DATA  (*((volatile GPIO_DATA_TYPE *)0x00000023))    //Port B Data Register
	#define GPIOC_DATA  (*((volatile GPIO_DATA_TYPE *)0x00000026))    //Port C Data Register
	#define GPIOD_DATA  (*((volatile GPIO_DATA_TYPE *)0x00000029))    //Port D Data Register

	#define PORTB  &GPIOB_DATA
	#define PORTC  &GPIOC_DATA
	#define PORTD  &GPIOD_DATA

	#define GPIO_DATA {PORTB, PORTC, PORTD};

#endif

#endif /* MICRO_H_ */