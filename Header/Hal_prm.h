/*
 * Hal_prm.h
 *
 * Created: 17/09/2025 07:39:42
 *  Author: 12279036932
 */ 


#ifndef HAL_PRM_H_
#define HAL_PRM_H_

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "..\Header\C_Types.h"


//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------

//-------------------------------------------------------------------------------------------
// --------------------------------- ON BOARD LEDs CONFIGURATION ----------------------------
//-------------------------------------------------------------------------------------------
//On board LEDs configuration
// Select ENABLED for LEDs that will be used otherwise DISABLED

#define USE_LED_0		ENABLED
#define USE_LED_1		ENABLED
#define USE_LED_2		ENABLED
#define USE_LED_3		ENABLED


//-------------------------------------------------------------------------------------------
// ---------------------------------  KEYS CONFIGURATION ----------------------------------
//-------------------------------------------------------------------------------------------
//On board Keys configuration
// Select ENABLED for Keys that will be used otherwise DISABLED
#define USE_KEY_0		ENABLED
#define USE_KEY_1		ENABLED
#define USE_KEY_2		ENABLED
#define USE_KEY_3		ENABLED




#endif /* HAL_PRM_H_ */