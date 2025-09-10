/*
 * SevenSeg.c
 *
 * Created: 10/09/2025 07:38:58
 *  Author: Vitor
 */ 
#include <avr/io.h>

#include "..\Header\Gpio.h"
#include "..\Header\SevenSeg.h"
#include "..\Header\Micro.h"
#include "util\delay.h"

/* Segment byte maps for numbers 0 to 9 */
const char SEGMENT_MAP_DIGIT[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0X80,0X90};
								//  0 , 1  ,  2 , 3  , 4 ,  5 , 6,   7 ,   8   ,9
/* Byte maps to select segment 1 to 4 */
const char SEGMENT_SELECT[] = {0xF1,0xF2,0xF4,0xF8};


/* Write a value to one of the 4 digits of the display */
void SevenSeg_WriteValueToSegment(char* ptr_display_values)
{
	for (char Segment = 0 ; Segment < NUM_SEG; Segment ++){
		GPIO_PIN_WRITE(PORT_D, LATCH_PIN, RESET);


		for (uint8_t i = 0; i < 8; i++) {
			if (ptr_display_values[0] & (1 << (7 - i))) {
				GPIO_PIN_WRITE(PORT_B, 0, SET);
			}
			else {
				GPIO_PIN_WRITE(PORT_B, 0, RESET);
			}

			GPIO_PIN_WRITE(PORT_D, CLK_PIN, SET);
			GPIO_PIN_WRITE(PORT_D, CLK_PIN, RESET);
		}

		for (uint8_t i = 0; i < 8; i++) {
			if (SEGMENT_SELECT[Segment] & (1 << (7 - i))) {
				GPIO_PIN_WRITE(PORT_B, 0, SET);
			} 
			else {
				GPIO_PIN_WRITE(PORT_B, 0, RESET);
			}

			GPIO_PIN_WRITE(PORT_D, CLK_PIN, SET);
			GPIO_PIN_WRITE(PORT_D, CLK_PIN, RESET);
		}

		GPIO_PIN_WRITE(PORT_D, LATCH_PIN, SET);
		ptr_display_values++;
	}
}


