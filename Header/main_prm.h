/*
 * main_prm.h
 *
 * Created: 02/04/2019 22:03:40
 *  Author: Ana Watanabe
 */ 


#ifndef MAIN_PRM_H_
#define MAIN_PRM_H_
//-------------------------------------- Include Files ----------------------------------------------------------------
#include "..\Header\C_Types.h"
#include "..\Header\Appl.h"
#include "..\Header\Display.h"
#include "..\Header\Gpio.h"
#include "..\Header\Adc.h"
#include "..\Header\Timer.h"
#include "..\Header\Hal.h"
#include "..\Header\TempSensor.h"
#include "..\Header\OvenTempControl.h"
#include "..\Header\Pwm.h"
#include "..\Header\Sounds.h"
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
	Pwm__Initialize();\
	Display__Initialize();\
	Timer__Initialize();\
	Sounds__Initialize();\
	Appl__Initialize();\
	ADC__Initialize();\
	TempSensor__Initialize();\
	OvenTempControl__Initialize();\
}

#define ALL_SLOTS_TASKS()\
{\
	Hal__FastHandler();\
	Timer__HMSHandler();\
	Hal__BackgroundHandler();\
	ADC__Handler();\
}

#define SLOT_1_TASKS()\
{\
	Sounds__Background();\
}

#define SLOT_2_TASKS()\
{\
	Appl__Handler();\
}

#define SLOT_3_TASKS()\
{\
	TempSensor__ConversionHandler();\
}

#define SLOT_4_TASKS()\
{\
	OvenTempControl__Handler();\
}

#define SLOT_5_TASKS()\
{\
	Display__Handler();\
}


#endif /* MAIN_PRM_H_ */
