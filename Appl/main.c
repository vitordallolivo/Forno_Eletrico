//-------------------------------------- Include Files ----------------------------------------------------------------
//#include "C_Types.h"
//#include <hidef.h> /* for EnableInterrupts macro */
//#include "derivative.h" /* include peripheral declarations */
#include "..\Header\main_prm.h"
#include "avr/interrupt.h"
//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------
typedef enum
{
	SLOT_1,
	SLOT_2,
	SLOT_3,
	SLOT_4,
	SLOT_5,
	NUM_OF_MAIN_SLOTS
}MAIN_SLOT_TYPE;

#define _1MS    0x08
#define _4MS    0x0A
#define _10MS   0x0B

#define F_CPU 16000000UL

//-------------------------------------- Global Variables ----------------------------------------------------------------

MAIN_SLOT_TYPE Slot;


//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================


void main(void)
{
	
	Slot = SLOT_1;
	
	TCCR1A = 0;                        //confira timer para operação normal pinos OC1A e OC1B desconectados
	TCCR1B = 0;                        //limpa registrador
	TCCR1B |= (1<<CS10)|(1 << CS12);   // configura prescaler para 1024: CS12 = 1 e CS10 = 1
	TCNT1 = 65520;      //para contar 1ms
	//TCNT1 = 0xC2F7;                    //inicia timer com valor para que estouro ocorra em 1 segundo
	//TCNT1 = 34186;                   // Para contar 2s=> 65536 - 31330
	// 65.535-(16MHz/1024/1Hz) =  65.535 - 15.625 = 49911(0xC2F7)=> 15.625 é o período desejado.
	// Usa-se a diferença porque o contador é crescente e estoura de 0xffff a 0.
	TIMSK1 |= (1 << TOIE1);
	sei();
	
	
	// Functions Initialization
	INITIALIZE_TASKS();
	
	
	//Main Loop
	for(;;)
	{
		ALL_SLOTS_TASKS();
		switch(Slot){
			
			case SLOT_1:
				SLOT_1_TASKS();
			break;

			case SLOT_2:
				SLOT_2_TASKS();
			break;

			case SLOT_3:
				SLOT_3_TASKS();
			break;

			case SLOT_4:
				SLOT_4_TASKS();
			break;

			case SLOT_5:
				SLOT_5_TASKS();
			break;

			default:
				Slot = SLOT_1;
			break;

		}
		while(TCNT1 <= 65534);
		Slot++;
		if(Slot >= NUM_OF_MAIN_SLOTS){
			Slot = SLOT_1;
		}
	}

}


