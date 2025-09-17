//-------------------------------------- Include Files ----------------------------------------------------------------
//#include "C_Types.h"
//#include <hidef.h> /* for EnableInterrupts macro */
//#include "derivative.h" /* include peripheral declarations */
#include "..\Header\main_prm.h"

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
//-------------------------------------- Global Variables ----------------------------------------------------------------

MAIN_SLOT_TYPE Slot;


//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================

void main(void)
{
	
	Slot = SLOT_1;
	
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

		Slot++;
		if(Slot >= NUM_OF_MAIN_SLOTS){
			Slot = SLOT_1;
		}
	}

}


