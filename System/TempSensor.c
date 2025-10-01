/*
 * TempSensor.c
 *
 *  Created on: 03/10/2017
 *      Author: MAASDN
 */

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "..\Header\C_Types.h"
#include "..\Header\TempSensor.h"
#include "..\Header\Hal.h"
//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------

unsigned short int Temperature[NUM_OF_TEMP_SENSOR];

const unsigned char TempSensorTable[NUM_OF_TEMP_SENSOR] = TEMP_SENSOR_CONFIG;
const unsigned char TempSensor_Enable_Table[NUM_OF_TEMP_SENSOR]= {USE_TEMP_SENSOR_1, USE_TEMP_SENSOR_2};
//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------


//-------------------------------------- Global Variables ----------------------------------------------------------------


//-------------------------------------- PRIVATE (Function Prototypes) ---------------------------------------------------



//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================

void TempSensor__Initialize(void)
{
	TEMP_SENSOR_TYPE sensor_id;

	for (sensor_id = 0; sensor_id < NUM_OF_TEMP_SENSOR; sensor_id++) 
	{
		Temperature[sensor_id] = 0;

	}
}
//
//  Esta função faz a conversão dos valores lidos nos sensores escolhidos
//  e são armazenados em Temperature[].
 
//---------------------------------------------------------------------------------------------------------------------
void TempSensor__ConversionHandler(void)
{
	unsigned short int ad_value;  // usar essa variável para fazer os cálculos!
	TEMP_SENSOR_TYPE sensor_id;   // identificador do sensor
	
	for (sensor_id = 0; sensor_id < NUM_OF_TEMP_SENSOR; sensor_id++) 
	{
		if(TempSensor_Enable_Table[sensor_id] == ENABLED)
		{
			ad_value = Hal_GetAnalogInput(TempSensorTable[sensor_id]);
			Temperature[sensor_id] = (float) (ad_value+400)/4 +50.0f;
		}
		
	}
	
}
//---------------------------------------------------------------------------------------------------------------------
unsigned short int TempSensor__GetCelsius(TEMP_SENSOR_TYPE sensor_id)
{
	if (sensor_id < NUM_OF_TEMP_SENSOR)
	{
		return Temperature[sensor_id];
	}
	else
	{
		return 0;
	}
	
}
//---------------------------------------------------------------------------------------------------------------------
