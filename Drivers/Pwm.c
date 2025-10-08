/*
 * Pwm.c
 *
 * Created: 05/11/2019 22:50:57
 *  Author: Ana Watanabe
 */ 

#include <avr/io.h>
#include "..\Header\Gpio.h"
#include "..\Header\Hal.h"
#include "..\Header\Pwm.h"
#include "..\Header\Micro.h"

//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------

const unsigned char PWM_Enable_Table[NUM_OF_PWM] = {
					CONFIG_PWM0, // PD6
					CONFIG_PWM1, // PD5
					CONFIG_PWM2, // PB1
					CONFIG_PWM3, // PB2
					CONFIG_PWM4, // PB3
					CONFIG_PWM5  // PD3
};

#ifndef F_CPU
	#define  F_CPU 16000000UL
#endif

//-------------------------------------- PRIVATE (Function Prototypes) ---------------------------------------------------




//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================

 
// Inicialização do módulo PWM ( Buzzer está no PD3 OC2B !!)
void Pwm__Initialize(void){
	PWM_ID_TYPE PWM_id = PWM0;
	PWM_TC_TYPE TC_channel = PWM_TC0;
	
	volatile TC0_REG_TYPE *pwm_pt0;
	volatile TC1_REG_TYPE *pwm_pt1;
	volatile TC2_REG_TYPE *pwm_pt2;

	pwm_pt0 = TC0_REGISTERS;
	pwm_pt1 = TC1_REGISTERS;
	pwm_pt2 = TC2_REGISTERS;
	
	
	for (PWM_id ; PWM_id <= NUM_OF_PWM; PWM_id++){
		if(PWM_Enable_Table[PWM_id] == ENABLED){ 
			switch(PWM_id){
				case PWM0: // OC0A
				// Modo fase corrigida (WGM00 = 1, WGM01 = 0), OC0A invertido (COM0A1:0 = 11)
				pwm_pt0->TCCR0A_REG.byte |= 0b11000001; // COM0A1:0 = 11, WGM00 = 1
				
				TC_channel = PWM_TC0;
				
				break;

				case PWM1: // OC0B
				// OC0B invertido (COM0B1:0 = 11)
				pwm_pt0->TCCR0A_REG.byte |= 0b00110001; // COM0B1:0 = 11, WGM00 = 1
				
				TC_channel = PWM_TC0;
				break;

				case PWM2: // OC1A
				// OC1A invertido (COM1A1:0 = 11), fase corrigida 8 bits (WGM10 = 1)
				pwm_pt1->TCCR1A_REG.byte |= 0b11000001;
				
				TC_channel = PWM_TC1;
				break;

				case PWM3: // OC1B
				// OC1B invertido (COM1B1:0 = 11), fase corrigida 8 bits
				pwm_pt1->TCCR1A_REG.byte |= 0b00110001;
				
				TC_channel = PWM_TC1;
				break;

				case PWM4: // OC2A
				// OC2A invertido, fase corrigida
				pwm_pt2->TCCR2A_REG.byte |= 0b11000001;
				
				TC_channel = PWM_TC2;
				break;

				case PWM5: // OC2B — já configurado antes, mas ok repetir
				pwm_pt2->TCCR2A_REG.byte |= 0b00110001;
				
				TC_channel = PWM_TC2;
				break;

				case NUM_OF_PWM:
				break;
			}
			
			Pwm__SetTCFrequency(TC_channel, BUZZER_DEFAULT_FREQ);
			Pwm__SetDutyCycle(PWM_id, BUZZER_OFF_DUTY);
		}

		
	}
	
}

//*********************************************************
//
//   Esta rotina configura o TC numa determinada frequência 
//   ( verifcar no livro para cada TC)
//
//*********************************************************
 
void Pwm__SetTCFrequency(PWM_TC_TYPE tc, unsigned short frequency) {
	volatile TC0_REG_TYPE *pwm_pt0 = TC0_REGISTERS;
	volatile TC1_REG_TYPE *pwm_pt1 = TC1_REGISTERS;
	volatile TC2_REG_TYPE *pwm_pt2 = TC2_REGISTERS;

	const uint32_t f_cpu = F_CPU;
	const uint16_t top = 255;
	const uint32_t target = 2UL * frequency * (top + 1); 

	uint8_t prescaler_bits = 0;
	uint8_t found = 0;

	switch (tc) {
		case PWM_TC0: {
			const uint16_t prescaler_values[] = {1, 8, 64, 256, 1024};
			const uint8_t prescaler_codes[]   = {0x01, 0x02, 0x03, 0x04, 0x05};

			for (uint8_t i = 0; i < sizeof(prescaler_values)/sizeof(prescaler_values[0]); i++) {
				if ((f_cpu / prescaler_values[i]) >= target) {
					prescaler_bits = prescaler_codes[i];
					found = 1;
					break;
				}
			}

			if (!found) {
				prescaler_bits = 0x05; // Máximo prescaler = 1024
			}

			// Atualiza TCCR0B apenas com os bits do prescaler
			pwm_pt0->TCCR0B_REG.byte = (pwm_pt0->TCCR0B_REG.byte & 0xF8) | prescaler_bits;
			break;
		}

		case PWM_TC1: {
			const uint16_t prescaler_values[] = {1, 8, 64, 256, 1024};
			const uint8_t prescaler_codes[]   = {0x01, 0x02, 0x03, 0x04, 0x05};

			for (uint8_t i = 0; i < sizeof(prescaler_values)/sizeof(prescaler_values[0]); i++) {
				if ((f_cpu / prescaler_values[i]) >= target) {
					prescaler_bits = prescaler_codes[i];
					found = 1;
					break;
				}
			}

			if (!found) {
				prescaler_bits = 0x05;
			}

			pwm_pt1->TCCR1B_REG.byte = (pwm_pt1->TCCR1B_REG.byte & 0xF8) | prescaler_bits;
			break;
		}

		case PWM_TC2: {
			const uint16_t prescaler_values[] = {1, 8, 32, 64, 128, 256, 1024};
			const uint8_t prescaler_codes[]   = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

			for (uint8_t i = 0; i < sizeof(prescaler_values)/sizeof(prescaler_values[0]); i++) {
				if ((f_cpu / prescaler_values[i]) >= target) {
					prescaler_bits = prescaler_codes[i];
					found = 1;
					break;
				}
			}

			if (!found) {
				prescaler_bits = 0x07;
			}

			pwm_pt2->TCCR2B_REG.byte = (pwm_pt2->TCCR2B_REG.byte & 0xF8) | prescaler_bits;
			break;
		}

		default:
		// Timer inválido
		break;
	}
}

//*********************************************************
//
//   Esta rotina configura o PWM TC num determinado 
//   ciclo de trabalho ( 0 a 100)
//
//*********************************************************
void Pwm__SetDutyCycle( PWM_ID_TYPE pwm, unsigned char duty){
	volatile TC0_REG_TYPE *pwm_pt0;
	volatile TC1_REG_TYPE *pwm_pt1;
	volatile TC2_REG_TYPE *pwm_pt2;

	pwm_pt0 = TC0_REGISTERS;
	pwm_pt1 = TC1_REGISTERS;
	pwm_pt2 = TC2_REGISTERS;
	
	if (duty >100){ 
		duty = 100;
	}
	
	
	switch (pwm){
		case PWM0:
			pwm_pt0->OCR0A_REG.byte = (unsigned char)(255*duty/100); //considerando TOP = 255
			break;
		case PWM1:
			pwm_pt0->OCR0B_REG.byte = (unsigned char)(255*duty/100); //considerando TOP = 255
			break;
		case PWM2:
			pwm_pt1->OCR1AH_REG.byte = (unsigned char)(255*duty/100); //considerando TOP = 255
 			break;    
		case PWM3:
			 pwm_pt1->OCR1BH_REG.byte = (unsigned char)(255*duty/100); //considerando TOP = 255
			 break;    
		case PWM4:
			 pwm_pt2->OCR2A_REG.byte = (unsigned char)(255*duty/100); //considerando TOP = 255
			 break;    
		case PWM5:
			pwm_pt2->OCR2B_REG.byte = (unsigned char)(255*duty/100); //considerando TOP = 255
			break;    
		default:
			break;	
	}
}

