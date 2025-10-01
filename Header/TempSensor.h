/*
 * TempSensor.h
 *
 *  Created on: 03/10/2017
 *      Author: MAASDN
 */

#ifndef TEMPSENSOR_H_
#define TEMPSENSOR_H_

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "..\Header\TempSensor_prm.h"

//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------

typedef enum
{
	TEMP_SENSOR_1 = 0,
	TEMP_SENSOR_2,
	NUM_OF_TEMP_SENSOR
}TEMP_SENSOR_TYPE;

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
void TempSensor__Initialize(void);
unsigned short int TempSensor__GetCelsius(TEMP_SENSOR_TYPE sensor_id);
void TempSensor__ConversionHandler(void);

#endif /* TEMPSENSOR_H_ */
