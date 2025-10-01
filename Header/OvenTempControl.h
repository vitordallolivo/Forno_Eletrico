/*
 * OvenTempControl.h
 *
 *  Created on: 03/10/2017
 *      Author: MAASDN
 */

#ifndef OVENTEMPCONTROL_H_
#define OVENTEMPCONTROL_H_


//-------------------------------------- Include Files ----------------------------------------------------------------

#include "..\Header\OvenTempControl_prm.h"




//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------

typedef enum
{
	OVEN_INSIDE_RANGE = 0,
	OVEN_HEATING
}OVEN_TEMP_CONTROL_STATE_TYPE;


typedef enum
{
	TEMP_LEVEL_MIN = 0,
	TEMP_LEVEL_MED,
	TEMP_LEVEL_MAX,
	TEMP_LEVEL_OVEN_OFF,
	NUM_OF_TEMP_LEVELS
}OVEN_TEMP_CONTROL_LEVELS_TYPE;

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================

void OvenTempControl__Initialize(void);
void OvenTempControl__Handler(void);
void OvenTempControl__SetLevel(OVEN_TEMP_CONTROL_LEVELS_TYPE level);
OVEN_TEMP_CONTROL_STATE_TYPE OvenTempControl__GetState(void);   //não usado

#endif /* OVENTEMPCONTROL_H_ */

