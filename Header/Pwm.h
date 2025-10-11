/*
 * Pwm.h
 *
 * Created: 05/11/2019 22:26:18
 *  Author: Ana Watanabe
 */ 


#ifndef Pwm_H_
#define Pwm_H_

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "..\Header\Micro.h"
#include "..\Header\Sounds.h"
#include "..\Header\Pwm_prm.h"
//**********ver SE não é Sounds_prm.h ********


typedef enum {
	PWM0 = 0,   // OC0A
	PWM1,       // OC0B
	PWM2,       // OC1A
	PWM3,       // OC1B
	PWM4,       // OC2A
	PWM5,       // OC2B
	NUM_OF_PWM,
} PWM_ID_TYPE;

typedef enum {
	PWM_TC0 = 0, // 8 bits
	PWM_TC1, // 16 bits
	PWM_TC2, // 8 bits
	NUM_OF_PWM_TC,
} PWM_TC_TYPE;

//protótipos
// Inicialização do módulo PWM                                                                                           
void Pwm__Initialize(void); 
void Pwm__SetTCFrequency( PWM_TC_TYPE tc, unsigned short int frequency); // Configura o TC numa determinada frequência ( verificar no livro para cada TC
void Pwm__SetDutyCycle( PWM_ID_TYPE pwm, unsigned char duty);// Configura o PWM TC num determinado ciclo de trabalho ( 0 a 100%)




#endif /* Pwm_H_ */