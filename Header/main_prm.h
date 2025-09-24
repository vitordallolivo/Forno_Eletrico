/*
 * main_prm.h
 *
 * Created: 02/04/2019 22:03:40
 *  Author: Ana Watanabe
 */ 


#ifndef MAIN_PRM_H_
#define MAIN_PRM_H_
//-------------------------------------- Include Files ----------------------------------------------------------------
//#include "C_Types.h"
#include "..\Header\Appl.h"
//#include "Gpio.h"


#include "..\Header\ADC.h"
#include "..\Header\Hal.h"
#include "..\Header\Display.h"

//#include "TempSensor.h"
//#include "OvenTempControl.h"
//#include "Sounds.h"
//#include "Timer.h"
//#include "PWM.h"
//#include "LcdMgr.h"
//-------------------------------------- Defines ----------------------------------------------------------------

// Select ENALBED to use a fixed slot time duration for each main slot, otherwise select DISABLED
// If ENALBED, need to define the slot time duration in SLOT_TIME parameters below
#define USE_FIXED_TIME_SLOT	ENABLED //ENABLED//

// Define the fixed time slot duration
// Each slot in main loop will take SLOT_TIME before switch to next slot 
// Use _1MS for 1ms, _5MS for 5ms or _10MS for 10ms 
#define SLOT_TIME	 _1MS	//_1MS  // _4MS  // _10MS  

// ENALBED or DISABLED the Watchdog
#define WATCHDOG_ENABLE  	 ENABLED// //DISABLED


#define INITIALIZE_TASKS()\
{\
	Hal__Initialize();\
	Display__Initialize();\
	Appl__Initialize();\
}

#define ALL_SLOTS_TASKS()\
{\
	Hal__FastHandler();\
	Hal__BackgroundHandler();\
}

#define SLOT_1_TASKS()\
{\
	Appl__Handler();\
}

#define SLOT_2_TASKS()\
{\
	Display__Handler();\
}
	
#define SLOT_3_TASKS()\
{\
	ADC__Handler();\
}
	
#define SLOT_4_TASKS()\
{\
}
	
#define SLOT_5_TASKS()\
{\
}
	



#endif /* MAIN_PRM_H_ */
